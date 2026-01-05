#include "system/includes.h"
#include "app_power_manage.h"
#include "app_main.h"
#include "app_config.h"
#include "app_action.h"
#include "asm/charge.h"
#include "ui_manage.h"
#include "tone_player.h"
#include "asm/adc_api.h"
#include "btstack/avctp_user.h"
#include "user_cfg.h"
#include "bt.h"
#include "asm/charge.h"
#include "adapter_process.h"

#if TCFG_USER_TWS_ENABLE
#include "bt_tws.h"
#endif

#define LOG_TAG_CONST       APP_POWER
#define LOG_TAG             "[APP_POWER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

enum {
    VBAT_NORMAL = 0,
    VBAT_WARNING,
    VBAT_LOWPOWER,
} VBAT_STATUS;

#define VBAT_DETECT_CNT     6
static int vbat_slow_timer = 0;
static int vbat_fast_timer = 0;
static int lowpower_timer = 0;
static u8 old_battery_level = 9;
static u16 bat_val = 0;
static volatile u8 cur_battery_level = 0;
static u16 battery_full_value = 0;
static u8 tws_sibling_bat_level = 0xff;
static u8 tws_sibling_bat_percent_level = 0xff;
static u8 cur_bat_st = VBAT_NORMAL;

void vbat_check(void *priv);
void sys_enter_soft_poweroff(void *priv);
void clr_wdt(void);
void power_event_to_user(u8 event);


u8 get_tws_sibling_bat_level(void)
{
#if TCFG_USER_TWS_ENABLE
    /* log_info("***********get_tws_sibling_bat_level: %2x", tws_sibling_bat_percent_level); */
    return tws_sibling_bat_level & 0x7f;
#endif
    return 0xff;
}

u8 get_tws_sibling_bat_persent(void)
{
#if TCFG_USER_TWS_ENABLE
    /* log_info("***********get_tws_sibling_bat_level: %2x", tws_sibling_bat_percent_level); */
    return tws_sibling_bat_percent_level;
#endif
    return 0xff;
}

void app_power_set_tws_sibling_bat_level(u8 vbat, u8 percent)
{
#if TCFG_USER_TWS_ENABLE
    tws_sibling_bat_level = vbat;
    tws_sibling_bat_percent_level = percent;
    /*
     ** 发出电量同步事件进行进一步处理
     **/
    power_event_to_user(POWER_EVENT_SYNC_TWS_VBAT_LEVEL);

    log_info("set_sibling_bat_level: %d, %d\n", vbat, percent);
#endif
}


static void set_tws_sibling_bat_level(void *_data, u16 len, bool rx)
{
    u8 *data = (u8 *)_data;

    if (rx) {
        app_power_set_tws_sibling_bat_level(data[0], data[1]);
    }
}

#if TCFG_USER_TWS_ENABLE
REGISTER_TWS_FUNC_STUB(vbat_sync_stub) = {
    .func_id = TWS_FUNC_ID_VBAT_SYNC,
    .func    = set_tws_sibling_bat_level,
};
#endif

void tws_sync_bat_level(void)
{
#if (TCFG_USER_TWS_ENABLE && BT_SUPPORT_DISPLAY_BAT)
    u8 battery_level = cur_battery_level;
#if CONFIG_DISPLAY_DETAIL_BAT
    u8 percent_level = get_vbat_percent();
#else
    u8 percent_level = get_self_battery_level() * 10 + 10;
#endif
    if (get_charge_online_flag()) {
        percent_level |= BIT(7);
    }

    u8 data[2];
    data[0] = battery_level;
    data[1] = percent_level;
    tws_api_send_data_to_sibling(data, 2, TWS_FUNC_ID_VBAT_SYNC);

    log_info("tws_sync_bat_level: %d,%d\n", battery_level, percent_level);
#endif
}

void power_event_to_user(u8 event)
{
    struct sys_event e;
    e.type = SYS_DEVICE_EVENT;
    e.arg  = (void *)DEVICE_EVENT_FROM_POWER;
    e.u.dev.event = event;
    e.u.dev.value = 0;
    sys_event_notify(&e);
}

