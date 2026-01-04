#include "adapter_idev.h"
#include "adapter_odev.h"
#include "adapter_idev_bt.h"
#include "adapter_odev_dac.h"
#include "adapter_process.h"
#include "adapter_media.h"
#include "application/audio_dig_vol.h"
#include "le_client_demo.h"
#include "system/malloc.h"
#include "key_event_deal.h"
#include "asm/pwm_led.h"
#include "ui_manage.h"
#include "adapter_idev_usb.h"
#include "adapter_wireless_command.h"
#include "ble_user.h"
#include "adapter_recorder.h"
#if CONFIG_CPU_BR28
#include "audio_effect/audio_eff_default_parm.h"
#elif CONFIG_CPU_BR30
#include "app_online_cfg.h"
#endif


#if (APP_MAIN ==  APP_WIRELESS_MIC_2T1 && WIRELESS_ROLE_SEL == APP_WIRELESS_SLAVE)

#define POWER_OFF_CNT       7
#define SLAVE_ENC_COMMAND_LEN		2

static struct adapter_media *wireless_mic_media = NULL;
static u8 command = WIRELESS_MIC_DENOISE_OFF;
static u8 echo_cmd = WIRELESS_MIC_ECHO_OFF;
u8 wireless_conn_status = 0;
static u16 tx_cmd = 0;
u8 user_voice_changer_mode = 0;


int exit_mic_flag = 1;
extern void adapter_wireless_enc_command_send(u8 command);
extern u8 get_charge_online_flag(void);
extern u8 app_common_device_event_deal(struct sys_event *event);


#if (WIRELESS_DENOISE_ENABLE)
const struct __stream_HighSampleRateSingleMicSystem_parm denoise_parm_1 = {
    .AggressFactor = 1.0f,
    .minSuppress = 0.5f,//0.5f,/*!< 最小压制,建议范围[0.04 - 0.5], 越大降得越少 */
    .init_noise_lvl = 0.0f,
    .frame_len = WIRELESS_CODING_FRAME_LEN,
};

const struct __stream_HighSampleRateSingleMicSystem_parm denoise_parm_2 = {
    .AggressFactor = 1.0f,
    .minSuppress = 0.25f,/*!< 最小压制,建议范围[0.04 - 0.5], 越大降得越少 */
    .init_noise_lvl = 0.0f,
    .frame_len = WIRELESS_CODING_FRAME_LEN,
};

const struct __stream_HighSampleRateSingleMicSystem_parm denoise_parm_3 = {
    .AggressFactor = 1.0f,
    .minSuppress = 0.1f,/*!< 最小压制,建议范围[0.04 - 0.5], 越大降得越少 */
    .init_noise_lvl = 0.0f,
    .frame_len = WIRELESS_CODING_FRAME_LEN,
};
#endif
#if WIRELESS_LLNS_ENABLE
const struct __stream_llns_parm llns_parm_1 = {
    .gainfloor = 0.5f,
    .suppress_level = 1.0f,
    .frame_len = WIRELESS_CODING_FRAME_LEN,
};
const struct __stream_llns_parm llns_parm_2 = {
    .gainfloor = 0.25f,
    .suppress_level = 1.0f,
    .frame_len = WIRELESS_CODING_FRAME_LEN,
};
const struct __stream_llns_parm llns_parm_3 = {
    .gainfloor = 0.1f,
    .suppress_level = 1.0f,
    .frame_len = WIRELESS_CODING_FRAME_LEN,
};
#endif
#if WIRELESS_PLATE_REVERB_ENABLE
Plate_reverb_parm plate_reverb_parm = {
    .wet = 40,                      //0-300%
    .dry = 80,                      //0-200%
    .pre_delay = 0,                 //0-40ms
    .highcutoff = 12200,                //0-20k 高频截止
    .diffusion = 43,                  //0-100%
    .decayfactor = 70,                //0-100%
    .highfrequencydamping = 26,       //0-100%
    .modulate = 1,                  // 0或1
    .roomsize = 100,                   //20%-100%
};
#endif

