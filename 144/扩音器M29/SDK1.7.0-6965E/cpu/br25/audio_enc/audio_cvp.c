/*
*********************************************************************
*                  		Audio CVP APIs

* Description:CVP用户调用接口
* Note(s)    :ANS等级和AEC滤波器长度可根据实际需要进行配置
*			  (1)CONST_ANS_MODE:ANS降噪等级配置
*			  (2)AEC_TAIL_LENGTH:AEC滤波器长度配置
*********************************************************************
*/
#include "system/includes.h"
#include "app_config.h"
#include "audio_config.h"
#include "aec_user.h"
#include "media/includes.h"
#include "circular_buf.h"
#include "clock_cfg.h"
#include "audio_eff_default_parm.h"

#define LOG_TAG_CONST       AEC_USER
#define LOG_TAG             "[AEC_USER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

#define CVP_USER_MALLOC_ENABLE	1

/*CVP_TOGGLE:CVP模块使能开关，Disable则数据完全不经过处理，CVP模块不占用资源*/
#define CVP_TOGGLE			1

#if (TCFG_EQ_ENABLE == 1)
#include "media/audio_eq.h"
#define CVP_DCCS_EN			1 /*mic去直流滤波eq*/
#define CVP_UL_EQ_EN		1 /*mic 普通eq*/
#else
#define CVP_DCCS_EN			0
#define CVP_UL_EQ_EN		0
#endif/*TCFG_EQ_ENABLE*/

/*使能即可跟踪通话过程的内存情况*/
#define CVP_MEM_TRACE_ENABLE	0

/*
 *ANS等级:0~2,
 *等级1比等级0多6k左右的ram
 *等级2比等级1多3k左右的ram
 */
static const u8 CONST_ANS_MODE = 1;

/*
 *AEC复杂等级，等级越高，ram和mips越大，适应性越好
 *回音路径不定/回音失真等情况才需要比较高的等级
 *音箱建议使用等级:4
 *耳机建议使用等级:2
 */
#define AEC_TAIL_LENGTH			4 /*range:2~10,default:4*/


/*单工连续清0的帧数*/
#define AEC_SIMPLEX_TAIL 	15
/*
 *远端数据大于CONST_AEC_SIMPLEX_THR,即清零近端数据
 *越小，回音限制得越好，同时也就越容易卡
 */
#define AEC_SIMPLEX_THR		100000	/*default:260000*/

/*aec mode select:AEC_MODE_REDUCE or AEC_MODE_ADVANCE */
#define AEC_MODULE_BIT		AEC_MODE_ADVANCE

//////////////////////////= EDN =//////////////////////////////////////

/*数据输出开头丢掉的数据包数*/
#define CVP_OUT_DUMP_PACKET		10

/**数据输出开头丢掉的数据包数*/
#define CVP_IN_DUMP_PACKET		1

extern struct adc_platform_data adc_data;

static void cvp_param_dump(struct aec_s_attr *param)
{
    log_info("===========dump aec param==================\n");
    log_info("toggle:%d\n", param->toggle);
    log_info("EnableBit:%x\n", param->EnableBit);
    log_info("ul_eq_en:%x\n", param->ul_eq_en);
    log_info("agc_en:%x\n", param->agc_en);
    //log_info("AGC_fade:%d\n", (int)(param->AGC_gain_step * 100));
    log_info("AGC_NDT_max_gain:%d\n", (int)(param->AGC_NDT_max_gain * 100));
    log_info("AGC_NDT_min_gain:%d\n", (int)(param->AGC_NDT_min_gain * 100));
    log_info("AGC_NDT_speech_thr:%d\n", (int)(param->AGC_NDT_speech_thr * 100));
    log_info("AGC_DT_max_gain:%d\n", (int)(param->AGC_DT_max_gain * 100));
    log_info("AGC_DT_min_gain:%d\n", (int)(param->AGC_DT_min_gain * 100));
    log_info("AGC_DT_speech_thr:%d\n", (int)(param->AGC_DT_speech_thr * 100));
    log_info("AGC_echo_present_thr:%d\n", (int)(param->AGC_echo_present_thr * 100));
    log_info("AEC_DT_AggressiveFactor:%d\n", (int)(param->AEC_DT_AggressiveFactor * 100));
    log_info("AEC_RefEngThr:%d\n", (int)(param->AEC_RefEngThr * 100));
    log_info("ES_AggressFactor:%d\n", (int)(param->ES_AggressFactor * 100));
    log_info("ES_MinSuppress:%d\n", (int)(param->ES_MinSuppress * 100));
    log_info("ANS_AggressFactor:%d\n", (int)(param->ANS_AggressFactor * 100));
    log_info("ANS_MinSuppress:%d\n", (int)(param->ANS_MinSuppress * 100));
    log_info("=================END=======================\n");
}

