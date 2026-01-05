#include "audio_dec_eff.h"

extern struct audio_dac_hdl dac_hdl;
extern const int const_surround_en;
void user_sat16(s32 *in, s16 *out, u32 npoint);
void a2dp_surround_set(u8 eff);
int audio_out_eq_get_filter_info(void *eq, int sr, struct audio_eq_filter_info *info);
int audio_out_eq_spec_set_info(struct audio_eq *eq, u8 idx, int freq, float gain);
void *dec_eq_drc_setup_new(void *priv, int (*eq_output_cb)(void *, void *, int), u32 sample_rate, u8 channel, u8 async, u8 drc_en);
void eq_cfg_default_init(EQ_CFG *eq_cfg);
void drc_default_init(EQ_CFG *eq_cfg, u8 mode);
int dec_drc_get_filter_info(void *drc, struct audio_drc_filter_info *info);


/*----------------------------------------------------------------------------*/
/**@brief    环绕音效切换测试例子
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void surround_switch_test(void *p)
{
#if 0
    if (!p) {
        return;
    }
    static u8 cnt_type = 0;
    if (EFFECT_OFF == cnt_type) {
        //中途关开测试
        static u8 en = 0;
        en = !en;
        audio_surround_parm_update(p, cnt_type, (surround_update_parm *)en);
    } else {
        //音效切换测试
        audio_surround_parm_update(p, cnt_type, NULL);
    }
    printf("cnt_type 0x%x\n", cnt_type);
    if (++cnt_type > EFFECT_OFF) {
        cnt_type = EFFECT_3D_PANORAMA;
    }
#endif
}

void *audio_surround_setup(u8 channel, u8 eff)
{
#if AUDIO_SURROUND_CONFIG
    struct dec_sur *sur = zalloc(sizeof(struct dec_sur));
    u8 nch = EFFECT_CH_L;
    if (channel == AUDIO_CH_L) {
        nch = EFFECT_CH_L;
    } else if (channel == AUDIO_CH_R) {
        nch = EFFECT_CH_R;
    } else if (channel == AUDIO_CH_LR) {
        nch = 2;
    } else if (channel == AUDIO_CH_DUAL_L) {
        nch = EFFECT_CH2_L;
    } else if (channel == AUDIO_CH_DUAL_R) {
        nch = EFFECT_CH2_R;
    } else {
        if (sur) {
            free(sur);
        }
        log_e("surround ch_type err %d\n", channel);
        return NULL;
    }
    surround_open_parm parm = {0};
    parm.channel = nch;
    parm.surround_effect_type = EFFECT_3D_PANORAMA;//打开时默认使用3d全景音,使用者，根据需求修改
    sur->surround = audio_surround_open(&parm);
    sur->surround_eff = eff;
    audio_surround_voice(sur, sur->surround_eff);//还原按键触发的音效
    //sur_test = sys_timer_add(sur->surround, surround_switch_test, 10000);
    return sur;
#else
    return NULL;
#endif//AUDIO_SURROUND_CONFIG

}

void audio_surround_free(void *sur)
{
#if AUDIO_SURROUND_CONFIG
    struct dec_sur *surh = (struct dec_sur *)sur;
    if (!surh) {
        return;
    }

    if (surh->surround) {
        audio_surround_close(surh->surround);
        surh->surround = NULL;
    }
    free(surh);
#endif//AUDIO_SURROUND_CONFIG

}

void audio_surround_set_ch(void *sur, u8 channel)
{
#if AUDIO_SURROUND_CONFIG
    struct dec_sur *surh = (struct dec_sur *)sur;
    if (!surh) {
        return;
    }

    u8 nch = EFFECT_CH_L;
    if (channel == AUDIO_CH_L) {
        nch = EFFECT_CH_L;
    } else if (channel == AUDIO_CH_R) {
        nch = EFFECT_CH_R;
    } else if (channel == AUDIO_CH_LR) {
        nch = 2;
    } else if (channel == AUDIO_CH_DUAL_L) {
        nch = EFFECT_CH2_L;
    } else if (channel == AUDIO_CH_DUAL_R) {
        nch = EFFECT_CH2_R;
    } else {
        log_e("surround ch_type err %d\n", channel);
        return ;
    }

    if (surh->surround) {
        audio_surround_switch_nch(surh->surround, nch);
    }
#endif//AUDIO_SURROUND_CONFIG

}

/*
 *环绕音效开关控制
 * */
