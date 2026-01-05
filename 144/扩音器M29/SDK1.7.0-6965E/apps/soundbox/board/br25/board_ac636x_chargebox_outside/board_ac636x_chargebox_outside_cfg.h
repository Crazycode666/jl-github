#ifndef CONFIG_BOARD_AC636X_CHARGEBOX_OUTSIDE_CFG_H
#define CONFIG_BOARD_AC636X_CHARGEBOX_OUTSIDE_CFG_H

#ifdef CONFIG_BOARD_AC636X_CHARGEBOX_OUTSIDE

#define CONFIG_SDFILE_ENABLE
#define CONFIG_FLASH_SIZE       (1024 * 1024)

//*********************************************************************************//
//                                 配置开始                                        //
//*********************************************************************************//
#define ENABLE_THIS_MOUDLE					1
#define DISABLE_THIS_MOUDLE					0

#define ENABLE								1
#define DISABLE								0

#define LINEIN_INPUT_WAY_ANALOG      0
#define LINEIN_INPUT_WAY_ADC         1
#define LINEIN_INPUT_WAY_DAC         2

#define NO_CONFIG_PORT						(-1)

//*********************************************************************************//
//                                  app 配置                                       //
//*********************************************************************************//
#define TCFG_APP_BT_EN			            0
#define TCFG_APP_MUSIC_EN			        0
#define TCFG_APP_LINEIN_EN					0
#define TCFG_APP_FM_EN					    0
#define TCFG_APP_PC_EN					    0
#define TCFG_APP_RTC_EN					    0
#define TCFG_APP_RECORD_EN				    0
#define TCFG_APP_SPDIF_EN                   0
//*********************************************************************************//
//                               PCM_DEBUG调试配置                                 //
//*********************************************************************************//

//#define AUDIO_PCM_DEBUG					  	//PCM串口调试，写卡通话数据

//*********************************************************************************//
//                                 UART配置                                        //
//*********************************************************************************//
#define TCFG_UART0_ENABLE					ENABLE_THIS_MOUDLE                     //串口打印模块使能
#define TCFG_UART0_RX_PORT					NO_CONFIG_PORT                         //串口接收脚配置（用于打印可以选择NO_CONFIG_PORT）
#define TCFG_UART0_TX_PORT  				IO_PORT_DM                             //串口发送脚配置
#define TCFG_UART0_BAUDRATE  				1000000                                //串口波特率配置

//*********************************************************************************//
//                                 IIC配置                                        //
//*********************************************************************************//
/*软件IIC设置*/
#define TCFG_SW_I2C0_CLK_PORT               IO_PORTA_09                             //软件IIC  CLK脚选择
#define TCFG_SW_I2C0_DAT_PORT               IO_PORTA_10                             //软件IIC  DAT脚选择
#define TCFG_SW_I2C0_DELAY_CNT              50                                      //IIC延时参数，影响通讯时钟频率

/*硬件IIC端口选择
  SCL         SDA
  'A': IO_PORT_DP   IO_PORT_DM
  'B': IO_PORTC_04  IO_PORTC_05
  'C': IO_PORTB_06  IO_PORTB_07
  'D': IO_PORTA_05  IO_PORTA_06
 */
#define TCFG_HW_I2C0_PORTS                  'B'
#define TCFG_HW_I2C0_CLK                    100000                                  //硬件IIC波特率

//*********************************************************************************//
//                                 硬件SPI 配置                                        //
//*********************************************************************************//
#define	TCFG_HW_SPI1_ENABLE		DISABLE_THIS_MOUDLE
//A组IO:    DI: PB2     DO: PB1     CLK: PB0
//B组IO:    DI: PC3     DO: PC5     CLK: PC4
#define TCFG_HW_SPI1_PORT		'A'
#define TCFG_HW_SPI1_BAUD		4000000L
#define TCFG_HW_SPI1_MODE		SPI_MODE_BIDIR_1BIT
#define TCFG_HW_SPI1_ROLE		SPI_ROLE_MASTER

#define	TCFG_HW_SPI2_ENABLE		DISABLE_THIS_MOUDLE
//A组IO:    DI: PB8     DO: PB10    CLK: PB9
//B组IO:    DI: PA13    DO: DM      CLK: DP
#define TCFG_HW_SPI2_PORT		'A'
#define TCFG_HW_SPI2_BAUD		2000000L
#define TCFG_HW_SPI2_MODE		SPI_MODE_BIDIR_1BIT
#define TCFG_HW_SPI2_ROLE		SPI_ROLE_MASTER

//*********************************************************************************//
//                                 FLASH 配置                                      //
//*********************************************************************************//
#define TCFG_NORFLASH_DEV_ENABLE			DISABLE_THIS_MOUDLE //需要关闭SD0
#define TCFG_FLASH_DEV_SPI_HW_NUM			1// 1: SPI1    2: SPI2
#define TCFG_FLASH_DEV_SPI_CS_PORT	    	IO_PORTA_03

//*********************************************************************************//
//                                  充电参数配置                                   //
//*********************************************************************************//
//是否支持芯片内置充电
#define TCFG_CHARGE_ENABLE					DISABLE_THIS_MOUDLE
//是否支持开机充电
#define TCFG_CHARGE_POWERON_ENABLE			DISABLE
//是否支持拔出充电自动开机功能
#define TCFG_CHARGE_OFF_POWERON_NE			DISABLE

#define TCFG_CHARGE_FULL_V					CHARGE_FULL_V_4202
#define TCFG_CHARGE_FULL_MA					CHARGE_FULL_mA_10
#define TCFG_CHARGE_MA						CHARGE_mA_60

//*********************************************************************************//
//                                  SD 配置                                        //
//*********************************************************************************//
#define     SD_CMD_DECT 	0
#define     SD_CLK_DECT  	1
#define     SD_IO_DECT 		2

//A组IO: CMD:PC4    CLK:PC5    DAT0:PC3             //D组IO: CMD:PB2    CLK:PB0    DAT0:PB3
//B组IO: CMD:PB6    CLK:PB7    DAT0:PB5             //E组IO: CMD:PA4    CLK:PC5    DAT0:DM
//C组IO: CMD:PA4    CLK:PA2    DAT0:PA3             //F组IO: CMD:PB6    CLK:PB7    DAT0:PB4
#define TCFG_SD0_ENABLE						DISABLE_THIS_MOUDLE
#define TCFG_SD0_PORTS						'D'
#define TCFG_SD0_DAT_MODE					1//AC696x不支持4线模式
#define TCFG_SD0_DET_MODE                   SD_CLK_DECT
#define TCFG_SD0_DET_IO 					IO_PORT_DM//当SD_DET_MODE为2时有效
#define TCFG_SD0_DET_IO_LEVEL				0//IO检查，0：低电平检测到卡。 1：高电平(外部电源)检测到卡。 2：高电平(SD卡电源)检测到卡。
#define TCFG_SD0_CLK						(3000000*2L)

#define TCFG_SD0_SD1_USE_THE_SAME_HW	    DISABLE_THIS_MOUDLE
#if TCFG_SD0_SD1_USE_THE_SAME_HW
#define TCFG_SD1_ENABLE						1
#else
#define TCFG_SD1_ENABLE						0
#endif
#define TCFG_SD1_PORTS						'F'
#define TCFG_SD1_DAT_MODE					1//AC696x不支持4线模式
#define TCFG_SD1_DET_MODE					SD_CLK_DECT
#define TCFG_SD1_DET_IO 					IO_PORT_DM//当SD_DET_MODE为2时有效
#define TCFG_SD1_DET_IO_LEVEL				0//IO检查，0：低电平检测到卡。 1：高电平(外部电源)检测到卡。 2：高电平(SD卡电源)检测到卡。
#define TCFG_SD1_CLK						(3000000*2L)




#define TCFG_KEEP_CARD_AT_ACTIVE_STATUS      0 //保持卡活跃状态
#define TCFG_SD_ACTIVE_STATUS_CTL_EN         0



//*********************************************************************************//
//                                 USB 配置                                        //
//*********************************************************************************//
#define TCFG_PC_ENABLE						TCFG_APP_PC_EN//PC模块使能
#define TCFG_UDISK_ENABLE					DISABLE_THIS_MOUDLE//U盘模块使能
#define TCFG_OTG_USB_DEV_EN                 BIT(0)//USB0 = BIT(0)  USB1 = BIT(1)

#include "usb_std_class_def.h"


#define TCFG_USB_PORT_CHARGE            DISABLE

#define TCFG_USB_DM_MULTIPLEX_WITH_SD_DAT0       DISABLE


#if TCFG_USB_DM_MULTIPLEX_WITH_SD_DAT0
//复用情况下，如果使用此USB口作为充电（即LDO5V_IN连接到此USB口），
//TCFG_OTG_MODE需要或上TCFG_OTG_MODE_CHARGE，用来把charge从host区
//分开；否则不需要，如果LDO5V_IN与其他IO绑定，则不能或上
#define TCFG_DM_MULTIPLEX_WITH_SD_PORT      0//0:sd0  1:sd1 //dm 参与复用的sd配置
#undef TCFG_OTG_MODE
#define TCFG_OTG_MODE                       (TCFG_OTG_MODE_HOST|TCFG_OTG_MODE_SLAVE|TCFG_OTG_MODE_CHARGE|OTG_DET_DP_ONLY)

