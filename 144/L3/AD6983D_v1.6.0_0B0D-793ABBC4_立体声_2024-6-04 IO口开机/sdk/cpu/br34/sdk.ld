































  local_irq_enable = ABSOLUTE(0x10fc4c);
  local_irq_disable = ABSOLUTE(0x10fc50);
  lp_signature_set = ABSOLUTE(0x10fc54);
  os_init = ABSOLUTE(0x10fc58);
  os_start = ABSOLUTE(0x10fc5c);
  os_get_curr_tcb_var = ABSOLUTE(0x10fc60);
  os_task_create_rom = ABSOLUTE(0x10fc64);
  os_current_task_rom = ABSOLUTE(0x10fc68);
  os_time_dly = ABSOLUTE(0x10fc6c);
  os_time_get = ABSOLUTE(0x10fc70);
  os_task_del_req = ABSOLUTE(0x10fc74);
  os_task_del_res = ABSOLUTE(0x10fc78);
  os_task_del = ABSOLUTE(0x10fc7c);
  __os_taskq_pend = ABSOLUTE(0x10fc80);
  os_taskq_pend = ABSOLUTE(0x10fc84);
  os_task_pend = ABSOLUTE(0x10fc88);
  __os_taskq_post = ABSOLUTE(0x10fc8c);
  os_taskq_post = ABSOLUTE(0x10fc90);
  os_taskq_post_type = ABSOLUTE(0x10fc94);
  os_taskq_flush = ABSOLUTE(0x10fc98);
  task_queue_post_event = ABSOLUTE(0x10fc9c);
  os_taskq_post_msg = ABSOLUTE(0x10fca0);
  os_taskq_post_event = ABSOLUTE(0x10fca4);
  os_taskq_accept = ABSOLUTE(0x10fca8);
  os_taskq_del = ABSOLUTE(0x10fcac);
  os_taskq_del_type = ABSOLUTE(0x10fcb0);
  os_sem_create = ABSOLUTE(0x10fcb4);
  os_sem_del = ABSOLUTE(0x10fcb8);
  os_sem_pend = ABSOLUTE(0x10fcbc);
  os_sem_post = ABSOLUTE(0x10fcc0);
  os_sem_set = ABSOLUTE(0x10fcc4);
  os_sem_valid = ABSOLUTE(0x10fcc8);
  os_sem_query = ABSOLUTE(0x10fccc);
  os_mutex_create = ABSOLUTE(0x10fcd0);
  os_mutex_del = ABSOLUTE(0x10fcd4);
  os_mutex_pend = ABSOLUTE(0x10fcd8);
  os_mutex_post = ABSOLUTE(0x10fcdc);
  os_mutex_valid = ABSOLUTE(0x10fce0);
  xTaskCreate = ABSOLUTE(0x10fce4);
  xTaskGetCurrentTaskHandle = ABSOLUTE(0x10fce8);
  xTaskGetTickCount = ABSOLUTE(0x10fcec);
  xTaskGetHandle = ABSOLUTE(0x10fcf0);
  os_task_get_handle = ABSOLUTE(0x10fcf0);
  vTaskDelete = ABSOLUTE(0x10fcf4);
  xTaskGetApplicationTaskTag = ABSOLUTE(0x10fcf8);
  vTaskSetApplicationTaskTag = ABSOLUTE(0x10fcfc);
  xQueueGenericCreateStatic = ABSOLUTE(0x10fd00);
  xQueueGenericReset = ABSOLUTE(0x10fd04);
  xQueueGenericSend = ABSOLUTE(0x10fd08);
  xQueueGenericSendFromISR = ABSOLUTE(0x10fd0c);
  xQueueGenericReceive = ABSOLUTE(0x10fd10);
  xQueueReceiveFromISR = ABSOLUTE(0x10fd14);
  vQueueDelete = ABSOLUTE(0x10fd18);
  uxQueueMessagesWaiting = ABSOLUTE(0x10fd1c);
  uxQueueMessagesWaitingFromISR = ABSOLUTE(0x10fd20);
  uxQueueSpacesAvailable = ABSOLUTE(0x10fd24);
  pcTaskGetName = ABSOLUTE(0x10fd28);
  prvGetExpectedIdleTime = ABSOLUTE(0x10fd2c);
  eTaskConfirmSleepModeStatus = ABSOLUTE(0x10fd30);
  vTaskStepTick = ABSOLUTE(0x10fd34);
  pxPortInitialiseStack = ABSOLUTE(0x10fd38);
  xPortStartScheduler = ABSOLUTE(0x10fd3c);
  vPortEndScheduler = ABSOLUTE(0x10fd40);
  vPortYield = ABSOLUTE(0x10fd44);
  vPortExitCritical = ABSOLUTE(0x10fd48);
  OS_ClrPending = ABSOLUTE(0x10fd4c);
  vTickISR = ABSOLUTE(0x10fd50);
  pmalloc_init = ABSOLUTE(0x10fd54);
  pmalloc = ABSOLUTE(0x10fd58);
  pfree = ABSOLUTE(0x10fd5c);
  pmalloc_get_unused_pages = ABSOLUTE(0x10fd60);
  get_physic_address = ABSOLUTE(0x10fd64);
  pmm_get_var = ABSOLUTE(0x10fd68);
  vmm_init_ = ABSOLUTE(0x10fd6c);
  vmalloc_ = ABSOLUTE(0x10fd70);
  vfree_ = ABSOLUTE(0x10fd74);
  vmem_get_phy_adr = ABSOLUTE(0x10fd78);
  vmem_start = ABSOLUTE(0x10fd7c);
  vmem_end = ABSOLUTE(0x10fd80);
  vmm_get_var = ABSOLUTE(0x10fd84);
  vmalloc_v2 = ABSOLUTE(0x10fd88);
  vfree_v2 = ABSOLUTE(0x10fd8c);
  vcopy_ = ABSOLUTE(0x10fd90);
  memmem = ABSOLUTE(0x10fd94);
  memcpy = ABSOLUTE(0x10fd98);
  memmove = ABSOLUTE(0x10fd9c);
  memcmp = ABSOLUTE(0x10fda0);
  memset = ABSOLUTE(0x10fda4);
  strcmp = ABSOLUTE(0x10fda8);
  strcpy = ABSOLUTE(0x10fdac);
  strlen = ABSOLUTE(0x10fdb0);
  strncmp = ABSOLUTE(0x10fdb4);
  strstr = ABSOLUTE(0x10fdb8);
  strchr = ABSOLUTE(0x10fdbc);
  IcuCmdKst = ABSOLUTE(0x10fdc0);
  DcuCmdKst = ABSOLUTE(0x10fdc4);
  IcuCmdSend = ABSOLUTE(0x10fdc8);
  DcuCmdSend = ABSOLUTE(0x10fdcc);
  flush_dcache = ABSOLUTE(0x10fdd0);
  flushinv_dcache = ABSOLUTE(0x10fdd4);
  sfc_suspend = ABSOLUTE(0x10fdd8);
  sfc_resume = ABSOLUTE(0x10fddc);
  sfc_drop_cache = ABSOLUTE(0x10fde0);
  chip_crc16 = ABSOLUTE(0x10fde4);
  CrcDecode = ABSOLUTE(0x10fde8);
  mask_init = ABSOLUTE(0x10fdec);
  clr_wdt = ABSOLUTE(0x10fdf0);
  nvram_set_boot_state = ABSOLUTE(0x10fdf4);
  chip_reset = ABSOLUTE(0x10fdf8);
  the_debug_isr = ABSOLUTE(0x10fdfc);
  print = ABSOLUTE(0x10fe00);
  sprintf = ABSOLUTE(0x10fe04);
  printf = ABSOLUTE(0x10fe08);
  puts = ABSOLUTE(0x10fe0c);
  doe = ABSOLUTE(0x10fe10);
  spi_get_port = ABSOLUTE(0x10fe14);
  _pll_init = ABSOLUTE(0x10fe18);
  flash_poweron = ABSOLUTE(0x10fe1c);
  spi_unmount = ABSOLUTE(0x10fe20);
  spi_port_io_init = ABSOLUTE(0x10fe24);
  LZ4_setStreamDecode = ABSOLUTE(0x10fe28);
  LZ4_decompress_safe_continue = ABSOLUTE(0x10fe2c);
  LZ4_decompress_generic = ABSOLUTE(0x10fe30);
  g_hash_function = ABSOLUTE(0x10fe34);
  f1_hash_function = ABSOLUTE(0x10fe38);
  f2_hash_function = ABSOLUTE(0x10fe3c);
  f3_hash_function = ABSOLUTE(0x10fe40);
  h2_hash_function = ABSOLUTE(0x10fe44);
  h3_hash_function = ABSOLUTE(0x10fe48);
  h4_hash_function = ABSOLUTE(0x10fe4c);
  h5_hash_function = ABSOLUTE(0x10fe50);
  g_function = ABSOLUTE(0x10fe54);
  f1_function = ABSOLUTE(0x10fe58);
  f2_function = ABSOLUTE(0x10fe5c);
  f3_function = ABSOLUTE(0x10fe60);
  sha256Compute = ABSOLUTE(0x10fe64);
  uECC_compute_public_key = ABSOLUTE(0x10fe68);
  uECC_shared_secret = ABSOLUTE(0x10fe6c);
  bi_initialize = ABSOLUTE(0x10fe70);
  bi_read_from_byte = ABSOLUTE(0x10fe74);
  bi_poly_mod2 = ABSOLUTE(0x10fe78);
  bi_poly_mul = ABSOLUTE(0x10fe7c);
  trim = ABSOLUTE(0x10fe80);
  bi_wirte_to_byte = ABSOLUTE(0x10fe84);
  bi_free = ABSOLUTE(0x10fe88);
  bi_terminate = ABSOLUTE(0x10fe8c);
  design_hp = ABSOLUTE(0x10fe90);
  design_lp = ABSOLUTE(0x10fe94);
  design_pe = ABSOLUTE(0x10fe98);
  eq_cos_sin = ABSOLUTE(0x10fe9c);
  eq_exp = ABSOLUTE(0x10fea0);
  eq_db2mag = ABSOLUTE(0x10fea4);
  eq_sqrt = ABSOLUTE(0x10fea8);
  eq_stable_check = ABSOLUTE(0x10feac);
  sf_sin_tab1 = ABSOLUTE(0x10feb0);
  get_cvsd_codec_ops = ABSOLUTE(0x10feb4);
  B_fir_cal_s = ABSOLUTE(0x10feb8);
  B_array_vol = ABSOLUTE(0x10febc);
  B_Syn_filt = ABSOLUTE(0x10fec0);
  B_Residu = ABSOLUTE(0x10fec4);
  B_comput_correlataionS = ABSOLUTE(0x10fec8);
  B_iircal = ABSOLUTE(0x10fecc);
  get_g729dec_ops = ABSOLUTE(0x10fed0);
  firfft = ABSOLUTE(0x10fed4);
  firifft = ABSOLUTE(0x10fed8);
  iCos_Tab = ABSOLUTE(0x10f710);
  _rfifft_wrap = ABSOLUTE(0x10fedc);
  _rififft_wrap = ABSOLUTE(0x10fee0);
  fCos_Tab = ABSOLUTE(0x10f714);
  flrfft = ABSOLUTE(0x10fee4);
  flrifft = ABSOLUTE(0x10fee8);
  _rflfft_wrap = ABSOLUTE(0x10feec);
  _riflfft_wrap = ABSOLUTE(0x10fef0);
  logAprx_CORDIC_float = ABSOLUTE(0x10fef4);
  expAprx_CORDIC_float = ABSOLUTE(0x10fef8);
  magnAprx_float = ABSOLUTE(0x10fefc);
  MatrixCopy_float_c_c = ABSOLUTE(0x10ff00);
  MatrixCopy_float_f_f = ABSOLUTE(0x10ff04);
  MatrixEwMulAndSumOneDim_float_c_c_c_s0 = ABSOLUTE(0x10ff08);
  MatrixEwMulAndSumOneDim_float_c_c_c_s1 = ABSOLUTE(0x10ff0c);
  MatrixEwMulAndSumOneDim_float_f_f_f_s0 = ABSOLUTE(0x10ff10);
  MatrixEwMulAndSumOneDim_float_f_f_f_s1 = ABSOLUTE(0x10ff14);
  MatrixEwConjMulAndSumOneDim_float_c_c_c_s0 = ABSOLUTE(0x10ff18);
  MatrixEwConjMulAndSumOneDim_float_c_c_c_s1 = ABSOLUTE(0x10ff1c);

  VecOverShift_s16_f32 = ABSOLUTE(0x10ff24);
  VecMinus_s16_f32_f32 = ABSOLUTE(0x10ff28);
  VectorCopy_f32_s16 = ABSOLUTE(0x10ff2c);
  VecEleMul_s16_s16_f32 = ABSOLUTE(0x10ff30);
  VecEleMul_f32_s16_f32 = ABSOLUTE(0x10ff34);
  VecMeanSq_float_f_f = ABSOLUTE(0x10ff38);
  VectorSet_float_f_f = ABSOLUTE(0x10ff3c);
  VecMagRecAve_float_c_f_f = ABSOLUTE(0x10ff40);
  VecMulScalar_float_c_f_c = ABSOLUTE(0x10ff44);
  VecConjEleMul_float_c_c_c = ABSOLUTE(0x10ff48);
  VecPlus_float_f_f_f = ABSOLUTE(0x10ff4c);
  VecDivide_float_c_f_c_f = ABSOLUTE(0x10ff50);
  VecPlus_float_c_c_c = ABSOLUTE(0x10ff54);
  VecConjMulRecAve_float_c_c_c_f = ABSOLUTE(0x10ff58);
  VecGetMag_float_c_f = ABSOLUTE(0x10ff5c);
  VecMax_float_f_f = ABSOLUTE(0x10ff60);
  VecRecAve_float_f_f_f = ABSOLUTE(0x10ff64);
  VecEleMul_float_f_f_f = ABSOLUTE(0x10ff68);
  VecMagAndDiv_float_c_f_f_f = ABSOLUTE(0x10ff6c);
  VecMin_float_f_f = ABSOLUTE(0x10ff70);
  VecMinus_float_f_f_f = ABSOLUTE(0x10ff74);
  VecMean_float_f_f = ABSOLUTE(0x10ff78);
  VecEleMul_float_c_f_c = ABSOLUTE(0x10ff7c);
  VecMeanSqu_float_c_f = ABSOLUTE(0x10ff80);
  VecCopy_float_f_f = ABSOLUTE(0x10ff84);
  VecMin_float_f_f_f = ABSOLUTE(0x10ff88);
  VecDivide_float_f_f_f_f = ABSOLUTE(0x10ff8c);
  VecCompBT_float_f_f_f = ABSOLUTE(0x10ff90);
  VecCondCopy_float_f_f_f = ABSOLUTE(0x10ff94);
  VecMulScalar_float_f_f_f = ABSOLUTE(0x10ff98);
  VecPlusScalar_float_f_f_f = ABSOLUTE(0x10ff9c);
  VecMinScalar_float_f_f_f = ABSOLUTE(0x10ffa0);
  VecOpposite_float_f_f = ABSOLUTE(0x10ffa4);
  VecEleMla_float_f_f_f = ABSOLUTE(0x10ffa8);
  VecEleMla_float_c_c_c = ABSOLUTE(0x10ffac);
  VecMinus_float_c_c_c = ABSOLUTE(0x10ffb0);
  VecDotProduct_float_f_f_f = ABSOLUTE(0x10ffb4);
  VecDotProduct_float_c_c_c = ABSOLUTE(0x10ffb8);
  VecDotProduct_float_c_f_c = ABSOLUTE(0x10ffbc);
  VecCopy_float_c_c = ABSOLUTE(0x10ffc0);
  VecCopy_float_f_c = ABSOLUTE(0x10ffc4);
  VecConjDotProduct_float_c_c_c = ABSOLUTE(0x10ffc8);
  VecNormalize_float_c_c_f = ABSOLUTE(0x10ffcc);
  VecRecAve_float_c_c_f = ABSOLUTE(0x10ffd0);
  VecOverlapShift_float_f_f_i = ABSOLUTE(0x10ffd4);
  VecMax_float_f_f_f = ABSOLUTE(0x10ffd8);
  VecConjEwMulAndDiv_float_c_c_f_f_c = ABSOLUTE(0x10ffdc);
  VecPlusMulScalar_float_c_c_f_c = ABSOLUTE(0x10ffe0);
  VecCondCopy_float_c_i_c = ABSOLUTE(0x10ffe4);
  VecEleMulAndDiv_float_f_f_f_f_f = ABSOLUTE(0x10ffe8);
  VectorSet_float_f_c = ABSOLUTE(0x10ffec);
  VecDivScalar_float_f_f_f = ABSOLUTE(0x10fff0);
  VecDivScalar_float_c_f_c = ABSOLUTE(0x10fff4);
  VecPlusScalar_float_c_f_c = ABSOLUTE(0x10fff8);
  VecMinScalar_float_c_f_c = ABSOLUTE(0x10fffc);
  STFT_Win_FixHalf_M512_D160 = ABSOLUTE(0x103804);
  STFT_Win_FixHalf_M256_D160 = ABSOLUTE(0x103c04);
  STFT_Win_FixHalf_M256_D80 = ABSOLUTE(0x103e04);
  STFT_Win_FixHalf_M128_D80 = ABSOLUTE(0x104004);
  WOLAAnalysisFilter_Float_M64_m4_r1 = ABSOLUTE(0x100004);
  WOLASynthesisFilter_Float_M64_m4_r1 = ABSOLUTE(0x100404);
  WOLAAnalysisFilter_Float_M128_m4_r1 = ABSOLUTE(0x100804);
  WOLASynthesisFilter_Float_M128_m4_r1 = ABSOLUTE(0x101004);
  WOLAAnalysisFilter_Float_M256_m4_r1 = ABSOLUTE(0x101804);
  WOLASynthesisFilter_Float_M256_m4_r1 = ABSOLUTE(0x102804);
  quantize_intervals_LF = ABSOLUTE(0x10c1ec);
  invert_quantize_dither_factors_LF = ABSOLUTE(0x10c2f0);
  quantize_dither_factors_LF = ABSOLUTE(0x10c3f4);
  quantize_factor_select_offset_LF = ABSOLUTE(0x10c4f8);
  hd_quantize_intervals_LF = ABSOLUTE(0x10c57c);
  boot_arg_list = ABSOLUTE(0x2bc04);
  _IRQ_MEM_ADDR = ABSOLUTE(0x2bf00);
  _MASK_MEM_BEGIN = ABSOLUTE(0x2bbe0);
  _MASK_MEM_SIZE = ABSOLUTE(0x308);