void audio_surround_voice(void *sur, u8 en)
{
#if AUDIO_SURROUND_CONFIG
    struct dec_sur *surh = (struct dec_sur *)sur;
    surround_hdl *surround = (surround_hdl *)surh->surround;
    if (surround) {
        if (en) {
            if (const_surround_en & BIT(2)) {
                surround_update_parm parm = {0};
                parm.surround_type = EFFECT_3D_LRDRIFT2;//音效类型
                parm.rotatestep    = 4;   //建议1~6,环绕速度
                parm.damping = 40;//混响音量（0~70）,空间感
                parm.feedback = 100;//干声音量(0~100),清晰度
                parm.roomsize = 128;//无效参数
                audio_surround_parm_update(surround, EFFECT_SUR2, &parm);
            } else {
                audio_surround_parm_update(surround, EFFECT_3D_ROTATES, NULL);
            }
        } else {
            surround_update_parm parm = {0};
            audio_surround_parm_update(surround, EFFECT_OFF2, &parm);//关音效
        }
    }
#endif /* AUDIO_SURROUND_CONFIG */
}




#if AUDIO_VBASS_CONFIG
/*----------------------------------------------------------------------------*/
/**@brief    虚拟低音参数更新例子
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/

void vbass_udate_parm_test(void *p)
{
    if (!p) {
        return;
    }
    vbass_hdl *vbass = p;
    //
#if 0
    //虚拟低音增益调节例子
    static  u32 test_level  = 4096;
    if (vbass) {
        vbass_update_parm def_parm = {0};
        def_parm.bass_f = 300;
        test_level += 100;
        if (test_level > 16384) {
            test_level = 4096;
        }
        def_parm.level = test_level;
        audio_vbass_parm_update(vbass, VBASS_UPDATE_PARM, &def_parm);
    }
#endif

#if 0
    //开关虚拟低音例子
    static u8 en = 0;// 0关  1开
    en = !en;
    audio_vbass_parm_update(vbass, VBASS_SW, (void *)en);
#endif
}

vbass_hdl *audio_vbass_setup(u32 sample_rate, u8 channel)
{
    vbass_hdl *vbass = NULL;
    vbass_open_parm vparm = {0};
    vparm.sr = sample_rate;
    vparm.channel = channel;
    vbass = audio_vbass_open(&vparm);
    if (vbass) {
        vbass_update_parm def_parm = {0};
        def_parm.bass_f = 200;//外放的低音截止频率
        def_parm.level = 4096;//增强强度(4096 等于 1db， 建议范围：4096 到 16384);
        audio_vbass_parm_update(vbass, VBASS_UPDATE_PARM, &def_parm);

        /* sys_timer_add(vbass, vbass_udate_parm_test, 2000); */
    }
    return vbass;
}

void audio_vbass_free(vbass_hdl *vbass)
{
    if (vbass) {
        audio_vbass_close(vbass);
    }
}
#endif//AUDIO_VBASS_CONFIG



void eq_32bit_out(struct dec_eq_drc *eff)
{
    if (!config_eq_lite_en) {
        int wlen = 0;
        if (eff->priv && eff->out_cb) {
            wlen = eff->out_cb(eff->priv, &eff->eq_out_buf[eff->eq_out_points], (eff->eq_out_total - eff->eq_out_points) * 2);
        }
        eff->eq_out_points += wlen / 2;
    }
}

static int eq_output(void *priv, void *buf, u32 len)
{
    if (!config_eq_lite_en) {
        int wlen = 0;
        int rlen = len;
        s16 *data = (s16 *)buf;
        struct dec_eq_drc *eff = priv;
        if (!eff->async) {
            return rlen;
        }

        if (eff->drc && eff->async) {
            if (eff->eq_out_buf && (eff->eq_out_points < eff->eq_out_total)) {
                eq_32bit_out(eff);
                if (eff->eq_out_points < eff->eq_out_total) {
                    return 0;
                }
            }

            audio_drc_run(eff->drc, data, len);

            if ((!eff->eq_out_buf) || (eff->eq_out_buf_len < len / 2)) {
                if (eff->eq_out_buf) {
                    free(eff->eq_out_buf);
                }
                eff->eq_out_buf_len = len / 2;
                eff->eq_out_buf = malloc(eff->eq_out_buf_len);
                ASSERT(eff->eq_out_buf);
            }
            user_sat16((s32 *)data, (s16 *)eff->eq_out_buf, len / 4);
            eff->eq_out_points = 0;
            eff->eq_out_total = len / 4;

            eq_32bit_out(eff);
            return len;
        }

        int out_len = 0;
        if (eff->priv && eff->out_cb) {
            out_len = eff->out_cb(eff->priv, data, len);
        }
        return out_len;
    } else {
        return len;
    }
}