#if WIRELESS_ECHO_ENABLE
#ifndef CONFIG_EFFECT_CORE_V2_ENABLE
ECHO_PARM_SET echo_parm = {
    .delay = 130,//200,				//回声的延时时间 0-300ms
    .decayval = 40,//50,				// 0-70%
    .direct_sound_enable = 1,	//直达声使能  0/1
    .filt_enable = 1,			//发散滤波器使能
};
EF_REVERB_FIX_PARM echo_fix_parm = {
    .wetgain = 2048,			////湿声增益：[0:4096]
    .drygain = 4096,				////干声增益: [0:4096]
    .sr = WIRELESS_CODING_SAMPLERATE,		////采样率
    .max_ms = 200,				////所需要的最大延时，影响 need_buf 大小
};
#else
ECHO_PARM_SET echo_parm = {
    .delay = 120,                      //回声的延时时间 0-max_ms, 单位ms
    .decayval = 35,                   // 0-70%
    .filt_enable = 1,                //滤波器使能标志
    .lpf_cutoff = 5000,                 //0-20k
    .wetgain = 2048,                    //0-200%
    .drygain = 4096,                    //0-100%
};
EF_REVERB_FIX_PARM echo_fix_parm = {
    .sr = WIRELESS_CODING_SAMPLERATE,		////采样率
    .max_ms = 200,				////所需要的最大延时，影响 need_buf 大小
};
#endif
#endif


//从机音频设置
#if (WIRELESS_NOISEGATE_EN)
/*#ifndef CONFIG_EFFECT_CORE_V2_ENABLE
const NOISEGATE_PARM slave_noisegate_parm = {
    .attackTime = 150,
    .releaseTime = 5,
    .threshold = -45000,
    .low_th_gain = 0,
    .sampleRate = WIRELESS_CODING_SAMPLERATE,
    .channel = 1,
 };
#else//701N跑下面的配置*/
const NoiseGateParam slave_noisegate_parm = {
    .attackTime = 150,
    .releaseTime = 5,
    .threshold = -45000,
    .low_th_gain = 0,
    .sampleRate = WIRELESS_CODING_SAMPLERATE,
    .channel = 1,
    .IndataInc = 0,
    .OutdataInc = 0,
};

//#endif
#endif//WIRELESS_NOISEGATE_EN
#if TCFG_EQ_ENABLE
#if TCFG_AEC_DCCS_EQ_ENABLE
struct stream_eq_dccs_parm dccs_parm = {
    .sr = WIRELESS_CODING_SAMPLERATE,
};
#endif
#endif
#if WIRELESS_VOICE_CHANGER_EN && TCFG_EFFECT_TOOL_ENABLE
//weak函数，库里面在线调试变声，会将模式通知到APP
void eff_cfg_set_voice_changer_mode(char mode)
{
    printf("%s,mode=%d", __func__, mode);
    user_voice_changer_mode = mode;
}
#endif
static volatile u8 g_ch_type = 0;
void set_ch_type(u8 ch)
{
    printf("%s,ch = %d", __func__, ch);
    g_ch_type = ch;
}

static void slave_audio_encode_callback(u8 *data, u16 len)
{
    //test code
    /* if (g_ch_type) { */
#if WIRELESS_MIC_DAC_ONLINE_CONFIG && TCFG_EQ_ENABLE
    data[0] = eq_online_get_dac_gain() | 0xA0;//0xA0用于校验
#endif

    data[1] = (u8)tx_cmd;
    tx_cmd = 0;
    /* data[1] = 0xBB; */
    /* } else { */
    /* data[0] = 0x55; */
    /* data[1] = 0x66; */
    /* } */
}
struct adapter_encoder_fmt slave_audio_stream_parm = {
    .enc_type = ADAPTER_ENC_TYPE_WIRELESS,
    .channel_type = &g_ch_type,//区分左右声道,这里传的是指针，目的可以动态获取
    .command_len = SLAVE_ENC_COMMAND_LEN,
    .command_callback = slave_audio_encode_callback,
};

u8 flag_mute_exdac = 0;
extern void ex_dac_prohandler(struct audio_stream_entry *entry,  struct audio_data_frame *in);
int encoder_pro_handler(struct audio_stream_entry *entry,  struct audio_data_frame *in)
{
#if WIRELESS_MIC_RECORDER_ENABLE
    if (wl_mic_get_recorder_status()) {
        //putchar('w');
        wireless_mic_recorder_pcm_data_write(in->data, in->data_len);
    }
#endif
    if (flag_mute_exdac) {
        memset(in->data, 0x00, in->data_len);
    }
}


