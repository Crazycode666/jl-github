/*
 ****************************************************************
 *							AUDIO_CVP_DEMO
 * File  : audio_cvp_demo.c
 * By    :
 * Notes :清晰语音测试使用，请不要修改本demo，如有需求，请拷贝副
 *		  本，自行修改!
 * Usage :
 *(1)测试单mic降噪
 *(2)支持监听：监听原始数据/处理后的数据(MONITOR)
 *	MIC ---------> CVP ---------->SPK
 *			|				|
 *	   monitor probe	monitor post
 *(3)调用audio_cvp_test()即可测试cvp模块
 ****************************************************************
 */
#include "asm/includes.h"
#include "media/includes.h"
#include "system/includes.h"
#include "audio_config.h"
#include "aec_user.h"
#include "clock_cfg.h"

#define CVP_LOG_ENABLE
#ifdef CVP_LOG_ENABLE
#define CVP_LOG(x, ...)  g_printf("[cvp_demo]" x " ", ## __VA_ARGS__)
#else
#define CVP_LOG(...)
#endif/*CVP_LOG_ENABLE*/

extern struct audio_dac_hdl dac_hdl;
extern struct audio_adc_hdl adc_hdl;

#define MIC_CH_NUM			1
#define MIC_BUF_NUM        	2
#define MIC_IRQ_POINTS     	256
#define MIC_BUFS_SIZE      	(MIC_BUF_NUM * MIC_IRQ_POINTS * MIC_CH_NUM)

#define CVP_MONITOR_DIS		0		//监听关闭
#define CVP_MONITOR_PROBE	1		//监听处理前数据
#define CVP_MONITOR_POST	2		//监听处理后数据
//默认监听选择
#define CVP_MONITOR_SEL		CVP_MONITOR_POST

typedef struct {
    u8 monitor;
    struct audio_adc_output_hdl adc_output;
    struct adc_mic_ch mic_ch;
    s16 tmp_buf[320 * 2];
    s16 mic_buf[MIC_BUFS_SIZE];
} audio_cvp_t;
audio_cvp_t *cvp_demo = NULL;

extern int audio_cvp_open(u16 sample_rate, s16 enablebit, int (*out_hdl)(s16 *data, u16 len), void (*param_hdl)(struct aec_s_attr *p));
extern void audio_cvp_close(void);
extern void audio_cvp_inbuf(s16 *buf, u16 len);

/*监听输出：默认输出到dac*/
static int cvp_monitor_output(s16 *data, int len)
{
#if (TCFG_AUDIO_DAC_CONNECT_MODE == DAC_OUTPUT_LR)//双声道数据结构
    int i = 0;
    for (i = 0; i < (len / 2); i++) {
        cvp_demo->tmp_buf[i * 2] = data[i];
        cvp_demo->tmp_buf[i * 2 + 1] = data[i];
    }
    int wlen = app_audio_output_write(cvp_demo->tmp_buf, len * 2);
    if (wlen != (len * 2)) {
        CVP_LOG("monitor output full\n");
    }
#else //单声道数据结构
    int wlen = app_audio_output_write(data, len);
    if (wlen != len) {
        CVP_LOG("monitor output full\n");
    }
#endif/*TCFG_AUDIO_DAC_CONNECT_MODE*/
    return wlen;
}

/*监听使能*/
static int cvp_monitor_en(u8 en, int sr)
{
    CVP_LOG("cvp_monitor_en:%d,sr:%d\n", en, sr);
    if (en) {
        app_audio_state_switch(APP_AUDIO_STATE_MUSIC, get_max_sys_vol());
        s8 vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
        CVP_LOG("cur_vol:%d,max_sys_vol:%d\n", vol, get_max_sys_vol());
        audio_dac_set_volume(&dac_hdl, vol, vol);
        app_audio_output_samplerate_set(sr);
        app_audio_output_start();
    } else {
        app_audio_output_stop();
    }
    return 0;
}

/*mic adc原始数据输出*/
static void mic_output(void *priv, s16 *data, int len)
{
    struct audio_adc_hdl *hdl = priv;
    putchar('o');
    if (hdl == NULL) {
        printf("audio_adc_hdl err:NULL!!!!");
        return;
    }

    if (cvp_demo->monitor == CVP_MONITOR_PROBE) {
        cvp_monitor_output(data, len);
    }
    audio_cvp_inbuf(data, len);
}

/*打开mic*/
static void mic_open(int sr, u8 gain)
{
    CVP_LOG("mic_open: %d, %d\n", sr, gain);
    if (cvp_demo) {
        audio_adc_mic_open(&cvp_demo->mic_ch, AUDIO_ADC_MIC_CH, &adc_hdl);
        audio_adc_mic_set_sample_rate(&cvp_demo->mic_ch, sr);
        audio_adc_mic_set_gain(&cvp_demo->mic_ch, gain);
        audio_adc_mic_set_buffs(&cvp_demo->mic_ch, cvp_demo->mic_buf, MIC_IRQ_POINTS * 2, MIC_BUF_NUM);
        cvp_demo->adc_output.handler = mic_output;
        cvp_demo->adc_output.priv = &adc_hdl;
        audio_adc_add_output_handler(&adc_hdl, &cvp_demo->adc_output);
        audio_adc_mic_start(&cvp_demo->mic_ch);
        CVP_LOG("mic_open succ\n");
    }
}
/*关闭mic*/
static void mic_close(void)
{
    if (cvp_demo) {
        audio_adc_mic_close(&cvp_demo->mic_ch);
        audio_adc_del_output_handler(&adc_hdl, &cvp_demo->adc_output);
    }
}