int wdrc_get_filter_info(void *drc, struct audio_drc_filter_info *info)
{
    static struct drc_ch wdrc_p = {0};
    struct threshold_group threshold[5] = {{-100 + 90.3f, -91.9f + 90.3f}, {-87 + 90.3f, -72.5f + 90.3f}, {-58.6f + 90.3f, -60.3f + 90.3f}, {-43.5f + 90.3f, -29.7f + 90.3f}, {0 + 90.3f, -10.9f + 90.3f}};
    /* struct threshold_group threshold[3] = {{0x42166666, 0x0}, {0x42580000, 0x42a40000},{0x42f00000, 0x42c50000}}; */

    wdrc_p.nband = 1;
    wdrc_p.type = 3;//wdrc

    //left
    int i = 0;
    wdrc_p._p.wdrc[i][0].attacktime = 1;
    wdrc_p._p.wdrc[i][0].releasetime = 500;
    memcpy(wdrc_p._p.wdrc[i][0].threshold, threshold, sizeof(threshold));
    wdrc_p._p.wdrc[i][0].threshold_num = ARRAY_SIZE(threshold);
    wdrc_p._p.wdrc[i][0].rms_time = 25;
    wdrc_p._p.wdrc[i][0].algorithm = 0;
    wdrc_p._p.wdrc[i][0].mode = 1;
    //right
    wdrc_p._p.wdrc[i][1].attacktime = 1;
    wdrc_p._p.wdrc[i][1].releasetime = 500;
    memcpy(wdrc_p._p.wdrc[i][1].threshold, threshold, sizeof(threshold));
    wdrc_p._p.wdrc[i][1].threshold_num = ARRAY_SIZE(threshold);
    wdrc_p._p.wdrc[i][1].rms_time = 25;
    wdrc_p._p.wdrc[i][1].algorithm = wdrc_p._p.wdrc[i][0].algorithm;
    wdrc_p._p.wdrc[i][1].mode = wdrc_p._p.wdrc[i][0].mode;

    info->R_pch = info->pch = &wdrc_p;
    return 0;
}
void *dec_eq_drc_setup(void *priv, int (*eq_output_cb)(void *, void *, int), u32 sample_rate, u8 channel, u8 async, u8 drc_en)
{
#if TCFG_EQ_ENABLE
    if (config_eq_lite_en) { //仅支持同步方式eq处理
        async = 0;//
    }
    u8 game_eff = 0;
#if defined(AUDIO_GAME_EFFECT_CONFIG) && AUDIO_GAME_EFFECT_CONFIG
    if (drc_en & BIT(1)) { //game eff drc
#if defined(EQ_CORE_V1)
        return dec_eq_drc_setup_new(priv, eq_output_cb, sample_rate, channel, async, drc_en);
#endif
        game_eff = 1;
    }
#endif/* AUDIO_GAME_EFFECT_CONFIG */

    struct dec_eq_drc *eff = zalloc(sizeof(struct dec_eq_drc));
    struct audio_eq_param eq_param = {0};

#if defined(AUDIO_GAME_EFFECT_CONFIG) && AUDIO_GAME_EFFECT_CONFIG
    if (game_eff) {
        eq_file_get_cfg(get_eq_cfg_hdl(), (u8 *)SDFILE_RES_ROOT_PATH"eq_game_eff.bin");//加载游戏音效
        eff->drc_bef_eq = NOR_GAME_EFF;
        async = 0;
        struct audio_drc_param drc_param = {0};
        drc_param.sr = sample_rate;
        drc_param.channels = channel;
        drc_param.online_en = 1;
        drc_param.remain_en = 1;
        drc_param.out_32bit = 0;
        drc_param.cb = drc_get_filter_info;
        drc_param.drc_name = song_eq_mode;
        eff->drc_prev = audio_dec_drc_open(&drc_param);
    }
#endif/* AUDIO_GAME_EFFECT_CONFIG */


    eff->priv = priv;
    eff->out_cb = eq_output_cb;

    eq_param.channels = channel;
    eq_param.online_en = 1;
    eq_param.mode_en = 1;
    eq_param.remain_en = 1;
    eq_param.no_wait = async;
    if (drc_en) {
        eq_param.out_32bit = 1;
    }
    eq_param.max_nsection = EQ_SECTION_MAX;
    eq_param.cb = eq_get_filter_info;
    eq_param.eq_name = song_eq_mode;
    eq_param.sr = sample_rate;
    eq_param.priv = eff;
    eq_param.output = eq_output;
    eff->eq = audio_dec_eq_open(&eq_param);
    eff->async = async;
#if TCFG_DRC_ENABLE
    if (drc_en) {
        struct audio_drc_param drc_param = {0};
        drc_param.sr = sample_rate;
        drc_param.channels = channel;
        if (eff->drc_bef_eq == NOR_GAME_EFF) {
            drc_param.online_en = 0;
            drc_param.remain_en = 0;
            drc_param.out_32bit = 1;
            drc_param.cb = dec_drc_get_filter_info;
        } else {
            drc_param.online_en = 1;
            drc_param.remain_en = 1;
            drc_param.out_32bit = 1;
        }
        drc_param.cb = drc_get_filter_info;
        drc_param.drc_name = song_eq_mode;
        eff->drc = audio_dec_drc_open(&drc_param);
    }
#endif//TCFG_DRC_ENABLE

    return eff;
#else
    return NULL;
#endif//TCFG_EQ_ENABLE

}