struct audio_cvp_hdl {
    u8 start;					//cvp模块状态
    u8 inbuf_clear_cnt;			//cvp输入数据丢掉
    u8 output_fade_in;			//cvp输出淡入使能
    u8 output_fade_in_gain;		//cvp输出淡入增益
#if CVP_UL_EQ_EN
    struct audio_eq *ul_eq;		//上行数据eq处理
#endif/*CVP_UL_EQ_EN*/
#if CVP_DCCS_EN
    struct audio_eq *dccs_eq;	//省电容mic去直流滤波
#endif/*CVP_DCCS_EN*/
    u16 dump_packet;			//前面如果有杂音，丢掉几包
    u8 output_buf[1000];		//cvp数据输出缓存
    cbuffer_t output_cbuf;
    struct aec_s_attr attr;		//cvp模块参数属性
};
#if CVP_USER_MALLOC_ENABLE
struct audio_cvp_hdl *cvp_hdl = NULL;
#else
struct audio_cvp_hdl cvp_handle;
#endif/*CVP_USER_MALLOC_ENABLE*/

void audio_cvp_ref_start(u8 en)
{
    if (cvp_hdl) {
        if (en != cvp_hdl->attr.fm_tx_start) {
            cvp_hdl->attr.fm_tx_start = en;
            y_printf("fm_tx_start:%d\n", en);
        }
    }
}

#if CVP_DCCS_EN
static const int DCCS_8k_Coeff[5] = {
    (943718 << 2),	-(856687 << 2),	(1048576 << 2),	(1887437 << 2),	-(2097152 << 2)
};
static const int DCCS_16k_Coeff[5] = {
    (1006633 << 2),	-(967542 << 2),	(1048576 << 2),	(2013266 << 2),	-(2097152 << 2)
};
static int cvp_dccs_eq_filter(void *eq, int sr, struct audio_eq_filter_info *info)
{
    //r_printf("dccs_eq sr:%d\n", sr);
    if (sr == 16000) {
        info->L_coeff = (void *)DCCS_16k_Coeff;
        info->R_coeff = (void *)DCCS_16k_Coeff;
    } else {
        info->L_coeff = (void *)DCCS_8k_Coeff;
        info->R_coeff = (void *)DCCS_8k_Coeff;
    }
    info->L_gain = 0;
    info->R_gain = 0;
    info->nsection = 1;
    return 0;
}

static int dccs_eq_output(void *priv, void *data, u32 len)
{
    return 0;
}
#endif/*CVP_DCCS_EN*/

#if CVP_UL_EQ_EN

static int ul_eq_output(void *priv, void *data, u32 len)
{
    return 0;
}
#endif/*CVP_UL_EQ_EN*/

/*
*********************************************************************
*                  Audio CVP Process_Probe
* Description: CVP模块数据前处理回调
* Arguments  : data 数据地址
*			   len	数据长度
* Return	 : 0 成功 其他 失败
* Note(s)    : 在源数据经过AEC模块前，可以增加自定义处理
*********************************************************************
*/
static int audio_cvp_probe(s16 *data, u16 len)
{
#if CVP_DCCS_EN
    if (cvp_hdl->dccs_eq) {
        audio_eq_run(cvp_hdl->dccs_eq, data, len);
    }
#endif/*CVP_DCCS_EN*/
    return 0;
}

/*
*********************************************************************
*                  Audio CVP Process_Post
* Description: CVP模块数据后处理回调
* Arguments  : data 数据地址
*			   len	数据长度
* Return	 : 0 成功 其他 失败
* Note(s)    : 在数据处理完毕，可以增加自定义后处理
*********************************************************************
*/
static int audio_cvp_post(s16 *data, u16 len)
{
#if CVP_UL_EQ_EN
    if (cvp_hdl->ul_eq) {
        audio_eq_run(cvp_hdl->ul_eq, data, len);
    }
#endif/*CVP_UL_EQ_EN*/
    return 0;
}

/*跟踪系统内存使用情况:physics memory size xxxx bytes*/
static void sys_memory_trace(void)
{
    static int cnt = 0;
    if (cnt++ > 200) {
        cnt = 0;
        mem_stats();
    }
}