int app_power_event_handler(struct device_event *dev)
{
    int ret = false;

#if(TCFG_SYS_LVD_EN == 1)
    switch (dev->event) {
    case POWER_EVENT_POWER_NORMAL:
        ui_update_status(STATUS_EXIT_LOWPOWER);
        if (lowpower_timer) {
            sys_timer_del(lowpower_timer);
            lowpower_timer = 0 ;
        }
        break;
    case POWER_EVENT_POWER_WARNING:
        //ui_update_status(STATUS_LOWPOWER);
        //led_light_time_display_del();
        //led7_charge_flash_add();
        if (lowpower_timer == 0) {
            lowpower_timer = sys_timer_add((void *)POWER_EVENT_POWER_WARNING, (void (*)(void *))power_event_to_user, LOW_POWER_WARN_TIME);
        }
        break;
    case POWER_EVENT_POWER_LOW:
        r_printf(" POWER_EVENT_POWER_LOW");
        vbat_timer_delete();
        if (lowpower_timer) {
            sys_timer_del(lowpower_timer);
            lowpower_timer = 0 ;
        }
#if TCFG_APP_BT_EN
#if (RCSP_ADV_EN)
        extern u8 adv_tws_both_in_charge_box(u8 type);
        adv_tws_both_in_charge_box(1);
#endif
        //sys_enter_soft_poweroff(NULL);
        adapter_process_event_notify(ADAPTER_EVENT_POWEROFF, 0);
#else
        void app_entry_idle() ;
        app_entry_idle() ;
#ifdef CONFIG_BOARD_AC6083A
        power_set_soft_poweroff();
#endif

#endif
        break;
#if TCFG_APP_BT_EN
#if TCFG_USER_TWS_ENABLE
    case POWER_EVENT_SYNC_TWS_VBAT_LEVEL:
        if (tws_api_get_role() == TWS_ROLE_MASTER) {
            user_send_cmd_prepare(USER_CTRL_HFP_CMD_UPDATE_BATTARY, 0, NULL);
        }
        break;
#endif

    case POWER_EVENT_POWER_CHANGE:
        /* log_info("POWER_EVENT_POWER_CHANGE\n"); */
#if TCFG_USER_TWS_ENABLE
        if (tws_api_get_tws_state() & TWS_STA_SIBLING_CONNECTED) {
            if (tws_api_get_tws_state()&TWS_STA_ESCO_OPEN) {
                break;
            }
            tws_sync_bat_level();
        }
#endif
        user_send_cmd_prepare(USER_CTRL_HFP_CMD_UPDATE_BATTARY, 0, NULL);
#endif
        break;
    case POWER_EVENT_POWER_CHARGE:
        if (lowpower_timer) {
            sys_timer_del(lowpower_timer);
            lowpower_timer = 0 ;
        }
        break;
    default:
        break;
    }
#endif

    return ret;
}

static int def_adc_dete_value = 0;

u16 get_vbat_level(void)
{
    //return 370;     //debug
    #if USER_SET_BAT_DETE
    //if(adc_get_voltage(AD_CH_VBAT) > 0)
    {
        //printf("#########################  def_adc_dete_value = %d ###########################\n",def_adc_dete_value);
        def_adc_dete_value = adc_get_voltage(AD_CH_VBAT);
    }



            if(def_adc_dete_value >= 1032 )            //100%
            {
                return 207;
            }
            else if(def_adc_dete_value >= 1013 && def_adc_dete_value < 1032)        //90% - 99%
            {
                return (((def_adc_dete_value) / 2) - 309);   //(100 - 90)
            }
            else if(def_adc_dete_value >= 953 && def_adc_dete_value < 1013)          //50%  - 89%
            {
                return (((def_adc_dete_value) * 14  / 21) - 478);
            }
            else if(def_adc_dete_value >= 891 && def_adc_dete_value < 953)          //20%  - 50%
            {
                return (((def_adc_dete_value)  / 2) - 318);
            }
            else if(def_adc_dete_value >= 846 && def_adc_dete_value < 891)          //5% - 20%
            {
                return (((def_adc_dete_value) /  3) - 170);    //(90- 80)
            }
            else if((820 <= def_adc_dete_value) && (def_adc_dete_value <= 845))    //0% - 5%
            {
                return ((def_adc_dete_value / 5) - 57);
            }
            else if(def_adc_dete_value < 820){                                      //0%
                return 107;
            }

    #else
    return (adc_get_voltage(AD_CH_VBAT) * 4 / 10);
    #endif

}