void dec_eq_drc_free(void *eff)
{
#if TCFG_EQ_ENABLE
    struct dec_eq_drc *eff_hdl = (struct dec_eq_drc *)eff;
    if (!eff_hdl) {
        return;
    }
    u8 tmp = 0;
    if (eff_hdl->drc_bef_eq) {
        tmp = 1;
    }
    if (eff_hdl->drc_prev) {
        audio_dec_drc_close(eff_hdl->drc_prev);
        eff_hdl->drc_prev = NULL;
    }

    if (eff_hdl->eq) {
        audio_dec_eq_close(eff_hdl->eq);
        eff_hdl->eq = NULL;
    }

    if (eff_hdl->drc) {
        audio_dec_drc_close(eff_hdl->drc);
        eff_hdl->drc = NULL;
    }
    if (eff_hdl->eq_out_buf) {
        free(eff_hdl->eq_out_buf);
        eff_hdl->eq_out_buf = NULL;
    }

#if AUDIO_EQ_FADE_EN
    if (eff_hdl->fade.tmr) {
        sys_hi_timer_del(eff_hdl->fade.tmr);
        eff_hdl->fade.tmr = 0;
    }
#endif
    free(eff_hdl);
    if (tmp) { //还原非游戏音效eq drc 效果
        EQ_CFG *eq_cfg = get_eq_cfg_hdl();
        eq_cfg->eq_type = EQ_TYPE_MODE_TAB;
        eq_cfg_default_init(get_eq_cfg_hdl());
        drc_default_init(get_eq_cfg_hdl(), song_eq_mode);
        if (!eq_file_get_cfg(get_eq_cfg_hdl(), (u8 *)SDFILE_RES_ROOT_PATH"eq_cfg_hw.bin")) {
            eq_cfg->eq_type = EQ_TYPE_FILE;
        }
    }
#endif//TCFG_EQ_ENABLE

}
struct drc_ch esco_drc_p = {0};
int esco_drc_get_filter_info(void *drc, struct audio_drc_filter_info *info)
{
    float th = -0.5f;//db -60db~0db,限幅器阈值
    int threshold = roundf(powf(10.0f, th / 20.0f) * 32768);
    esco_drc_p.nband = 1;
    esco_drc_p.type = 1;
    esco_drc_p._p.limiter[0].attacktime = 5;
    esco_drc_p._p.limiter[0].releasetime = 500;
    esco_drc_p._p.limiter[0].threshold[0] = threshold;
    esco_drc_p._p.limiter[0].threshold[1] = 32768;
    info->R_pch = info->pch = &esco_drc_p;
    return 0;
}
void *esco_eq_drc_setup(void *priv, int (*eq_output_cb)(void *, void *, int), u32 sample_rate, u8 channel, u8 async, u8 drc_en)
{
#if TCFG_EQ_ENABLE && TCFG_PHONE_EQ_ENABLE

    if (config_eq_lite_en) { //仅支持同步方式eq处理
        async = 0;//
    }

    struct dec_eq_drc *eff = zalloc(sizeof(struct dec_eq_drc));
    struct audio_eq_param eq_param = {0};

    eff->priv = priv;
    eff->out_cb = eq_output_cb;
    eq_param.channels = channel;
    eq_param.online_en = 1;
    eq_param.mode_en = 0;
    eq_param.remain_en = 0;
    eq_param.no_wait = async;//a2dp_low_latency ? 0 : 1;
    if (drc_en) {
        eq_param.out_32bit = 1;
    }
    eq_param.max_nsection = EQ_SECTION_MAX;
    eq_param.cb = eq_phone_get_filter_info;
    eq_param.eq_name = call_eq_mode;
    eq_param.sr = sample_rate;
    eq_param.priv = eff;
    eq_param.output = eq_output;
    eff->eq = audio_dec_eq_open(&eq_param);

#if TCFG_DRC_ENABLE
    if (drc_en) {
        struct audio_drc_param drc_param = {0};
        drc_param.sr = sample_rate;
        drc_param.channels = channel;
        drc_param.online_en = 0;
        drc_param.remain_en = 0;
        drc_param.out_32bit = 1;
        drc_param.cb = esco_drc_get_filter_info;
        drc_param.drc_name = call_eq_mode;
        eff->drc = audio_dec_drc_open(&drc_param);
        eff->async = async;
    }
#endif//TCFG_DRC_ENABLE

    return eff;
#else
    return NULL;
#endif//TCFG_EQ_ENABLE && TCFG_PHONE_EQ_ENABLE

}
void esco_eq_drc_free(void *eff)
{
    dec_eq_drc_free(eff);
}
#define audio_out_drc_get_filter esco_drc_get_filter_info//可复用通话下行限幅器系数
void *audio_out_eq_drc_setup(void *priv, int (*eq_output_cb)(void *, void *, int), u32 sample_rate, u8 channel, u8 async, u8 drc_en)
{
#if TCFG_EQ_ENABLE &&AUDIO_OUT_EQ_USE_SPEC_NUM
    if (config_eq_lite_en) { //仅支持同步方式eq处理
        async = 0;//
    }

    struct dec_eq_drc *eff = zalloc(sizeof(struct dec_eq_drc));
    struct audio_eq_param eq_param = {0};

    eff->priv = priv;
    eff->out_cb = eq_output_cb;

    eq_param.channels = channel;
    eq_param.online_en = 0;
    eq_param.mode_en = 0;
    eq_param.remain_en = 0;
    eq_param.no_wait = async;
    if (drc_en) {
        eq_param.out_32bit = 1;
    }
    eq_param.max_nsection = AUDIO_OUT_EQ_USE_SPEC_NUM;
    eq_param.cb = audio_out_eq_get_filter_info;
    eq_param.eq_name = song_eq_mode;
    eq_param.sr = sample_rate;
    eq_param.priv = eff;
    eq_param.output = eq_output;
    eff->eq = audio_dec_eq_open(&eq_param);
#if TCFG_DRC_ENABLE
    if (drc_en) {
        struct audio_drc_param drc_param = {0};
        drc_param.sr = sample_rate;
        drc_param.channels = channel;
        drc_param.online_en = 0;
        drc_param.remain_en = 0;
        drc_param.out_32bit = 1;
        drc_param.cb = audio_out_drc_get_filter;
        drc_param.drc_name = song_eq_mode;
        eff->drc = audio_dec_drc_open(&drc_param);
        eff->async = async;
    }
#endif //TCFG_DRC_ENABLE

    return eff;
#else
    return NULL;
#endif//TCFG_EQ_ENABLE &&AUDIO_OUT_EQ_USE_SPEC_NUM

}
void audio_out_eq_drc_free(void *eff)
{
#if AUDIO_OUT_EQ_USE_SPEC_NUM
    dec_eq_drc_free(eff);
#endif//AUDIO_OUT_EQ_USE_SPEC_NUM

}