/*
*********************************************************************
*                  Audio CVP Output Handle
* Description: CVP模块数据输出回调
* Arguments  : data 输出数据地址
*			   len	输出数据长度
* Return	 : 数据输出消耗长度
* Note(s)    : None.
*********************************************************************
*/
extern void esco_enc_resume(void);
static int audio_cvp_output(s16 *data, u16 len)
{
#if CVP_MEM_TRACE_ENABLE
    sys_memory_trace();
#endif/*CVP_MEM_TRACE_ENABLE*/

    if (cvp_hdl->dump_packet) {
        cvp_hdl->dump_packet--;
        memset(data, 0, len);
    } else  {
        if (cvp_hdl->output_fade_in) {
            s32 tmp_data;
            //printf("fade:%d\n",cvp_hdl->output_fade_in_gain);
            for (int i = 0; i < len / 2; i++) {
                tmp_data = data[i];
                data[i] = tmp_data * cvp_hdl->output_fade_in_gain >> 7;
            }
            cvp_hdl->output_fade_in_gain += 12;
            if (cvp_hdl->output_fade_in_gain >= 128) {
                cvp_hdl->output_fade_in = 0;
            }
        }
    }
    u16 wlen = cbuf_write(&cvp_hdl->output_cbuf, data, len);
    //printf("wlen:%d-%d\n",len,cvp_hdl.output_cbuf.data_len);

    /* esco_enc_resume(); */
#if 1
    static u32 aec_output_max = 0;
    if (aec_output_max < cvp_hdl->output_cbuf.data_len) {
        aec_output_max = cvp_hdl->output_cbuf.data_len;
        y_printf("o_max:%d", aec_output_max);
    }
#endif
    if (wlen != len) {
        putchar('F');
    }
    return wlen;
}

/*
*********************************************************************
*                  Audio CVP Output Read
* Description: 读取cvp模块的输出数据
* Arguments  : buf  读取数据存放地址
*			   len	读取数据长度
* Return	 : 数据读取长度
* Note(s)    : None.
*********************************************************************
*/
int audio_cvp_output_read(s16 *buf, u16 len)
{
    //printf("rlen:%d-%d\n",len,cvp_hdl.output_cbuf.data_len);
    local_irq_disable();
    if (!cvp_hdl || !cvp_hdl->start) {
        printf("audio_a2dp_aec close now");
        local_irq_enable();
        return -EINVAL;
    }
    u16 rlen = cbuf_read(&cvp_hdl->output_cbuf, buf, len);
    if (rlen == 0) {
        //putchar('N');
    }
    local_irq_enable();
    return rlen;
}

static const char *CVP_ModuleName[] = {
    "AEC", "NLP", "ANS", "ENC", "AGC"
};
static const char *CVP_ModuleStatus[] = {
    "Disable", "Enable"
};
static void dumpModulaStatus(int EnableBit)
{
    printf("EnableBitDebug = 0x%x\n", EnableBit);
    for (int i = 0; i < 5; i++) {
        int k = 1 << i;
        printf("%s : %s\n", CVP_ModuleName[i], CVP_ModuleStatus[((EnableBit & k) != 0)]);
    }
}

