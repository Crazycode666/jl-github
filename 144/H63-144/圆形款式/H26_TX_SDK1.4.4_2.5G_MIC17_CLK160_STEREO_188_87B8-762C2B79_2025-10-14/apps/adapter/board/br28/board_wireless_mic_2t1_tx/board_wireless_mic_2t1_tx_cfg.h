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
#define WIRELESS_2T1_MICROPHONE_MODE	DISABLE
#define WIRELESS_24G_ENABLE				ENABLE //使能此功能可以屏蔽手机搜索到此无线设备名
#define WIRELESS_NOISEGATE_EN		    DISABLE	//噪声门限使能
#define WIRELESS_ECHO_ENABLE			DISABLE //混响
#define WIRELESS_PLATE_REVERB_ENABLE	DISABLE //混响,only support 701
#define WIRELESS_HOWLING_ENABLE			DISABLE	//防啸叫
#define WIRELESS_DENOISE_ENABLE			DISABLE //只支持32k采样率,降噪使能
#define WIRELESS_LLNS_ENABLE			DISABLE //支持16k,32k,48K采样率,低延时降噪,延时低，降噪算法时间5ms
//低延时模式,比非低延时模式少3ms，距离会变短，用户可根据产品应用场景选择,txrx需要保持一致
#define WIRELESS_LOW_LATENCY			DISABLE
//编解码采样率如果有修改，请对应修改另一方的编解码采样率
#define WIRELESS_CODING_SAMPLERATE		(48000)

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
#define WIRELESS_MIC_OUTPUT_DAC_SAMETIME	DISABLE

#define	WIRELESS_TOOL_BLE_NAME_EN		ENABLE
//rf测试，由工具触发样机进入dut模式
#define TCFG_RF_TEST_EN					DISABLE

//配对绑定
#define WIRELESS_PAIR_BONDING			DISABLE

//使用PA延长距离,需要硬件添加PA电路,默认使用PC2/PC3
#define CONFIG_BT_RF_USING_EXTERNAL_PA_EN	DISABLE

#if WIRELESS_CODING_FRAME_LEN == 100
#define TCFG_RF_OOB		1
#endif

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
#define TCFG_UART0_ENABLE					ENABLE_THIS_MOUDLE                     //串口打印模块使能
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
#define USB_DEVICE_CLASS_CONFIG             MASSSTORAGE_CLASS


//*********************************************************************************//
//                                  SD 配置                                        //
//*********************************************************************************//
#define TCFG_SD0_ENABLE						DISABLE_THIS_MOUDLE                    //SD0模块使能
#define TCFG_SD0_DAT_MODE					1               //线数设置，1：一线模式  4：四线模式
#define TCFG_SD0_DET_MODE					SD_CMD_DECT     //SD卡检测方式
#define TCFG_SD0_DET_IO                     IO_PORTB_03     //当检测方式为IO检测可用
#define TCFG_SD0_DET_IO_LEVEL               0               //当检测方式为IO检测可用,0：低电平检测到卡。 1：高电平(外部电源)检测到卡。 2：高电平(SD卡电源)检测到卡。
#define TCFG_SD0_CLK						(3000000 * 4L)  //SD卡时钟频率设置
#define TCFG_SD0_PORT_CMD					IO_PORTC_04//IO_PORTC_04
#define TCFG_SD0_PORT_CLK					IO_PORTC_05//IO_PORTC_05
#define TCFG_SD0_PORT_DA0					IO_PORTC_03//IO_PORTC_03
#define TCFG_SD0_PORT_DA1					NO_CONFIG_PORT  //当选择4线模式时要用
#define TCFG_SD0_PORT_DA2					NO_CONFIG_PORT
#define TCFG_SD0_PORT_DA3					NO_CONFIG_PORT

#define TCFG_SD_ALWAY_ONLINE_ENABLE         DISABLE
#define TCFG_KEEP_CARD_AT_ACTIVE_STATUS	    ENABLE	// 保持卡活跃状态。会增加功耗

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

// #define TCFG_IOKEY_PREV_CONNECT_WAY			ONE_PORT_TO_LOW  //按键一端接低电平一端接IO
// #define TCFG_IOKEY_PREV_ONE_PORT			IO_PORTB_00