__attribute__((always_inline))
void sat16_to_sat32(s16 *in, s32 *out, u32 npoint, int factor)
{
#if 0
    for (int i = 0; i < npoint; i ++) {
        out[i] = in[i] * factor;
    }
#else
    s64 tmp;
    __asm__ volatile(
        "1:											\n\t"
        "rep %2 {									\n\t"        //循环
        "%3 = h[%1 ++= 2]*%4(s)                              \n\t"
        "[%0 ++= 4] = %3.l                            \n\t"   //%3.l意思是取tmp的低32位
        "}										    \n\t"
        "if(%2 != 0) goto 1b			            \n\t"
        :
        "=&r"(out),
        "=&r"(in),
        "=&r"(npoint),
        "=&r"(tmp)
        :
        "r"(factor),
        "0"(out),
        "1"(in),
        "2"(npoint),
        "3"(tmp)
        :
    );

#endif
}

int eq_drc_run(void *priv, void *data, u32 len)
{
#if TCFG_EQ_ENABLE
    struct dec_eq_drc *eff = (struct dec_eq_drc *)priv;
    if (!eff) {
        return 0;
    }

#if TCFG_DRC_ENABLE
    if (eff->drc && !eff->async) {//同步32bit eq drc 处理
        if ((!eff->eq_out_buf) || (eff->eq_out_buf_len < len * 2)) {
            if (eff->eq_out_buf) {
                free(eff->eq_out_buf);
            }
            eff->eq_out_buf_len = len * 2;
            eff->eq_out_buf = malloc(eff->eq_out_buf_len);
            ASSERT(eff->eq_out_buf);
        }
        audio_eq_set_output_buf(eff->eq, eff->eq_out_buf, len);

        if ((eff->drc_bef_eq == V1_GAME_EFF) && eff->drc_prev) {
            sat16_to_sat32((short *)data, (int *)eff->eq_out_buf, len >> 1, 1);
            audio_drc_run(eff->drc_prev, eff->eq_out_buf, len * 2);//32bit drc
        } else if ((eff->drc_bef_eq == NOR_GAME_EFF) && eff->drc_prev) {
            audio_drc_run(eff->drc_prev, data, len);//16bit drc
        }
    }
#endif//TCFG_DRC_ENABLE

    int eqlen = 0;
    if (eff->drc_bef_eq == V1_GAME_EFF) {
        eqlen = audio_eq_run(eff->eq, eff->eq_out_buf, len * 2);//32bit in out
    } else {
        eqlen = audio_eq_run(eff->eq, data, len);
    }

#if TCFG_DRC_ENABLE
    if (eff->drc && !eff->async) {//同步32bit eq drc 处理
        audio_drc_run(eff->drc, eff->eq_out_buf, len * 2);
        user_sat16((s32 *)eff->eq_out_buf, (s16 *)data, (len * 2) / 4);
    }
#endif//TCFG_DRC_ENABLE

    if (eff->drc && !eff->async) {
        return len;
    }
    return eqlen;
#else
    return len;
#endif
}