#undef USB_DEVICE_CLASS_CONFIG
#if TCFG_SD0_SD1_USE_THE_SAME_HW //开启了双卡的可以使能读卡器存续设备
#define     USB_DEVICE_CLASS_CONFIG (MASSSTORAGE_CLASS|SPEAKER_CLASS|MIC_CLASS|HID_CLASS)
#else
#define     USB_DEVICE_CLASS_CONFIG (SPEAKER_CLASS|MIC_CLASS|HID_CLASS)
#endif

#undef TCFG_SD0_DET_MODE
#define TCFG_SD0_DET_MODE					SD_CLK_DECT
#define TCFG_USB_SD_MULTIPLEX_IO            IO_PORTB_03

#endif

//*********************************************************************************//
//                                 fat_FLASH 配置                                      //
//*********************************************************************************//
#define TCFG_CODE_FLASH_ENABLE				DISABLE_THIS_MOUDLE

#define FLASH_INSIDE_REC_ENABLE             0

#if  TCFG_NORFLASH_DEV_ENABLE
#define TCFG_NOR_FAT                    1//ENABLE
#define TCFG_NOR_FS                     0//ENABLE
#define TCFG_NOR_REC                    1//ENABLE
#else
#define TCFG_NOR_FAT                    0//ENABLE
#define TCFG_NOR_FS                     0//ENABLE
#define TCFG_NOR_REC                    0//ENABLE
#endif

#define TCFG_VIRFAT_FLASH_ENABLE  0
#if TCFG_VIRFAT_FLASH_ENABLE
#undef TCFG_NOR_FS
#define TCFG_NOR_FS               1
#endif
// #define TCFG_VIRFAT_FLASH_SIMPLE


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
//*********************************************************************************//
//                                 iokey 配置                                      //
//*********************************************************************************//
#define TCFG_IOKEY_ENABLE					ENABLE_THIS_MOUDLE //是否使能IO按键

#define TCFG_IOKEY_POWER_CONNECT_WAY		ONE_PORT_TO_LOW    //按键一端接低电平一端接IO

#define TCFG_IOKEY_POWER_ONE_PORT			IO_PORTB_01        //IO按键端口

//*********************************************************************************//
//                                 adkey 配置                                      //
//*********************************************************************************//
#define TCFG_ADKEY_ENABLE                   DISABLE_THIS_MOUDLE//是否使能AD按键
#define TCFG_ADKEY_LED_IO_REUSE				DISABLE_THIS_MOUDLE	//ADKEY 和 LED IO复用，led只能设置蓝灯显示
#define TCFG_ADKEY_IR_IO_REUSE				DISABLE_THIS_MOUDLE	//ADKEY 和 红外IO复用
#define TCFG_ADKEY_LED_SPI_IO_REUSE			DISABLE_THIS_MOUDLE	//ADKEY 和 LED SPI IO复用
#define TCFG_ADKEY_PORT                     IO_PORTA_06         //AD按键端口(需要注意选择的IO口是否支持AD功能)
#define TCFG_ADKEY_AD_CHANNEL               AD_CH_PA6
#define TCFG_ADKEY_EXTERN_UP_ENABLE         ENABLE_THIS_MOUDLE //是否使用外部上拉

#if TCFG_ADKEY_EXTERN_UP_ENABLE
#define R_UP    220                 //22K，外部上拉阻值在此自行设置
#else
#define R_UP    100                 //10K，内部上拉默认10K
#endif

//必须从小到大填电阻，没有则同VDDIO,填0x3ffL
#define TCFG_ADKEY_AD0      (0)                                 //0R
#define TCFG_ADKEY_AD1      (0x3ffL * 30   / (30   + R_UP))     //3k
#define TCFG_ADKEY_AD2      (0x3ffL * 62   / (62   + R_UP))     //6.2k
#define TCFG_ADKEY_AD3      (0x3ffL * 91   / (91   + R_UP))     //9.1k
#define TCFG_ADKEY_AD4      (0x3ffL * 150  / (150  + R_UP))     //15k
#define TCFG_ADKEY_AD5      (0x3ffL * 240  / (240  + R_UP))     //24k
#define TCFG_ADKEY_AD6      (0x3ffL * 330  / (330  + R_UP))     //33k
#define TCFG_ADKEY_AD7      (0x3ffL * 510  / (510  + R_UP))     //51k
#define TCFG_ADKEY_AD8      (0x3ffL * 1000 / (1000 + R_UP))     //100k
#define TCFG_ADKEY_AD9      (0x3ffL * 2200 / (2200 + R_UP))     //220k
#define TCFG_ADKEY_VDDIO    (0x3ffL)

#define TCFG_ADKEY_VOLTAGE0 ((TCFG_ADKEY_AD0 + TCFG_ADKEY_AD1) / 2)
#define TCFG_ADKEY_VOLTAGE1 ((TCFG_ADKEY_AD1 + TCFG_ADKEY_AD2) / 2)
#define TCFG_ADKEY_VOLTAGE2 ((TCFG_ADKEY_AD2 + TCFG_ADKEY_AD3) / 2)
#define TCFG_ADKEY_VOLTAGE3 ((TCFG_ADKEY_AD3 + TCFG_ADKEY_AD4) / 2)
#define TCFG_ADKEY_VOLTAGE4 ((TCFG_ADKEY_AD4 + TCFG_ADKEY_AD5) / 2)
#define TCFG_ADKEY_VOLTAGE5 ((TCFG_ADKEY_AD5 + TCFG_ADKEY_AD6) / 2)
#define TCFG_ADKEY_VOLTAGE6 ((TCFG_ADKEY_AD6 + TCFG_ADKEY_AD7) / 2)
#define TCFG_ADKEY_VOLTAGE7 ((TCFG_ADKEY_AD7 + TCFG_ADKEY_AD8) / 2)
#define TCFG_ADKEY_VOLTAGE8 ((TCFG_ADKEY_AD8 + TCFG_ADKEY_AD9) / 2)
#define TCFG_ADKEY_VOLTAGE9 ((TCFG_ADKEY_AD9 + TCFG_ADKEY_VDDIO) / 2)

#define TCFG_ADKEY_VALUE0                   0
#define TCFG_ADKEY_VALUE1                   1
#define TCFG_ADKEY_VALUE2                   2
#define TCFG_ADKEY_VALUE3                   3
#define TCFG_ADKEY_VALUE4                   4
#define TCFG_ADKEY_VALUE5                   5
#define TCFG_ADKEY_VALUE6                   6
#define TCFG_ADKEY_VALUE7                   7
#define TCFG_ADKEY_VALUE8                   8
#define TCFG_ADKEY_VALUE9                   9

//*********************************************************************************//
//                                 irkey 配置                                      //
//*********************************************************************************//
#define TCFG_IRKEY_ENABLE                   DISABLE_THIS_MOUDLE//是否使能ir按键
#define TCFG_IRKEY_PORT                     IO_PORTA_02        //IR按键端口

//*********************************************************************************//
//                             tocuh key 配置 (不支持)                                      //
//*********************************************************************************//
//#define TCFG_TOUCH_KEY_ENABLE 				ENABLE_THIS_MOUDLE 		//是否使能触摸按键
#define TCFG_TOUCH_KEY_ENABLE 				DISABLE_THIS_MOUDLE 		//是否使能触摸按键

/* 触摸按键计数参考时钟选择, 频率越高, 精度越高
** 可选参数:
	1.TOUCH_KEY_OSC_CLK,
    2.TOUCH_KEY_MUX_IN_CLK,  //外部输入, ,一般不用, 保留
    3.TOUCH_KEY_PLL_192M_CLK,
    4.TOUCH_KEY_PLL_240M_CLK,
*/
#define TCFG_TOUCH_KEY_CLK 					TOUCH_KEY_PLL_192M_CLK 	//触摸按键时钟配置
#define TCFG_TOUCH_KEY_CHANGE_GAIN 			4 	//变化放大倍数, 一般固定
#define TCFG_TOUCH_KEY_PRESS_CFG 			-100//触摸按下灵敏度, 类型:s16, 数值越大, 灵敏度越高
#define TCFG_TOUCH_KEY_RELEASE_CFG0 		-50 //触摸释放灵敏度0, 类型:s16, 数值越大, 灵敏度越高
#define TCFG_TOUCH_KEY_RELEASE_CFG1 		-80 //触摸释放灵敏度1, 类型:s16, 数值越大, 灵敏度越高

//key0配置
#define TCFG_TOUCH_KEY0_PORT 				IO_PORTB_06  //触摸按键IO配置
#define TCFG_TOUCH_KEY0_VALUE 				1 		 	 //触摸按键key0 按键值

//key1配置
#define TCFG_TOUCH_KEY1_PORT 				IO_PORTB_07  //触摸按键key1 IO配置
#define TCFG_TOUCH_KEY1_VALUE 				2 		 	 //触摸按键key1按键值

//*********************************************************************************//
//                            ctmu tocuh key 配置 (不支持)                                     //
//*********************************************************************************//
#define TCFG_CTMU_TOUCH_KEY_ENABLE              DISABLE_THIS_MOUDLE             //是否使能CTMU触摸按键
//key0配置
#define TCFG_CTMU_TOUCH_KEY0_PORT 				IO_PORTB_06  //触摸按键key0 IO配置
#define TCFG_CTMU_TOUCH_KEY0_VALUE 				0 		 	 //触摸按键key0 按键值