// #define TCFG_IOKEY_NEXT_CONNECT_WAY 		ONE_PORT_TO_LOW  //按键一端接低电平一端接IO
// #define TCFG_IOKEY_NEXT_ONE_PORT			IO_PORTB_02
//*********************************************************************************//
//                                 rdec_key 配置                                      //
//*********************************************************************************//
#define TCFG_RDEC_KEY_ENABLE					DISABLE_THIS_MOUDLE //是否使能RDEC按键
//RDEC0配置
#define TCFG_RDEC0_ECODE1_PORT					IO_PORTB_02
#define TCFG_RDEC0_ECODE2_PORT					IO_PORTB_03
#define TCFG_RDEC0_KEY0_VALUE 				 	0
#define TCFG_RDEC0_KEY1_VALUE 				 	1

//RDEC1配置
#define TCFG_RDEC1_ECODE1_PORT					IO_PORTA_01
#define TCFG_RDEC1_ECODE2_PORT					IO_PORTA_02
#define TCFG_RDEC1_KEY0_VALUE 				 	2
#define TCFG_RDEC1_KEY1_VALUE 				 	3

//RDEC2配置
#define TCFG_RDEC2_ECODE1_PORT					IO_PORTB_00
#define TCFG_RDEC2_ECODE2_PORT					IO_PORTB_01
#define TCFG_RDEC2_KEY0_VALUE 				 	4
#define TCFG_RDEC2_KEY1_VALUE 				 	5


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
#define TCFG_CHARGE_OFF_POWERON_NE			DISABLE
#define TCFG_CHARGE_FULL_V					CHARGE_FULL_V_4199
#define TCFG_CHARGE_FULL_MA					CHARGE_FULL_mA_15
/*恒流充电电流可选配置*/
#define TCFG_CHARGE_MA						CHARGE_mA_60
/*涓流充电电流配置*/
#define TCFG_CHARGE_TRICKLE_MA              CHARGE_mA_10

//*********************************************************************************//
//                                  低功耗配置                                     //
//*********************************************************************************//
#define TCFG_LOWPOWER_POWER_SEL				PWR_DCDC15                   //电源模式设置，可选DCDC和LDO

//*********************************************************************************//
//                                 Audio配置                                       //
//*********************************************************************************//
#define TCFG_AUDIO_ADC_ENABLE				ENABLE_THIS_MOUDLE
#define TCFG_AUDIO_ADC_LINE_CHA				AUDIO_ADC_LINE0
#define TCFG_AUDIO_ADC_MIC_CHA				AUDIO_ADC_MIC_0
/*MIC LDO电流档位设置：
    0:0.625ua    1:1.25ua    2:1.875ua    3:2.5ua*/
#define TCFG_AUDIO_ADC_LDO_SEL				3

#define TCFG_AUDIO_DAC_ENABLE				ENABLE_THIS_MOUDLE
#define TCFG_AUDIO_DAC_LDO_SEL				1
/*
            DAC模式选择
#define DAC_MODE_L_DIFF          (0)  // 低压差分模式   , 适用于低功率差分耳机  , 输出幅度 0~2Vpp
#define DAC_MODE_H1_DIFF         (1)  // 高压1档差分模式, 适用于高功率差分耳机  , 输出幅度 0~3Vpp
#define DAC_MODE_H1_SINGLE       (2)  // 高压1档单端模式, 适用于高功率单端PA音箱, 输出幅度 0~1.5Vpp
#define DAC_MODE_H2_DIFF         (3)  // 高压2档差分模式, 适用于高功率差分PA音箱, 输出幅度 0~5Vpp
#define DAC_MODE_H2_SINGLE       (4)  // 高压2档单端模式, 适用于高功率单端PA音箱, 输出幅度 0~2.5Vpp
*/
#define TCFG_AUDIO_DAC_MODE         DAC_MODE_H1_SINGLE    // DAC_MODE_L_DIFF 低压， DAC_MODE_H1_DIFF 高压


/*
DACVDD电压设置(要根据具体的硬件接法来确定):
    DACVDD_LDO_1_20V        DACVDD_LDO_1_30V        DACVDD_LDO_2_35V        DACVDD_LDO_2_50V
    DACVDD_LDO_2_65V        DACVDD_LDO_2_80V        DACVDD_LDO_2_95V        DACVDD_LDO_3_10V*/