EXTERN(
_start

sbc_hw_decoder
msbc_hw_decoder

cvsd_decoder
pcm_decoder






mp3_decoder
g729_decoder



aac_decoder
cvsd_encoder
msbc_hw_encoder
);



UPDATA_SIZE = 0x80;
UPDATA_BEG = _MASK_MEM_BEGIN - UPDATA_SIZE;
UPDATA_BREDR_BASE_BEG = 0x2c000;

RAM_LIMIT_L = 0;
RAM_LIMIT_H = UPDATA_BEG;
PHY_RAM_SIZE = RAM_LIMIT_H - RAM_LIMIT_L;


ISR_BASE = _IRQ_MEM_ADDR;
ROM_RAM_SIZE = _MASK_MEM_SIZE;
ROM_RAM_BEG = _MASK_MEM_BEGIN;

RAM0_BEG = RAM_LIMIT_L;
RAM0_END = RAM_LIMIT_H;
RAM0_SIZE = RAM0_END - RAM0_BEG;



EQ_PRIV_COEFF_BASE = 0x02E7A0;
EQ_PRIV_SECTION_NUM = 10;
EQ_PRIV_COEFF_END = EQ_PRIV_COEFF_BASE + 4 * EQ_PRIV_SECTION_NUM * 14;
CODE_BEG = 0x1e00100;