//key1配置
#define TCFG_CTMU_TOUCH_KEY1_PORT 				IO_PORTB_07  //触摸按键key1 IO配置
#define TCFG_CTMU_TOUCH_KEY1_VALUE 				1 		 	 //触摸按键key1 按键值

//*********************************************************************************//
//                                 rdec_key 配置                                      //
//*********************************************************************************//
#define TCFG_RDEC_KEY_ENABLE					DISABLE_THIS_MOUDLE //是否使能RDEC按键
//RDEC0配置
#define TCFG_RDEC0_ECODE1_PORT					IO_PORTA_03
#define TCFG_RDEC0_ECODE2_PORT					IO_PORTA_04
#define TCFG_RDEC0_KEY0_VALUE 				 	0
#define TCFG_RDEC0_KEY1_VALUE 				 	1

//RDEC1配置
#define TCFG_RDEC1_ECODE1_PORT					IO_PORTB_02
#define TCFG_RDEC1_ECODE2_PORT					IO_PORTB_03
#define TCFG_RDEC1_KEY0_VALUE 				 	2
#define TCFG_RDEC1_KEY1_VALUE 				 	3

//RDEC2配置
#define TCFG_RDEC2_ECODE1_PORT					IO_PORTB_04
#define TCFG_RDEC2_ECODE2_PORT					IO_PORTB_05
#define TCFG_RDEC2_KEY0_VALUE 				 	4
#define TCFG_RDEC2_KEY1_VALUE 				 	5

//*********************************************************************************//
//                                 Audio配置                                       //
//*********************************************************************************//
#define TCFG_AUDIO_ADC_ENABLE				ENABLE_THIS_MOUDLE
//MIC只有一个声道，固定选择右声道
#define TCFG_AUDIO_ADC_MIC_CHA				LADC_CH_MIC_R
/*MIC LDO电流档位设置：
    0:0.625ua    1:1.25ua    2:1.875ua    3:2.5ua*/
#define TCFG_AUDIO_ADC_LDO_SEL				2

// LADC通道
#define TCFG_AUDIO_ADC_LINE_CHA0			LADC_LINE1_MASK
#define TCFG_AUDIO_ADC_LINE_CHA1			LADC_CH_LINE0_L

#define TCFG_AUDIO_DAC_ENABLE				ENABLE_THIS_MOUDLE
#define TCFG_AUDIO_DAC_LDO_SEL				1
/*
DACVDD电压设置(要根据具体的硬件接法来确定):
    DACVDD_LDO_1_20V        DACVDD_LDO_1_30V        DACVDD_LDO_2_35V        DACVDD_LDO_2_50V
    DACVDD_LDO_2_65V        DACVDD_LDO_2_80V        DACVDD_LDO_2_95V        DACVDD_LDO_3_10V*/
#define TCFG_AUDIO_DAC_LDO_VOLT				DACVDD_LDO_2_90V
/*预留接口，未使用*/
#define TCFG_AUDIO_DAC_PA_PORT				NO_CONFIG_PORT
/*
DAC硬件上的连接方式,可选的配置：
    DAC_OUTPUT_MONO_L               左声道
    DAC_OUTPUT_MONO_R               右声道
    DAC_OUTPUT_LR                   立体声
    DAC_OUTPUT_MONO_LR_DIFF         单声道差分输出
*/
#define TCFG_AUDIO_DAC_CONNECT_MODE    DAC_OUTPUT_LR



#define AUDIO_OUTPUT_WAY_DAC        0
#define AUDIO_OUTPUT_WAY_IIS        1
#define AUDIO_OUTPUT_WAY_FM         2
#define AUDIO_OUTPUT_WAY_HDMI       3
#define AUDIO_OUTPUT_WAY_SPDIF      4
#define AUDIO_OUTPUT_WAY_BT      	5	// bt emitter
#define AUDIO_OUTPUT_WAY_DONGLE		7
#define AUDIO_OUTPUT_WAY            AUDIO_OUTPUT_WAY_DAC
#define LINEIN_INPUT_WAY            LINEIN_INPUT_WAY_ANALOG

#define AUDIO_OUTPUT_AUTOMUTE       0//ENABLE
/*
 *系统音量类型选择
 *软件数字音量是指纯软件对声音进行运算后得到的
 *硬件数字音量是指dac内部数字模块对声音进行运算后输出
 */
#define VOL_TYPE_DIGITAL		0	//软件数字音量
#define VOL_TYPE_ANALOG			1	//硬件模拟音量
#define VOL_TYPE_AD				2	//联合音量(模拟数字混合调节)
#define VOL_TYPE_DIGITAL_HW		3  	//硬件数字音量
#define VOL_TYPE_DIGGROUP       4   //独立通道数字音量

//每个解码通道都开启数字音量管理,音量类型为VOL_TYPE_DIGGROUP时要使能
#define SYS_DIGVOL_GROUP_EN     DISABLE


#define SYS_VOL_TYPE            VOL_TYPE_ANALOG

#if  (SYS_VOL_TYPE == VOL_TYPE_DIGGROUP)
#undef SYS_DIGVOL_GROUP_EN
#define SYS_DIGVOL_GROUP_EN     ENABLE
#endif



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

/*
 *支持省电容MIC模块
 *(1)要使能省电容mic,首先要支持该模块:TCFG_SUPPORT_MIC_CAPLESS
 *(2)只有支持该模块，才能使能该模块:TCFG_MIC_CAPLESS_ENABLE
 */
#define TCFG_SUPPORT_MIC_CAPLESS			ENABLE_THIS_MOUDLE
//省电容MIC使能
#define TCFG_MIC_CAPLESS_ENABLE				DISABLE_THIS_MOUDLE
//AudioEffects代码链接管理
#define AUDIO_EFFECTS_DRC_AT_RAM			0
#define AUDIO_EFFECTS_REVERB_AT_RAM			0
#define AUDIO_EFFECTS_ECHO_AT_RAM			0
#define AUDIO_EFFECTS_AFC_AT_RAM			0
#define AUDIO_EFFECTS_EQ_AT_RAM				0
#define AUDIO_EFFECTS_NOISEGATE_AT_RAM		0
#define AUDIO_EFFECTS_MIC_EFFECT_AT_RAM		0
#define AUDIO_EFFECTS_MIC_STREAM_AT_RAM		0
#define AUDIO_EFFECTS_DEBUG_AT_RAM			0
#define AUDIO_EFFECTS_SURROUND_AT_RAM       0

//*********************************************************************************//
//                                  充电仓配置                                     //
//*********************************************************************************//
#define TCFG_CHARGESTORE_ENABLE				DISABLE_THIS_MOUDLE       //是否支持智能充点仓
#define TCFG_TEST_BOX_ENABLE			    1
#define TCFG_CHARGESTORE_PORT				IO_PORT_DP                //耳机和充点仓通讯的IO口
#define TCFG_CHARGESTORE_UART_ID			IRQ_UART1_IDX             //通讯使用的串口号

#ifdef AUDIO_PCM_DEBUG
#ifdef	TCFG_TEST_BOX_ENABLE
#undef 	TCFG_TEST_BOX_ENABLE
#define TCFG_TEST_BOX_ENABLE				0		//因为使用PCM使用到了串口1
#endif
#endif/*AUDIO_PCM_DEBUG*/

//*********************************************************************************//
//                                  LED 配置                                       //
//******************************************************************************
#if TCFG_ADKEY_LED_IO_REUSE
//打开ADKEY和LED IO复用功能，LED使用ADKEY_IO
#define TCFG_PWMLED_ENABLE					ENABLE_THIS_MOUDLE			//是否支持PMW LED推灯模块
#define TCFG_PWMLED_IOMODE					LED_ONE_IO_MODE				//LED模式，单IO还是两个IO推灯
#define TCFG_PWMLED_PIN						TCFG_ADKEY_PORT						//LED使用的IO口

#else

#define TCFG_PWMLED_ENABLE					DISABLE_THIS_MOUDLE			//是否支持PMW LED推灯模块
#define TCFG_PWMLED_IOMODE					LED_TWO_IO_MODE				//LED模式，单IO还是两个IO推灯
#define TCFG_PWMLED_PIN0					IO_PORTA_04					//LED
#define TCFG_PWMLED_PIN1					IO_PORT_DM 					//LED

#endif
//*********************************************************************************//
//                                  UI 配置                                        //
//*********************************************************************************//
#define TCFG_UI_ENABLE 						DISABLE_THIS_MOUDLE 	//UI总开关
#define CONFIG_UI_STYLE                     STYLE_JL_LED7
#define TCFG_UI_LED7_ENABLE 			 	ENABLE_THIS_MOUDLE 	//UI使用LED7显示
// #define TCFG_UI_LCD_SEG3X9_ENABLE 		ENABLE_THIS_MOUDLE 	//UI使用LCD段码屏显示
// #define TCFG_LCD_ST7735S_ENABLE	        ENABLE_THIS_MOUDLE
// #define TCFG_LCD_ST7789VW_ENABLE	        ENABLE_THIS_MOUDLE
#define TCFG_SPI_LCD_ENABLE                 DISABLE_THIS_MOUDLE //spi lcd开关
#define TCFG_TFT_LCD_DEV_SPI_HW_NUM		    1// 1: SPI1    2: SPI2 配置lcd选择的spi口
#define TCFG_LED7_RUN_RAM 					DISABLE_THIS_MOUDLE 	//led7跑ram 不屏蔽中断(需要占据2k附近ram)

