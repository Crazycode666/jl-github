#include "system/includes.h"
#include "system/event.h"

///自定义事件推送的线程
extern const struct task_info task_info_table[];

#define Q_USER_DEAL   0xAABBCC ///自定义队列类型
#define Q_USER_DATA_SIZE  10///理论Queue受任务声明struct task_info.qsize限制,但不宜过大,建议<=6

enum {
    KEY_USER_DEAL_POST = 0,
    KEY_USER_DEAL_POST_MSG,
    KEY_USER_DEAL_POST_EVENT,
    KEY_USER_DEAL_POST_2,
};

void user_deal_send_ver(void)
{
    //os_taskq_post("user_deal", 1,KEY_USER_DEAL_POST);
    os_taskq_post_msg("user_deal", 1, KEY_USER_DEAL_POST_MSG);
    //os_taskq_post_event("user_deal",1, KEY_USER_DEAL_POST_EVENT);
}

void user_deal_rand_set(u32 rand)
{
    os_taskq_post("user_deal", 2, KEY_USER_DEAL_POST_2, rand);
}

void user_deal_send_array(int *msg, int argc)
{
    if (argc > Q_USER_DATA_SIZE) {
        return;
    }
    os_taskq_post_type("user_deal", Q_USER_DEAL, argc, msg);
}
void user_deal_send_msg(void)
{
    os_taskq_post_event("user_deal", 1, KEY_USER_DEAL_POST_EVENT);
}

void user_deal_send_test(void)///模拟测试函数,可按键触发调用，自行看打印
{
    user_deal_send_ver();
    user_deal_rand_set(0x11223344);
    static u32 data[Q_USER_DATA_SIZE] = {0x11223344, 0x55667788, 0x11223344, 0x55667788, 0x11223344,
                                         0xff223344, 0x556677ee, 0x11223344, 0x556677dd, 0x112233ff,
                                        };
    user_deal_send_array(data, sizeof(data) / sizeof(int));
}

static void user_deal_task_handle(void *p)
{
    int msg[Q_USER_DATA_SIZE + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 00, 0};
    int res = 0;
    while (1) {
        res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));
        if (res != OS_TASKQ) {
            continue;
        }
        r_printf("user_deal_task_handle:0x%x", msg[0]);
        put_buf(msg, (Q_USER_DATA_SIZE + 1) * 4);
        if (msg[0] == Q_MSG) {
            printf("use os_taskq_post_msg");
            switch (msg[1]) {
            case KEY_USER_DEAL_POST_MSG:
                printf("KEY_USER_DEAL_POST_MSG");
                break;
            default:
                break;
            }
        } else if (msg[0] == Q_EVENT) {
            printf("use os_taskq_post_event");
            switch (msg[1]) {
            case KEY_USER_DEAL_POST_EVENT:
                printf("KEY_USER_DEAL_POST_EVENT");
                break;
            default:
                break;
            }
        } else if (msg[0] == Q_CALLBACK) {
        } else if (msg[0] == Q_USER) {
            printf("use os_taskq_post");
            switch (msg[1]) {
            case KEY_USER_DEAL_POST:
                printf("KEY_USER_DEAL_POST");
                break;
            case KEY_USER_DEAL_POST_2:
                printf("KEY_USER_DEAL_POST_2:0x%x", msg[2]);
                break;
            default:
                break;
            }
        } else if (msg[0] == Q_USER_DEAL) {
            printf("use os_taskq_post_type");
            printf("0x%x 0x%x 0x%x 0x%x 0x%x", msg[1], msg[2], msg[3], msg[4], msg[5]);
            printf("0x%x 0x%x 0x%x 0x%x 0x%x", msg[6], msg[7], msg[8], msg[9], msg[10]);
        }
        puts("");
    }
}

void user_deal_init(void)
{
    task_create(user_deal_task_handle, NULL, "user_deal");
}

void user_deal_exit(void)
{
    task_kill("user_deal");
}