static void auto_mute_handler(u8 event, u8 ch)
{
    printf(">>>> ch:%d %s\n", ch, event ? ("MUTE") : ("UNMUTE"));
    if (event) {
        adapter_process_event_notify(ADAPTER_EVENT_MEDIA_MUTE, 0);
    } else {
        adapter_process_event_notify(ADAPTER_EVENT_MEDIA_UNMUTE, 0);
    }
}
static const audio_energy_detect_param auto_mute_parm = {
    .mute_energy = 5,
    .unmute_energy = 10,
    .mute_time_ms = 1000,
    .unmute_time_ms = 100,
    .count_cycle_ms = 10,
    .sample_rate = WIRELESS_DECODE_SAMPLERATE,
    .event_handler = auto_mute_handler,
    .ch_total = 1,//app_audio_output_channel_get(),
    .dcc = 1,
};

static const struct adapter_stream_fmt slave_audio_stream_list[] = {

#if (TCFG_AUTO_SHUT_DOWN_BY_AUTO_MUTE)
    {
        .attr = ADAPTER_STREAM_ATTR_AUTO_MUTE,
        .value = {
            .auto_mute = {
                .parm = &auto_mute_parm,
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
            }
        },
    },
#endif

#if 0
    {
        .attr = ADAPTER_STREAM_ATTR_STREAM_DEMO,
        .value = {
            .demo = {
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
            },
        },
    },
#endif

#if TCFG_AEC_DCCS_EQ_ENABLE
    {
        .attr  = ADAPTER_STREAM_ATTR_DCCS,
        .value = {
            .dccs = {
                .parm = &dccs_parm,
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
            },
        },
    },
#endif
#if WIRELESS_ECHO_ENABLE
    {
        .attr  = ADAPTER_STREAM_ATTR_ECHO,
        .value = {
            .echo = {
                .parm = &echo_parm,
                .fix_parm = &echo_fix_parm,
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
            },
        },
    },
#endif
#if WIRELESS_PLATE_REVERB_ENABLE
    {
        .attr  = ADAPTER_STREAM_ATTR_PLATE_REVERB,
        .value = {
            .plate_reverb = {
                .parm = &plate_reverb_parm,
                .samplerate = WIRELESS_CODING_SAMPLERATE,
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
            },
        },
    },
    {
        .attr = ADAPTER_STREAM_ATTR_CH_SW,	//reverb会把数据转成双声道，这里要重新转成单声道
        .value = {
            .ch_sw = {
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
                .out_ch_type = AUDIO_CH_DIFF,
                .buf_len = 0,
            },
        },
    },
#endif


#if TCFG_PHONE_EQ_ENABLE
    {
        .attr  = ADAPTER_STREAM_ATTR_MICEQ,
        .value = {
            .miceq = {
                .samplerate = WIRELESS_CODING_SAMPLERATE,
                .ch_num = 1,
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
            },
        },
    },
#endif

#if (WIRELESS_DENOISE_ENABLE)
    //降噪节点
    {
        .attr  = ADAPTER_STREAM_ATTR_DENOISE,
        .value = {
            .denoise = {
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
                .sample_rate = 32000,
                .onoff = 1,
                .parm = {
                    .AggressFactor = 1.0f,
                    .minSuppress = 0.1f,
                    .init_noise_lvl = 0.0f,
                    .frame_len = WIRELESS_CODING_FRAME_LEN,
                },
            },
        },
    },
#endif
#if (WIRELESS_LLNS_ENABLE)
    {
        .attr  = ADAPTER_STREAM_ATTR_LLNS,
        .value = {
            .llns = {
                .samplerate  = WIRELESS_CODING_SAMPLERATE,
                .onoff = 0,
                .llns_parm = {
                    .gainfloor = 0.1f,
                    .suppress_level = 1.0f,
                    .frame_len = WIRELESS_CODING_FRAME_LEN,
                },
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
                //其他关于encoder的参数配置
            },
        },
    },
#endif
#if (WIRELESS_NOISEGATE_EN)
    {
        .attr  = ADAPTER_STREAM_ATTR_NOISEGATE,
        .value = {
            .noisegate = {
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
                .parm = &slave_noisegate_parm,
            },
        },
    },
#endif



#if WIRELESS_HOWLING_ENABLE
    {
        .attr  = ADAPTER_STREAM_ATTR_HOWLING,
        .value = {
            .howling = {
                .howl_para = NULL,
                .sample_rate = WIRELESS_CODING_SAMPLERATE,
                .channel = 0,
                .mode = 1,
                .data_handle = NULL,//如果要关注处理前的数据可以在这里注册回调
            },
        },
    },
    {
        .attr  = ADAPTER_STREAM_ATTR_HOWLINGSUPPRESS,
    },
#endif
#if WIRELESS_VOICE_CHANGER_EN
    {
        .attr  = ADAPTER_STREAM_ATTR_VOICE_CHANGER,
    },
#endif
#if WIRELESS_DRC_EN
    {
        .attr  = ADAPTER_STREAM_ATTR_DRC,
    },
#endif
    {
        .attr  = ADAPTER_STREAM_ATTR_ENCODE,
        .value = {
            .encoder = {
                .parm = &slave_audio_stream_parm,
                .data_handle = encoder_pro_handler,//如果要关注处理前的数据可以在这里注册回调
                //其他关于encoder的参数配置
            },
        },
    },
};
static struct adapter_decoder_fmt slave_audio_stream = {
    .dec_type = ADAPTER_DEC_TYPE_MIC,
    .list	  = slave_audio_stream_list,
    .list_num = sizeof(slave_audio_stream_list) / sizeof(slave_audio_stream_list[0]),
};
static const struct adapter_media_fmt slave_media_list[] = {
    [0] = {
        .upstream =	NULL,
        .downstream = &slave_audio_stream,
    },

};