__attribute__((weak)) u8 remap_calculate_vbat_percent(u16 bat_val)
{
    return 0;
}

u16 get_vbat_value(void)
{
    return bat_val;
}


static u16 user_define_vbat = 0;

#define CHARGE_ADD_VALUE 4

u8 get_vbat_percent(void)
{
    u16 tmp_bat_val;
    #if USER_SET_BAT_DETE
    u16 bat_val = get_vbat_level() + 215;
    #else
    u16 bat_val = get_vbat_level();
    #endif
    //printf("################ BAT_VAL ############# %d\n",bat_val);
    if (battery_full_value == 0) {
#if TCFG_CHARGE_ENABLE
        battery_full_value = (get_charge_full_value() - 100) / 10; //防止部分电池充不了这么高电量，充满显示未满的情况
#else
        battery_full_value = 420;
#endif
    }

    if (bat_val <= app_var.poweroff_tone_v) {
        return 0;
    }


    tmp_bat_val = remap_calculate_vbat_percent(bat_val);
    #if USER_SET_BAT_DETE

    if (!tmp_bat_val) {

         tmp_bat_val = (bat_val  - 322) * 100 / 100;//(battery_full_value - app_var.poweroff_tone_v);


        //printf("############## TMP BAT VAL %d ###############\n",tmp_bat_val);
        if (tmp_bat_val > 100) {
            tmp_bat_val = 100;
        }
    }
    #else
     if (!tmp_bat_val) {
        tmp_bat_val = ((u32)bat_val - app_var.poweroff_tone_v) * 100 / (battery_full_value - app_var.poweroff_tone_v);
        //tmp_bat_val = bat_val - 322;
        printf("############## TMP BAT VAL %d ###############\n",tmp_bat_val);
        if (tmp_bat_val > 100) {
            tmp_bat_val = 100;
        }
    }
    #endif

    return (u8)tmp_bat_val;
}

bool get_vbat_need_shutdown(void)
{
    if ((bat_val <= LOW_POWER_SHUTDOWN) || adc_check_vbat_lowpower()) {
        return TRUE;
    }
    return FALSE;
}

//将当前电量转换为1~9级发送给手机同步电量
u8  battery_value_to_phone_level(u16 bat_val)
{
    u8  battery_level = 0;
    u8 vbat_percent = get_vbat_percent();

    if (vbat_percent < 5) { //小于5%电量等级为0，显示10%
        return 0;
    }

    battery_level = (vbat_percent - 5) / 10;

    return battery_level;
}

//获取自身的电量
u8  get_self_battery_level(void)
{
    return cur_battery_level;
}

u8  get_cur_battery_level(void)
{
    u8 bat_lev = tws_sibling_bat_level & (~BIT(7));
#if TCFG_USER_TWS_ENABLE
    if (bat_lev == 0x7f) {
        return cur_battery_level;
    }

#if (CONFIG_DISPLAY_TWS_BAT_TYPE == CONFIG_DISPLAY_TWS_BAT_LOWER)
    return cur_battery_level < bat_lev ? cur_battery_level : bat_lev;
#elif (CONFIG_DISPLAY_TWS_BAT_TYPE == CONFIG_DISPLAY_TWS_BAT_HIGHER)
    return cur_battery_level < bat_lev ? bat_lev : cur_battery_level;
#elif (CONFIG_DISPLAY_TWS_BAT_TYPE == CONFIG_DISPLAY_TWS_BAT_LEFT)
    return tws_api_get_local_channel() == 'L' ? cur_battery_level : bat_lev;
#elif (CONFIG_DISPLAY_TWS_BAT_TYPE == CONFIG_DISPLAY_TWS_BAT_RIGHT)
    return tws_api_get_local_channel() == 'R' ? cur_battery_level : bat_lev;
#else
    return cur_battery_level;
#endif //END CONFIG_DISPLAY_TWS_BAT_TYPE

#else  //TCFG_USER_TWS_ENABLE == 0
    return cur_battery_level;
#endif
}

