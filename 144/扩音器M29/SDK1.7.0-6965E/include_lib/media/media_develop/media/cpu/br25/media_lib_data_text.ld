

        media_data_code_start = .;
        . = ALIGN(4);
		*(.sbc_eng_code)
#if (TCFG_CODE_RUN_RAM_FM_MODE)
        /* *(.pcm_code) */
        *(.pcm_const)
		/* *(.audio_dec_pcm_code) */
		*(.audio_dec_pcm_const)
		/* *(.stream_code_nor_run)			// 数据流普通输出处理 */
		/* *(.mixer_code_nor_run)			// mixer数据流直通输出 */
		/* *(.audio_codec_code)			// 解码任务流程 */
		/* *(.audio_codec_code_read_file)	// 解码读文件 */
		/* *(.audio_src_code_nor_run)		// audio_src运行处理 */
		/* *(.src_base_code_nor_run)		// src_base运行处理 */
		/* *(.audio_dac_code_nor_run)		// audio_dac普通输出运行处理 */
		/* *(.audio_cfifo_code_nor_run)	// audio_cfifo普通运行处理 */
		/* *(.audio_track_code) */
		*(.audio_track_const)
#endif /*(TCFG_CODE_RUN_RAM_FM_MODE)*/
        . = ALIGN(4);
#if AUDIO_EFFECTS_DVOL_AT_RAM 
		*(.dvol_ram_code)
        . = ALIGN(4);
#endif

        AudioEffects_data_code_begin = .;



#if AUDIO_EFFECTS_REVERB_AT_RAM
		*(.platereverb_code)
		*(.platereverb_const)
#endif/*AUDIO_EFFECTS_REVERB_AT_RAM*/

#if AUDIO_EFFECTS_AFC_AT_RAM
	    *(.howlings_phf_code)
		*(.howlings_phf_const)
		/*AFC_Lib_陷波*/
		*(.notchhowling_code)
		*(.notchhowling_const)
		*(.notchhowling_sparse_code)
		*(.notchhowling_sparse_const)
#endif/*AUDIO_EFFECTS_AFC_AT_RAM*/

   /*      *(.audio_drc_code) */
		/* *(.audio_drc_const) */
#if AUDIO_EFFECTS_DRC_AT_RAM
		/* *(.drc_run_code) */
		/* *(.sw_drc_code) */
		*(.sw_drc_const)
		*(.drc_const)
		/* *(.drc_code) */
	   /*  *(.crossOver_code) */
		/* *(.crossOver_const) */
#endif/*AUDIO_EFFECTS_DRC_AT_RAM*/

#if AUDIO_EFFECTS_EQ_AT_RAM
		/* *(.audio_eq_code) */
		/* *(.audio_eq_const) */
		/* *(.eq_run_code) */
		*(.hw_eq_code)
		*(.hw_eq_const)
#endif/*AUDIO_EFFECTS_EQ_AT_RAM*/

#if AUDIO_EFFECTS_NOISEGATE_AT_RAM
		*(.audio_noisegate_code)
		*(.audio_noisegate_const)
		/*Lib_NoiseGate*/
		*(.noisegate_code)
		*(.noisegate_const)
		*(.noisegate_sparse_code)
		*(.noisegate_sparse_const)
#endif/*AUDIO_EFFECTS_NOISEGATE_AT_RAM*/

#if AUDIO_EFFECTS_MIC_EFFECT_AT_RAM
		*(.audio_mic_effect_const)
		*(.audio_mic_effect_code)
#endif/*AUDIO_EFFECTS_MIC_EFFECT_AT_RAM*/

#if AUDIO_EFFECTS_MIC_STREAM_AT_RAM
		*(.audio_mic_stream_const)
		*(.audio_mic_stream_code)
#endif/*AUDIO_EFFECTS_MIC_STREAM_AT_RAM*/

#if AUDIO_EFFECTS_DEBUG_AT_RAM
		*(.audio_effect_adj_const)
		*(.audio_effect_adj_code)
#endif/*AUDIO_EFFECTS_DEBUG_AT_RAM*/

#if AUDIO_EFFECTS_SURROUND_AT_RAM 
		*(.audio_surround_code)
		*(.audio_surround_const)
		*(.sur_cal_common_code)
		*(.sur_TYPE0_cal_code)
	    *(.sur_TYPE1_cal_code)
		*(.sur_TYPE0_cal_const)
	    *(.sur_TYPE1_cal_const)
		/* *(.sur_LRDRIFT2_cal_code) */
		/* *(.sur_LRDRIFT2_cal_const) */
		/* *(.sur_ROTATE_cal_code) */
		/* *(.sur_ROTATE_cal_const) */
        /* *(.sur_LRDRIFT_cal_code) */
        /* *(.sur_LRDRIFT_cal_const) */
#endif

#if AUDIO_EFFECTS_VOCAL_TRACK_AT_RAM 
	*(.audio_vocal_tract_synthesis_code)
        *(.audio_vocal_tract_synthesis_const)
#endif

#if AUDIO_EFFECTS_VBASS_AT_RAM
     	/* *(.vbss_code) */
     	*(.vbss_cost)
		/* *(.audio_vbass_code) */
		*(.audio_vbass_const)
#endif


        AudioEffects_data_code_end = .;
        AudioEffects_data_code_size = AudioEffects_data_code_end - AudioEffects_data_code_begin;
        media_data_code_end = .;