//*********************************************************************************//
//                                  时钟配置                                       //
//*********************************************************************************//
// #define TCFG_CLOCK_SYS_SRC					SYS_CLOCK_INPUT_PLL_BT_OSC   //系统时钟源选择
#define TCFG_CLOCK_SYS_SRC					SYS_CLOCK_INPUT_PLL_RCL      //系统时钟源选择
#define TCFG_CLOCK_SYS_HZ					24000000                     //系统时钟设置
#define TCFG_CLOCK_OSC_HZ					24000000                     //外界晶振频率设置
#define TCFG_CLOCK_MODE                     CLOCK_MODE_ADAPTIVE

//*********************************************************************************//
//                                  低功耗配置                                     //
//*********************************************************************************//
#define TCFG_LOWPOWER_POWER_SEL				PWR_LDO15                    //电源模式设置，可选DCDC和LDO
#define TCFG_LOWPOWER_BTOSC_DISABLE			0                            //低功耗模式下BTOSC是否保持
#define TCFG_LOWPOWER_LOWPOWER_SEL			SLEEP_EN                  //SNIFF状态下芯片是否进入powerdown
/*强VDDIO等级配置,可选：
    VDDIOM_VOL_20V    VDDIOM_VOL_22V    VDDIOM_VOL_24V    VDDIOM_VOL_26V
    VDDIOM_VOL_30V    VDDIOM_VOL_30V    VDDIOM_VOL_32V    VDDIOM_VOL_36V*/
#define TCFG_LOWPOWER_VDDIOM_LEVEL			VDDIOM_VOL_32V    //VDDIO 设置的值要和vbat的压差要大于300mv左右，否则会出现DAC杂音
/*弱VDDIO等级配置，可选：
    VDDIOW_VOL_21V    VDDIOW_VOL_24V    VDDIOW_VOL_28V    VDDIOW_VOL_32V*/
#define TCFG_LOWPOWER_VDDIOW_LEVEL			VDDIOW_VOL_28V               //弱VDDIO等级配置
#if (TCFG_CLOCK_SYS_SRC == SYS_CLOCK_INPUT_PLL_RCL)
#define TCFG_LOWPOWER_OSC_TYPE              OSC_TYPE_LRC
#endif

//*********************************************************************************//
//                                  EQ配置                                         //
//*********************************************************************************//
#define TCFG_EQ_ENABLE                      	1     //支持EQ功能,EQ总使能
#if TCFG_EQ_ENABLE
#define TCFG_BT_MUSIC_EQ_ENABLE             	1     //支持蓝牙音乐EQ
#define TCFG_PHONE_EQ_ENABLE                	1     //支持通话近端EQ
#define TCFG_AEC_DCCS_EQ_ENABLE           	    1     // AEC DCCS
#define TCFG_AEC_UL_EQ_ENABLE           	    1     // AEC UL
#define TCFG_MUSIC_MODE_EQ_ENABLE           	1     //支持音乐模式EQ
#define TCFG_LINEIN_MODE_EQ_ENABLE          	1     //支持linein近端EQ
#define TCFG_FM_MODE_EQ_ENABLE              	0     //支持fm模式EQ
#define TCFG_SPDIF_MODE_EQ_ENABLE           	1     //支持SPDIF模式EQ
#define TCFG_PC_MODE_EQ_ENABLE              	1     //支持pc模式EQ
#define TCFG_AUDIO_OUT_EQ_ENABLE				0 	  //高低音EQ
#define TCFG_AUDIO_MIC_EFFECT_POST_EQ_ENABLE	0	  //MIC音效后置EQ使能(includes DRC)


#define EQ_SECTION_MAX                      20//eq 段数
#define TCFG_DYNAMIC_EQ_ENABLE              0     //动态eq使能，接在eq后，需输入32bit位宽数据
#endif//TCFG_EQ_ENABLE

#define TCFG_DRC_ENABLE						1 	  //DRC 总使能
#define TCFG_AUDIO_MDRC_ENABLE              0     //多带drc使能  0:关闭多带drc，  1：使能多带drc  2：使能多带drc 并且 多带drc后再做一次全带的drc
#if TCFG_DRC_ENABLE
#define TCFG_BT_MUSIC_DRC_ENABLE            1     //支持蓝牙音乐DRC
#define TCFG_MUSIC_MODE_DRC_ENABLE          1     //支持音乐模式DRC
#define TCFG_LINEIN_MODE_DRC_ENABLE         1     //支持LINEIN模式DRC
#define TCFG_FM_MODE_DRC_ENABLE             0     //支持FM模式DRC
#define TCFG_SPDIF_MODE_DRC_ENABLE          1     //支持SPDIF模式DRC
#define TCFG_PC_MODE_DRC_ENABLE             1     //支持PC模式DRC
#define TCFG_AUDIO_OUT_DRC_ENABLE			0 	  //高低音EQ后的drc
#define TCFG_PHONE_DRC_ENABLE               0     //支持通话近端DRC(下行drc)
#endif//TCFG_DRC_ENABLE

#define LINEIN_MODE_SOLE_EQ_EN              0  //linein模式是否需要独立的eq与drc

//*********************************************************************************//
//                          新音箱配置工具 && 调音工具                             //
//*********************************************************************************//
#define TCFG_SOUNDBOX_TOOL_ENABLE			DISABLE		  	//是否支持音箱在线配置工具
#define TCFG_EFFECT_TOOL_ENABLE				DISABLE		  	//是否支持在线音效调试,使能该项还需使能EQ总使能TCFG_EQ_ENABL,
#define TCFG_NULL_COMM						0				//不支持通信
#define TCFG_UART_COMM						1				//串口通信
#define TCFG_USB_COMM						2				//USB通信
#if (TCFG_SOUNDBOX_TOOL_ENABLE || TCFG_EFFECT_TOOL_ENABLE)
#define TCFG_COMM_TYPE						TCFG_USB_COMM	//通信方式选择
#else
#define TCFG_COMM_TYPE						TCFG_NULL_COMM
#endif
#define TCFG_ONLINE_TX_PORT					IO_PORT_DP      //UART模式调试TX口选择
#define TCFG_ONLINE_RX_PORT					IO_PORT_DM      //UART模式调试RX口选择
#define TCFG_ONLINE_ENABLE                  (TCFG_EFFECT_TOOL_ENABLE)    //是否支持音效在线调试功能

/***********************************非用户配置区***********************************/
#if (TCFG_SOUNDBOX_TOOL_ENABLE || TCFG_ONLINE_ENABLE)
#if TCFG_COMM_TYPE == TCFG_UART_COMM
#undef TCFG_UDISK_ENABLE
#define TCFG_UDISK_ENABLE 0
#undef TCFG_SD0_PORTS
#define TCFG_SD0_PORTS 'D'
#endif
#endif

#include "usb_std_class_def.h"
#if (TCFG_SOUNDBOX_TOOL_ENABLE || TCFG_EFFECT_TOOL_ENABLE)
#if (TCFG_COMM_TYPE == TCFG_USB_COMM)
#define TCFG_USB_CDC_BACKGROUND_RUN         ENABLE
#if (TCFG_USB_CDC_BACKGROUND_RUN && (!TCFG_PC_ENABLE))
#undef TCFG_OTG_USB_DEV_EN
#define TCFG_OTG_USB_DEV_EN                 0
#endif
#endif
#if (TCFG_COMM_TYPE == TCFG_UART_COMM)
#define TCFG_USB_CDC_BACKGROUND_RUN         DISABLE
#endif
#endif
/**********************************************************************************/


//*********************************************************************************//
//                                  混响配置                                   //
//*********************************************************************************//
#define TCFG_MIC_EFFECT_ENABLE       0//DISABLE
#define TCFG_MIC_EFFECT_START_DIR    0//开机直接启动混响

#define MIC_EFFECT_REVERB             1//混响
#define MIC_EFFECT_ECHO               2//回声
#define MIC_EFFECT_REVERB_ECHO        3//混响+回声
#define MIC_EFFECT_MEGAPHONE          4//大声公
// #define TCFG_MIC_EFFECT_SEL           MIC_EFFECT_REVERB
#define TCFG_MIC_EFFECT_SEL           MIC_EFFECT_ECHO


#define CALLING_MIC_EFFECT_DISABLE            DISABLE //通话过程中是否关闭混响 1关闭 0不关闭;//置1后会使用默认TCFG_AEC_ENABLE设置
#define TCFG_MIC_VOICE_CHANGER_ENABLE         DISABLE  //变声模块使能
#define TCFG_MIC_AUTOTUNE_ENABLE              DISABLE//电音模块使能
#define TCFG_MIC_TUNNING_EQ_ENABLE            DISABLE//混响高低音使能
/***********************************非用户配置区***********************************/
#if TCFG_MIC_EFFECT_ENABLE
#undef EQ_SECTION_MAX
#define EQ_SECTION_MAX 25
#undef AUDIO_EFFECTS_DRC_AT_RAM
#define AUDIO_EFFECTS_DRC_AT_RAM 1  //开混响DRC放ram


#if (!CALLING_MIC_EFFECT_DISABLE)
#ifdef TCFG_AEC_ENABLE
#undef TCFG_AEC_ENABLE
#define TCFG_AEC_ENABLE 0
#endif
#endif//TCFG_AEC_ENABLE