void vbat_check_slow(void *priv)
{
    if (vbat_fast_timer == 0) {
        vbat_fast_timer = usr_timer_add(NULL, vbat_check, 10, 1);
    }
    if (get_charge_online_flag()) {
        sys_timer_modify(vbat_slow_timer, 60 * 1000);
    } else {
        sys_timer_modify(vbat_slow_timer, 10 * 1000);
    }
}

void vbat_check_init(void)
{
    if (vbat_slow_timer == 0) {
        vbat_slow_timer = sys_timer_add(NULL, vbat_check_slow, 10 * 1000);
    } else {
        sys_timer_modify(vbat_slow_timer, 10 * 1000);
    }

    if (vbat_fast_timer == 0) {
        vbat_fast_timer = usr_timer_add(NULL, vbat_check, 10, 1);
    }
}

void vbat_timer_delete(void)
{
    if (vbat_slow_timer) {
        sys_timer_del(vbat_slow_timer);
        vbat_slow_timer = 0;
    }
    if (vbat_fast_timer) {
        usr_timer_del(vbat_fast_timer);
        vbat_fast_timer = 0;
    }
}

/*
#define VBAT_DETE_INTAL_TIME    210        //放电时长

#define CHARGE_VBAT_DETE_INTAL_TIME1     40
#define CHARGE_VBAT_DETE_INTAL_TIME2     55
#define CHARGE_VBAT_DETE_INTAL_TIME3     65

#define LOW_VBAT_DETE_INTAL_TIME    50

extern u8 hundreds;
extern u8 tens;
extern u8 unit;

static u16 power = 0;

static  u16 curr_vbat_value = 0;

#define EXC_NORMAL_CAL_COUNT  (15) ////充电计算次数/////
#define EXC_NORMAL_ON_COUNT  (10) /////正常开机计算次数///

extern int led7_init_num[1];



extern u16 is_first_poweron[1];
void low_bat_poweroff()
{
    //if(led7_init_num[0] ==0)
    is_first_poweron[0] = 0;
    syscfg_write(USER_CFG_FIRST_POWERON,&is_first_poweron,1);
        power_set_soft_poweroff();
}


static u16 low_bat_poweroff_time = 0;

void low_bat_poweroff_add()
{
    if(!low_bat_poweroff_time)
    {
        low_bat_poweroff_time = sys_timeout_add(NULL,low_bat_poweroff,120*1000);
    }
}


void low_bat_poweroff_dete()
{
    if(led7_init_num[0] == 0)
        low_bat_poweroff_add();
    if(led7_init_num[0] <= 5)
    {
        led7_charge_flash_add();
        //low_bat_poweroff_dete_del();
    }
}


static u16 low_bat_poweroff_dete_time = 0;

void low_bat_poweroff_dete_add()
{
    if(!low_bat_poweroff_dete_time)
    {
        low_bat_poweroff_dete_time = sys_timer_add(NULL,low_bat_poweroff_dete,1*1000);
    }
}

void low_bat_poweroff_dete_del()
{
    if(low_bat_poweroff_dete_time)
    {
        sys_timer_del(low_bat_poweroff_dete_time);
        low_bat_poweroff_dete_time = 0;
    }
}

void charge_vbat_led_states()
{
    if(get_charge_online_flag())
    {
        if(led7_init_num[0] < 100)
            led7_init_num[0]++;
        syscfg_write(USER_CFG_CHARGE_VALUE,&led7_init_num,1);
    }
    else
    {
        if(led7_init_num[0] > 0)
            led7_init_num[0]--;
        syscfg_write(USER_CFG_CHARGE_VALUE,&led7_init_num,1);
        if(led7_init_num[0] == 0)
            low_bat_poweroff_add();
        if(led7_init_num[0] == 5)
        {
            led_light_time_display_del();
            led7_charge_flash_add();
        }

    }
    printf("################ led7_init_num = %d ####################\n",led7_init_num[0]);
    if(led7_init_num[0] == 100)
    {
        hundreds = 3;
        tens = 0;
        unit = 0;
            //return ;
    }
    else{
        hundreds = 0;
        tens = led7_init_num[0] / 10;
        unit = led7_init_num[0] % 10;
    }

}


static u16 charge_vbat_flag = 0;
void charge_vbat_led_states_add()
{
    if(!charge_vbat_flag)
    {
        charge_vbat_flag = sys_timer_add(NULL,charge_vbat_led_states,1000*VBAT_DETE_INTAL_TIME);
    }

}

void charge_vbat_led_states_del()
{
    if(charge_vbat_flag)
    {
        sys_timer_del(charge_vbat_flag);
        charge_vbat_flag = 0;
    }
}

static u16 charge_bat_level = 0;
static u16 charge_bat_level_2 = 1;
static u16 charge_bat_level_3 = 2;

static u16 charge_bat_init_level = 3;

void bat_level_display()
{

        if(led7_init_num[0] >= 0 && led7_init_num[0] <=40)
        {
            charge_bat_level = 0;
        }
            //sys_timer_modify(charge_vbat_flag,CHARGE_VBAT_DETE_INTAL_TIME1*1000);
        else if(led7_init_num[0] > 40 && led7_init_num[0] <=70)
        {
            charge_bat_level = 1;
        }
            //sys_timer_modify(charge_vbat_flag,CHARGE_VBAT_DETE_INTAL_TIME2*1000);
        else{
            charge_bat_level = 2;
            //sys_timer_modify(charge_vbat_flag,CHARGE_VBAT_DETE_INTAL_TIME3*1000);
        }

        if(charge_bat_init_level != charge_bat_level)
        {
            charge_bat_init_level = charge_bat_level;
            if(led7_init_num[0] >= 0 && led7_init_num[0] <=40)
            {
                sys_timer_del(charge_vbat_flag);
                charge_vbat_flag = 0;
                charge_vbat_flag = sys_timer_add(NULL,charge_vbat_led_states,1000*CHARGE_VBAT_DETE_INTAL_TIME1);
            }
            else if(led7_init_num[0] > 40 && led7_init_num[0] <=70)
            {
                sys_timer_del(charge_vbat_flag);
                charge_vbat_flag = 0;
                charge_vbat_flag = sys_timer_add(NULL,charge_vbat_led_states,1000*CHARGE_VBAT_DETE_INTAL_TIME2);
            }
            else{
                sys_timer_del(charge_vbat_flag);
                charge_vbat_flag = 0;
                charge_vbat_flag = sys_timer_add(NULL,charge_vbat_led_states,1000*CHARGE_VBAT_DETE_INTAL_TIME3);
            }
        }
        if(led7_init_num[0] == 100)
        {
            led7_charge_flash1_del();
            led_water_flash_add();
        }

}



static u16 bat_level_display_time = 0;
void bat_level_display_add()
{
    if(!bat_level_display_time)
    {
        bat_level_display_time = sys_timer_add(NULL,bat_level_display,1000);
    }
}
*/

