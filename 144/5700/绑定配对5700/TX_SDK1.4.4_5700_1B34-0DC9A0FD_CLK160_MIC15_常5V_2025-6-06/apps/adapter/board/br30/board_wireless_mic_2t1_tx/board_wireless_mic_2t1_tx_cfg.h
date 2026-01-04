#ifndef CONFIG_BOARD_WIRELESS_MIC_2T1_TX_CFG_H
#define CONFIG_BOARD_WIRELESS_MIC_2T1_TX_CFG_H

#ifdef CONFIG_BOARD_WIRELESS_MIC_2T1_TX

#include "board_wireless_mic_2t1_tx_global_build_cfg.h"

//*********************************************************************************//
//                                 无线麦配置                                      //
//*********************************************************************************//
//两发一收无线mic方案，发射端配置为从机，接收端配置为主机
#define WIRELESS_ROLE_SEL				APP_WIRELESS_SLAVE// APP_WIRELESS_SLAVE//角色选择

//适用于话筒音箱这种与经典蓝牙靠近并且同时使用的方案，彼此干扰小,距离远。不是和经典蓝牙靠近并且同时使用的方案，不建议打开
#define WIRELESS_2T1_MICROPHONE_MODE	DISABLE//ENABLE

#define WIRELESS_24G_ENABLE				ENABLE //使能此功能可以屏蔽手机搜索到此无线设备名
#define WIRELESS_NOISEGATE_EN		    DISABLE//噪声门限使能
#define WIRELESS_ECHO_ENABLE			ENABLE//DISABLE //混响
#define WIRELESS_HOWLING_ENABLE			DISABLE	//防啸叫
#define WIRELESS_DENOISE_ENABLE			ENABLE//DISABLE //只支持32k采样率,降噪使能
#define WIRELESS_LLNS_ENABLE			DISABLE //支持16k,32k,48K采样率,低延时降噪,延时低，降噪算法时间5ms
#define WIRELESS_VOICE_CHANGER_EN       DISABLE //变声
#define WIRELESS_VOICE_CHANGER_MAX_NUM	5		//变声类型数量,目前调音工具最大支持10种
#define WIRELESS_DRC_EN                 DISABLE
//低延时模式,比非低延时模式少3ms，距离会变短，用户可根据产品应用场景选择,txrx需要保持一致
#define WIRELESS_LOW_LATENCY			DISABLE
//编解码采样率如果有修改，请对应修改另一方的编解码采样率
#define WIRELESS_CODING_SAMPLERATE		(32000)

#define	WIRELESS_MIC_STEREO_EN			0

#if WIRELESS_2T1_MICROPHONE_MODE
#define WIRELESS_CODING_FRAME_LEN		100
#define TCFG_RF_OOB		1
#else
#if WIRELESS_LOW_LATENCY
#define WIRELESS_CODING_FRAME_LEN		25
#else
#define WIRELESS_CODING_FRAME_LEN		50
#endif
#endif

#define WIRELESS_DECODE_SAMPLERATE		WIRELESS_CODING_SAMPLERATE

//两发一收支持两个tx分别作为左右声道，需要RXTX都开这个功能
//靠电阻区分TX的声道,默认有下拉电阻的作为左声道
#define WIRELESS_TX_MIC_STEREO_OUTPUT		DISABLE
#define WIRELESS_TX_L_CH_IO				    IO_PORTB_00

//mic声音同时输出到dac
#define WIRELESS_MIC_OUTPUT_DAC_SAMETIME	ENABLE//DISABLE

#define	WIRELESS_TOOL_BLE_NAME_EN		ENABLE
//rf测试，由工具触发样机进入dut模式
#define TCFG_RF_TEST_EN					DISABLE

//配对绑定
#define WIRELESS_PAIR_BONDING			1//DISABLE

//使用PA延长距离,需要硬件添加PA电路,默认使用PC2/PC3
#define CONFIG_BT_RF_USING_EXTERNAL_PA_EN	DISABLE


#define WIRELESS_MIC_DAC_ONLINE_CONFIG		0
//*********************************************************************************//
//                                  app 配置                                       //
//*********************************************************************************//
#define TCFG_APP_BT_EN			            1
#define TCFG_APP_MUSIC_EN			        0
#define TCFG_APP_LINEIN_EN					0
#define TCFG_APP_FM_EN					    0
#define TCFG_APP_PC_EN					    0
#define TCFG_APP_RTC_EN					    0
#define TCFG_APP_RECORD_EN				    0
#define TCFG_APP_SPDIF_EN                   0
//*********************************************************************************//
//                                 UART配置                                        //
//*********************************************************************************//
#define TCFG_UART0_ENABLE					DISABLE_THIS_MOUDLE //串口打印模块使能
#define TCFG_UART0_RX_PORT					NO_CONFIG_PORT                         //串口接收脚配置（用于打印可以选择NO_CONFIG_PORT）
#define TCFG_UART0_TX_PORT  				IO_PORTC_05                            //串口发送脚配置
#define TCFG_UART0_BAUDRATE  				1000000                                //串口波特率配置