#if TCFG_DYNAMIC_EQ_ENABLE
#undef TCFG_DYNAMIC_EQ_ENABLE
#define TCFG_DYNAMIC_EQ_ENABLE 0
#endif

#if TCFG_AUDIO_MDRC_ENABLE
#undef TCFG_AUDIO_MDRC_ENABLE
#define TCFG_AUDIO_MDRC_ENABLE 0
#endif
#if !TCFG_EQ_ENABLE
#undef TCFG_EQ_ENABLE
#define TCFG_EQ_ENABLE 1//混响必开eq
#endif
#if !TCFG_DRC_ENABLE
#undef TCFG_DRC_ENABLE
#define TCFG_DRC_ENABLE 1//混响必开drc
#endif

#endif
/**********************************************************************************/

#define TCFG_MIC_DODGE_EN  0//闪避是否使能


#define TCFG_REVERB_SAMPLERATE_DEFUAL  (44100)
#define MIC_EFFECT_SAMPLERATE			(44100L)

#if TCFG_MIC_EFFECT_ENABLE
#undef MIC_SamplingFrequency
#define     MIC_SamplingFrequency         1
#undef MIC_AUDIO_RATE
#define     MIC_AUDIO_RATE              MIC_EFFECT_SAMPLERATE
#undef  SPK_AUDIO_RATE
#define SPK_AUDIO_RATE                  TCFG_REVERB_SAMPLERATE_DEFUAL
#endif




/*********扩音器功能使用mic_effect.c混响流程，功能选配在effect_reg.c中 ***********/
/*********配置MIC_EFFECT_CONFIG宏定义即可********************************/
#define TCFG_LOUDSPEAKER_ENABLE            DISABLE //扩音器功能使能
#define TCFG_USB_MIC_ECHO_ENABLE           DISABLE //不能与TCFG_MIC_EFFECT_ENABLE同时打开
#define TCFG_USB_MIC_DATA_FROM_MICEFFECT   DISABLE //要确保开usbmic前已经开启混响
#define TCFG_KARAOKE_EARPHONE              DISABLE

//*********************************************************************************//
//                                  g-sensor配置                                   //
//*********************************************************************************//
#define TCFG_GSENSOR_ENABLE                       0     //gSensor使能
#define TCFG_DA230_EN                             0
#define TCFG_SC7A20_EN                            0
#define TCFG_STK8321_EN                           0
#define TCFG_GSENOR_USER_IIC_TYPE                 0     //0:软件IIC  1:硬件IIC

//*********************************************************************************//
//                                  系统配置                                         //
//*********************************************************************************//
#define TCFG_AUTO_SHUT_DOWN_TIME		    0   //没有蓝牙连接自动关机时间
#define TCFG_SYS_LVD_EN						0   //电量检测使能
#define TCFG_POWER_ON_NEED_KEY				0	  //是否需要按按键开机配置
#define TWFG_APP_POWERON_IGNORE_DEV         4000//上电忽略挂载设备，0时不忽略，非0则n毫秒忽略

//*********************************************************************************//
//                                  AI配置                                       //
//*********************************************************************************//
#if ((TCFG_CLOCK_SYS_SRC == SYS_CLOCK_INPUT_PLL_BT_OSC) && TCFG_APP_BT_EN)
#define CONFIG_APP_BT_ENABLE // AI功能、流程总开关
#endif

#ifdef CONFIG_APP_BT_ENABLE
#define    TRANS_DATA_EN                    0
#define    SMART_BOX_EN 			        1
#define	   ANCS_CLIENT_EN			        0
#define	   BLE_CLIENT_EN 			 		0
#else
#define    TRANS_DATA_EN                    0
#define    SMART_BOX_EN 			        0
#define	   ANCS_CLIENT_EN			        0
#define	   BLE_CLIENT_EN 			 		0
#endif

#if (SMART_BOX_EN)                          //rcsp需要打开ble
#define CONFIG_DOUBLE_BANK_ENABLE           0
#define RCSP_UPDATE_EN		                1     //是否支持rcsp升级
#define OTA_TWS_SAME_TIME_ENABLE            0     //是否支持TWS同步升级
#define UPDATE_MD5_ENABLE                   1     //升级是否支持MD5校验
#define RCSP_FILE_OPT				        0
#define JL_EARPHONE_APP_EN			        0
#define TCFG_LFN_EN					        0
#define TCFG_BS_DEV_PATH_EN			        0
#else
#define OTA_TWS_SAME_TIME_ENABLE            0
#define RCSP_UPDATE_EN                      0
#define UPDATE_MD5_ENABLE                   0     //升级是否支持MD5校验
#define RCSP_FILE_OPT				        0
#define JL_EARPHONE_APP_EN			        0
#endif


//*********************************************************************************//
//                                  蓝牙配置                                       //
//*********************************************************************************//
#define TCFG_USER_TWS_ENABLE                0   //tws功能使能
#ifdef CONFIG_APP_BT_ENABLE
#define TCFG_USER_BLE_ENABLE                1   //BLE功能使能
#else
#define TCFG_USER_BLE_ENABLE                0   //BLE功能使能
#endif
#define TCFG_USER_BT_CLASSIC_ENABLE         1   //经典蓝牙功能使能
#define TCFG_BT_SUPPORT_AAC                 0   //AAC格式支持
#define TCFG_USER_EMITTER_ENABLE            0   //(暂不支持)emitter功能使能
#define TCFG_BT_SNIFF_ENABLE                0   //bt sniff 功能使能

#define USER_SUPPORT_PROFILE_SPP    0
#define USER_SUPPORT_PROFILE_HFP    1
#define USER_SUPPORT_PROFILE_A2DP   1
#define USER_SUPPORT_PROFILE_AVCTP  1
#define USER_SUPPORT_PROFILE_HID    0
#define USER_SUPPORT_PROFILE_PNP    1
#define USER_SUPPORT_PROFILE_PBAP   0



#if TCFG_USER_TWS_ENABLE
#define TCFG_BD_NUM						    1   //连接设备个数配置
#define TCFG_AUTO_STOP_PAGE_SCAN_TIME       0   //配置一拖二第一台连接后自动关闭PAGE SCAN的时间(单位分钟)
#define TCFG_USER_ESCO_SLAVE_MUTE           1   //对箱通话slave出声音
#else
#define TCFG_BD_NUM						    1   //连接设备个数配置
#define TCFG_AUTO_STOP_PAGE_SCAN_TIME       0 //配置一拖二第一台连接后自动关闭PAGE SCAN的时间(单位分钟)
#define TCFG_USER_ESCO_SLAVE_MUTE           0   //对箱通话slave出声音
#endif

#define BT_INBAND_RINGTONE                  0   //是否播放手机自带来电铃声
#define BT_PHONE_NUMBER                     0   //是否播放来电报号
#define BT_SYNC_PHONE_RING                  0   //是否TWS同步播放来电铃声
#define BT_SUPPORT_DISPLAY_BAT              1   //是否使能电量检测
#define BT_SUPPORT_MUSIC_VOL_SYNC           0   //是否使能音量同步

#define TCFG_BLUETOOTH_BACK_MODE			0	//不支持后台模式

#if(TCFG_BLUETOOTH_BACK_MODE)
#error "ont support background mode!!!!"
#endif

#if (TCFG_BLUETOOTH_BACK_MODE == 0)
//696非后台解码库空间使用overlay
#ifdef TCFG_MEDIA_LIB_USE_MALLOC
#undef TCFG_MEDIA_LIB_USE_MALLOC
#define TCFG_MEDIA_LIB_USE_MALLOC			0
#endif//TCFG_MEDIA_LIB_USE_MALLOC
#endif//(TCFG_BLUETOOTH_BACK_MODE == 0)

#if (TCFG_USER_TWS_ENABLE && TCFG_BLUETOOTH_BACK_MODE) && (TCFG_BT_SNIFF_ENABLE==0) && defined(CONFIG_LOCAL_TWS_ENABLE)
#define TCFG_DEC2TWS_ENABLE					0
#define TCFG_PCM_ENC2TWS_ENABLE				0
#define TCFG_TONE2TWS_ENABLE				0
#else
#define TCFG_DEC2TWS_ENABLE					0
#define TCFG_PCM_ENC2TWS_ENABLE				0
#define TCFG_TONE2TWS_ENABLE				0
#endif



#if (APP_ONLINE_DEBUG && !USER_SUPPORT_PROFILE_SPP)
#error "NEED ENABLE USER_SUPPORT_PROFILE_SPP!!!"
#endif


//*********************************************************************************//
//                                  REC 配置                                       //
//*********************************************************************************//
#define RECORDER_MIX_EN						DISABLE//混合录音使能
#define TCFG_RECORD_FOLDER_DEV_ENABLE       DISABLE//音乐播放录音区分使能

#if RECORDER_MIX_EN
#undef TCFG_DRC_ENABLE
#define TCFG_DRC_ENABLE    0//开混合录音不能开DRC
#endif