////////////////// USER VBAT DISPLAY /////////////////////////////
extern u8 hundreds;	//百位，0不显示，1仅百分比，2百分比+供电，3-百分比+百位，4全部显示
extern u8 tens; 		//十位，10-F，11-不显示
extern u8 unit;		//个位，10-F，11-不显示
//static u16 curr_vbat_value = 0;
extern void led7_charge_flash_add();

static int user_vbat_percent = 0;
static u16 vbat_cnt = 0;

static int curr_vbat_value = 0;
static int really_vbat_value = 0;
extern int led7_init_num[1];
void user_vbat_init()
{
    syscfg_read(USER_CFG_CHARGE_VALUE,&led7_init_num,1);
    curr_vbat_value = led7_init_num[0];//get_vbat_percent();
    really_vbat_value = curr_vbat_value;
    if(curr_vbat_value >= 100)
    {
        hundreds = 3;
        tens = 0;
        unit = 0;
    }
    else{
        hundreds = 0;
        tens = curr_vbat_value / 10;
        unit = curr_vbat_value % 10;
    }
    if(really_vbat_value <= 10){
        if(!get_charge_online_flag())
            led7_charge_flash_add();
    }
}

void really_vbat_display()
{
    if(really_vbat_value >= 100)
    {
        hundreds = 3;
        tens = 0;
        unit = 0;
    }
    else{
        hundreds = 0;
        tens = really_vbat_value / 10;
        unit = really_vbat_value % 10;
    }
}