//*********************************************************************************//
//                                 USB 配置                                        //
//*********************************************************************************//
#define TCFG_PC_ENABLE                      0
#define USB_MALLOC_ENABLE                   1
#define USB_PC_NO_APP_MODE                  1
#define USB_MEM_NO_USE_OVERLAY_EN		    1
#define USB_DEVICE_CLASS_CONFIG             0

#define TCFG_USB_APPLE_DOCK_EN              0



//*********************************************************************************//
//                                 key 配置                                        //
//*********************************************************************************//
//#define KEY_NUM_MAX                        	10
//#define KEY_NUM                            	3
#define KEY_IO_NUM_MAX						6
#define KEY_AD_NUM_MAX						10
#define KEY_IR_NUM_MAX						21
#define KEY_TOUCH_NUM_MAX					6
#define KEY_RDEC_NUM_MAX                    6
#define KEY_CTMU_TOUCH_NUM_MAX				6

#define MULT_KEY_ENABLE						DISABLE 		//是否使能组合按键消息, 使能后需要配置组合按键映射表

#define TCFG_KEY_TONE_EN					DISABLE		// 按键提示音。建议音频输出使用固定采样率

//*********************************************************************************//
//                                 iokey 配置                                      //
//*********************************************************************************//
#define TCFG_IOKEY_ENABLE					ENABLE_THIS_MOUDLE //是否使能IO按键

#define TCFG_IOKEY_POWER_CONNECT_WAY		ONE_PORT_TO_LOW    //按键一端接低电平一端接IO

#define TCFG_IOKEY_POWER_ONE_PORT			IO_PORTB_01        //IO按键端口

//#define TCFG_IOKEY_PREV_CONNECT_WAY			ONE_PORT_TO_LOW  //按键一端接低电平一端接IO
//#define TCFG_IOKEY_PREV_ONE_PORT			IO_PORTB_00

// #define TCFG_IOKEY_NEXT_CONNECT_WAY 		ONE_PORT_TO_LOW  //按键一端接低电平一端接IO
// #define TCFG_IOKEY_NEXT_ONE_PORT			IO_PORTB_02
//*********************************************************************************//
//                                  NTC配置                                       //
//*********************************************************************************//
#define NTC_DET_EN  					    DISABLE_THIS_MOUDLE
#define NTC_POWER_IO   						IO_PORTC_04
#define NTC_DETECT_IO   					IO_PORTC_05
#define NTC_DET_AD_CH   					(AD_CH_PC5)   //根据adc_api.h修改通道号

#define NTC_DET_UPPER        				799  //正常范围AD值上限，0度时
#define NTC_DET_LOWER        				297  //正常范围AD值下限，45度时

//*********************************************************************************//
//                                  充电参数配置                                   //
//*********************************************************************************//
#define TCFG_CHARGE_ENABLE					ENABLE_THIS_MOUDLE
#define TCFG_TEST_BOX_ENABLE				ENABLE_THIS_MOUDLE
#define TCFG_CHARGESTORE_PORT				IO_PORTP_00
//是否支持开机充电
#define TCFG_CHARGE_POWERON_ENABLE			DISABLE
//是否支持拔出充电自动开机功能
#define TCFG_CHARGE_OFF_POWERON_NE			ENABLE//ENABLE
#define TCFG_CHARGE_FULL_V					CHARGE_FULL_V_4222
#define TCFG_CHARGE_FULL_MA					CHARGE_FULL_mA_15
#define TCFG_CHARGE_MA						CHARGE_mA_80
//涓流电流
#define TCFG_CHARGE_TRICKLE_MA				CHARGE_mA_20


//*********************************************************************************//
//                                  低功耗配置                                     //
//*********************************************************************************//
#define TCFG_LOWPOWER_POWER_SEL				PWR_DCDC15                   //电源模式设置，可选DCDC和LDO

//*********************************************************************************//
//                                 Audio配置                                       //
//*********************************************************************************//
#define TCFG_AUDIO_ADC_ENABLE				ENABLE_THIS_MOUDLE
/*
 *LADC_CH_MIC_L: MIC0(PA1)
 *LADC_CH_MIC_R: MIC1(PB8)
 */