//*********************************************************************************//
//                                  linein配置                                     //
//*********************************************************************************//
#define TCFG_LINEIN_ENABLE					TCFG_APP_LINEIN_EN	// linein使能
// #define TCFG_LINEIN_LADC_IDX				0					// linein使用的ladc通道，对应ladc_list
#if (RECORDER_MIX_EN)
#define TCFG_LINEIN_LR_CH					AUDIO_LIN0L_CH//AUDIO_LIN0_LR
#else
#define TCFG_LINEIN_LR_CH					AUDIO_LIN0_LR
#endif/*RECORDER_MIX_EN*/
#define TCFG_LINEIN_CHECK_PORT				IO_PORTB_01			// linein检测IO
#define TCFG_LINEIN_PORT_UP_ENABLE        	1					// 检测IO上拉使能
#define TCFG_LINEIN_PORT_DOWN_ENABLE       	0					// 检测IO下拉使能
#define TCFG_LINEIN_AD_CHANNEL             	NO_CONFIG_PORT		// 检测IO是否使用AD检测
#define TCFG_LINEIN_VOLTAGE                	0					// AD检测时的阀值
#if(TCFG_MIC_EFFECT_ENABLE)
#define TCFG_LINEIN_INPUT_WAY               LINEIN_INPUT_WAY_ANALOG
#else
#if (RECORDER_MIX_EN)
#define TCFG_LINEIN_INPUT_WAY               LINEIN_INPUT_WAY_ADC//LINEIN_INPUT_WAY_ANALOG
#else
#define TCFG_LINEIN_INPUT_WAY               LINEIN_INPUT_WAY_ANALOG
#endif/*RECORDER_MIX_EN*/
#endif
#define TCFG_LINEIN_MULTIPLEX_WITH_FM		DISABLE 				// linein 脚与 FM 脚复用
#define TCFG_LINEIN_MULTIPLEX_WITH_SD		DISABLE 				// linein 检测与 SD cmd 复用
#define TCFG_LINEIN_SD_PORT		            0// 0:sd0 1:sd1     //选择复用的sd

//*********************************************************************************//
//                                  music 配置                                     //
//*********************************************************************************//
#define TCFG_DEC_G729_ENABLE                DISABLE
#define TCFG_DEC_MP3_ENABLE					DISABLE
#define TCFG_DEC_WMA_ENABLE					DISABLE
#define TCFG_DEC_WAV_ENABLE					DISABLE
#define TCFG_DEC_FLAC_ENABLE				DISABLE
#define TCFG_DEC_APE_ENABLE					DISABLE
#define TCFG_DEC_M4A_ENABLE					DISABLE
#define TCFG_DEC_ALAC_ENABLE				DISABLE
#define TCFG_DEC_AMR_ENABLE					DISABLE
#define TCFG_DEC_DTS_ENABLE					DISABLE
#define TCFG_DEC_MIDI_ENABLE                DISABLE
#define TCFG_DEC_G726_ENABLE                DISABLE
#define TCFG_DEC_MTY_ENABLE					DISABLE
#define TCFG_DEC_WTGV2_ENABLE				DISABLE


#define TCFG_DEC_ID3_V1_ENABLE				DISABLE
#define TCFG_DEC_ID3_V2_ENABLE				DISABLE
#define TCFG_DEC_DECRYPT_ENABLE				DISABLE
#define TCFG_DEC_DECRYPT_KEY				(0x12345678)

////<变速变调
#define TCFG_SPEED_PITCH_ENABLE             DISABLE//
//*********************************************************************************//
//                                  fm 配置                                     //
//*********************************************************************************//
#define TCFG_FM_ENABLE							TCFG_APP_FM_EN // fm 使能
#define TCFG_FM_INSIDE_ENABLE					DISABLE
#define TCFG_FM_RDA5807_ENABLE					DISABLE
#define TCFG_FM_BK1080_ENABLE					DISABLE
#define TCFG_FM_QN8035_ENABLE					DISABLE

#define TCFG_FMIN_LADC_IDX				1				// linein使用的ladc通道，对应ladc_list
#define TCFG_FMIN_LR_CH					AUDIO_LIN1_LR
#define TCFG_FM_INPUT_WAY               LINEIN_INPUT_WAY_ANALOG

//*********************************************************************************//
//                                  fm emitter 配置 (不支持)                                    //
//*********************************************************************************//
#define TCFG_APP_FM_EMITTER_EN                  DISABLE_THIS_MOUDLE
#define TCFG_FM_EMITTER_INSIDE_ENABLE			DISABLE
#define TCFG_FM_EMITTER_AC3433_ENABLE			DISABLE
#define TCFG_FM_EMITTER_QN8007_ENABLE			DISABLE
#define TCFG_FM_EMITTER_QN8027_ENABLE			DISABLE

//*********************************************************************************//
//                                  rtc 配置(不支持)                               //
//*********************************************************************************//
#define TCFG_RTC_ENABLE						TCFG_APP_RTC_EN

#if TCFG_RTC_ENABLE
#define TCFG_USE_VIRTUAL_RTC                   ENABLE
#else
#define TCFG_USE_VIRTUAL_RTC                   DISABLE
#endif

//*********************************************************************************//
//                                  SPDIF & ARC 配置(不支持)                                     //
//*********************************************************************************//
#define TCFG_SPDIF_ENABLE                       TCFG_APP_SPDIF_EN
#define TCFG_SPDIF_OUTPUT_ENABLE                ENABLE
#define TCFG_HDMI_ARC_ENABLE                    ENABLE
#define TCFG_HDMI_CEC_PORT                      IO_PORTA_02
//*********************************************************************************//
//                                  IIS 配置                                     //
//*********************************************************************************//
#define TCFG_IIS_ENABLE                       DISABLE_THIS_MOUDLE
#define TCFG_IIS_MODE                         (0)   //  0:master  1:slave

#define TCFG_IIS_OUTPUT_EN                    (ENABLE && TCFG_IIS_ENABLE)
#define TCFG_IIS_OUTPUT_PORT                  (0) // 0:portA  1:portB
#define TCFG_IIS_OUTPUT_CH_NUM                1 //0:mono,1:stereo
#define TCFG_IIS_OUTPUT_SR                    44100
#define TCFG_IIS_OUTPUT_DATAPORT_SEL          (BIT(0)|BIT(1))

#define TCFG_IIS_INPUT_EN                    (DISABLE && TCFG_IIS_ENABLE)
#define TCFG_IIS_INPUT_PORT                  (0) // 0:portA  1:portB
#define TCFG_IIS_INPUT_CH_NUM                1 //0:mono,1:stereo
#define TCFG_IIS_INPUT_SR                    44100
#define TCFG_IIS_INPUT_DATAPORT_SEL          (BIT(0))
//*********************************************************************************//
//                                  fat 文件系统配置                                       //
//*********************************************************************************//
#define CONFIG_FATFS_ENABLE					DISABLE



//*********************************************************************************//
//                                  REC 配置                                       //
//*********************************************************************************//
#define TCFG_LINEIN_REC_EN					DISABLE
#define	 TCFG_MIXERCH_REC_EN				DISABLE
#define TCFG_MIC_REC_PITCH_EN               DISABLE
#define TCFG_MIC_REC_REVERB_EN              DISABLE


//*********************************************************************************//
//                                  encoder 配置                                   //
//*********************************************************************************//
#define TCFG_ENC_CVSD_ENABLE                DISABLE
#define TCFG_ENC_MSBC_ENABLE                DISABLE
#define TCFG_ENC_MP3_ENABLE                 DISABLE
#define TCFG_ENC_ADPCM_ENABLE               DISABLE
#define TCFG_ENC_SBC_ENABLE                 DISABLE
#define TCFG_ENC_OPUS_ENABLE                DISABLE
#define TCFG_ENC_SPEEX_ENABLE               DISABLE

//*********************************************************************************//

//*********************************************************************************//
//                                 电源切换配置                                    //
//*********************************************************************************//

#define CONFIG_PHONE_CALL_USE_LDO15	    1

//*********************************************************************************//
//                                人声消除使能
//*********************************************************************************//
#define AUDIO_VOCAL_REMOVE_EN       0

///*********************************************************************************//
//          等响度 开启后，需要固定模拟音量,调节软件数字音量
//          等响度使用eq实现，同个数据流中，若打开等响度，请开eq总使能，关闭其他eq,例如蓝牙模式eq
//*********************************************************************************//
#define AUDIO_EQUALLOUDNESS_CONFIG  0  //等响度, 不支持四声道

///*********************************************************************************//
//          环绕音效使能
//*********************************************************************************//
#define AUDIO_SURROUND_CONFIG     0//3d环绕

#define AUDIO_VBASS_CONFIG        0//虚拟低音,虚拟低音不支持四声道
#define AUDIO_SPECTRUM_CONFIG     0  //频响能量值获取接口
#define AUDIO_MIDI_CTRL_CONFIG    0  //midi电子琴接口使能

#if AUDIO_VBASS_CONFIG
#undef AUDIO_EFFECTS_VBASS_AT_RAM
#define AUDIO_EFFECTS_VBASS_AT_RAM 1
#undef  AUDIO_EFFECTS_DRC_AT_RAM
#define AUDIO_EFFECTS_DRC_AT_RAM 1
#undef AUDIO_EFFECTS_EQ_AT_RAM
#define AUDIO_EFFECTS_EQ_AT_RAM 1
#endif

#if TCFG_AUDIO_OUT_EQ_ENABLE
#undef  AUDIO_EFFECTS_DRC_AT_RAM
#define AUDIO_EFFECTS_DRC_AT_RAM 1
#undef AUDIO_EFFECTS_EQ_AT_RAM
#define AUDIO_EFFECTS_EQ_AT_RAM 1
#endif