void user_vbat_display()
{
    user_vbat_percent += get_vbat_percent();
    vbat_cnt++;
    if(vbat_cnt ==10)
    {
        user_vbat_percent = user_vbat_percent / 10;
        printf("*********** user_vbat_percent = %d ***********\n",user_vbat_percent);
        if((really_vbat_value - user_vbat_percent >= 2) || (really_vbat_value < user_vbat_percent))
        {
            curr_vbat_value = user_vbat_percent;
            if(really_vbat_value > curr_vbat_value)
            {
                really_vbat_value--;
            }
            //user_set_real_charge_time_add();
            printf("********** really_vbat_value = %d   curr_vbat_value = %d **********\n",really_vbat_value,curr_vbat_value);
            /*if(really_vbat_value == curr_vbat_value)
            {
                user_set_real_charge_time_del();
            }*/
            really_vbat_display();
            vbat_cnt = 0;
            user_vbat_percent = 0;
        }
        else
        {
            really_vbat_value = user_vbat_percent;
            really_vbat_display();
            //really_vbat_value = user_vbat_percent;
            vbat_cnt = 0;
            user_vbat_percent = 0;
        }
        if(really_vbat_value <= 10)
        {
            led7_charge_flash_add();
        }
        led7_init_num[0] = really_vbat_value;
        syscfg_write(USER_CFG_CHARGE_VALUE,&led7_init_num,1);
    }
    else{
        return ;
    }

}



static u16 user_vbat_display_time = 0;
void user_vbat_display_add()
{
    if(!user_vbat_display_time)
    {
        user_vbat_display_time = sys_timer_add(NULL,user_vbat_display,3200);
    }
}

void user_vbat_display_del()
{
    if(user_vbat_display_time)
    {
        sys_timer_del(user_vbat_display_time);
        user_vbat_display_time = 0;
    }
}



/////////////////充电电量显示////////////////////////////////////


static u16 charge_vbat_percent = 0;
static u16 charge_vbat_cnt = 0;


#define USER_DEFINE_REALLY_INTERAL  20


void user_set_real_charge_time()
{
    if(really_vbat_value < curr_vbat_value)
    {
        really_vbat_value++;
    }
}

static u16 really_time = 0;
void user_set_real_charge_time_add()
{
    if(!really_time)
    {
        really_time = sys_timer_add(NULL,user_set_real_charge_time,1000 * USER_DEFINE_REALLY_INTERAL);
    }
}

void user_set_real_charge_time_del()
{
    if(really_time)
    {
        sys_timer_del(really_time);
        really_time = 0;
    }
}