#if AUDIO_OUT_EQ_USE_SPEC_NUM

static struct eq_seg_info audio_out_eq_tab[AUDIO_OUT_EQ_USE_SPEC_NUM] = {
#ifdef EQ_CORE_V1
    {0, EQ_IIR_TYPE_BAND_PASS, 125,   0, 0.7f},
    {1, EQ_IIR_TYPE_BAND_PASS, 12000, 0, 0.3f},
#else
    {0, EQ_IIR_TYPE_BAND_PASS, 125,   0 * (1 << 20), 0.7f * (1 << 24)},
    {1, EQ_IIR_TYPE_BAND_PASS, 12000, 0 * (1 << 20), 0.3f * (1 << 24)},
#endif
};



int audio_out_eq_get_filter_info(void *eq, int sr, struct audio_eq_filter_info *info)
{
    struct audio_eq *eq_hdl = (struct audio_eq *)eq;
    if (!eq_hdl) {
        return -1;
    }
    local_irq_disable();
    u8 nsection = ARRAY_SIZE(audio_out_eq_tab);
    if (!eq_hdl->eq_coeff_tab) {
        eq_hdl->eq_coeff_tab = zalloc(sizeof(int) * 5 * nsection);
    }
    for (int i = 0; i < nsection; i++) {
        eq_seg_design(&audio_out_eq_tab[i], sr, &eq_hdl->eq_coeff_tab[5 * i]);
    }

    local_irq_enable();
    info->L_coeff = info->R_coeff = (void *)eq_hdl->eq_coeff_tab;
    info->L_gain = info->R_gain = 0;
    info->nsection = nsection;
    return 0;
}
int audio_out_eq_spec_set_info(struct audio_eq *eq, u8 idx, int freq, float gain)
{
    if (idx >= AUDIO_OUT_EQ_USE_SPEC_NUM) {
        return false;
    }
    if (gain > 12) {
        gain = 12;
    }
    if (gain < -12) {
        gain = -12;
    }
    if (freq) {
        audio_out_eq_tab[idx].freq = freq;
    }

#ifdef EQ_CORE_V1
    audio_out_eq_tab[idx].gain = gain;
#else
    audio_out_eq_tab[idx].gain = gain * (1 << 20);
#endif

    /* printf("audio out eq, idx:%d, freq:%d,%d, gain:%d,%d \n", idx, freq, audio_out_eq_tab[idx].freq, gain, audio_out_eq_tab[idx].gain); */

#if !AUDIO_EQ_FADE_EN
    local_irq_disable();
    if (eq) {
        eq->updata = 1;
    }
    local_irq_enable();
#endif

    return true;
}

#if AUDIO_EQ_FADE_EN

void eq_fade_run(void *p)
{
    struct dec_eq_drc *eff = (struct dec_eq_drc *)p;
    struct eq_filter_fade *fade = &eff->fade;
    struct audio_eq *eq = (struct audio_eq *)eff->eq;


    u8 update = 0;
    u8 design = 0;
    for (int i = 0; i < ARRAY_SIZE(audio_out_eq_tab); i++) {
        if (fade->cur_gain[i] > fade->use_gain[i]) {
#ifdef EQ_CORE_V1
            fade->cur_gain[i] -= HIGH_BASS_EQ_FADE_STEP;
#else
            fade->cur_gain[i] -= HIGH_BASS_EQ_FADE_STEP * (1 << 20);
#endif
            if (fade->cur_gain[i] < fade->use_gain[i]) {
                fade->cur_gain[i] = fade->use_gain[i];
            }
            design = 1;
        } else if (fade->cur_gain[i] < fade->use_gain[i]) {
#ifdef EQ_CORE_V1
            fade->cur_gain[i] += HIGH_BASS_EQ_FADE_STEP;
#else
            fade->cur_gain[i] += HIGH_BASS_EQ_FADE_STEP * (1 << 20);
#endif
            if (fade->cur_gain[i] > fade->use_gain[i]) {
                fade->cur_gain[i] = fade->use_gain[i];
            }
            design = 1;
        }

        if (design) {
            design = 0;
            update = 1;
            /* audio_out_eq_spec_set_info(p, i, 0, fade->cur_gain[i]); */
            /* if (eq) { */
            audio_out_eq_tab[i].gain = fade->cur_gain[i];//gain;//gain << 20;
            /* } */

        }
    }

    if (update) {
        update = 0;
        local_irq_disable();
        if (eq) {
            eq->updata = 1;
        }
        local_irq_enable();
    }
}