MEMORY
{
 code0(rx) : ORIGIN = CODE_BEG, LENGTH = 0x100000
 ram0(rwx) : ORIGIN = RAM0_BEG, LENGTH = RAM0_SIZE
}


ENTRY(_start)

SECTIONS
{
    . = ORIGIN(code0);
    .text ALIGN(4):
    {
        PROVIDE(text_rodata_begin = .);

        *(.entry_text)
        *(.startup.text)

        bank_stub_start = .;
        *(.bank.stub.*)
        bank_stub_size = . - bank_stub_start;

  *(.text)

        . = ALIGN(4);

        lcd_interface_begin = .;
        KEEP(*(.lcd_if_info))
        lcd_interface_end = .;

  ui_style_begin = .;
  KEEP(*(.ui_style))
  ui_style_end = .;


        elm_event_handler_begin_JL = .;
        KEEP(*(.elm_event_handler_JL))
  elm_event_handler_end_JL = .;

        elm_event_handler_begin_UPGRADE = .;
        KEEP(*(.elm_event_handler_UPGRADE))
        elm_event_handler_end_UPGRADE = .;



  elm_event_handler_begin_DIAL = .;
        KEEP(*(.elm_event_handler_DIAL))
  elm_event_handler_end_DIAL = .;


  control_event_handler_begin = .;
        KEEP(*(.control_event_handler))
  control_event_handler_end = .;

        control_ops_begin = .;
        KEEP(*(.control_ops))
        control_ops_end = .;

        battery_notify_begin = .;
        *(.battery_notify)
        battery_notify_end = .;

  *(.LOG_TAG_CONST*)
        *(.rodata*)
        *(.fat_data_code_ex)

  . = ALIGN(4);
        PROVIDE(text_rodata_end = .);

        clock_critical_handler_begin = .;
        KEEP(*(.clock_critical_txt))
        clock_critical_handler_end = .;

        gsensor_dev_begin = .;
        KEEP(*(.gsensor_dev))
        gsensor_dev_end = .;

        fm_dev_begin = .;
        KEEP(*(.fm_dev))
        fm_dev_end = .;

        fm_emitter_dev_begin = .;
        KEEP(*(.fm_emitter_dev))
        fm_emitter_dev_end = .;

  . = ALIGN(4);
  tool_interface_begin = .;
  KEEP(*(.tool_interface))
  tool_interface_end = .;


        storage_device_begin = .;
        KEEP(*(.storage_device))
        storage_device_end = .;

        . = ALIGN(4);
        __VERSION_BEGIN = .;
        KEEP(*(.sys.version))
        __VERSION_END = .;

        *(.noop_version)

  . = ALIGN(4);
        _SPI_CODE_START = . ;
        *(.spi_code)
  . = ALIGN(4);
        _SPI_CODE_END = . ;
  . = ALIGN(4);

  . = ALIGN(32);
  m_code_addr = . ;
  *(.m.code*)
  *(.movable.code*)
   m_code_size = ABSOLUTE(. - m_code_addr) ;
  . = ALIGN(32);

        MEDIA_CODE_BEGIN = .;


  . = ALIGN(4);
        media_text_start = .;

  . = ALIGN(4);
        *(.dns_16k_data)
        *(.dns_8k_data)
  *(.jlsp_const)
  *(.jlsp_code)
     anc_code_begin = .;
  *(.anc_code)
  *(.anc_const)
  *(.anc_user_code)
  *(.anc_user_const)
  *(.anc_box_code)
  *(.anc_box_const)
  *(.anc_btspp_code)
  *(.anc_btspp_const)
  *(.anc_debug_code)
  *(.anc_debug_const)
     anc_code_end = .;
  anc_code_size = anc_code_end - anc_code_begin;

  *(.ns_sparse_code )
  *(.aec_sparse_code)
  *(.nlp_sparse_code)
  *(.der_sparse_code)
  *(.qmf_sparse_code)
  *(.bt_audioplc_code)
  *(.bt_audioplc_sparse_code)
  *(.bt_audioplc_const)
  *(.lf_audioplc_code)
  *(.lf_audioplc_sparse_code)
  *(.lf_audioplc_const)
  *(.dms_sparse_code)

  . = ALIGN(4);
        *(.pcm_code)
        *(.pcm_const)

        *(.cvsd_code)
        *(.cvsd_const)

        *(.g729_code)
        *(.g729_const)
  *(.wtgv2_code)
  *(.wtgv2_const)
  *(.wtgv2dec_code)
  *(.wtgv2dec_const)
  *(.wtgv2dec_str)
  *(.wtg_decv2_sparse_code)
        *(.mp3_code)
        *(.mp3_const)
        *(.mp3_dec_code)
        *(.mp3_dec_const)
        *(.mp3_dec_sparse_code)

        *(.mp3_decstream_code)
        *(.mp3_decstream_const)
        *(.mp3_decstream_sparse_code)

        *(.mp3tsy_dec_code)
 *(.mty_code)
 *(.mp3tsy_dec_sparse_code)
 *(.mp3tsy_dec_const)

  *( .wtg_dec_code )
        *( .wtg_dec_const)
        *( .wtg_dec_sparse_code)

  *(.msbc_code)
  *(.msbc_const)


  *(.sbc_code)
  *(.sbc_const)
        *(.sbc_msbc_code)
        *(.sbc_msbc_const)
 *(.speex_encoder_code)
 *(.opus_encoder_code)
        *(.adpcm_encode_sparse_code)
        *(.adpcm_encode_code)
        *(.adpcm_encode_const)
        *(.lc3_decoder_code)
        *(.lc3_decoder_const)
        *(.sbc_encoder_code)


  *(.sine_code)
  *(.sine_const)
        *(.wav_code)
        *(.wav_const)
  *(.wav_dec_code)
  *(.wav_dec_const)
  *(.wav_dec_sparse_code)
  *(.wav_dec_sparse_const)


        *(.aac_code)
        *(.aac_const)
  *(.amr_code)
  *(.amr_const)


  *(.audio_decoder_code)
  *(.audio_decoder_const)
        *(.audio_track_const)
        *(.audio_track_code)
  *(.media_device_code)
  *(.media_device_const)
  *(.audio_encoder_code)
  *(.audio_encoder_const)
  *(.mixer_code)
  *(.mixer_const)
  *(.dec_server_code)
  *(.dec_server_const)
  *(.rec_server_code)
  *(.rec_server_const)
  *(.auto_mute_code)
  *(.auto_mute_const)
  *(.plc_code)
  *(.plc_const)
  *(.wireless_sync_code)
  *(.wireless_sync_const)
  *(.sbc_eng_code)
  *(.sbc_eng_const)

  *(.audio_codec_code)

  *(.bt_compressor_sparse_const)
  *(.bt_compressor_sparse_code)
  *(.compressor_sparse_code)
  *(.compressor_sparse_const)

  *(.bt_limiter_sparse_const)
  *(.bt_limiter_sparse_code)
  *(.limiter_sparse_code)
  *(.limiter_sparse_const)

  *(.bt_crossOver_sparse_const)
  *(.bt_crossOver_sparse_code)
  *(.crossOver_sparse_code)
  *(.crossOver_sparse_const)
  . = ALIGN(4);
     _audio_decoder_begin = .;
     PROVIDE(audio_decoder_begin = .);
     KEEP(*(.audio_decoder))
     _audio_decoder_end = .;
     PROVIDE(audio_decoder_end = .);

     _audio_encoder_begin = .;
     PROVIDE(audio_encoder_begin = .);
     KEEP(*(.audio_encoder))
     _audio_encoder_end = .;
     PROVIDE(audio_encoder_end = .);

     _audio_package_begin = .;
     PROVIDE(audio_package_begin = .);
     KEEP(*(.audio_package))
     _audio_package_end = .;
     PROVIDE(audio_package_end = .);

     _audio_dev_begin = .;
     PROVIDE(audio_dev_begin = .);
     KEEP(*(.audio_device))
     _audio_dev_end = .;
     PROVIDE(audio_dev_end = .);

     _audio_hwaccel_begin = .;
     PROVIDE(audio_hwaccel_begin = .);
     KEEP(*(.audio_hwaccel))
     _audio_hwaccel_end = .;
     PROVIDE(audio_hwaccel_end = .);

  . = ALIGN(4);
     media_code_begin = .;
         *(.media.*.text)
  . = ALIGN(4);

  *(.app_audio_code)
  *(.app_audio_const)

  *(.compressor_code)
  *(.compressor_const)
  *(.bt_compressor_const)
  *(.bt_compressor_code)

  *(.crossOver_code)
  *(.crossOver_const)
  *(.bt_crossOver_const)
  *(.bt_crossOver_code)

  *(.limiter_code)
  *(.limiter_const)
  *(.bt_limiter_const)
  *(.bt_limiter_code)
        *(.drc_const)
  *(.drc_code)
  *(.drc_sparse_code)
  *(.drc_sparse_const)
 . = ALIGN(4);
  *(.sur_cal_const)
  *(.sur_cal_code)
 . = ALIGN(4);
 *(.lib_pitchshift_code)
 *(.lib_pitchshift_const)
 . = ALIGN(4);

     *(.resample_fastcal_sparse_code)
            *(.resample_fastcal_code)
            *(.resample_fastcal_const)
     . = ALIGN(4);

     media_code_end = .;
  . = ALIGN(4);
  media_code_size = media_code_end - media_code_begin;

  . = ALIGN(4);
        media_text_end = .;


        . = ALIGN(4);
        aac_dec_code_begin = .;
        *(.bt_aac_dec_code)
        *(.bt_aac_dec_sparse_code)
        aac_dec_code_end = .;
        aac_dec_code_size = aac_dec_code_end - aac_dec_code_begin ;


        *(.app_tone_code)
        *(.app_tone_const)

        *(.app_aec_code)
        *(.app_aec_const)


        *(.opcore_table_maskrom)
        *(.bfilt_table_maskroom)
        *(.opcore_maskrom)
        *(.bfilt_code)
        *(.bfilt_const)

  . = ALIGN(4);
        MEDIA_CODE_SIZE = . - MEDIA_CODE_BEGIN;

        *(.audio_decoder_code)
        *(.audio_decoder_const)






        SYSTEM_CODE_BEGIN = .;


  . = ALIGN(4);
        system_text_start = .;

   _device_node_begin = .;
     PROVIDE(device_node_begin = .);
     KEEP(*(.device))
     _device_node_end = .;
     PROVIDE(device_node_end = .);

  config_target_begin = .;
     PROVIDE(config_target_begin = .);
     KEEP(*(.config_target))
  config_target_end = .;
     PROVIDE(config_target_end = .);

     system_code_begin = .;
     KEEP(*(.system.*.text))
     system_code_end = .;
  . = ALIGN(4);
  system_code_size = system_code_end - system_code_begin;

  vfs_ops_begin = .;
  KEEP(*(.vfs_operations))
  vfs_ops_end = .;

     _lib_version_begin = .;
     PROVIDE(lib_version_begin = .);
     KEEP(*(.lib_version))
     _lib_version_end = .;
     PROVIDE(lib_version_end = .);

  _initcall_begin = .;
  PROVIDE(initcall_begin = .);
     KEEP(*(.initcall))
  _initcall_end = .;
  PROVIDE(initcall_end = .);

  _early_initcall_begin = .;
  PROVIDE(early_initcall_begin = .);
  KEEP(*(.early.initcall))
  _early_initcall_end = .;
  PROVIDE(early_initcall_end = .);

  _late_initcall_begin = .;
  PROVIDE(late_initcall_begin = .);
  KEEP(*(.late.initcall))
  _late_initcall_end = .;
  PROVIDE(late_initcall_end = .);

  _platform_initcall_begin = .;
  PROVIDE(platform_initcall_begin = .);
  KEEP(*(.platform.initcall))
  _platform_initcall_end = .;
  PROVIDE(platform_initcall_end = .);

  _module_initcall_begin = .;
  PROVIDE(module_initcall_begin = .);
  KEEP(*(.module.initcall))
  _module_initcall_end = .;
  PROVIDE(module_initcall_end = .);

  _sys_event_handler_begin = .;
  PROVIDE(sys_event_handler_begin = .);
  KEEP(*(.sys_event.4.handler))
  KEEP(*(.sys_event.3.handler))
  KEEP(*(.sys_event.2.handler))
  KEEP(*(.sys_event.1.handler))
  KEEP(*(.sys_event.0.handler))
  _sys_event_handler_end = .;
  PROVIDE(sys_event_handler_end = .);

  _syscfg_arg_begin = .;
  PROVIDE(syscfg_arg_begin = .);
  KEEP(*(.syscfg.arg))
  _syscfg_arg_end = .;
  PROVIDE(syscfg_arg_end = .);

  _syscfg_handler_begin = .;
  PROVIDE(syscfg_handler_begin = .);
  KEEP(*(.syscfg.handler))
  _syscfg_handler_end = .;
  PROVIDE(syscfg_handler_end = .);

  _syscfg_ops_begin = .;
  PROVIDE(syscfg_ops_begin = .);
  KEEP(*(.syscfg.2.ops))
  KEEP(*(.syscfg.1.ops))
  KEEP(*(.syscfg.0.ops))
  _syscfg_ops_end = .;
  PROVIDE(syscfg_ops_end = .);

  _server_info_begin = .;
  PROVIDE(server_info_begin = .);
  KEEP(*(.server_info))
  _server_info_end = .;
  PROVIDE(server_info_end = .);

  _bus_device_begin = .;
  PROVIDE(bus_device_begin = .);
  KEEP(*(.bus_device))
  _bus_device_end = .;
  PROVIDE(bus_device_end = .);

     _sys_power_hal_ops_begin = .;
     PROVIDE(sys_power_hal_ops_begin = .);
     KEEP(*(.sys_power_hal_ops))
     _sys_power_hal_ops_end = .;
     PROVIDE(sys_power_hal_ops_end = .);


  . = ALIGN(4);
     lp_target_begin = .;
     PROVIDE(lp_target_begin = .);
     KEEP(*(.lp_target))
     lp_target_end = .;
     PROVIDE(lp_target_end = .);

  . = ALIGN(4);
        deepsleep_target_begin = .;
        PROVIDE(deepsleep_target_begin = .);
        KEEP(*(.deepsleep_target))
        deepsleep_target_end = .;
        PROVIDE(deepsleep_target_end = .);

     crypto_begin = .;
     *(.crypto_ecdh_code)
     *(.crypto_ecdh_const)

     *(.crypto_bigint_code)
     *(.crypto_bigint_const)

     *(.crypto_code)
     *(.crypto_const)

     *(.ECDH_sample_code)
     *(.ECDH_sample_const)

     *(.uECC_code)
     *(.uECC_const)

     *(.hmac_code)
     *(.hmac_const)

     *(.hash_sample_code)
     *(.hash_sample_const)

     *(.aes_cmac_sample_code)
     *(.aes_cmac_sample_const)
     crypto_end = .;
     crypto_size = . - crypto_begin;

        *(.mem_code)
        *(.mem_const)

        *(.os_port_code)
        *(.os_port_const)

        __movable_function_start = .;
        *(movable.text.*);
        *(movable.stub.*);
        *(movable.region.*);

        __movable_function_end = .;
        __movable_function_size = __movable_function_end - __movable_function_start;

        system_text_end = .;



        system_code_total_size = system_text_end - system_text_start;
 . = ALIGN(4);
        SYSTEM_CODE_SIZE = . - SYSTEM_CODE_BEGIN;

  . = ALIGN(4);
     update_target_begin = .;
     PROVIDE(update_target_begin = .);
     KEEP(*(.update_target))
     update_target_end = .;
     PROVIDE(update_target_end = .);
  . = ALIGN(4);


  . = ALIGN(32);

   } > code0

    . = ORIGIN(ram0);

    .mmu_tlb ALIGN(0x4000):
    {
        *(.mmu_tlb_segment);
    } > ram0

 .boot_info ALIGN(32):
 {
  *(.boot_info)
        . = ALIGN(32);
 } > ram0

 .irq_stack ALIGN(32):
    {
  *(.stack_magic)
        _cpu0_sstack_begin = .;
        PROVIDE(cpu0_sstack_begin = .);
        *(.stack)
        _cpu0_sstack_end = .;
        PROVIDE(cpu0_sstack_end = .);
     _stack_end = . ;
  *(.stack_magic0)
  . = ALIGN(4);

    } > ram0

 .data ALIGN(32):
 {

        . = ALIGN(4);
        *(.data_magic)

        *(.data*)

  . = ALIGN(4);


 . = ALIGN(4);
 audio_sync_data_begin = .;
        *(.audio_sync_data)
 audio_sync_data_end = .;
 . = ALIGN(4);
 *(.jlsp_data)

    *(.sbc_data)
    *(.sbc_msbc_data)
    *(.msbc_data)
    *(.cvsd_data)
    *(.aac_data)
 *(.sbc_eng_data)
 *(.bt_audioplc_data)
    *(.lc3_decoder_data)





    *(.wtgv2_data)
    *(.wtgv2dec_data)
 *(.mp3tsy_dec_data)
 *(.mp3tsy_data)
        *(.sbc_encoder_data)

    *(.anc_data)
    *(.anc_user_data)
    *(.anc_box_data)
    *(.anc_btspp_data)
    *(.anc_debug_data)

 *(.sms_data)
 *(.audio_track_data)

  . = ALIGN(4);


  . = ALIGN(4);
        system_data_start = .;

  _video_subdev_begin = .;
  PROVIDE(video_subdev_begin = .);
  KEEP(*(.video_subdev.0))
  KEEP(*(.video_subdev.1))
  KEEP(*(.video_subdev.2))
  KEEP(*(.video_subdev.3))
  KEEP(*(.video_subdev.4))
  KEEP(*(.video_subdev.5))
  _video_subdev_end = .;
  PROVIDE(video_subdev_end = .);

  _audio_subdev_begin = .;
  PROVIDE(audio_subdev_begin = .);
  KEEP(*(.audio_subdev.0))
  KEEP(*(.audio_subdev.1))
  KEEP(*(.audio_subdev.2))
  KEEP(*(.audio_subdev.3))
  _audio_subdev_end = .;
  PROVIDE(audio_subdev_end = .);

  _iic_device_begin = .;
  PROVIDE(iic_device_begin = .);
  KEEP(*(.iic))
  _iic_device_end = .;
  PROVIDE(iic_device_end = .);

        _avin_spi_device_begin = .;
  PROVIDE(avin_spi_device_begin = .);
  KEEP(*(.sw_spi))
  _avin_spi_device_end = .;
  PROVIDE(avin_spi_device_end = .);

  _video_dev_begin = .;
  PROVIDE(video_dev_begin = .);
  KEEP(*(.video_device))
  _video_dev_end = .;
  PROVIDE(video_dev_end = .);

  _key_driver_ops_begin = .;
  PROVIDE(key_driver_ops_begin = .);
  KEEP(*(.key_driver_ops))
  _key_driver_ops_end = .;
  PROVIDE(key_driver_ops_end = .);

  _touch_driver_begin = .;
  PROVIDE(touch_driver_begin = .);
  KEEP(*(.touch_driver))
  _touch_driver_end = .;
  PROVIDE(touch_driver_end = .);

  _static_hi_timer_begin = .;
  PROVIDE(static_hi_timer_begin = .);
  KEEP(*(.hi_timer))
  _static_hi_timer_end = .;
  PROVIDE(static_hi_timer_end = .);

  _sys_cpu_timer_begin = .;
  PROVIDE(sys_cpu_timer_begin = .);
  KEEP(*(.sys_cpu_timer))
  _sys_cpu_timer_end = .;
  PROVIDE(sys_cpu_timer_end = .);

     _sys_config_begin = .;
     PROVIDE(sys_config_begin = .);
     KEEP(*(.sys_cfg))
     _sys_config_end = .;
     PROVIDE(sys_config_end = .);

     _sys_fat_begin = .;
     PROVIDE(sys_fat_begin = .);
     KEEP(*(.fs_fat))
     _sys_fat_end = .;
     PROVIDE(sys_fat_end = .);

  _app_begin = .;
  PROVIDE(app_begin = .);
  KEEP(*(.app))
  _app_end = .;
  PROVIDE(app_end = .);

  _os_begin = .;
  PROVIDE(os_begin = .);




     *(.os_str)
     *(.os_data)
  _os_end = .;
  PROVIDE(os_end = .);

     *(.crypto_ecdh_data)
     *(.crypto_data)

     *(.mem_data)
        *(.os_port_data)

     *(.uECC_data)
     *(.ECDH_sample_data)

         __movable_slot_start = .;
         *(movable.slot.*);
         __movable_slot_end = .;

        system_data_end = .;

  . = ALIGN(4);
 } > ram0

 .bss ALIGN(32):
    {
            *(.usb_ep0)
            *(.usb_msd_dma)
            *(.usb_hid_dma)
            *(.usb_iso_dma)
            *(.usb_cdc_dma)
            *(.uac_var)
            *(.usb_config_var)
            *(.cdc_var)

        . = ALIGN(4);


        system_bss_start = .;
        . = ALIGN(4);
        *(.os_bss)
        *(.mem_heap)
  *(.memp_memory_x)
        *(.mem_bss)
        *(.os_port_bss)

        *(.uECC_bss)
        *(.ECDH_sample_bss)

        system_bss_end = .;

        . = ALIGN(4);
        *(.bss)

        . = ALIGN(4);


 . = ALIGN(4);
 audio_sync_bss_begin = .;
        *(.audio_sync_bss)
 audio_sync_bss_end = .;
 . = ALIGN(4);
 *(.jlsp_bss)

    *(.sbc_msbc_bss)
    *(.cvsd_bss)
    *(.aac_bss)
 *(.sbc_eng_bss)
 *(.bt_audioplc_bss)
    *(.lc3_decoder_bss)




    *(.wtgv2_bss)
    *(.wtgv2dec_bss)
 *(.mp3tsy_dec_bss)
 *(.mp3tsy_bss)

    *(.anc_bss)
    *(.anc_user_bss)
    *(.anc_box_bss)
    *(.anc_btspp_bss)
    *(.anc_debug_bss)
 *(.audio_track_bss)

        . = ALIGN(4);

        *(.os_bss)
        *(.volatile_ram)
  *(.btstack_pool)

  *(.audio_buf)
        *(.src_filt)
        *(.src_dma)
        *(.mem_heap)
  *(.memp_memory_x)

        . = ALIGN(4);
  *(.non_volatile_ram)

        . = ALIGN(32);

    } > ram0

 .data_code ALIGN(32):
 {
        data_code_pc_limit_begin = .;
  *(.bank_critical_code)

        . = ALIGN(4);
    } > ram0

    .common ALIGN(32):
    {

        common_code_run_addr = .;
        *(.common*)

  *(.flushinv_icache)
        *(.cache)
        *(.volatile_ram_code)

        *(.os_critical_code)
  *(.os_code)
  *(.os_str)

        *(.fat_data_code)



        audio_sync_code_begin = .;
        *(.audio_sync_code)
        audio_sync_code_end = .;



       . = ALIGN(4);
    } > ram0






 __report_overlay_begin = .;
 overlay_code_begin = .;
 OVERLAY : AT(0x200000) SUBALIGN(4)
    {
  .overlay_aec
  {
            . = ALIGN(4);
   aec_code_begin = . ;
   *(.text._*)
   *(.data._*)
   *(.aec_code)
   *(.aec_const)
   *(.res_code)
   *(.res_const)
            *(.dns_common_data)
            *(.dns_param_data_single)
            *(.dns_param_data_dual)
   *(.ns_code)
   *(.ns_const)
   *(.fft_code)
   *(.fft_const)
   *(.nlp_code)
   *(.nlp_const)
   *(.der_code)
   *(.der_const)
   *(.qmf_code)
   *(.qmf_const)
   *(.aec_data)
   *(.res_data)
   *(.ns_data)
   *(.nlp_data)
         *(.der_data)
         *(.qmf_data)
         *(.fft_data)
   *(.dms_code)
   *(.dms_const)
   *(.dms_data)
   *(.agc_code)
   *(.bank_const)

            . = ALIGN(4);
   *(.aec_mux)
            . = ALIGN(4);
   aec_code_end = . ;
   aec_code_size = aec_code_end - aec_code_begin ;
  }

  .overlay_aac
  {
   . = ALIGN(4);
   bt_aac_dec_const_begin = .;
   *(.bt_aac_dec_const)
            *(.bt_aac_dec_sparse_const)
   . = ALIGN(4);
   bt_aac_dec_const_end = .;
   bt_aac_dec_const_size = bt_aac_dec_const_end - bt_aac_dec_const_begin ;

   *(.bt_aac_dec_data)
   . = ALIGN(4);
  }

    } > ram0


    .ram0_empty0 ALIGN(4) :
 {
        . = . + 4;
    } > ram0


 OVERLAY : AT(0x210000) SUBALIGN(4)
    {
  .overlay_aec_ram
  {
            . = ALIGN(4);
   *(.msbc_enc)
   *(.cvsd_codec)
   *(.aec_bss)
   *(.res_bss)
   *(.ns_bss)
   *(.nlp_bss)
         *(.der_bss)
         *(.qmf_bss)
         *(.fft_bss)
   *(.aec_mem)
   *(.dms_bss)
  }

  .overlay_aac_ram
  {
            . = ALIGN(4);
   *(.bt_aac_dec_bss)

   . = ALIGN(4);
   *(.aac_mem)
   *(.aac_ctrl_mem)


  }

  .overlay_mp3
  {
   *(.mp3_mem)
   *(.mp3_ctrl_mem)
   *(.mp3pick_mem)
   *(.mp3pick_ctrl_mem)
   *(.dec2tws_mem)
  }
  .overlay_wma
  {
   *(.wma_mem)
   *(.wma_ctrl_mem)
   *(.wmapick_mem)
   *(.wmapick_ctrl_mem)
  }
  .overlay_ape
        {
            *(.ape_mem)
            *(.ape_ctrl_mem)
  }
  .overlay_flac
        {
            *(.flac_mem)
            *(.flac_ctrl_mem)
  }
  .overlay_m4a
        {
            *(.m4a_mem)
            *(.m4a_ctrl_mem)
  }
  .overlay_amr
        {
            *(.amr_mem)
            *(.amr_ctrl_mem)
  }
  .overlay_dts
        {
            *(.dts_mem)
            *(.dts_ctrl_mem)
  }
  .overlay_fm
  {
   *(.fm_mem)
  }
        .overlay_pc
  {
            *(.usb_audio_play_dma)
            *(.usb_audio_rec_dma)
            *(.uac_rx)
            *(.mass_storage)

            *(.usb_ep0)
            *(.usb_msd_dma)
            *(.usb_hid_dma)
            *(.usb_iso_dma)
            *(.usb_cdc_dma)
            *(.uac_var)
            *(.usb_config_var)
            *(.cdc_var)
  }




    } > ram0


    bank_code_run_addr = .;

    OVERLAY : AT(0x300000) SUBALIGN(4)
    {
        .overlay_bank0
        {
            *(.bank.code.0*)
            *(.bank.const.0*)
            . = ALIGN(4);
        }
        .overlay_bank1
        {
            *(.bank.code.1*)
            *(.bank.const.1*)
            . = ALIGN(4);
        }
        .overlay_bank2
        {
            *(.bank.code.2*)
            *(.bank.const.2*)
            *(.bank.ecdh.*)
            . = ALIGN(4);
        }
        .overlay_bank3
        {
            *(.bank.code.3*)
            *(.bank.const.3*)
            *(.bank.enc.*)
            . = ALIGN(4);
        }
        .overlay_bank4
        {
            *(.bank.code.4*)
            *(.bank.const.4*)
            . = ALIGN(4);
        }
        .overlay_bank5
        {
            *(.bank.code.5*)
            *(.bank.const.5*)
            . = ALIGN(4);
        }
        .overlay_bank6
        {
            *(.bank.code.6*)
            *(.bank.const.6*)
            . = ALIGN(4);
        }
        .overlay_bank7
        {
            *(.bank.code.7*)
            *(.bank.const.7*)
            . = ALIGN(4);
        }
        .overlay_bank8
        {
            *(.bank.code.8*)
            *(.bank.const.8*)
            . = ALIGN(4);
        }
        .overlay_bank9
        {
            *(.bank.code.9*)
            *(.bank.const.9*)
            . = ALIGN(4);
        }
    } > ram0

 data_code_pc_limit_end = .;
 __report_overlay_end = .;

 _HEAP_BEGIN = . ;
 _HEAP_END = RAM0_END;
}