extern void led7_charge_flash_del();
void user_charge_vbat_display()
{
    charge_vbat_percent += get_vbat_percent();
    charge_vbat_cnt++;
    if(charge_vbat_cnt ==10)
    {
        charge_vbat_percent = charge_vbat_percent / 10;
        printf("*********** charge_vbat_percent = %d ***********\n",charge_vbat_percent);
        if((charge_vbat_percent - really_vbat_value) >= 2 || really_vbat_value > charge_vbat_percent)
        {
            curr_vbat_value = charge_vbat_percent;
            if(really_vbat_value < curr_vbat_value)
            {
                really_vbat_value++;
            }
            //user_set_real_charge_time_add();
            printf("********** really_vbat_value = %d   curr_vbat_value = %d **********\n",really_vbat_value,curr_vbat_value);
            /*if(really_vbat_value == curr_vbat_value)
            {
                user_set_real_charge_time_del();
            }*/
            if(really_vbat_value >= 100)
            {
                hundreds = 3;
                tens = 0;
                unit = 0;
                led7_charge_flash_del();
            }
            else{
                hundreds = 0;
                tens = really_vbat_value / 10;
                unit = really_vbat_value % 10;
            }
            charge_vbat_cnt = 0;
            charge_vbat_percent = 0;
        }
        else
        {
            if(really_vbat_value != 100)
                really_vbat_value = charge_vbat_percent;

            if(really_vbat_value >= 100)
            {
                hundreds = 3;
                tens = 0;
                unit = 0;
                led7_charge_flash_del();
            }
            else{
                hundreds = 0;
                tens = really_vbat_value / 10;
                unit = really_vbat_value % 10;
            }

            charge_vbat_cnt = 0;
            charge_vbat_percent = 0;
        }
        led7_init_num[0] = really_vbat_value;
        syscfg_write(USER_CFG_CHARGE_VALUE,&led7_init_num,1);
    }
    else{
        return ;
    }

}

static u16 charge_dete_time = 0;
void user_charge_vbat_display_add()
{
    if(!charge_dete_time)
    {
        charge_dete_time = sys_timer_add(NULL,user_charge_vbat_display,3000);
    }
}


void user_charge_vbat_display_del()
{
    if(charge_dete_time)
    {
        sys_timer_del(charge_dete_time);
        charge_dete_time = 0;
    }
}

/////////////////////////////////////////////////////////////////