#endif


int audio_out_eq_set_gain(void *eff, u8 idx, int gain)
{
    struct dec_eq_drc *eff_hdl = (struct dec_eq_drc *)eff;
    if (!eff_hdl) {
        return 0;
    }
    if (!idx) {
        idx = 0;
    } else {
        idx = 1;
    }

#if AUDIO_EQ_FADE_EN
    eff_hdl->fade.use_gain[idx] = gain;
    if (eff_hdl->fade.tmr == 0) {
        eff_hdl->fade.tmr = sys_hi_timer_add(eff_hdl, eq_fade_run, 20);
    }
#else
    if (!idx) {
        audio_out_eq_spec_set_info(eff_hdl->eq, 0, 0, gain);//低音
    } else {
        audio_out_eq_spec_set_info(eff_hdl->eq, 1, 0, gain);//高音
    }
#endif

    return true;
}
#endif /*AUDIO_OUT_EQ_USE_SPEC_NUM*/


static struct audio_drc *mix_out_drc = NULL;


static float mix_out_drc_threadhold = -0.5f;//db -60db~0db,限幅器阈值
static struct drc_ch mix_out_drc_p = {0};
int mix_out_drc_get_filter_info(void *drc, struct audio_drc_filter_info *info)
{
    float th = mix_out_drc_threadhold;//db -60db~0db,限幅器阈值
    int threshold = roundf(powf(10.0f, th / 20.0f) * 32768);
    mix_out_drc_p.nband = 1;
    mix_out_drc_p.type = 1;
    mix_out_drc_p._p.limiter[0].attacktime = 5;
    mix_out_drc_p._p.limiter[0].releasetime = 500;
    mix_out_drc_p._p.limiter[0].threshold[0] = threshold;
    mix_out_drc_p._p.limiter[0].threshold[1] = 32768;
    info->R_pch = info->pch = &mix_out_drc_p;
    return 0;
}

void mix_out_drc_open(u16 sample_rate)
{
    u8 ch_num;
#if TCFG_APP_FM_EMITTER_EN
    ch_num = 2;
#else
    u8 dac_connect_mode = audio_dac_get_channel(&dac_hdl);
    if (dac_connect_mode == DAC_OUTPUT_LR) {
        ch_num =  2;
    } else {
        ch_num =  1;
    }
#endif//TCFG_APP_FM_EMITTER_EN

#if TCFG_DRC_ENABLE
    struct audio_drc_param drc_param = {0};
    drc_param.sr = sample_rate;
    drc_param.channels = ch_num;
    drc_param.online_en = 0;
    drc_param.remain_en = 0;
    drc_param.out_32bit = 0;
    drc_param.cb = mix_out_drc_get_filter_info;
    drc_param.drc_name = song_eq_mode;
    mix_out_drc = audio_dec_drc_open(&drc_param);
#endif//TCFG_DRC_ENABLE

}

void mix_out_drc_close()
{
#if TCFG_DRC_ENABLE
    if (mix_out_drc) {
        audio_dec_drc_close(mix_out_drc);
        mix_out_drc = NULL;
    }
#endif//TCFG_DRC_ENABLE

}

void mix_out_drc_run(s16 *data, u32 len)
{
#if TCFG_DRC_ENABLE
    if (mix_out_drc) {
        audio_drc_run(mix_out_drc, data, len);
    }
#endif//TCFG_DRC_ENABLE

}

/*----------------------------------------------------------------------------*/
/**@brief    mix_out后限幅器系数更新
   @param    threadhold限幅器阈值，-60~0,单位db
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mix_out_drc_threadhold_update(float threadhold)
{
#if TCFG_DRC_ENABLE
    mix_out_drc_threadhold = threadhold;

    local_irq_disable();
    if (mix_out_drc) {
        mix_out_drc->updata = 1;
    }
    local_irq_enable();
#endif//TCFG_DRC_ENABLE

}
#if defined(EQ_CORE_V1)
struct audio_eq *audio_dec_eq_open_new(struct audio_eq_param *parm, struct eq_parm_new *par_new)
{
    struct audio_eq_param *eq_param = parm;
    struct audio_eq *eq = zalloc(sizeof(struct audio_eq) + sizeof(struct hw_eq_ch));
    if (eq) {
        eq->eq_ch = (struct hw_eq_ch *)((int)eq + sizeof(struct audio_eq));

        audio_eq_open(eq, eq_param);
        audio_eq_set_samplerate(eq, eq_param->sr);
        audio_eq_set_info_new(eq, eq_param->channels, par_new->in_mode, eq_param->out_32bit, par_new->run_mode, par_new->data_in_mode, par_new->data_out_mode);
        /* log_info("eq_param->sr %d, eq_param->channels %d\n", eq_param->sr,  eq_param->channels); */
        audio_eq_set_output_handle(eq, eq_param->output, eq_param->priv);
        audio_eq_start(eq);
        /* log_info("audio_dec_eq_open name %d\n", eq_param->eq_name); */
    }
    return eq;
}
#endif/*defined(EQ_CORE_V1)*/