#if !TCFG_DRC_ENABLE
#undef  AUDIO_EFFECTS_DRC_AT_RAM
#define AUDIO_EFFECTS_DRC_AT_RAM 0
#endif
#if !TCFG_EQ_ENABLE
#undef AUDIO_EFFECTS_EQ_AT_RAM
#define AUDIO_EFFECTS_EQ_AT_RAM 0
#endif

//*********************************************************************************//
//                                  充电盒配置                                     //
//*********************************************************************************//
#define TCFG_CHARGE_BOX_ENABLE                          ENABLE_THIS_MOUDLE  //充电舱模块开启宏
#define TCFG_CHARGE_MOUDLE_OUTSIDE                      ENABLE_THIS_MOUDLE  //使用外置充电模块
#define TCFG_USB_KEY_UPDATE_ENABLE                      ENABLE_THIS_MOUDLE  //USB插入升级使能
#define TCFG_WIRELESS_ENABLE                            DISABLE_THIS_MOUDLE //是否支持无线充
#define TCFG_LDO_DET_ENABLE                             ENABLE_THIS_MOUDLE  //是否支持升压检测
#define TCFG_CHARGE_BOX_SOFT_POWER_OFF_IO_CTRL_ENABLE   ENABLE_THIS_MOUDLE  //一些外设（如某些升压芯片）休眠时需要设置上下拉来维持关闭态
#define TCFG_HANDSHAKE_ENABLE                           DISABLE_THIS_MOUDLE //充电握手协议
#define TCFG_TEMPERATURE_ENABLE                         ENABLE_THIS_MOUDLE  //过温充电保护使能(给充电盒充电)
#define TCFG_CURRENT_LIMIT_ENABLE                       ENABLE_THIS_MOUDLE  //充电过流保护使能(给耳机充电)
#define TCFG_SHORT_PROTECT_ENABLE                       DISABLE_THIS_MOUDLE //充电过程中短路保护使能(给耳机充电)
#define TCFG_CHARGE_BOX_UI_ENABLE                       ENABLE_THIS_MOUDLE  //充电舱UI开启宏
#define TCFG_CHARGGBOX_AUTO_SHUT_DOWN_TIME              8                   //充电仓自动休眠时间 单位秒
#define TCFG_CHARGE_FULL_ENTER_SOFTOFF                  0                   //充电舱整机充满电后是否要进入soft power off
#define TCFG_CHARGE_BOX_AUTO_WAKEUP  					DISABLE_THIS_MOUDLE	//充电仓休眠后可配置时间自动唤醒
#define AUTO_WAKEUP_TIME_SEC							2592000				//默认定时一个月唤醒

#define TCFG_HALL_PORT                                  IO_PORTB_03         //hall传感器的IO
#define TCFG_CHARGEBOX_L_PORT                           IO_PORTB_05         //充电盒和左耳通信的IO口需要为高压IO
#define TCFG_CHARGEBOX_R_PORT                           IO_PORTB_02         //充电盒和右耳通信的IO口需要为高压IO
#define TCFG_USB_ONLE_DET_IO                            IO_PORTA_00         //检测USB插入拔出配置
#define TCFG_CHARGE_FULL_DET_IO                         IO_PORTC_01         //满电检测IO配置
#define TCFG_STOP_CHARGE_IO                             IO_PORTA_02         //停止充电控制脚-高阻时正常充电 输出1时充电截止
#define TCFG_BOOST_CTRL_IO                              IO_PORTC_02         //升压控制IO
#define TCFG_BAT_DET_IO                                 NO_CONFIG_PORT      //电池电量检测IO(使用外部分压检测时需要配置)
#define TCFG_BAT_DET_AD_CH                              AD_CH_VBAT          //电池电量检测AD通道

//PWR控制方式根据电路设计去选择
#define TCFG_PWR_CTRL_IO                                IO_PORTB_00         //耳机电源开关控制引脚
#define PWR_CTRL_TYPE_PU_PD                             0                   //用上下拉方式控制
#define PWR_CTRL_TYPE_OUTPUT_0                          1                   //输出0使能(选择高压IO的时候配成该选项)
#define PWR_CTRL_TYPE_OUTPUT_1                          2                   //输出1使能
#define TCFG_PWR_CTRL_TYPE                              PWR_CTRL_TYPE_OUTPUT_0

#if TCFG_LDO_DET_ENABLE
#define TCFG_CHG_LDO_DET_IO                             IO_PORTB_07         //5V升压是否在成功检测IO
#define TCFG_CHG_LDO_DET_AD_CH                          AD_CH_PB7           //5V升压是否在成功检测AD通道
#endif

#if TCFG_CHARGE_BOX_UI_ENABLE
#define TCFG_CHGBOX_UI_TIMERLED                         0//timer模拟的PWM呼吸灯,不支持亮灯进入低功耗
#define TCFG_CHGBOX_UI_PWMLED                           1//pwmled模块支持低功耗亮灯
#define CHG_LED_MODE                                    0//timerLED模式有效 1--高亮 0--低亮, PWMLED模式请修改 PWM_LED_TWO_IO_CONNECT 这个宏定义
#define CHG_RED_LED_IO                                  IO_PORTA_04
#define CHG_GREEN_LED_IO                                IO_PORT_DM
#define CHG_BLUE_LED_IO                                 NO_CONFIG_PORT
#if (defined(CONFIG_DEBUG_ENABLE) && (TCFG_UART0_TX_PORT == IO_PORT_DM))
#undef CHG_GREEN_LED_IO
#define CHG_GREEN_LED_IO                                NO_CONFIG_PORT
#endif
#endif

#if TCFG_CURRENT_LIMIT_ENABLE
#define TCFG_CURRENT_DET_IO                             IO_PORTB_06         //检测电流的IO,定义了TCFG_CURRENT_LIMIT_ENABLE才有效
#define TCFG_CURRENT_DET_AD_CH                          AD_CH_PB6           //耳机充电电流检测AD通道
#endif

#if TCFG_SHORT_PROTECT_ENABLE
#define TCFG_SHORT_PROTECT_IO                           IO_PORTB_07         //短路保护检测IO
#if TCFG_LDO_DET_ENABLE && (TCFG_CHG_LDO_DET_IO == TCFG_SHORT_PROTECT_IO)
#error "短路保护和升压检测IO冲突"
#endif
#endif

#if TCFG_TEMPERATURE_ENABLE
#define TCFG_CHARGE_TEMP_IO                             IO_PORTA_03
#define TCFG_CHARGE_TEMP_AD_CH                          AD_CH_PA3
#define TCFG_CHARGE_EXTERN_UP_ENABLE                    DISABLE_THIS_MOUDLE //是否使用外部上拉
#if TCFG_CHARGE_EXTERN_UP_ENABLE
#define TCFG_RES_UP                                     100//外部上拉值在这里修改
#else
#define TCFG_RES_UP                                     100//内部上拉默认10K
#endif
#endif

#if TCFG_HANDSHAKE_ENABLE
#define TCFG_HANDSHAKE_IO                               NO_CONFIG_PORT      //握手IO
#endif

#if TCFG_WIRELESS_ENABLE
#define TCFG_WPC_COMM_IO                                NO_CONFIG_PORT      //无线充电通信IO
#define TCFG_WL_AD_DET_IO                               NO_CONFIG_PORT      //无线充电AD检测IO
#define TCFG_WL_AD_DET_CH                               NO_CONFIG_PORT      //无线充电AD检测通道
#define TCFG_DCDC_CTRL_EN                               0                   //无线充电是否使能dcdc控制
#define TCFG_DCDC_EN_IO                                 NO_CONFIG_PORT      //无线充电dcdc使能IO
#endif

#if (TCFG_CLOCK_SYS_SRC == SYS_CLOCK_INPUT_PLL_RCL)//免晶振时,USB key不能用
#undef TCFG_USB_KEY_UPDATE_ENABLE
#define TCFG_USB_KEY_UPDATE_ENABLE                      DISABLE_THIS_MOUDLE
#endif

#if TCFG_CHARGE_BOX_ENABLE && TCFG_PC_ENABLE
#undef USB_DEVICE_CLASS_CONFIG
#define USB_DEVICE_CLASS_CONFIG     (MASSSTORAGE_CLASS)
#endif

//*********************************************************************************//
//                                 编译警告                                         //
//*********************************************************************************//
#if ((ANCS_CLIENT_EN || TRANS_DATA_EN || ((TCFG_ONLINE_TX_PORT == IO_PORT_DP) && (TCFG_COMM_TYPE == TCFG_UART_COMM) && TCFG_ONLINE_ENABLE) || ((TCFG_ONLINE_TX_PORT == IO_PORT_DP) && (TCFG_COMM_TYPE == TCFG_UART_COMM) && TCFG_SOUNDBOX_TOOL_ENABLE)) && (TCFG_PC_ENABLE || TCFG_UDISK_ENABLE || TCFG_SD0_PORTS == 'E'))
#error "eq online adjust enable, plaease close usb marco  and sdcard port not e!!!"
#endif// ((TRANS_DATA_EN || TCFG_ONLINE_ENABLE) && (TCFG_PC_ENABLE || TCFG_UDISK_ENABLE))

#if ((TCFG_COMM_TYPE == TCFG_UART_COMM) && TCFG_ONLINE_ENABLE) && (TCFG_PC_ENABLE || TCFG_UDISK_ENABLE)
#error "eq online adjust enable, plaease close usb marco"
#endif// ((TCFG_ONLINE_ENABLE) && (TCFG_PC_ENABLE || TCFG_UDISK_ENABLE))