SECTIONS
{
    .data : ALIGN(4)
    {
        btstack_data_start = .;
        *(.bt_stack_data)
        *(.ble_db_data)
        *(.ble_sm_data)
        *(.ble_att_data)
        *(.ble_gatt_data)


        BTSTACK_LE_HOST_MESH_DATA_START = .;
  . = (. +3) & ~ 3;
        _net_buf_pool_list = .;
        *(._net_buf_pool.static.*)

        *(.ble_mesh_data)
        *(.ble_mesh_tinycrypt_data)
        BTSTACK_LE_HOST_MESH_DATA_SIZE = ABSOLUTE(. - BTSTACK_LE_HOST_MESH_DATA_START);

        btstack_data_end = .;

    } > ram0

    .bss (NOLOAD) :ALIGN(4)
    {
        btstack_bss_start = .;
        *(.bt_stack_bss)
        *(.ble_db_bss)
        *(.ble_sm_bss)
        *(.ble_att_bss)
        *(.ble_gatt_bss)
        *(.btstack_pool)


        BTSTACK_LE_HOST_MESH_BSS_START = .;
        *(.ble_mesh_bss)
        *(.ble_mesh_tinycrypt_bss)
        BTSTACK_LE_HOST_MESH_BSS_SIZE = ABSOLUTE(. - BTSTACK_LE_HOST_MESH_BSS_START);

        btstack_bss_end = .;
    } > ram0

    .text : ALIGN(4)
    {
        btstack_code_start = .;

        . = ALIGN(4);

        a2dp_source_media_codec_begin = .;
        KEEP(*(.a2dp_source_media_codec))
            a2dp_source_media_codec_end = .;
        a2dp_sink_media_probe_begin = .;
        KEEP(*(.a2dp_sink_media_probe))
            a2dp_sink_media_probe_end = .;

        a2dp_sink_media_codec_begin = .;
        KEEP(*(.a2dp_sink_media_codec))
            a2dp_sink_media_codec_end = .;

        a2dp_event_handler_begin = .;
        KEEP(*(.a2dp_event_handler))
            a2dp_event_handler_end = .;

        sdp_record_item_begin = .;
        KEEP(*(.sdp_record_item))
            sdp_record_item_end = .;

        bt_sleep_begin = .;
        KEEP(*(.bt_sleep))
            bt_sleep_end = .;

  *(.bt_stack_const)
  *(.bt_stack_code)
        *(.ble_db_const)
        *(.ble_db_code)
        *(.ble_sm_const)
        *(.ble_sm_code)
        *(.ble_att_const)
        *(.ble_att_code)
        *(.ble_gatt_const)
        *(.ble_gatt_code)


        BTSTACK_LE_HOST_MESH_CODE_START = .;
        *(.ble_mesh_code)
        *(.ble_mesh_tinycrypt_code)

        *(.ble_mesh_const)
        *(.ble_mesh_tinycrypt_const)
        BTSTACK_LE_HOST_MESH_CODE_SIZE = ABSOLUTE(. - BTSTACK_LE_HOST_MESH_CODE_START);

        btstack_code_end = .;
  . = ALIGN(4);
    } > code0
}