static const struct adapter_media_config slave_media_config = {
    .list = slave_media_list,
    .list_num = sizeof(slave_media_list) / sizeof(slave_media_list[0]),
};

//bt idev config
struct _odev_bt_parm odev_bt_parm_list = {
    .mode = BIT(ODEV_BLE),
};

//bt odev config
#if !WIRELESS_TOOL_BLE_NAME_EN
static u8 dongle_remoter_name1[] = "W_MIC_120";
static client_match_cfg_t match_dev01 = {
    .create_conn_mode = BIT(CLI_CREAT_BY_NAME),
    .compare_data_len = sizeof(dongle_remoter_name1) - 1, //去结束符
    .compare_data = dongle_remoter_name1,
    .bonding_flag = 0,
};
#else
static u8 dongle_remoter_name1[] = "W_MIC_05";
static u8 *ble_pair_name;
client_match_cfg_t match_dev01 = {0};
#endif

void tx_send_data_to_rx(u16 data)
{
    tx_cmd = data;
    printf("tx_cmd = %d", tx_cmd);
}

struct idev *idev;
struct odev *odev;
struct adapter_media *media;
struct adapter_pro *pro;

static u8 denoise_flag = 0;
static u8 echo_flag = 0;

static int event_handle_callback(struct sys_event *event);

