#include "app_config.h"

1:
#if (TCFG_CODE_RUN_RAM_FM_MODE)
#if (!TCFG_LED7_RUN_RAM)
.gpio_ram
.LED_code
#endif

.usr_timer_code
.timer_code
.cbuf_code
.fm_data_code
.pcm_code
.audio_dec_pcm_code
.audio_track_code
.stream_code_nor_run		// 数据流普通输出处理
.mixer_code_nor_run			// mixer数据流直通输出
.audio_codec_code			// 解码任务流程
.audio_codec_code_read_file	// 解码读文件
.audio_src_code_nor_run		// audio_src运行处理
.src_base_code_nor_run		// src_base运行处理
.audio_dac_code_nor_run		// audio_dac普通输出运行处理
.audio_cfifo_code_nor_run	// audio_cfifo普通运行处理

#endif

2:
#if (AUDIO_EFFECTS_VBASS_AT_RAM)
.vbss_code
.audio_vbass_code
#endif

3:
#if (TCFG_VM_SPI_CODE_AT_RAM_DYANMIC)
.spi_code
#endif

4:
#if (AUDIO_EFFECTS_DRC_AT_RAM)
.drc_run_code
.sw_drc_code
.drc_code
#endif