BTSTACK_LE_HOST_MESH_RAM_TOTAL = BTSTACK_LE_HOST_MESH_DATA_SIZE + BTSTACK_LE_HOST_MESH_BSS_SIZE;
BTSTACK_LE_HOST_MESH_FLASH_TOTAL = BTSTACK_LE_HOST_MESH_CODE_SIZE;

BTSTACK_CODE_SIZE = (btstack_code_end - btstack_code_start) + (btstack_data_end - btstack_data_start);
SECTIONS
{
    .data : ALIGN(4)
    {
        btctler_data_start = .;

        BTCTLER_CONTROLLER_DATA_START = .;
        *(.bt_rf_data)
  *(.vendor_manager_data)
  *(.device_manager_data)
  *(.hci_controller_data)
  *(.hci_interface_data)
        BTCTLER_CONTROLLER_DATA_SIZE = ABSOLUTE(. - BTCTLER_CONTROLLER_DATA_START);

        BTCTLER_LE_CONTROLLER_DATA_START = .;
        *(.ble_ll_data)
        *(.ble_hci_data)
        *(.classic_hci_data)
        *(.ble_rf_data)
        BTCTLER_LE_CONTROLLER_DATA_SIZE = ABSOLUTE(. - BTCTLER_LE_CONTROLLER_DATA_START);

        BTCTLER_CL_DATA_START = .;
        *(.classic_lmp_data)
        *(.classic_lmp_auth_data)
        *(.classic_lmp_bigint_data)
        *(.classic_lmp_crypt_data)
        *(.classic_lmp_ecdh_data)
        *(.classic_lmp_linkbulk_data)
        *(.classic_lmp_hmac_data)
        *(.classic_rf_data)
        *(.classic_bb_data)
        BTCTLER_CL_DATA_SIZE = ABSOLUTE(. - BTCTLER_CL_DATA_START);

        btctler_data_end = .;

    } > ram0

    .bss (NOLOAD) :ALIGN(4)
    {
        btctler_bss_start = .;

        BTCTLER_CONTROLLER_BSS_START = .;

        *(.bd_base)
        *(.bredr_rxtx_bulk)
        acl_tx_pool = .;
        *(.bredr_tx_bulk)

        acl_tx_pool_end = acl_tx_pool + (4 * 1024);



        . = acl_tx_pool_end;

        acl_rx_pool = .;
        *(.bredr_rx_bulk)

        acl_rx_pool_end = acl_rx_pool + (14 * 1024);





        tws_bulk_pool = .;



        tws_bulk_pool_end = tws_bulk_pool;

        . = tws_bulk_pool_end;

        *(.bt_rf_bss)
  *(.hci_controller_bss)
  *(.hci_interface_bss)
  *(.device_manager_bss)
  *(.vendor_manager_bss)
        BTCTLER_CONTROLLER_BSS_SIZE = ABSOLUTE(. - BTCTLER_CONTROLLER_BSS_START);

        BTCTLER_LE_CONTROLLER_BSS_START = .;
        *(.ble_hci_bss)
        *(.ble_ll_bss)
        *(.ble_rf_bss)
        BTCTLER_LE_CONTROLLER_BSS_SIZE = ABSOLUTE(. - BTCTLER_LE_CONTROLLER_BSS_START);

        BTCTLER_CL_BSS_START = .;
        *(.classic_rf_bss)
        *(.classic_lmp_bss)
        *(.classic_lmp_auth_bss)
        *(.classic_lmp_bigint_bss)
        *(.classic_lmp_crypt_bss)
        *(.classic_lmp_ecdh_bss)
        *(.classic_lmp_linkbulk_bss)
        *(.classic_lmp_hmac_bss)
        *(.classic_bb_bss)
        *(.classic_hci_bss)
        BTCTLER_CL_BSS_SIZE = ABSOLUTE(. - BTCTLER_CL_BSS_START);

        btctler_bss_end = .;
    } > ram0

    .text : ALIGN(4)
    {
        btctler_code_start = .;

        BTCTLER_CONTROLLER_CODE_START = .;
  *(.bt_rf_const)
  *(.bt_rf_code)
  *(.vendor_manager_const)
  *(.vendor_manager_code)
  *(.device_manager_const)
  *(.device_manager_code)
  *(.hci_controller_const)
  *(.hci_controller_code)
  *(.hci_interface_const)
  *(.hci_interface_code)
        BTCTLER_CONTROLLER_CODE_SIZE = ABSOLUTE(. - BTCTLER_CONTROLLER_CODE_START);

        BTCTLER_LE_CONTROLLER_CODE_START = .;
        *(.ble_rf_const)
        *(.ble_rf_code)

     *(.ble_ll_const)
     *(.ble_ll_code)
  *(.ble_hci_const)
  *(.ble_hci_code)
  *(.classic_hci_const)
  *(.classic_hci_code)
        BTCTLER_LE_CONTROLLER_CODE_SIZE = ABSOLUTE(. - BTCTLER_LE_CONTROLLER_CODE_START);

        BTCTLER_CL_CODE_START = .;
        *(.bredr_irq)
        *(.bredr_irq_code)
        *(.bredr_irq_const)

        *(.classic_lmp_const)
        *(.classic_lmp_auth_const)
        *(.classic_lmp_bigint_const)
        *(.classic_lmp_crypt_const)
        *(.classic_lmp_ecdh_const)
        *(.classic_lmp_hmac_const)
        *(.classic_lmp_code)
        *(.classic_lmp_auth_code)
        *(.classic_lmp_bigint_code)
        *(.classic_lmp_crypt_code)
        *(.classic_lmp_ecdh_code)
        *(.classic_lmp_hmac_code)
        *(.classic_rf_const)
        *(.classic_rf_code)
        *(.classic_bb_const)
        *(.classic_bb_code)
        BTCTLER_CL_CODE_SIZE = ABSOLUTE(. - BTCTLER_CL_CODE_START);


        *(.classic_tws_const)
        *(.classic_tws_code)
        *(.classic_tws_code.esco)

        btctler_code_end = .;

    } > code0


 .common ALIGN(32):



 {

        btctler_ram_code_start = .;

  . = ALIGN(4);

        *(.lmp_irq_code)
        *(.link_bulk_code)
        *(.frame_irq_code)

  . = ALIGN(4);
        *(.link_task_const)
        *(.link_task_code)

  . = ALIGN(4);
        *(.classic_irq_const)
        *(.classic_irq_code)


  . = ALIGN(4);
        *(.tws_irq_code)

  . = ALIGN(4);
        tws_sync_call_begin = .;
        KEEP(*(.tws_sync_call))
        tws_sync_call_end = .;

  . = ALIGN(4);
        tws_func_stub_begin = .;
        KEEP(*(.tws_func_stub))
        tws_func_stub_end = .;

        *(.tws_media_sync_code)
        *(.tws_media_sync_const)

        *(.tws_data_forward_code)
        *(.tws_data_forward_const)

  . = ALIGN(4);
        tws_sync_channel_begin = .;
        KEEP(*(.tws_sync_channel.0))
        KEEP(*(.tws_sync_channel.1))
        KEEP(*(.tws_sync_channel.2))
        KEEP(*(.tws_sync_channel.3))
        KEEP(*(.tws_sync_channel.4))
        KEEP(*(.tws_sync_channel.5))
        KEEP(*(.tws_sync_channel.6))
        KEEP(*(.tws_sync_channel.7))
        KEEP(*(.tws_sync_channel.8))
        KEEP(*(.tws_sync_channel.9))
        KEEP(*(.tws_sync_channel.10))
        KEEP(*(.tws_sync_channel.11))
        KEEP(*(.tws_sync_channel.12))
        KEEP(*(.tws_sync_channel.13))
        KEEP(*(.tws_sync_channel.14))
        KEEP(*(.tws_sync_channel.15))
        tws_sync_channel_end = .;

        btctler_ram_code_end = .;

  . = ALIGN(4);


    } > ram0







    BTCTLER_LE_RAM_TOTAL = BTCTLER_LE_CONTROLLER_DATA_SIZE + BTCTLER_LE_CONTROLLER_BSS_SIZE;
    BTCTLER_LE_CODE_TOTAL = BTCTLER_LE_CONTROLLER_CODE_SIZE;

    BTCTLER_CL_RAM_TOTAL = BTCTLER_CL_DATA_SIZE + BTCTLER_CL_BSS_SIZE;
    BTCTLER_CL_CODE_TOTAL = BTCTLER_CL_CODE_SIZE;

    BTCTLER_COMMON_RAM_TOTAL = BTCTLER_CONTROLLER_BSS_SIZE + BTCTLER_CONTROLLER_DATA_SIZE;
    BTCTLER_COMMON_CODE_TOTAL = BTCTLER_CONTROLLER_CODE_SIZE ;

    BTCTLER_RAM_TOTAL = (btctler_data_end - btctler_data_start) + (btctler_bss_end - btctler_bss_start);
    BTCTLER_CODE_TOTAL = (btctler_code_end - btctler_code_start) + (btctler_ram_code_end - btctler_ram_code_start);
}