extern u8 flag_key_sw_recorder;
extern ble_state_e get_adapter_server_ble_status(void);
static int adapter_key_event_handler(struct sys_event *event)
{
    int ret = 0;
    struct key_event *key = &event->u.key;

    u16 key_event = event->u.key.event;

    static u8 key_poweroff_cnt = 0;
    static u8 flag_poweroff = 0;
    printf("key_event:%d %d %d\n", key_event, key->value, key->event);
    switch (key_event) {
    case KEY_MUSIC_PP:
    case KEY_MUSIC_NEXT:
        tx_send_data_to_rx(key_event);
        break;
#if WIRELESS_MIC_RECORDER_ENABLE
    case KEY_RECORD_SW:
        if (!adapter_get_sd_online_status() || adapter_get_otg_online_status()) {
            //sd卡不在线或者otg在线，不能录音
            printf("can't recode !!!!!!");
            break;
        }
        flag_key_sw_recorder = !flag_key_sw_recorder;
        printf("flag_key_sw_recorder=%d", flag_key_sw_recorder);
        if (flag_key_sw_recorder) {
            wireless_mic_recorder_start();
        } else {
            wireless_mic_recorder_stop();
        }
        break;
#endif
#if (WIRELESS_LLNS_ENABLE)

    case KEY_WIRELESS_MIC_DENOISE_SET:
#if !ALWAYS_RUN_STREAM	//未连接也可以设置降噪档位
        if (!wireless_conn_status) {
            printf("no conn,break");
            break;
        }
#endif
        command++;
        if (command > WIRELESS_MIC_DENOISE_LEVEL_MAX) {
            command = WIRELESS_MIC_DENOISE_OFF;
        }
        printf("KEY_WIRELESS_MIC_LLNS_SET %d\n", command);
        if (wireless_mic_media) {
            switch (command) {
            case 1:
                //关闭降噪
                /* adapter_media_stop(wireless_mic_media); */
                /* adapter_media_start(wireless_mic_media); */
                adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_LLNS_SWITCH, 1, (int *)0);
                break;
            case 2:
                //轻度降噪
                /* adapter_media_stop(wireless_mic_media); */
                /* adapter_media_start(wireless_mic_media); */
                adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_LLNS_SWITCH, 1, (int *)1);
                adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_LLNS_SET_PARM, 1, (int *)&llns_parm_1);
                break;
            case 3:
                //中度降噪
                adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_LLNS_SWITCH, 1, (int *)1);
                adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_LLNS_SET_PARM, 1, (int *)&llns_parm_2);
                break;
            case 4:
                //深度降噪
                adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_LLNS_SWITCH, 1, (int *)1);
                adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_LLNS_SET_PARM, 1, (int *)&llns_parm_3);
                break;
            default:
                break;
            }
        }
        break;
#endif


#if (WIRELESS_DENOISE_ENABLE)

    case KEY_WIRELESS_MIC_DENOISE_SET:
        //主机响应实际按键事件， 通过命令转发到从机， 由从机实现降噪
        //主机发出按键降噪设置命令, 1:关闭降噪， 2:轻度降噪，3:中度降噪，4:深度降噪
        //主机的降噪等级可以通过VM记忆， 根据方案需求自行添加， 记忆command即可，每次开机读取默认值
        if(exit_mic_flag)
        {


            #if !ALWAYS_RUN_STREAM
                    if (!wireless_conn_status) {
                        printf("no conn,break");
                        break;
                    }
            #endif
            command++;
            if (command > 2) {
                command = WIRELESS_MIC_DENOISE_OFF;
            }
            printf("KEY_WIRELESS_MIC_DENOISE_SET %d\n", command);

            if (wireless_mic_media) {
                switch (command) {
                case 1:
                    //深度降噪
                    adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_DENOISE_SWITCH, 1, (int *)1);
                    adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_DENOISE_SET_PARM, 1, (int *)&denoise_parm_3);
                    if(echo_flag)
                    {
                        //red_led_flash_del();
                        gpio_disable_fun_output_port(TCFG_PWMLED_PIN1);
                        gpio_led_high_block(TCFG_PWMLED_PIN1);
                        green_led_flash_add();
                    }

                    else
                    {
                        gpio_disable_fun_output_port(TCFG_PWMLED_PIN1);
                        gpio_led_high_block(TCFG_PWMLED_PIN1);
                        green_led_flash_del();
                        green_led_init();
                    }

                    denoise_flag = 0;
                    break;
                case 2:
                    //关闭降噪
                    /* adapter_media_stop(wireless_mic_media); */
                    /* adapter_media_start(wireless_mic_media); */
                    adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_DENOISE_SWITCH, 1, (int *)0);
                    if(echo_flag)
                    {

                        gpio_disable_fun_output_port(TCFG_PWMLED_PIN0);
                        gpio_led_high_block(TCFG_PWMLED_PIN0);
                        red_led_init();
                        green_led_flash_add();
                    }

                    else
                    {
                        gpio_disable_fun_output_port(TCFG_PWMLED_PIN0);
                        gpio_led_high_block(TCFG_PWMLED_PIN0);
                        green_led_flash_del();
                        red_led_init();
                    }

                        denoise_flag = 1;
                    break;

                default:
                    break;
                }
            }
        }
        break;