/*
*********************************************************************
*                  Audio CVP Open
* Description: 初始化CVP模块
* Arguments  : sr 			    采样率(8000/16000)
*			   enablebit	    使能模块(AEC/NLP/AGC/ANS...)
*			   out_hdl		    自定义回调函数，NULL则用默认的回调
*			   param_hdl        自定义参数回调函数，NULL则用默认的参数
* Return	 : 0 成功 其他 失败
* Note(s)    : null
*********************************************************************
*/
int audio_cvp_open(u16 sample_rate, s16 enablebit, int (*out_hdl)(s16 *data, u16 len), void (*param_hdl)(struct aec_s_attr *p))
{
    struct aec_s_attr *cvp_param;

    printf("audio_aec_open\n");
    mem_stats();
#if CVP_USER_MALLOC_ENABLE
    cvp_hdl = zalloc(sizeof(struct audio_cvp_hdl));
    if (cvp_hdl == NULL) {
        log_error("cvp_hdl malloc failed");
        return -ENOMEM;
    }
#else
    cvp_hdl = &cvp_handle;
#endif/*CVP_USER_MALLOC_ENABLE*/
    cbuf_init(&cvp_hdl->output_cbuf, cvp_hdl->output_buf, sizeof(cvp_hdl->output_buf));
    cvp_hdl->start = 1;
    cvp_hdl->dump_packet = CVP_OUT_DUMP_PACKET;
    cvp_hdl->inbuf_clear_cnt = CVP_IN_DUMP_PACKET;
    cvp_hdl->output_fade_in = 1;
    cvp_hdl->output_fade_in_gain = 0;
    cvp_param = &cvp_hdl->attr;

    cvp_param->output_way = 0;

    cvp_param->toggle = 1;
    cvp_param->EnableBit = AEC_MODULE_BIT;

    cvp_param->agc_en = 0;

    cvp_param->wideband = 0;
    cvp_param->ul_eq_en = 1;
    cvp_param->packet_dump = 50;/*0~255(u8)*/

    /*AGC*/
    cvp_param->AGC_NDT_fade_in_step = 1.3f;
    cvp_param->AGC_NDT_fade_out_step = 0.9f;
    cvp_param->AGC_DT_fade_in_step = 1.3f;
    cvp_param->AGC_DT_fade_out_step = 0.9f;
    cvp_param->AGC_NDT_max_gain = 12.f;
    cvp_param->AGC_NDT_min_gain = 0.f;
    cvp_param->AGC_NDT_speech_thr = -50.f;
    cvp_param->AGC_DT_max_gain = 12.f;
    cvp_param->AGC_DT_min_gain = 0.f;
    cvp_param->AGC_DT_speech_thr = -40.f;
    cvp_param->AGC_echo_look_ahead = 0;
    cvp_param->AGC_echo_present_thr = -70.f;
    cvp_param->AGC_echo_hold = 400;

    /*AEC*/
    cvp_param->AEC_DT_AggressiveFactor = 1.f;	/*范围：1~5，越大追踪越好，但会不稳定,如破音*/
    cvp_param->AEC_RefEngThr = -70.f; /*范围：-90 ~ -60 dB*/

    /*ES*/
    cvp_param->ES_AggressFactor = -3.0f;	/*范围：-1 ~ -5*/
    cvp_param->ES_MinSuppress = 4.f;		/*范围：0 ~ 10*/
    cvp_param->ES_Unconverge_OverDrive = cvp_param->ES_MinSuppress;

    /*ANS*/
    cvp_param->ANS_mode = CONST_ANS_MODE;
    cvp_param->ANS_AggressFactor = 1.25f;	/*范围：1~2,动态调整,越大越强(1.25f)*/
    cvp_param->ANS_MinSuppress = 0.04f;	/*范围：0~1,静态定死最小调整,越小越强(0.09f)*/
    cvp_param->ANS_NoiseLevel = 2.2e4f;

    cvp_param->wn_en = 0;
    cvp_param->aec_tail_length = AEC_TAIL_LENGTH;
    cvp_param->wn_gain = 331;
    cvp_param->SimplexTail = AEC_SIMPLEX_TAIL;
    cvp_param->SimplexThr = AEC_SIMPLEX_THR;
    cvp_param->dly_est = 0;
    cvp_param->dst_delay = 50;
    cvp_param->aec_probe = audio_cvp_probe;
    cvp_param->aec_post = audio_cvp_post;
    cvp_param->output_handle = audio_cvp_output;
    cvp_param->output_handle = out_hdl;
    cvp_param->ref_sr  = audio_output_nor_rate();
    if (cvp_param->ref_sr == 0) {
        cvp_param->ref_sr = sample_rate;
    }

    if (enablebit >= 0) {
        cvp_param->EnableBit = enablebit;
    }
    if (out_hdl) {
        cvp_param->output_handle = out_hdl;
    }
    if (param_hdl) {
        param_hdl(cvp_param);
    }

    if (sample_rate == 16000) {
        cvp_param->wideband = 1;
        cvp_param->hw_delay_offset = 50;
        if (cvp_param->EnableBit == AEC_MODE_ADVANCE) {
            clock_add(AEC16K_ADV_CLK);
        } else {
            clock_add(AEC16K_CLK);
        }
    } else {
        cvp_param->wideband = 0;
        cvp_param->hw_delay_offset = 75;
        if (cvp_param->EnableBit == AEC_MODE_ADVANCE) {
            clock_add(AEC8K_ADV_CLK);
        } else {
            clock_add(AEC8K_CLK);
        }
    }


#if CVP_UL_EQ_EN
    if (cvp_param->ul_eq_en) {
        u8 mode = 2;
        if (sample_rate == 8000) {
            mode = 3;
        }
        struct audio_eq_param ul_eq_param = {0};
        ul_eq_param.sr = sample_rate;
        ul_eq_param.channels = 1;
        ul_eq_param.max_nsection = phone_mode[mode].eq_parm.seg_num;
        ul_eq_param.nsection = phone_mode[mode].eq_parm.seg_num;
        ul_eq_param.seg = phone_mode[mode].eq_parm.seg;
        ul_eq_param.global_gain = phone_mode[mode].eq_parm.global_gain;
        ul_eq_param.cb = eq_get_filter_info;
        ul_eq_param.eq_name = AEID_ESCO_UL_EQ;
        cvp_hdl->ul_eq = audio_dec_eq_open(&ul_eq_param);
    }
#endif/*CVP_UL_EQ_EN*/

#if CVP_DCCS_EN
    if (adc_data.mic_capless) {
        struct audio_eq_param dccs_eq_param = {0};
        dccs_eq_param.sr = sample_rate;
        dccs_eq_param.channels = 1;
        dccs_eq_param.max_nsection = 1;
        dccs_eq_param.cb = cvp_dccs_eq_filter;
        cvp_hdl->dccs_eq = audio_dec_eq_open(&dccs_eq_param);
    }
#endif/*CVP_DCCS_EN*/

    //cvp_param_dump(cvp_param);

#if CVP_TOGGLE
    aec_open(cvp_param);
#endif
    mem_stats();
    printf("audio_a2dp_aec_open succ\n");
    return 0;
}