#define TCFG_AUDIO_DAC_LDO_VOLT				DACVDD_LDO_2_80V
/*预留接口，未使用*/
#define TCFG_AUDIO_DAC_PA_PORT				NO_CONFIG_PORT
/*
DAC硬件上的连接方式,可选的配置：
    DAC_OUTPUT_MONO_L               左声道
    DAC_OUTPUT_MONO_R               右声道
    DAC_OUTPUT_LR                   立体声
*/
#define TCFG_AUDIO_DAC_CONNECT_MODE    DAC_OUTPUT_MONO_LR_DIFF//DAC_OUTPUT_LR


#define AUDIO_OUT_WAY_TYPE           AUDIO_WAY_TYPE_DAC
#define LINEIN_INPUT_WAY            LINEIN_INPUT_WAY_ANALOG

#define AUDIO_OUTPUT_AUTOMUTE       0//ENABLE

#define  DUT_AUDIO_DAC_LDO_VOLT   				DACVDD_LDO_1_25V

//每个解码通道都开启数字音量管理,音量类型为VOL_TYPE_DIGGROUP时要使能
#define SYS_DIGVOL_GROUP_EN     DISABLE

#define SYS_VOL_TYPE            VOL_TYPE_DIGITAL


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

/*MIC模式配置:单端隔直电容模式/差分隔直电容模式/单端省电容模式*/
/*
 *默认使用差分麦， 对底噪有明显优化， 对于驻极体mic和模拟硅mic JL701N同封装芯片由MIC2_BIAS提供电压
 *如果是动圈麦， 可以不使能MIC2_BIAS， 可以在板级C文件将audio_adc_mic_ldo_en调用注释掉
 *如果使用单端麦，则配置AUDIO_MIC_CAP_MODE即可
 * */
#define TCFG_AUDIO_MIC_MODE					AUDIO_MIC_CAP_DIFF_MODE
#define TCFG_AUDIO_MIC1_MODE				AUDIO_MIC_CAP_MODE
#define TCFG_AUDIO_MIC2_MODE				AUDIO_MIC_CAP_MODE
#define TCFG_AUDIO_MIC3_MODE				AUDIO_MIC_CAP_MODE

/*
    *>>MIC电源管理:根据具体方案，选择对应的mic供电方式
	 *(1)如果是多种方式混合，则将对应的供电方式或起来即可，比如(MIC_PWR_FROM_GPIO | MIC_PWR_FROM_MIC_BIAS)
	  *(2)如果使用固定电源供电(比如dacvdd)，则配置成DISABLE_THIS_MOUDLE
	   */
#define MIC_PWR_FROM_GPIO		(1UL << 0)	//使用普通IO输出供电
#define MIC_PWR_FROM_MIC_BIAS	(1UL << 1)	//使用内部mic_ldo供电(有上拉电阻可配)
#define MIC_PWR_FROM_MIC_LDO	(1UL << 2)	//使用内部mic_ldo供电
//配置MIC电源
#define TCFG_AUDIO_MIC_PWR_CTL				MIC_PWR_FROM_MIC_BIAS

//使用内部mic_ldo供电(有上拉电阻可配)
#if (TCFG_AUDIO_MIC_PWR_CTL & MIC_PWR_FROM_MIC_BIAS)
#define TCFG_AUDIO_MIC0_BIAS_EN				ENABLE_THIS_MOUDLE/*Port:PA2*/
#define TCFG_AUDIO_MIC1_BIAS_EN				ENABLE_THIS_MOUDLE/*Port:PA4*/
#define TCFG_AUDIO_MIC2_BIAS_EN				ENABLE_THIS_MOUDLE/*Port:PG7*/
#define TCFG_AUDIO_MIC3_BIAS_EN				ENABLE_THIS_MOUDLE/*Port:PG5*/
#endif/*MIC_PWR_FROM_MIC_BIAS*/

//使用内部mic_ldo供电(Port:PA0)
#if (TCFG_AUDIO_MIC_PWR_CTL & MIC_PWR_FROM_MIC_LDO)
#define TCFG_AUDIO_MIC_LDO_EN				ENABLE_THIS_MOUDLE
#endif/*MIC_PWR_FROM_MIC_LDO*/
/*>>MIC电源管理配置结束*/


/*
 *支持省电容MIC模块
 *(1)要使能省电容mic,首先要支持该模块:TCFG_SUPPORT_MIC_CAPLESS
 *(2)只有支持该模块，才能使能该模块:TCFG_MIC_CAPLESS_ENABLE
 */