#define TCFG_AUDIO_ADC_MIC_CHA				LADC_CH_MIC_L
/*MIC LDO电流档位设置：
    0:0.625ua    1:1.25ua    2:1.875ua    3:2.5ua*/
#define TCFG_AUDIO_ADC_LDO_SEL				3

// LADC通道
#define TCFG_AUDIO_ADC_LINE_CHA0			LADC_LINE1_MASK
#define TCFG_AUDIO_ADC_LINE_CHA1			LADC_CH_LINE0_L

#define TCFG_AUDIO_DAC_ENABLE				ENABLE_THIS_MOUDLE
#define TCFG_AUDIO_DAC_LDO_SEL				1
/*
DACVDD电压设置(要根据具体的硬件接法来确定):
    DACVDD_LDO_1_20V        DACVDD_LDO_1_30V        DACVDD_LDO_2_35V        DACVDD_LDO_2_50V
    DACVDD_LDO_2_65V        DACVDD_LDO_2_80V        DACVDD_LDO_2_95V        DACVDD_LDO_3_10V*/
#define TCFG_AUDIO_DAC_LDO_VOLT				DACVDD_LDO_1_25V
/*预留接口，未使用*/
#define TCFG_AUDIO_DAC_PA_PORT				NO_CONFIG_PORT
/*
DAC硬件上的连接方式,可选的配置：
    DAC_OUTPUT_MONO_L               左声道
    DAC_OUTPUT_MONO_R               右声道
    DAC_OUTPUT_LR                   立体声
    DAC_OUTPUT_MONO_LR_DIFF         单声道差分输出
*/
#define TCFG_AUDIO_DAC_CONNECT_MODE    DAC_OUTPUT_MONO_LR_DIFF

/*
解码后音频的输出方式:
    AUDIO_OUTPUT_ORIG_CH            按原始声道输出
    AUDIO_OUTPUT_STEREO             按立体声
    AUDIO_OUTPUT_L_CH               只输出原始声道的左声道
    AUDIO_OUTPUT_R_CH               只输出原始声道的右声道
    AUDIO_OUTPUT_MONO_LR_CH         输出左右合成的单声道
 */

#define AUDIO_OUTPUT_MODE          AUDIO_OUTPUT_MONO_LR_CH

#define AUDIO_OUTPUT_WAY            AUDIO_OUTPUT_WAY_BT
#define LINEIN_INPUT_WAY            LINEIN_INPUT_WAY_ANALOG

#define AUDIO_OUTPUT_AUTOMUTE       0//ENABLE

#define  DUT_AUDIO_DAC_LDO_VOLT   				DACVDD_LDO_1_25V

//每个解码通道都开启数字音量管理,音量类型为VOL_TYPE_DIGGROUP时要使能
#define SYS_DIGVOL_GROUP_EN     DISABLE

#define SYS_VOL_TYPE            VOL_TYPE_ANALOG


/*
 *通话的时候使用数字音量
 *0：通话使用和SYS_VOL_TYPE一样的音量调节类型
 *1：通话使用数字音量调节，更加平滑
 */
#define TCFG_CALL_USE_DIGITAL_VOLUME		0

// 使能改宏，提示音音量使用music音量
#define APP_AUDIO_STATE_WTONE_BY_MUSIC      (1)
// 0:提示音不使用默认音量； 1:默认提示音音量值
#define TONE_MODE_DEFAULE_VOLUME            (0)

#if (WIRELESS_MIC_STEREO_EN == 0)
/*
 *默认使用差分麦， 对底噪有明显优化， 对于驻极体mic和模拟硅mic JL6976M同封装芯片由MIC1_BIAS提供电压
 *如果是动圈麦， 可以不使能MIC1_BIAS， 可以在板级C文件将audio_mic_ldo_en(1, &adc_data);调用注释掉
 *如果使用单端麦，则配置MIC_MODE_SINGLE_END即可
 * */
#define TCFG_AUDIO_MIC_MODE                 MIC_MODE_SINGLE_END //MIC_MODE_DIFF_END
#else
#define TCFG_AUDIO_MIC_MODE                 MIC_MODE_SINGLE_END
#endif

#define TCFG_AUDIO_MIC1_MODE                MIC_MODE_DIFF_END //MIC_MODE_SINGLE_END
/*
 *支持省电容MIC模块
 *(1)要使能省电容mic,首先要支持该模块:TCFG_SUPPORT_MIC_CAPLESS
 *(2)只有支持该模块，才能使能该模块:TCFG_MIC_CAPLESS_ENABLE
 */
