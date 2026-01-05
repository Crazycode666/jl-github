#include "generic/gpio.h"
#include "asm/includes.h"
#include "system/timer.h"
#include "board_config.h"
#include "record/record.h"
#include "dev_manager.h"
#include "media/audio_base.h"
#include "audio_enc.h"
#include "tone_player.h"
#include "audio_dec.h"
#include "clock_cfg.h"



#ifdef CONFIG_BOARD_AC696X_DEMO
#include "effect_reg.h"
#include "media/effects_adj.h"
#include "audio_effect/audio_eff_default_parm.h"

/*----------------------------------------------------------------------------*/
/**@brief   叠加播放需要添加的函数
   @param
   @return
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
#define OVERLAY_PLAY     0  //叠加播放
#define INTERRUPT_PLAY   1  //打断之前所有提示音再进行播放

struct tone_dec_handle *tone_dec_lev1 = NULL;
struct tone_dec_handle *tone_dec_lev2 = NULL;

struct audio_eq     *record_eq_lev1 = NULL;
struct audio_eq     *record_eq_lev2 = NULL;
ECHO_API_STRUCT 		*record_play_echo_hdl_lev1 = NULL;
ECHO_API_STRUCT 		*record_play_echo_hdl_lev2 = NULL;
voice_changer_hdl			*record_play_pitch_hdl_lev1 = NULL;
voice_changer_hdl			*record_play_pitch_hdl_lev2 = NULL;

//变声模式切换
extern void audio_voice_changer_mode_switch(u32 voice_changer_name, VOICE_CHANGER_MODE voice_changer_mode);


const ECHO_PARM_SET record_echo_parm = {
    .delay = 200,				//回声的延时时间 0-300ms
    .decayval = 50,				// 0-70%
    .filt_enable = 1,			//发散滤波器使能
};
const EF_REVERB_FIX_PARM record_echo_fix_parm_default = {
    .sr = 16000,		////采样率
    .max_ms = 200,				////所需要的最大延时，影响 need_buf 大小

};
static void record_play_stream_resume(void *p)
{
    struct audio_dec_app_hdl *app_dec = p;
    audio_decoder_resume(&app_dec->decoder);
}

void record_play_stream_handler_lev1(void *priv, int event, struct audio_dec_app_hdl *app_dec)
{
    switch (event) {
    case AUDIO_DEC_APP_EVENT_START_INIT_OK: {
        u8 entry_cnt = 0;
        struct audio_stream_entry *entries[8] = {NULL};
        entries[entry_cnt++] = &app_dec->decoder.entry;
        {
            clock_add_set(REVERB_CLK);
            //打开pitch和添加处理入口
            //record_play_pitch_hdl_lev1 = audio_voice_changer_open_demo(AEID_MIC_VOICE_CHANGER, 16000);
            //entries[entry_cnt++] = &record_play_pitch_hdl_lev1->entry;

            //打开echo和添加处理入口
            //record_play_echo_hdl_lev1 = open_echo((ECHO_PARM_SET *)&record_echo_parm, &record_echo_fix_parm_default);
            //entries[entry_cnt++] = &record_play_echo_hdl_lev1->entry;

            //打开EQ和添加处理入口
            //record_eq_lev1 = music_eq_open(16000, 1);
            //entries[entry_cnt++] = &record_eq_lev1->entry;
        }
        entries[entry_cnt++] = &app_dec->mix_ch.entry;
        app_dec->stream = audio_stream_open(app_dec, record_play_stream_resume);
        audio_stream_add_list(app_dec->stream, entries, entry_cnt);
        break;
    }
    case AUDIO_DEC_APP_EVENT_DEC_CLOSE:
        //如果打开了pitch则删除pitch处理入口和关闭pitch
#if defined(TCFG_MIC_VOICE_CHANGER_ENABLE) && TCFG_MIC_VOICE_CHANGER_ENABLE
        if (record_play_pitch_hdl_lev1) {
            audio_voice_changer_close_demo(record_play_pitch_hdl_lev1);
            record_play_pitch_hdl_lev1 = NULL;
        }
#endif
        //如果打开了echo则删除echo处理入口和关闭echo
        if (record_play_echo_hdl_lev1) {
            close_echo(record_play_echo_hdl_lev1);
            record_play_echo_hdl_lev1 = NULL;
        }
        //如果打开了EQ则删除EQ处理入口和关闭EQ
        if (record_eq_lev1) {
            music_eq_close(record_eq_lev1);
            record_eq_lev1 = NULL;
        }
        break;
    }
}

void record_play_stream_handler_lev2(void *priv, int event, struct audio_dec_app_hdl *app_dec)
{
    switch (event) {
    case AUDIO_DEC_APP_EVENT_START_INIT_OK:
        printf("AUDIO_DEC_APP_EVENT_START_INIT_OK\n");
        struct audio_stream_entry *entries[8] = {NULL};
        u8 entry_cnt = 0;
        entries[entry_cnt++] = &app_dec->decoder.entry;
        {
            clock_add_set(REVERB_CLK);
            //打开pitch和添加处理入口
            //record_play_pitch_hdl_lev2 = audio_voice_changer_open_demo(AEID_MIC_VOICE_CHANGER, 16000);
            //entries[entry_cnt++] = &record_play_pitch_hdl_lev2->entry;

            //打开echo和添加处理入口
            //record_play_echo_hdl_lev2 = open_echo((ECHO_PARM_SET *)&record_echo_parm, &record_echo_fix_parm_default);
            //entries[entry_cnt++] = &record_play_echo_hdl_lev2->entry;

        }
        entries[entry_cnt++] = &app_dec->mix_ch.entry;
        app_dec->stream = audio_stream_open(app_dec, record_play_stream_resume);
        audio_stream_add_list(app_dec->stream, entries, entry_cnt);
        break;
    case AUDIO_DEC_APP_EVENT_DEC_CLOSE:
        //如果打开了pitch则删除pitch处理入口和关闭pitch
#if defined(TCFG_MIC_VOICE_CHANGER_ENABLE) && TCFG_MIC_VOICE_CHANGER_ENABLE
        if (record_play_pitch_hdl_lev2) {
            audio_voice_changer_close_demo(record_play_pitch_hdl_lev2);
            record_play_pitch_hdl_lev2 = NULL;
        }
#endif
        //如果打开了echo则删除echo处理入口和关闭echo
        if (record_play_echo_hdl_lev2) {
            close_echo(record_play_echo_hdl_lev2);
            record_play_echo_hdl_lev2 = NULL;
        }
        //如果打开了EQ则删除EQ处理入口和关闭EQ
        if (record_eq_lev2) {
            music_eq_close(record_eq_lev2);
            record_eq_lev2 = NULL;
        }

        break;
    }
}

int record_play_with_callback_by_path_lev1(char *name, u8 preemption, void (*evt_handler)(void *priv, int flag), void *evt_priv)
{
    static char *single_file[2] = {NULL};
    single_file[0] = name;
    single_file[1] = NULL;
    printf("record_play_with_callback_by_path_lev1\n");
    tone_dec_stop(&tone_dec_lev1, 1, TONE_DEC_STOP_BY_OTHER_PLAY);
    tone_dec_lev1 = tone_dec_create();
    if (tone_dec_lev1 == NULL) {
        return -1;
    }
    struct tone_dec_list_handle *dec_list = tone_dec_list_create(tone_dec_lev1, (const char **) single_file, preemption, evt_handler, NULL, record_play_stream_handler_lev1, NULL);
    return tone_dec_list_add_play(tone_dec_lev1, dec_list);
}

int record_play_with_callback_by_path_lev2(char *name, u8 preemption, void (*evt_handler)(void *priv, int flag), void *evt_priv)
{
    static char *single_file[2] = {NULL};
    single_file[0] = name;
    single_file[1] = NULL;
    printf("record_play_with_callback_by_path_lev2 \n");
    tone_dec_stop(&tone_dec_lev2, 1, TONE_DEC_STOP_BY_OTHER_PLAY);
    tone_dec_lev2 = tone_dec_create();
    if (tone_dec_lev2 == NULL) {
        return -1;
    }
    struct tone_dec_list_handle *dec_list = tone_dec_list_create(tone_dec_lev2, (const char **)single_file, preemption, evt_handler, NULL, record_play_stream_handler_lev2, NULL);
    return tone_dec_list_add_play(tone_dec_lev2, dec_list);
}

void record_play_end_callback_lev1(void *priv, int data)
{
    printf("record_play_end_callback_lev1\n");
}
void record_play_end_callback_lev2(void *priv, int data)
{
    printf("record_play_end_callback_lev2\n");
}
void record_file_replay_lev1()
{
    char path[64] = {0};
    char filepath[] = {"/JL_REC/REC_TEST.MP3"};
    sprintf(path, "%s%s%s%s", "storage/", "sd0", "/C", filepath);
    record_play_with_callback_by_path_lev1(path, INTERRUPT_PLAY, record_play_end_callback_lev1, 0);
}

void record_file_replay_lev2()
{
    char path[64] = {0};
    char filepath[] = {"/JL_REC/REC_TEST.WAV"};
    sprintf(path, "%s%s%s%s", "storage/", "sd0", "/C", filepath);
    record_play_with_callback_by_path_lev2(path, OVERLAY_PLAY, record_play_end_callback_lev2, 0);
}

#endif