#define TCFG_SUPPORT_MIC_CAPLESS			ENABLE_THIS_MOUDLE
//省电容MIC使能
#define TCFG_MIC_CAPLESS_ENABLE				DISABLE_THIS_MOUDLE
//省电容MIC1使能
#define TCFG_MIC1_CAPLESS_ENABLE			DISABLE_THIS_MOUDLE

#if (WIRELESS_DENOISE_ENABLE)
#define WIRELESS_MIC_ADC_RESUME_CODING_EN   DISABLE
#else
#define WIRELESS_MIC_ADC_RESUME_CODING_EN   DISABLE
#endif
#define WIRELESS_MIC_ADC_GAIN				(7)//mic增益设置
#if (WIRELESS_CODING_SAMPLERATE == 44100)
#define WIRELESS_MIC_ADC_POINT_UNIT			(48000*WIRELESS_CODING_FRAME_LEN/10000)
#else
#define WIRELESS_MIC_ADC_POINT_UNIT			(WIRELESS_CODING_SAMPLERATE*WIRELESS_CODING_FRAME_LEN/10000)
#endif


//*********************************************************************************//
//                                  PWM_LED 配置                                       //
//******************************************************************************
#define TCFG_PWMLED_ENABLE					ENABLE_THIS_MOUDLE			//是否支持PMW LED推灯模块
#define TCFG_PWMLED_IOMODE					LED_ONE_IO_MODE				//LED模式，单IO还是两个IO推灯
#define TCFG_PWMLED_PIN						IO_PORTG_05					//LED使用的IO口 注意和led7是否有io冲突


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
#if 1
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


#endif
//*********************************************************************************//
//                                  系统配置                                         //
//*********************************************************************************//
#define TCFG_AUTO_SHUT_DOWN_TIME		    0        //动关机时间配置
#define TCFG_AUTO_SHUT_DOWN_BY_AUTO_MUTE    DISABLE  //配合TCFG_AUTO_SHUT_DOWN_TIME使用，在音频MUTE之后会触发关机计时
#define TCFG_SYS_LVD_EN						1   //电量检测使能
#define TCFG_POWER_ON_NEED_KEY				0	  //是否需要按按键开机配置
#if TCFG_PC_ENABLE
#define TCFG_LOWPOWER_VDDIOM_LEVEL			VDDIOM_VOL_32V             //VDDIO 设置的值要和vbat的压差要大于300mv左右，否则会出现DAC杂音
#endif
#define TCFG_LOWPOWER_OSC_TYPE              OSC_TYPE_LRC		//低功耗晶振类型，btosc/lrc

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
#define TCFG_WIFI_DETECT_ENABLE			DISABLE
#define TCFG_WIFI_DETCET_PRIOR			ENABLE//2t1 client收数多 主机优先
#define WIRELESS_24G_CODE_ID            13

#define WIRELESS_HIGH_BW_EN             ENABLE
#if !WIRELESS_HIGH_BW_EN && WIRELESS_LOW_LATENCY
"error !!!! no support"
#endif

//2t1 必须使用4
#if WIRELESS_HIGH_BW_EN
#define WIRELESS_BLE_CONNECT_INTERVAL	2
#else
#define WIRELESS_BLE_CONNECT_INTERVAL	4
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
#define WIRELESS_CLK							144//tx需要跑快一点，否则算法可能跑不过来
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


//*********************************************************************************//
//                                  录音 配置                                   //
//*********************************************************************************//
#define WIRELESS_MIC_RECORDER_ENABLE		DISABLE

#if WIRELESS_MIC_RECORDER_ENABLE
#define CONFIG_FATFS_ENABLE					ENABLE
#define TCFG_DEV_MANAGER_ENABLE											1
#if !TCFG_SD0_ENABLE
#undef TCFG_SD0_ENABLE
#define TCFG_SD0_ENABLE						ENABLE		//使能SD0录音
#endif
//录音文件格式
#define TCFG_ENC_MP3_ENABLE                 ENABLE
#define TCFG_ENC_ADPCM_ENABLE				DISABLE
//读卡器功能
#if !TCFG_PC_ENABLE
#undef TCFG_PC_ENABLE
#define TCFG_PC_ENABLE						ENABLE
#endif
#define TCFG_OTG_USB_DEV_EN					ENABLE
//发射端一直跑数据流,未连接时也可以录音
#define ALWAYS_RUN_STREAM					ENABLE
#endif

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