void vbat_check(void *priv)
{
    static u8 unit_cnt = 0;
    static u8 low_warn_cnt = 0;
    static u8 low_off_cnt = 0;
    static u8 low_voice_cnt = 0;
    static u8 low_power_cnt = 0;
    static u8 power_normal_cnt = 0;
    static u8 charge_online_flag = 0;
    static u8 low_voice_first_flag = 1;//进入低电后先提醒一次

    if (!bat_val) {
        #if USER_SET_BAT_DETE
        bat_val = get_vbat_level() + 215;
        #else
        bat_val = get_vbat_level();
        #endif
    } else {
        #if USER_SET_BAT_DETE
        bat_val = (get_vbat_level() + bat_val + 215) / 2;
        #else
        bat_val = (get_vbat_level() + bat_val) / 2;
        #endif
    }

    cur_battery_level = battery_value_to_phone_level(bat_val);

    /* printf("bv:%d, bl:%d , check_vbat:%d\n", bat_val, cur_battery_level, adc_check_vbat_lowpower()); */

    unit_cnt++;

    /* if (bat_val < LOW_POWER_OFF_VAL) { */
    #if 0//USER_SET_BAT_DETE
    if (adc_check_vbat_lowpower() || led7_init_num[0] == 0) {
        low_off_cnt++;
    }
    /* if (bat_val < LOW_POWER_WARN_VAL) { */
    if (bat_val <= app_var.warning_tone_v || led7_init_num[0] <= 5) {
        low_warn_cnt++;
    }

    #else
    if (adc_check_vbat_lowpower() || (bat_val <= app_var.poweroff_tone_v)) {
        low_off_cnt++;
    }
    /* if (bat_val < LOW_POWER_WARN_VAL) { */
    if (bat_val <= app_var.warning_tone_v) {
        low_warn_cnt++;
    }

    #endif // 1

    /* log_info("unit_cnt:%d\n", unit_cnt); */

    if (unit_cnt >= VBAT_DETECT_CNT) {

        if (get_charge_online_flag() == 0) {
            if (low_off_cnt > (VBAT_DETECT_CNT / 2)) { //低电关机
                low_power_cnt++;
                low_voice_cnt = 0;
                power_normal_cnt = 0;
                cur_bat_st = VBAT_LOWPOWER;
                if (low_power_cnt > 6) {
                    log_info("\n*******Low Power,enter softpoweroff********\n");

                    low_power_cnt = 0;
                    power_event_to_user(POWER_EVENT_POWER_LOW);
                    usr_timer_del(vbat_fast_timer);
                    vbat_fast_timer = 0;
                }
            } else if (low_warn_cnt > (VBAT_DETECT_CNT / 2)) { //低电提醒
                low_voice_cnt ++;
                low_power_cnt = 0;
                power_normal_cnt = 0;
                cur_bat_st = VBAT_WARNING;
                if ((low_voice_first_flag && low_voice_cnt > 1) || //第一次进低电10s后报一次
                    (!low_voice_first_flag && low_voice_cnt >= 5)) {
                    low_voice_first_flag = 0;
                    low_voice_cnt = 0;
                    if (!lowpower_timer) {
                        log_info("\n**Low Power,Please Charge Soon!!!**\n");
                        power_event_to_user(POWER_EVENT_POWER_WARNING);
                    }
                }
            } else {
                power_normal_cnt++;
                low_voice_cnt = 0;
                low_power_cnt = 0;
                if (power_normal_cnt > 2) {
                    if (cur_bat_st != VBAT_NORMAL) {
                        log_info("[Noraml power]\n");
                        cur_bat_st = VBAT_NORMAL;
                        power_event_to_user(POWER_EVENT_POWER_NORMAL);
                    }
                }
            }
        } else {
            power_event_to_user(POWER_EVENT_POWER_CHARGE);
        }

        unit_cnt = 0;
        low_off_cnt = 0;
        low_warn_cnt = 0;

        if (cur_bat_st != VBAT_LOWPOWER) {
            usr_timer_del(vbat_fast_timer);
            vbat_fast_timer = 0;
            cur_battery_level = battery_value_to_phone_level(bat_val);
            if (cur_battery_level != old_battery_level) {
                power_event_to_user(POWER_EVENT_POWER_CHANGE);
            } else {
                if (charge_online_flag != get_charge_online_flag()) {
                    //充电变化也要交换，确定是否在充电仓
                    power_event_to_user(POWER_EVENT_POWER_CHANGE);
                }
            }
            charge_online_flag =  get_charge_online_flag();
            old_battery_level = cur_battery_level;
        }
    }
}

bool vbat_is_low_power(void)
{
    return (cur_bat_st != VBAT_NORMAL);
}


static u32 led7_init_aux_total_value = 0;


void check_power_on_voltage(void)
{
#if(TCFG_SYS_LVD_EN == 1)

    u16 val = 0;
    u8 normal_power_cnt = 0;
    u8 low_power_cnt = 0;

    while (1) {
        clr_wdt();
        val = get_vbat_level() + 213;
        printf("vbat: %d\n", val);
        if ((val < app_var.poweroff_tone_v) || adc_check_vbat_lowpower()) {
            low_power_cnt++;
            normal_power_cnt = 0;
            if (low_power_cnt > 10) {
                ui_update_status(STATUS_POWERON_LOWPOWER);
                os_time_dly(100);
                log_info("power on low power , enter softpoweroff!\n");
                power_set_soft_poweroff();
            }
        } else {
            normal_power_cnt++;
            low_power_cnt = 0;
            if (normal_power_cnt > 10) {
                vbat_check_init();
                return;
            }
        }
    }
#endif
}

//#if(CONFIG_CPU_BR25)
#ifdef CONFIG_CPU_BR25
void app_reset_vddiom_lev(u8 lev)
{
    if (TCFG_LOWPOWER_VDDIOM_LEVEL == VDDIOM_VOL_34V) {
        /* printf("\n\n\n\n\n -------------------set vddiom again %d -----------------------\n\n\n\n\n",lev); */
        reset_vddiom_lev(lev);
    }
}
#else
void app_reset_vddiom_lev(u8 lev)
{

}
#endif