SECTIONS
{
    .data : ALIGN(4)
    {
        update_data_start = .;

        update_data_end = .;
    } > ram0

    .bss (NOLOAD) :ALIGN(4)
    {
        update_bss_start = .;

        *(.update_bss)
        update_bss_end = .;
    } > ram0

    .text : ALIGN(4)
    {
  update_code_start = .;

  *(.bt_updata_ram_code)
  *(.update_const)
  *(.update_code)

  update_code_end = .;
    } > code0


    UPDATE_CODE_TOTAL_SIZE = update_code_end - update_code_start;
}
SECTIONS
{
    .data : ALIGN(4)
    {
        driver_data_start = .;


        CLOCK_DATA_START = .;
        *(.clock_data)
        CLOCK_DATA_SIZE = ABSOLUTE(. - CLOCK_DATA_START);

        *(.debug_data)
        *(.power_data)

        *(.uart_data)

        driver_data_end = .;
        . = ALIGN(32);
    } > ram0

    .bss (NOLOAD) :ALIGN(4)
    {
        driver_bss_start = .;

        CLOCK_BSS_START = .;
        *(.clock_bss)
        CLOCK_BSS_SIZE = ABSOLUTE(. - CLOCK_BSS_START);

        *(.debug_bss)
        *(.power_bss)

        *(.uart_bss)

        *(.sd_var)
        driver_bss_end = .;
    } > ram0

    .text : ALIGN(4)
    {
        driver_code_start = .;

        *(.fm_code)

        CLOCK_CODE_START = .;
        *(.clock_code)
        *(.clock_const)
        CLOCK_CODE_SIZE = ABSOLUTE(. - CLOCK_CODE_START);

        *(.debug_code)
        *(.debug_const)

        *(.power_code)
        *(.power_const)

        *(.uart_code)
        *(.uart_const)

        driver_code_end = .;
  . = ALIGN(4);
    } > code0


    DRIVER_RAM_TOTAL = (driver_data_end - driver_data_start) + (driver_bss_end - driver_bss_start);
    DRIVER_CODE_TOTAL = (driver_code_end - driver_code_start);
}

