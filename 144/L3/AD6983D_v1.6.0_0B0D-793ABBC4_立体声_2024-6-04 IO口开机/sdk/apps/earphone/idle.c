#include "system/includes.h"
#include "media/includes.h"
#include "app_config.h"
#include "app_action.h"
#include "tone_player.h"
#include "asm/charge.h"
#include "app_charge.h"
#include "app_main.h"
#include "ui_manage.h"
#include "vm.h"
#include "app_chargestore.h"
#include "user_cfg.h"
#include "default_event_handler.h"

#if TCFG_ANC_BOX_ENABLE
#include "app_ancbox.h"
#endif

#define LOG_TAG_CONST       APP_IDLE
#define LOG_TAG             "[APP_IDLE]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

#ifdef CONFIG_MEDIA_DEVELOP_ENABLE
#define AUDIO_PLAY_EVENT_END 		AUDIO_DEC_EVENT_END
#endif /* #ifdef CONFIG_MEDIA_DEVELOP_ENABLE */

static void app_idle_enter_softoff(void)
{
    //ui_update_status(STATUS_POWEROFF);
    while (get_ui_busy_status()) {
        log_info("ui_status:%d\n", get_ui_busy_status());
    }
#if TCFG_CHARGE_ENABLE
    if (get_lvcmp_det() && (0 == get_charge_full_flag())) {
        log_info("charge inset, system reset!\n");
        cpu_reset();
    }
#endif

    extern void dac_power_off(void);
    dac_power_off();    // 关机前先关dac

    power_set_soft_poweroff();
}

static int app_idle_tone_event_handler(struct device_event *dev)
{
    int ret = false;

    switch (dev->event) {
    case AUDIO_PLAY_EVENT_END:
        if (app_var.goto_poweroff_flag) {
            log_info("audio_play_event_end,enter soft poweroff");
            app_idle_enter_softoff();
        }
        break;
    }

    return ret;
}

static int idle_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return 0;
    case SYS_BT_EVENT:
        return 0;
    case SYS_DEVICE_EVENT:
        if ((u32)event->arg == DEVICE_EVENT_FROM_CHARGE) {
#if TCFG_CHARGE_ENABLE
            return app_charge_event_handler(&event->u.dev);
#endif
        }
        if ((u32)event->arg == DEVICE_EVENT_FROM_TONE) {
            return app_idle_tone_event_handler(&event->u.dev);
        }
#if TCFG_CHARGESTORE_ENABLE || TCFG_TEST_BOX_ENABLE
        if ((u32)event->arg == DEVICE_EVENT_CHARGE_STORE) {
            app_chargestore_event_handler(&event->u.chargestore);
        }
#endif
#if TCFG_ANC_BOX_ENABLE
        if ((u32)event->arg == DEVICE_EVENT_FROM_ANC) {
            return app_ancbox_event_handler(&event->u.ancbox);
        }
#endif
        break;
    default:
        return false;
    }

#if (CONFIG_BT_BACKGROUND_ENABLE || TCFG_PC_ENABLE)
    default_event_handler(event);
#endif

    return false;
}

static int idle_state_machine(struct application *app, enum app_state state,
                              struct intent *it)
{
    int ret;
    switch (state) {
    case APP_STA_CREATE:
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_IDLE_MAIN:
            log_info("ACTION_IDLE_MAIN\n");
            if (app_var.goto_poweroff_flag) {
                syscfg_write(CFG_MUSIC_VOL, &app_var.music_volume, 1);
                /* tone_play(TONE_POWER_OFF); */
                os_taskq_flush();
                STATUS *p_tone = get_tone_config();
                ret = tone_play_index(p_tone->power_off, 1);
                printf("power_off tone play ret:%d", ret);
                if (ret) {
                    if (app_var.goto_poweroff_flag) {
                        log_info("power_off tone play err,enter soft poweroff");
                        app_idle_enter_softoff();
                    }
                }
            }
            break;
        case ACTION_IDLE_POWER_OFF:
            os_taskq_flush();
            syscfg_write(CFG_MUSIC_VOL, &app_var.music_volume, 1);
            break;
        }
        break;
    case APP_STA_PAUSE:
        break;
    case APP_STA_RESUME:
        break;
    case APP_STA_STOP:
        break;
    case APP_STA_DESTROY:
        break;
    }

    return 0;
}

static const struct application_operation app_idle_ops = {
    .state_machine  = idle_state_machine,
    .event_handler 	= idle_event_handler,
};

REGISTER_APPLICATION(app_app_idle) = {
    .name 	= "idle",
    .action	= ACTION_IDLE_MAIN,
    .ops 	= &app_idle_ops,
    .state  = APP_STA_DESTROY,
};