/*清晰语音数据输出*/
static int cvp_output_hdl(s16 *data, u16 len)
{
    /* putchar('.'); */
    if (cvp_demo->monitor == CVP_MONITOR_POST) {
        cvp_monitor_output(data, len);
    }
    return len;
}

/*清晰语音参数*/
static void cvp_param_hdl(struct aec_s_attr *p)
{
    /*AGC*/
    p->agc_en = 0;
    p->AGC_NDT_fade_in_step = 1.3f;
    p->AGC_NDT_fade_out_step = 0.9f;
    p->AGC_DT_fade_in_step = 1.3f;
    p->AGC_DT_fade_out_step = 0.9f;
    p->AGC_NDT_max_gain = 12.f;
    p->AGC_NDT_min_gain = 0.f;
    p->AGC_NDT_speech_thr = -50.f;
    p->AGC_DT_max_gain = 12.f;
    p->AGC_DT_min_gain = 0.f;
    p->AGC_DT_speech_thr = -40.f;
    p->AGC_echo_look_ahead = 0;
    p->AGC_echo_present_thr = -70.f;
    p->AGC_echo_hold = 400;

    /*AEC*/
    p->AEC_DT_AggressiveFactor = 1.f;	/*范围：1~5，越大追踪越好，但会不稳定,如破音*/
    p->AEC_RefEngThr = -70.f; /*范围：-90 ~ -60 dB*/

    /*ES*/
    p->ES_AggressFactor = -2.5f;	/*范围：-1 ~ -5*/
    p->ES_MinSuppress = 0.f;		/*范围：0 ~ 10*/
    p->ES_Unconverge_OverDrive = p->ES_MinSuppress;

    /*ANS*/
    p->ANS_mode = 1;
    p->ANS_AggressFactor = 1.25f;	/*范围：1~2,动态调整,越大越强(1.25f)*/
    p->ANS_MinSuppress = 0.04f;	/*范围：0~1,静态定死最小调整,越小越强(0.09f)*/
    p->ANS_NoiseLevel = 2.2e4f;

    /*EQ*/
    p->ul_eq_en = 0;
}

/*
*********************************************************************
*                  AUDIO CVP DEMO OPEN
* Description: 打开cvp模块
* Arguments  : sr 	    	mic和cvp采样率(8000/16000)
*			   gain			mic增益
*			   enablebit	cvp使能模块(AEC_EN、NLP_EN、ANS_EN)
*			   monitor  	mic数据（通过DAC）监听
* Return	 : None.
* Note(s)    : (1)打开一个mic通道示例：
*				audio_cvp_demo_open(16000, 10, ANS_EN, 2);
*********************************************************************
*/
int audio_cvp_demo_open(int sr, u8 gain, s16 enablebit, u8 monitor)
{
    if (cvp_demo == NULL) {
        cvp_demo = zalloc(sizeof(audio_cvp_t));
        ASSERT(cvp_demo);
        cvp_demo->monitor = monitor;
        if (cvp_demo->monitor) {
            cvp_monitor_en(1, sr);
        }
        mic_open(sr, gain);
        audio_cvp_open(sr, enablebit, cvp_output_hdl, cvp_param_hdl);
        clock_set_cur();
        CVP_LOG("cvp demo open\n");
    } else {
        CVP_LOG("[err] cvp demo alreadly open !!!\n");
    }
    return 0;
}

/*关闭cvp demo*/
int audio_cvp_demo_close(void)
{
    if (cvp_demo) {
        mic_close();
        if (cvp_demo->monitor) {
            cvp_monitor_en(0, 0);
        }
        audio_cvp_close();
        clock_set_cur();
        free(cvp_demo);
        cvp_demo = NULL;
        CVP_LOG("cvp demo close\n");
    }
    return 0;
}

/*清晰语音测试模块*/
int audio_cvp_test(void)
{
    if (cvp_demo == NULL) {
        audio_cvp_demo_open(16000, 10, ANS_EN, CVP_MONITOR_SEL);
    } else {
        audio_cvp_demo_close();
    }
    return 0;
}

/*切换监听源*/
void audio_cvp_monitor_change(void)
{
    if (cvp_demo) {
        cvp_demo->monitor ++;
        if (cvp_demo->monitor > 2) {
            cvp_demo->monitor = 0;
        }
    }
}

static u8 audio_cvp_idle_query()
{
    return (cvp_demo == NULL) ? 1 : 0;
}
REGISTER_LP_TARGET(audio_cvp_lp_target) = {
    .name = "audio_cvp",
    .is_idle = audio_cvp_idle_query,
};