text_begin = ADDR(.text);
text_size = SIZEOF(.text);
text_end = text_begin + text_size;

bss_begin = ADDR(.bss);
bss_size = SIZEOF(.bss);
bss_end = bss_begin + bss_size;

data_addr = ADDR(.data);
data_begin = text_begin + text_size;
data_size = SIZEOF(.data);





data_code_addr = ADDR(.data_code);
data_code_begin = data_begin + data_size;
data_code_size = SIZEOF(.data_code);


aec_addr = ADDR(.overlay_aec);
aec_begin = data_code_begin + data_code_size;
aec_size = SIZEOF(.overlay_aec);

aac_addr = ADDR(.overlay_aac);
aac_begin = aec_begin + aec_size;
aac_size = SIZEOF(.overlay_aac);



bank_code_load_addr = data_code_begin + data_code_size;





PROVIDE(HEAP_BEGIN = _HEAP_BEGIN);
PROVIDE(HEAP_END = _HEAP_END);
_MALLOC_SIZE = _HEAP_END - _HEAP_BEGIN;
PROVIDE(MALLOC_SIZE = _HEAP_END - _HEAP_BEGIN);






report_text_beign = ADDR(.text);
report_text_size = SIZEOF(.text);
report_text_end = report_text_beign + report_text_size;