/*
*********************************************************************
*                  Audio CVP Close
* Description: 关闭CVP模块
* Arguments  : None.
* Return	 : None.
* Note(s)    : None.
*********************************************************************
*/
void audio_cvp_close(void)
{
    printf("audio_a2dp_aec_close\n");
    struct aec_s_attr *cvp_param;
    if (cvp_hdl) {
        cvp_hdl->start = 0;

        cvp_param = &cvp_hdl->attr;
        if (cvp_param->wideband) {
            if (cvp_param->EnableBit == AEC_MODE_ADVANCE) {
                clock_remove(AEC16K_ADV_CLK);
            } else {
                clock_remove(AEC16K_CLK);
            }
        } else {
            if (cvp_param->EnableBit == AEC_MODE_ADVANCE) {
                clock_remove(AEC8K_ADV_CLK);
            } else {
                clock_remove(AEC8K_CLK);
            }
        }

#if CVP_TOGGLE
        aec_close();
#endif/*CVP_TOGGLE*/
#if CVP_DCCS_EN
        if (cvp_hdl->dccs_eq) {
            audio_dec_eq_close(cvp_hdl->dccs_eq);
        }
#endif/*CVP_DCCS_EN*/
#if CVP_UL_EQ_EN
        if (cvp_hdl->ul_eq) {
            audio_dec_eq_close(cvp_hdl->ul_eq);
        }
#endif/*CVP_UL_EQ_EN*/
        local_irq_disable();
#if CVP_USER_MALLOC_ENABLE
        free(cvp_hdl);
#endif/*CVP_USER_MALLOC_ENABLE*/
        cvp_hdl = NULL;
        local_irq_enable();
    }
    printf("audio_a2dp_aec_close ok\n");
}

/*
*********************************************************************
*                  Audio CVP Input
* Description: CVP源数据输入
* Arguments  : buf	输入源数据地址
*			   len	输入源数据长度
* Return	 : None.
* Note(s)    : 输入一帧数据，唤醒一次运行任务处理数据，默认帧长256点
*********************************************************************
*/
void audio_cvp_inbuf(s16 *buf, u16 len)
{
    if (cvp_hdl && cvp_hdl->start) {
#if CVP_TOGGLE
        if (cvp_hdl->inbuf_clear_cnt) {
            cvp_hdl->inbuf_clear_cnt--;
            memset(buf, 0, len);
        }
        int ret = aec_in_data(buf, len);
        if (ret == -1) {
#if (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_DAC)
            /* log_info("fill dac data\n");
            u8 tmp_buf[64] = {0};
            for (u8 i = 0; i < 512 / sizeof(tmp_buf); i++) {
                app_audio_output_write(tmp_buf, sizeof(tmp_buf));
            } */
#endif
        } else if (ret == -2) {
            log_error("a2dp aec inbuf full\n");
        }
#else
        cvp_hdl->attr.output_handle(buf, len);
#endif/*CVP_TOGGLE*/
    }
}

/*
*********************************************************************
*                  Audio CVP Reference
* Description: CVP模块参考数据输入
* Arguments  : buf	输入参考数据地址
*			   len	输入参考数据长度
* Return	 : None.
* Note(s)    : 声卡设备是DAC，默认不用外部提供参考数据
*********************************************************************
*/
void audio_cvp_refbuf(s16 *buf, u16 len)
{
    if (cvp_hdl && cvp_hdl->start) {
#if CVP_TOGGLE
        aec_ref_data(buf, len);
#endif/*CVP_TOGGLE*/
    }
}

/* void aec_estimate_dump(int DlyEst)
{
	printf("DlyEst:%d\n",DlyEst);
} */