#endif//#if (WIRELESS_DENOISE_ENABLE)
#if WIRELESS_ECHO_ENABLE||WIRELESS_PLATE_REVERB_ENABLE

    case KEY_WIRELESS_MIC_ECHO_SET:
        if(exit_mic_flag)
        {
            if (!wireless_conn_status)
            {
                printf("no conn,break");
                break;
            }
            echo_cmd++;
            if (echo_cmd > WIRELESS_MIC_ECHO_ON) {
                echo_cmd = WIRELESS_MIC_ECHO_OFF;
            }
            printf("KEY_WIRELESS_MIC_ECHO %d\n", echo_cmd);

            if (wireless_mic_media)
            {
                if(echo_cmd == WIRELESS_MIC_ECHO_OFF)
                    {
                        adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_ECHO_EN, 1, (int *)(echo_cmd));
                        if(connect_state_flag)
                        {
                            if(echo_flag)
                            {
                                if(!denoise_flag)
                                {
                                    green_led_flash_del();
                                    green_led_init();
                                }
                                else{
                                    green_led_flash_del();
                                    red_led_init();
                                }
                                echo_flag = 0;
                            }
                        }
                        else
                        {
                            pwm_led_mode_set(PWM_LED0_LED1_FAST_FLASH);
                            echo_flag = 0;
                        }
                    }
                    if(echo_cmd == WIRELESS_MIC_ECHO_ON)
                    {
                        adapter_decoder_ioctrl(wireless_mic_media->downdecode, ADAPTER_DEC_IOCTRL_CMD_ECHO_EN, 1, (int *)(echo_cmd));
                        if(!echo_flag)
                        {
                            //if(!denoise_flag)
                                green_led_flash_add();
                            //else
                               // red_led_flash_add();
                            echo_flag = 1;
                        }
                    }
            }
        }
        break;
#endif//
    case KEY_SW_SAMETIME_OUTPUT:
        //开关同时输出到dac
        flag_mute_exdac = !flag_mute_exdac;
        printf("flag_mute_exdac = %d", flag_mute_exdac);
        break;
#if WIRELESS_VOICE_CHANGER_EN
    case KEY_VOICE_CHANGE_SW:
#ifndef CONFIG_EFFECT_CORE_V2_ENABLE
        EQ_CFG *eq_cfg = get_eq_cfg_hdl();
        user_voice_changer_mode++;
        if (user_voice_changer_mode >= WIRELESS_VOICE_CHANGER_MAX_NUM) {
            user_voice_changer_mode = 0;
        }
        printf("KEY_VOICE_CHANGE_SW,mode=%d", user_voice_changer_mode);
        audio_voice_changer_update_parm(AEID_MIC_VOICE_CHANGER, &eq_cfg->cfg_parm[wirless_mic_mode].voice_changer_parm.parm[user_voice_changer_mode]);
        break;
#endif
#endif


    case  KEY_EXIT_MIC:
         printf("connect_state_flag  %d\n",connect_state_flag);
        if(connect_state_flag)
        {
            if(exit_mic_flag)
            {
                printf("!!!!!!!!!!!!!!!!!1111111111\n");

                exit_mic_flag = 0;
                //pwm_led_mode_set(PWM_LED0_FAST_FLASH);
                green_led_flash_add();
                gpio_disable_fun_output_port(TCFG_PWMLED_PIN0);
                gpio_led_high_block(TCFG_PWMLED_PIN0);

            }
            else
            {
                printf("!!!!!!!!!!!!!!!!!222222222222\n");

                exit_mic_flag = 1;
                //pwm_led_mode_set(PWM_LED0_ON);
                green_led_flash_del();
                green_led_init();

            }
            flag_mute_exdac = !exit_mic_flag;
        }
    break;
    case KEY_WIRELESS_PAIR:
        #if WIRELESS_PAIR_BONDING
            clear_bonding_info();
            ble_module_enable(1);
        #endif // WIRELESS_PAIR_BONDING
        break;
    case  KEY_POWEROFF:
        printf("KEY POWEROFF\n");
        key_poweroff_cnt = 0;
        flag_poweroff = 1;
        break;
    case  KEY_POWEROFF_HOLD:
        printf("KEY POWEROFF_HOLD\n");
        if (flag_poweroff) {
            if (++key_poweroff_cnt >= POWER_OFF_CNT) {
                key_poweroff_cnt = 0;
                ret = 1;
            }
        }

        break;

    case  KEY_NULL:
        break;
    }
    return ret;
}