#if ((TCFG_COMM_TYPE == TCFG_UART_COMM) && TCFG_SOUNDBOX_TOOL_ENABLE ) && TCFG_PC_ENABLE
#error "soundbox tool enable, plaease close pc marco"
#endif// (TCFG_SOUNDBOX_TOOL_ENABLE) && (TCFG_PC_ENABLE)

#if TCFG_UI_ENABLE
#if ((TCFG_SPI_LCD_ENABLE &&  TCFG_CODE_FLASH_ENABLE) && (TCFG_FLASH_DEV_SPI_HW_NUM == TCFG_TFT_LCD_DEV_SPI_HW_NUM))
#error "flash spi port == lcd spi port, please close one !!!"
#endif//((TCFG_SPI_LCD_ENABLE &&  TCFG_CODE_FLASH_ENABLE) && (TCFG_FLASH_DEV_SPI_HW_NUM == TCFG_TFT_LCD_DEV_SPI_HW_NUM))
#endif//TCFG_UI_ENABLE

#if((TRANS_DATA_EN + DUEROS_DMA_EN + ANCS_CLIENT_EN) > 1)
#error "they can not enable at the same time,just select one!!!"
#endif//(TRANS_DATA_EN && DUEROS_DMA_EN)

#if (TCFG_DEC2TWS_ENABLE && (TCFG_APP_RECORD_EN || TCFG_APP_RTC_EN ||TCFG_DRC_ENABLE))
#error "对箱支持音源转发，请关闭录音等功能 !!!"
#endif// (TCFG_DEC2TWS_ENABLE && (TCFG_APP_RECORD_EN || TCFG_APP_RTC_EN ||TCFG_DRC_ENABLE))

#if (TCFG_DRC_ENABLE && TCFG_MIC_EFFECT_ENABLE && (TCFG_DEC_APE_ENABLE || TCFG_DEC_FLAC_ENABLE || TCFG_DEC_DTS_ENABLE))
#error "无损格式+混响不支持DRC !!!"
#endif//(TCFG_MIC_EFFECT_ENABLE && (TCFG_DEC_APE_ENABLE || TCFG_DEC_FLAC_ENABLE || TCFG_DEC_DTS_ENABLE))

#if (TCFG_REVERB_DODGE_EN && (USER_DIGITAL_VOLUME_ADJUST_ENABLE == 0))
#error "使用闪避功能，打开自定义数字音量调节 !!!"
#endif

#if ((TCFG_NORFLASH_DEV_ENABLE || TCFG_NOR_FS_ENABLE) &&  TCFG_UI_ENABLE)
#error "引脚复用问题，使用norflash需要关闭UI ！！！"
#endif


#if ((TCFG_APP_RECORD_EN) && (TCFG_USER_TWS_ENABLE))
#error "TWS 暂不支持录音功能"
#endif

#include "app_config.h"
#if ((TCFG_SD0_ENABLE) && (TCFG_SD0_PORTS == 'D') && ((RECORDER_MIX_EN) || (TCFG_SD0_DET_MODE == SD_CMD_DECT)))
/*
 1.如果有FM模式下录音的功能，即FM和SD同时工作的情况，那么SD IO就不能用PB0,PB2,PB3这组口。
 2.如果FM模式没有录音的功能，即FM和SD不会有同时工作的情况，那么 SD IO可以使用PB0,PB2,PB3这组口，
   但SD就不能使用CMD检测。要用CLK或IO检测，这样就要有硬件上的支持，如3.3K电阻或者牺牲另一个引脚做IO检测*
 */
#error "SD IO使用D组口 引脚干扰FM的问题 ！！！"
#endif

#if ((TCFG_CLOCK_SYS_SRC == SYS_CLOCK_INPUT_PLL_RCL) && (TCFG_APP_PC_EN || TCFG_APP_BT_EN))
/*免晶振时,不能开蓝牙,不能开PC升级*/
#error "免晶振时不能使用,PC升级模式,不能开蓝牙"
#endif

#if (TCFG_TEST_BOX_ENABLE && ((TCFG_CHARGESTORE_PORT == IO_PORT_DP) || (TCFG_CHARGESTORE_PORT == IO_PORT_DM)) && TCFG_APP_PC_EN)
#error "DP DM使用冲突"
#endif

/* #if (TCFG_EQ_ONLINE_ENABLE && (!TCFG_EFFECT_TOOL_ENABLE) || (!TCFG_EQ_ONLINE_ENABLE && (TCFG_EFFECT_TOOL_ENABLE))) */
// #error "音效在线调试需使能调音工具宏TCFG_EFFECT_TOOL_ENABLE"
/* #endif */

#if TCFG_DYNAMIC_EQ_ENABLE && !TCFG_DRC_ENABLE //动态eq使能后，需接入drc进行幅度控制
#error "动态eq使能后，需使能TCFG_DRC_ENABLE接入drc进行幅度控制"
#endif
#if TCFG_DYNAMIC_EQ_ENABLE && !TCFG_AUDIO_MDRC_ENABLE
#error "动态eq使能后，需使能TCFG_AUDIO_MDRC_ENABLE 为1接入多带drc进行幅度控制"
#endif
#if TCFG_DYNAMIC_EQ_ENABLE && TCFG_EQ_DIVIDE_ENABLE
#error "高阶音箱调音 不支持四声道"
#endif
#if TCFG_EQ_DIVIDE_ENABLE && (TCFG_AUDIO_DAC_CONNECT_MODE != DAC_OUTPUT_FRONT_LR_REAR_LR)
#error "eq效果独立，需使能四声道宏DAC_OUTPUT_FRONT_LR_REAR_LR"
#endif
#if SOUND_TRACK_2_P_X_CH_CONFIG && !TCFG_EQ_DIVIDE_ENABLE
#error  "2.1/2.2声道，需使能宏TCFG_EQ_DIVIDE_ENABLE"
#endif
/* #if SOUND_TRACK_2_P_X_CH_CONFIG && TCFG_AUDIO_MDRC_ENABLE */
// #error  "2.1/2.2声道，不支持多带drc"
/* #endif */
#if TCFG_MIC_VOICE_CHANGER_ENABLE && (TCFG_MIC_EFFECT_SEL != MIC_EFFECT_ECHO)
#error  "变声目前支持加载ECHO音效下"
#endif
#if TCFG_USER_TWS_ENABLE && TCFG_MIC_EFFECT_ENABLE &&((TCFG_MIC_EFFECT_SEL != MIC_EFFECT_ECHO) && (TCFG_MIC_EFFECT_SEL != MIC_EFFECT_MEGAPHONE))
#error "tws时，只支持ehco混响或者megaphone"
#endif
#if TCFG_DYNAMIC_EQ_ENABLE && (!AUDIO_VBASS_CONFIG)
#error "高阶音箱调音需使能虚拟低音AUDIO_VBASS_CONFIG"
#endif
#if TCFG_DYNAMIC_EQ_ENABLE && SOUND_TRACK_2_P_X_CH_CONFIG
#error "高阶音箱调音 不支持2.1/2.2声道"
#endif
#if TCFG_DYNAMIC_EQ_ENABLE && TCFG_MIC_EFFECT_ENABLE
#error "高阶音箱调音 不支持混响"
#endif

#if MUSIC_EXT_EQ_AFTER_DRC && TCFG_DYNAMIC_EQ_ENABLE
#error "动态eq开启时，不需要开启扩展eq MUSIC_EXT_EQ_AFTER_DRC"
#endif
#if TCFG_USER_TWS_ENABLE && (AUDIO_VBASS_CONFIG && TCFG_DRC_ENABLE)
#error "对箱不支持开虚拟低音"
#endif

#if TCFG_USER_TWS_ENABLE && (TCFG_DRC_ENABLE && AUDIO_EFFECTS_DRC_AT_RAM)&& (!TCFG_MIC_EFFECT_ENABLE)
#error "对箱不支持drc代码放ram, 需关闭宏AUDIO_EFFECTS_DRC_AT_RAM"
#endif

#if TCFG_USER_TWS_ENABLE && (TCFG_EQ_ENABLE && AUDIO_EFFECTS_EQ_AT_RAM)&&(!TCFG_MIC_EFFECT_ENABLE)
#error "对箱不支持eq代码放ram, 需关闭宏AUDIO_EFFECTS_EQ_AT_RAM"
#endif

#if (CONFIG_CPU_BR25) && TCFG_AUDIO_MDRC_ENABLE
#error "AC696N 不支持多带drc"
#endif
#if AUDIO_VBASS_CONFIG && TCFG_AUDIO_OUT_EQ_ENABLE
#error "AC696N 不支持虚拟低音和高低音同时使用"
#endif
#if TCFG_AUDIO_OUT_DRC_ENABLE && TCFG_AUDIO_OUT_EQ_ENABLE
#error "AC696N 不支持高低音eq和高低音后的drc同时使用"
#endif


///<<<<所有宏定义不要在编译警告后面定义！！！！！！！！！！！！！！！！！！！！！！！！！！
///<<<<所有宏定义不要在编译警告后面定义！！！！！！！！！！！！！！！！！！！！！！！！！！


//*********************************************************************************//
//                                 配置结束                                         //
//*********************************************************************************//


#endif //CONFIG_BOARD_AC693X_DEMO
#endif //CONFIG_BOARD_AC693X_DEMO_CFG_H
