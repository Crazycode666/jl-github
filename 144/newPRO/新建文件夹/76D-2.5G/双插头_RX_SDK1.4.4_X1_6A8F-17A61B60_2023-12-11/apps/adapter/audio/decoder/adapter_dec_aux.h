#ifndef __ADAPTER_DEC_MASTER_MIC_H__
#define __ADAPTER_DEC_MASTER_MIC_H__

#include "generic/typedef.h"
#include "media/includes.h"
#include "adapter_decoder.h"

struct __adapter_wireless_dec;

struct __adapter_dec_master_mic *adapter_dec_master_mic_open(
        struct adapter_decoder_fmt *fmt,
        struct adapter_media_parm *media_parm,
        struct audio_mixer *mixer,
        struct adapter_audio_stream	*adapter_stream);
void adapter_master_mic_dec_close(struct __adapter_dec_master_mic **hdl);
void adapter_wireless_dec_set_vol(struct __adapter_wireless_dec *dec, u32 channel, u8 vol);

#endif