// tx 接收 rx 发过来的数据
void wireless_mic_server_recieve_data(void *priv, void *data, u16 len)
{
    put_buf(data, len);
}
static int event_handle_callback(struct sys_event *event)
{
    //处理用户关注的事件
    int ret = 0;
    switch (event->type) {
    case SYS_KEY_EVENT:
        ret = adapter_key_event_handler(event);
        break;
    case SYS_DEVICE_EVENT:
        app_common_device_event_deal(event);
#if (TCFG_DEV_MANAGER_ENABLE)
        dev_status_event_filter(event);
#endif
        switch ((u32)event->arg) {
        case DEVICE_EVENT_FROM_ADAPTER:
            switch (event->u.dev.event) {
            case ADAPTER_EVENT_CONNECT :
                printf("ADAPTER_EVENT_CONNECT\n");
                wireless_conn_status = 1;
                if(!connect_state_flag)
                    connect_state_flag = 1;

                /*if(!exit_mic_flag)
                {
                    pwm_led_mode_set(PWM_LED0_DOUBLE_FLASH_5S);
                }
                else{*/
                    ui_update_status(STATUS_BT_CONN);
                //}
                sys_auto_shut_down_disable();
                break;
            case ADAPTER_EVENT_DISCONN :
                printf("ADAPTER_EVENT_DISCONN\n");
                cpu_reset();
                echo_cmd = 5;
                wireless_conn_status = 0;
                if(connect_state_flag)
                    connect_state_flag = 0;
                sys_auto_shut_down_enable();
                ui_update_status(STATUS_BT_DISCONN);
                break;
            case ADAPTER_EVENT_IDEV_MEDIA_CLOSE :
            case ADAPTER_EVENT_ODEV_MEDIA_CLOSE :
                break;
            case ADAPTER_EVENT_POWEROFF:
                ret = 1;
                break;
            case ADAPTER_EVENT_MEDIA_MUTE:
                sys_auto_shut_down_enable();
                break;
            case ADAPTER_EVENT_MEDIA_UNMUTE:
                sys_auto_shut_down_disable();
                break;
            }
            break;
        }
        break;

    default:
        break;

    }
    return ret;
}

void wireless_cfg_tool_read_name(void)
{
    u8 ble_name_len;
    extern const char *bt_get_local_name();
    ble_pair_name = (u8 *)(bt_get_local_name());
    ble_name_len = strlen(ble_pair_name);

    match_dev01.create_conn_mode = BIT(CLI_CREAT_BY_NAME);
    match_dev01.compare_data_len = ble_name_len;
    match_dev01.compare_data = ble_pair_name;
    match_dev01.bonding_flag = 0;

}
void app_main_run(void)
{
    ui_update_status(STATUS_POWERON);
#if WIRELESS_TOOL_BLE_NAME_EN
    wireless_cfg_tool_read_name();
#endif

    while (1) {
        //初始化
        idev = adapter_idev_open(ADAPTER_IDEV_MIC, NULL);
        odev = adapter_odev_open(ADAPTER_ODEV_BT, (void *)&odev_bt_parm_list);
        media = adapter_media_open((struct adapter_media_config *)&slave_media_config);
        printf("wireless_mic_2t1_tx ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        ASSERT(idev);
        ASSERT(odev);
        ASSERT(media);
        pro = adapter_process_open(idev, odev, media, event_handle_callback);//event_handle_callback 用户想拦截处理的事件

        ASSERT(pro, "adapter_process_open fail!!\n");

        wireless_mic_media = media;

        //执行(包括事件解析、事件执行、媒体启动/停止, HID等事件转发)
        adapter_process_run(pro);
#if WIRELESS_MIC_RECORDER_ENABLE
        if (wl_mic_get_recorder_status()) {
            wireless_mic_recorder_stop();
        }
#endif
        wireless_mic_media = NULL;

        //退出/关闭
        adapter_process_close(&pro);
        adapter_media_close(&media);
        adapter_idev_close(idev);
        adapter_odev_close(odev);

        ui_update_status(STATUS_POWEROFF);
        ///run idle off poweroff
        printf("enter poweroff !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        if (get_charge_online_flag()) {
            printf("charge_online,cpu reset");
            cpu_reset();
        } else {
            power_set_soft_poweroff();
        }
    }
}


#endif

