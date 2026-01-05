#ifndef __AUDIO_GAIN_PORCESS__H
#define __AUDIO_GAIN_PORCESS__H

#include "media/audio_stream.h"

#ifndef RUN_NORMAL
#define RUN_NORMAL  0
#endif

#ifndef RUN_BYPASS
#define RUN_BYPASS  1
#endif

struct aud_gain_parm {
    float gain[2];//增加多少dB
    u16 gain_name;
    u8 channel;//通道数
    u8 indata_inc;//channel ==1 ?1:2;
    u8 outdata_inc;//channel ==1 ?1:2;
    u8 bit_wide;//0:16bit  1：32bit
    u8 divide;//左右声道是否需要独立的gain
};
struct aud_gain_parm_update {
    float gain[2];//增加多少dB
};

struct aud_gain_process {
    struct audio_stream_entry entry;	// 音频流入口
    struct list_head hentry;                         //
    struct aud_gain_parm parm;
    u8 status;                           //内部运行状态机
    u8 update;                           //设置参数更新标志
};


struct aud_gain_process *audio_gain_process_open(struct aud_gain_parm *parm);
void audio_gain_process_run(struct aud_gain_process *hdl, s16 *data, int len);
void audio_gain_process_close(struct aud_gain_process *hdl);
void audio_gain_process_update(u16 gain_name, struct aud_gain_parm_update *parm);
void audio_gain_process_bypass(u16 gain_name, u8 bypass);
struct aud_gain_process *get_cur_gain_hdl_by_name(u32 gain_name);

void GainProcess_16Bit(short *in, short *out, float gain, int channel, int IndataInc, int OutdataInc, int per_channel_npoint); //16位宽
void GainProcess_32Bit(int *in, int *out, float gain, int channel, int IndataInc, int OutdataInc, int per_channel_npoint); //32位宽
void SplitGainProcess_16Bit(short *in, short *out, float *gain, int channel, int IndataInc, int OutdataInc, int per_channel_npoint); //16位宽
void SplitGainProcess_32Bit(int *in, int *out, float *gain, int channel, int IndataInc, int OutdataInc, int per_channel_npoint); //32位宽
#endif