#define TCFG_SUPPORT_MIC_CAPLESS			ENABLE_THIS_MOUDLE
//省电容MIC使能
#define TCFG_MIC_CAPLESS_ENABLE				DISABLE_THIS_MOUDLE

#if (WIRELESS_DENOISE_ENABLE)
#define WIRELESS_MIC_ADC_RESUME_CODING_EN   DISABLE
#else
#define WIRELESS_MIC_ADC_RESUME_CODING_EN   DISABLE
#endif
#define WIRELESS_MIC_ADC_GAIN				(15)//mic增益设置,使用单端麦adc增益建议设置为10，用户可根据自己需求修改
#if (WIRELESS_CODING_SAMPLERATE == 44100)
#define WIRELESS_MIC_ADC_POINT_UNIT			(48000*WIRELESS_CODING_FRAME_LEN/10000)
#else
#define WIRELESS_MIC_ADC_POINT_UNIT			(WIRELESS_CODING_SAMPLERATE*WIRELESS_CODING_FRAME_LEN/10000)
#endif


//*********************************************************************************//
//                                  PWM_LED 配置                                       //
//******************************************************************************
#define TCFG_PWMLED_ENABLE					DISABLE_THIS_MOUDLE//ENABLE_THIS_MOUDLE			//是否支持PMW LED推灯模块
#define TCFG_PWMLED_IOMODE					LED_ONE_IO_MODE				//LED模式，单IO还是两个IO推灯
#define TCFG_PWMLED_PIN						IO_PORTB_06					//红灯

#define TCFG_PWMLED_PIN0						IO_PORTB_02	            //9脚，蓝灯
#define TCFG_PWMLED_PIN1						IO_PORTB_06             //3脚，红灯
//#define TCFG_PWMLED_PIN2						IO_PORTC_04             //21脚，开机灯
//#define TCFG_PWMLED_PIN3						IO_PORTC_03             //22脚，混响


//*********************************************************************************//
//                                  EQ配置                                         //
//*********************************************************************************//
#define TCFG_EQ_ENABLE						DISABLE_THIS_MOUDLE
#define TCFG_EQ_ONLINE_ENABLE               0     //支持在线EQ调试, 如果使用蓝牙串口调试，需要打开宏 APP_ONLINE_DEBUG，否则，默认使用uart调试(二选一)
#define TCFG_PHONE_EQ_ENABLE				DISABLE_THIS_MOUDLE
#define EQ_SECTION_MAX                      10    //eq段数
#define TCFG_USE_EQ_FILE                    1    //离线eq使用配置文件还是默认系数表 1：使用文件  0 使用默认系数表
#define TCFG_AEC_DCCS_EQ_ENABLE				TCFG_MIC_CAPLESS_ENABLE//省电容mic需要加dccs直流滤波
/*省电容mic通过eq模块实现去直流滤波*/
#if (TCFG_SUPPORT_MIC_CAPLESS && (TCFG_MIC_CAPLESS_ENABLE || TCFG_MIC1_CAPLESS_ENABLE))
#if ((TCFG_EQ_ENABLE == 0) || (TCFG_AEC_DCCS_EQ_ENABLE == 0))
#error "MicCapless enable,Please enable TCFG_EQ_ENABLE and TCFG_AEC_DCCS_EQ_ENABLE"
#endif
#endif
#if WIRELESS_DRC_EN
#undef TCFG_DRC_ENABLE
#define TCFG_DRC_ENABLE 1
#endif

//*********************************************************************************//
//                          新音箱配置工具 && 调音工具                             //
//*********************************************************************************//
#define TCFG_EFFECT_TOOL_ENABLE				DISABLE		  	//是否支持在线音效调试,使能该项还需使能EQ总使能TCFG_EQ_ENABL,
#define TCFG_NULL_COMM						0				//不支持通信
#define TCFG_UART_COMM						1				//串口通信
#define TCFG_USB_COMM						2				//USB通信
#if (TCFG_CFG_TOOL_ENABLE || TCFG_EFFECT_TOOL_ENABLE)
#define TCFG_COMM_TYPE						TCFG_UART_COMM	//通信方式选择
#else
#define TCFG_COMM_TYPE						TCFG_NULL_COMM
#endif
#define TCFG_TOOL_TX_PORT					IO_PORT_DP      //UART模式调试TX口选择
#define TCFG_TOOL_RX_PORT					IO_PORT_DM      //UART模式调试RX口选择
#define TCFG_ONLINE_ENABLE                  (TCFG_EFFECT_TOOL_ENABLE)    //是否支持音效在线调试功能