#if defined(AUDIO_GAME_EFFECT_CONFIG) && AUDIO_GAME_EFFECT_CONFIG

struct drc_ch dec_drc_p = {0};
int dec_drc_get_filter_info(void *drc, struct audio_drc_filter_info *info)
{
    float th = -0.5f;//db -60db~0db,限幅器阈值
    int threshold = roundf(powf(10.0f, th / 20.0f) * 32768);
    dec_drc_p.nband = 1;
    dec_drc_p.type = 1;
    dec_drc_p._p.limiter[0].attacktime = 5;
    dec_drc_p._p.limiter[0].releasetime = 500;
    dec_drc_p._p.limiter[0].threshold[0] = threshold;
    dec_drc_p._p.limiter[0].threshold[1] = 32768;
    info->R_pch = info->pch = &dec_drc_p;
    return 0;
}


#if	defined(EQ_CORE_V1)
void *dec_eq_drc_setup_new(void *priv, int (*eq_output_cb)(void *, void *, int), u32 sample_rate, u8 channel, u8 async, u8 drc_en)
{
#if  TCFG_EQ_ENABLE

    struct dec_eq_drc *eff = zalloc(sizeof(struct dec_eq_drc));
    if (config_eq_lite_en) { //仅支持同步方式eq处理
        async = 0;//
    }

#if TCFG_DRC_ENABLE
    if (drc_en & BIT(1)) { //game eff drc
        if (!eq_file_get_cfg(get_eq_cfg_hdl(), (u8 *)SDFILE_RES_ROOT_PATH"eq_game_eff.bin")) { //加载游戏音效
            EQ_CFG *eq_cfg = get_eq_cfg_hdl();
            eq_cfg->eq_type = EQ_TYPE_FILE;
        }
        eff->drc_bef_eq = V1_GAME_EFF;
        async = 0;
        struct audio_drc_param drc_param = {0};
        drc_param.sr = sample_rate;
        drc_param.channels = channel;
        drc_param.online_en = 1;
        drc_param.remain_en = 1;
        drc_param.out_32bit = 1;
        drc_param.cb = drc_get_filter_info;
        drc_param.drc_name = song_eq_mode;
        eff->drc_prev = audio_dec_drc_open(&drc_param);
    }
#endif//TCFG_DRC_ENABLE

    eff->priv = priv;
    eff->out_cb = eq_output_cb;

    struct audio_eq_param eq_param = {0};
    eq_param.channels = channel;
    eq_param.online_en = 1;
    eq_param.mode_en = 1;
    eq_param.remain_en = 1;
    eq_param.no_wait = async;
    if (drc_en) {
        eq_param.out_32bit = 1;
    }
    eq_param.max_nsection = EQ_SECTION_MAX;
    eq_param.cb = eq_get_filter_info;
    eq_param.eq_name = song_eq_mode;
    eq_param.sr = sample_rate;
    eq_param.priv = eff;
    eq_param.output = eq_output;

    struct eq_parm_new par_new = {0};
    par_new.in_mode = DATI_INT;
    par_new.run_mode = NORMAL;
    par_new.data_in_mode = SEQUENCE_DAT_IN;
    par_new.data_out_mode = SEQUENCE_DAT_OUT;
    eff->eq = audio_dec_eq_open_new(&eq_param, &par_new);
    eff->async = async;
#if TCFG_DRC_ENABLE
    if (drc_en) {
        struct audio_drc_param drc_param = {0};
        drc_param.sr = sample_rate;
        drc_param.channels = channel;
        if (eff->drc_bef_eq == V1_GAME_EFF) {
            drc_param.online_en = 0;
            drc_param.remain_en = 0;
            drc_param.out_32bit = 1;
            drc_param.cb = dec_drc_get_filter_info;
            drc_param.drc_name = mic_eq_mode;
        } else {
            drc_param.online_en = 1;
            drc_param.remain_en = 1;
            drc_param.out_32bit = 1;
            drc_param.cb = drc_get_filter_info;
            drc_param.drc_name = song_eq_mode;
        }
        eff->drc = audio_dec_drc_open(&drc_param);
    }
#endif//TCFG_DRC_ENABLE

    return eff;
#else
    return NULL;
#endif//TCFG_EQ_ENABLE

}
#endif/*EQ_CORE_V1*/
#endif /*AUDIO_GAME_EFFECT_CONFIG*/