report_mmu_tlb_begin = ADDR(.mmu_tlb);
report_mmu_tlb_size = SIZEOF(.mmu_tlb);
report_mmu_tlb_end = report_mmu_tlb_begin + report_mmu_tlb_size;

report_boot_info_begin = ADDR(.boot_info);
report_boot_info_size = SIZEOF(.boot_info);
report_boot_info_end = report_boot_info_begin + report_boot_info_size;

report_irq_stack_begin = ADDR(.irq_stack);
report_irq_stack_size = SIZEOF(.irq_stack);
report_irq_stack_end = report_irq_stack_begin + report_irq_stack_size;

report_data_begin = ADDR(.data);
report_data_size = SIZEOF(.data);
report_data_end = report_data_begin + report_data_size;

report_bss_begin = ADDR(.bss);
report_bss_size = SIZEOF(.bss);
report_bss_end = report_bss_begin + report_bss_size;

report_data_code_begin = ADDR(.data_code);
report_data_code_size = SIZEOF(.data_code);
report_data_code_end = report_data_code_begin + report_data_code_size;

report_overlay_begin = __report_overlay_begin;
report_overlay_size = __report_overlay_end - __report_overlay_begin;
report_overlay_end = __report_overlay_end;

report_heap_beign = _HEAP_BEGIN;
report_heap_size = _HEAP_END - _HEAP_BEGIN;
report_heap_end = _HEAP_END;

BR34_PHY_RAM_SIZE = PHY_RAM_SIZE;
BR34_SDK_RAM_SIZE = report_mmu_tlb_size + report_boot_info_size + report_irq_stack_size + report_data_size + report_bss_size + report_overlay_size + report_data_code_size + report_heap_size;