#if (TCFG_EQ_ONLINE_ENABLE && !TCFG_EFFECT_TOOL_ENABLE) || (!TCFG_EQ_ONLINE_ENABLE && TCFG_EFFECT_TOOL_ENABLE)
#error "在线调音，两个宏定义都需要使能"
#endif

#if (((TCFG_COMM_TYPE == TCFG_UART_COMM) && TCFG_ONLINE_ENABLE) && TCFG_SHARE_OSC_EN)
#error "online uart enable, plaease close TCFG_SHARE_OSC_EN"
#endif

//*********************************************************************************//
//                                  系统配置                                         //
//*********************************************************************************//
#define TCFG_AUTO_SHUT_DOWN_TIME		    120   //没有蓝牙连接自动关机时间
#define TCFG_AUTO_SHUT_DOWN_BY_AUTO_MUTE    DISEABLE  //配合TCFG_AUTO_SHUT_DOWN_TIME使用，在音频MUTE之后会触发关机计时
#define TCFG_SYS_LVD_EN						1   //电量检测使能
#define TCFG_POWER_ON_NEED_KEY				1	  //是否需要按按键开机配置
#if TCFG_PC_ENABLE
#define TCFG_LOWPOWER_VDDIOM_LEVEL			VDDIOM_VOL_32V             //VDDIO 设置的值要和vbat的压差要大于300mv左右，否则会出现DAC杂音
#endif

//*********************************************************************************//
//                                  蓝牙配置                                       //
//*********************************************************************************//
#if TCFG_RF_TEST_EN
#define TCFG_USER_BT_CLASSIC_ENABLE         1   //经典蓝牙功能使能
#endif

#define TCFG_USER_BLE_ENABLE                1   //BLE功能使能
#define BT_FOR_APP_EN                       0

#if TCFG_USER_BLE_ENABLE
//BLE多连接,多开注意RAM的使用

#define BLE_WIRELESS_SERVER_EN          1   //使能透传

#endif
//wifi抗干扰
#define TCFG_WIFI_DETECT_ENABLE			ENABLE
#define TCFG_WIFI_DETCET_PRIOR			ENABLE//2t1 client收数多 主机优先
#define WIRELESS_24G_CODE_ID            13

#define WIRELESS_HIGH_BW_EN             ENABLE
#if !WIRELESS_HIGH_BW_EN && WIRELESS_LOW_LATENCY
#error "!!!! no support"
#endif

#if WIRELESS_HIGH_BW_EN
#define WIRELESS_BLE_CONNECT_INTERVAL	2
#else
#define WIRELESS_BLE_CONNECT_INTERVAL	4//6//8
#endif /* WIRELESS_HIGH_BW_EN */

#if	(WIRELESS_MIC_STEREO_EN)
#define WIRELESS_CODING_CHANNEL_NUM		2 //编码通道通道数， 最大为2
#else
#define WIRELESS_CODING_CHANNEL_NUM		1 //编码通道通道数， 最大为2
#endif

#if WIRELESS_CODING_FRAME_LEN == 25
#define WIRELESS_CODING_BIT_RATE				(80000)
#else
#define WIRELESS_CODING_BIT_RATE				(64000)//(128000)
#endif
#if WIRELESS_LLNS_ENABLE&&WIRELESS_LOW_LATENCY
#define WIRELESS_CLK							160//tx需要跑快一点，否则算法可能跑不过来
#endif
//*********************************************************************************//
//                                  encoder 配置                                   //
//*********************************************************************************//
#define TCFG_ENC_JLA_ENABLE				    ENABLE

//*********************************************************************************//
//                                  decoder 配置                                   //
//*********************************************************************************//
#define TCFG_DEC_JLA_ENABLE				    DISABLE

#define TCFG_MEDIA_LIB_USE_MALLOC										1

#define TCFG_DEV_MANAGER_ENABLE											0
//*********************************************************************************//
//                                  不合理定义报错                                   //
//*********************************************************************************//
#if WIRELESS_LLNS_ENABLE
#if WIRELESS_CODING_SAMPLERATE == 44100
#error "llns no support 44100 samplerate"
#endif
#endif
#if WIRELESS_DENOISE_ENABLE
#if WIRELESS_CODING_SAMPLERATE != 32000
#error "denoise only support 32000 samplerate"
#endif
#endif
//*********************************************************************************//
//                                 配置结束                                         //
//*********************************************************************************//



#endif //CONFIG_BOARD_WIRELESS_MIC_2T1_TX
#endif //CONFIG_BOARD_WIRELESS_MIC_2T1_TX_CFG_H
