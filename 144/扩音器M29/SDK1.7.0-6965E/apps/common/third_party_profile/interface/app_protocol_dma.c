#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "app_protocol_api.h"
#include "system/includes.h"
#include "vm.h"
#include "audio_config.h"
#include "app_power_manage.h"
#include "user_cfg.h"
#include "app_main.h"
#include "bt_tws.h"
#include "btstack/avctp_user.h"
#if APP_PROTOCOL_DMA_CODE

#if 1
#define APP_DMA_LOG       printf
#define APP_DMA_DUMP      put_buf
#else
#define APP_DMA_LOG(...)
#define APP_DMA_DUMP(...)
#endif

//*********************************************************************************//
//                                 DMA认证信息                                     //
//*********************************************************************************//
#define DMA_PRODUCT_INFO_TEST       1

#if DMA_PRODUCT_INFO_TEST
static const char *dma_product_id  = "asoYwYghv0fy6HFexl6bTIZUHjyZGnEH";
static const char *dma_triad_id    = "0004BcJb0000000200000006";
static const char *dma_secret      = "c2485845b6f3640a";
#endif
static const char *dma_product_key = "Yg5Xb2NOK01bgB9csSUHAAgG4lUjMXXZ";

#define DMA_PRODUCT_ID_LEN      65
#define DMA_PRODUCT_KEY_LEN     65
#define DMA_TRIAD_ID_LEN        32
#define DMA_SECRET_LEN          16

#define DMA_LEGAL_CHAR(c)       ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

static u16 dma_get_one_info(const u8 *in, u8 *out)
{
    int read_len = 0;
    const u8 *p = in;

    while (DMA_LEGAL_CHAR(*p) && *p != ',') { //read Product ID
        *out++ = *p++;
        read_len++;
    }
    return read_len;
}

const u8 *get_dma_mac_addr()
{
    u8 mac_addr[6];
    memcpy(mac_addr, bt_get_mac_addr(), 6);
#if TCFG_USER_TWS_ENABLE
    int read_len;
    read_len = syscfg_read(CFG_TWS_COMMON_ADDR, mac_addr, 6);
    if (read_len == 6) {
        return mac_addr;
    }
#endif
    return mac_addr;
}

u8 read_dma_product_info_from_flash(u8 *read_buf, u16 buflen)
{
    u8 *rp = read_buf;
    const u8 *dma_ptr = (u8 *)app_protocal_get_license_ptr();

    if (dma_ptr == NULL) {
        return FALSE;
    }

    if (dma_get_one_info(dma_ptr, rp) != 32) {
        return FALSE;
    }
    dma_ptr += 33;

    rp = read_buf + DMA_PRODUCT_ID_LEN;
    memcpy(rp, dma_product_key, strlen(dma_product_key));

    rp = read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN;
    if (dma_get_one_info(dma_ptr, rp) != 24) {
        return FALSE;
    }
    dma_ptr += 25;

    rp = read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN;
    if (dma_get_one_info(dma_ptr, rp) != 16) {
        return FALSE;
    }

    return TRUE;
}

void dueros_dma_manufacturer_info_init()
{
    u8 read_buf[DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN + DMA_SECRET_LEN + 1] = {0};
    bool ret = FALSE;

    APP_DMA_LOG("dueros_dma_manufacturer_info_init\n");

#if DMA_PRODUCT_INFO_TEST
    memcpy(read_buf, dma_product_id, strlen(dma_product_id));
    memcpy(read_buf + DMA_PRODUCT_ID_LEN, dma_product_key, strlen(dma_product_key));
    memcpy(read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN, dma_triad_id, strlen(dma_triad_id));
    memcpy(read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN, dma_secret, strlen(dma_secret));
    ret = TRUE;
#else
    ret = read_dma_product_info_from_flash(read_buf, sizeof(read_buf));
#endif

#if TCFG_USER_TWS_ENABLE
    int len;
    char channel = bt_tws_get_local_channel();
    if (channel == 'R') {
        len = syscfg_read(VM_DMA_MASTER_LIC, read_buf, sizeof(read_buf));
        if (len == sizeof(read_buf)) {
            ret = TRUE;
        }
    }
#endif

    if (ret == TRUE) {
        APP_DMA_LOG("read license success\n");
        APP_DMA_LOG("product id: %s\n", read_buf);
        APP_DMA_LOG("product key: %s\n", read_buf + DMA_PRODUCT_ID_LEN);
        APP_DMA_LOG("triad id: %s\n", read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN);
        APP_DMA_LOG("secret: %s\n", read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN);
        app_protocol_set_info_group(DMA_HANDLER_ID, read_buf);
    } else {
        app_protocol_set_info_group(DMA_HANDLER_ID, NULL);
    }

#if 0
    //c7:f4:27:e6:2f:d8
    // u8 mac[] = {0xF4, 0x43, 0x8D, 0x29, 0x17, 0x02};
    u8 mac[] = {0xC7, 0xF4, 0x27, 0xE6, 0x2F, 0xD8};
    u8 ble_mac[6];
    void bt_update_mac_addr(u8 * addr);
    void lmp_hci_write_local_address(const u8 * addr);
    void bt_update_testbox_addr(u8 * addr);
    extern int le_controller_set_mac(void *addr);
    extern void lib_make_ble_address(u8 * ble_address, u8 * edr_address);
    bt_update_mac_addr(mac);
    lmp_hci_write_local_address(mac);
    bt_update_testbox_addr(mac);
    lib_make_ble_address(ble_mac, mac);
    le_controller_set_mac(ble_mac); //修改BLE地址
    APP_DMA_DUMP(mac, 6);
    APP_DMA_DUMP(ble_mac, 6);
#endif
}

//*********************************************************************************//
//                                 DMA提示音                                       //
//*********************************************************************************//
const char *dma_notice_tab[APP_RROTOCOL_TONE_MAX] = {
    [APP_PROTOCOL_TONE_CONNECTED_ALL_FINISH]		= TONE_RES_ROOT_PATH"tone/xd_ok.*",//所有连接完成【已连接，你可以按AI键来和我进行对话】
    [APP_PROTOCOL_TONE_PROTOCOL_CONNECTED]		= TONE_RES_ROOT_PATH"tone/xd_con.*",//小度APP已连接，经典蓝牙未连接【请在手机上完成蓝牙配对】
    [APP_PROTOCOL_TONE_CONNECTED_NEED_OPEN_APP]	= TONE_RES_ROOT_PATH"tone/xd_btcon.*",//经典蓝牙已连接，小度app未连接【已配对，请打开小度app进行连接】
    [APP_PROTOCOL_TONE_DISCONNECTED]				= TONE_RES_ROOT_PATH"tone/xd_dis.*",//经典蓝牙已断开【蓝牙已断开，请在手机上完成蓝牙配对】
    [APP_PROTOCOL_TONE_DISCONNECTED_ALL]			= TONE_RES_ROOT_PATH"tone/xd_alldis.*",//经典蓝牙和小度都断开了【蓝牙未连接，请用手机蓝牙和我连接吧】
    [APP_RROTOCOL_TONE_SPEECH_APP_START]	    	= TONE_NORMAL,
    [APP_RROTOCOL_TONE_SPEECH_KEY_START]	    	= TONE_NORMAL,
};

#endif

//*********************************************************************************//
//                                 DMA私有消息处理                                 //
//*********************************************************************************//
#if TCFG_USER_TWS_ENABLE
//固定使用左耳的三元组

void tws_conn_sync_conn_state(dma_pair_state, init_flag)
{
    u8 dma_state_sync_buf[2];
    dma_state_sync_buf[0] = dma_pair_state;
    dma_state_sync_buf[1] = init_flag;
    app_protocol_tws_send_to_sibling(DMA_TWS_CMD_SYNC_DMA_CONN_STATE, dma_state_sync_buf, sizeof(dma_state_sync_buf));
}

static void tws_conn_sync_lic()
{
    u8 read_buf[DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN + DMA_SECRET_LEN + 1] = {0};
    bool ret = FALSE;
    if (tws_api_get_local_channel() == 'L') {
#if DMA_PRODUCT_INFO_TEST
        memcpy(read_buf, dma_product_id, strlen(dma_product_id));
        memcpy(read_buf + DMA_PRODUCT_ID_LEN, dma_product_key, strlen(dma_product_key));
        memcpy(read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN, dma_triad_id, strlen(dma_triad_id));
        memcpy(read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN, dma_secret, strlen(dma_secret));
        ret = TRUE;
#else
        ret = read_dma_product_info_from_flash(read_buf, sizeof(read_buf));
#endif
    }
    if (ret) {
        APP_DMA_LOG("dueros_dma start sync manufacturer info\n");
        app_protocol_tws_send_to_sibling(DMA_TWS_CMD_SYNC_LIC, read_buf, sizeof(read_buf));
    }
}

extern u8 get_dma_rand(u8 *buf);
void tws_conn_sync_connect_info()
{
    u8 tx_buf[10] = {0};
    u8 tx_buf_len = 0;
    if (is_tws_master_role()) {
        tx_buf_len = get_dma_rand(tx_buf);
        if (tx_buf_len > 0) {
            put_buf(tx_buf, tx_buf_len);
            app_protocol_tws_send_to_sibling(DMA_TWS_LIB_INFO_SYNC, tx_buf, tx_buf_len);
        }
    }
}

static void dma_tws_rx_license_deal(u8 *license, u16 len)
{
    int ret;
    u8 read_buf[DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN + DMA_SECRET_LEN + 1] = {0};
    ret = syscfg_read(VM_DMA_MASTER_LIC, read_buf, sizeof(read_buf));
    if (ret == sizeof(read_buf)) {
        if (memcmp(read_buf, license, len)) {
            syscfg_write(VM_DMA_MASTER_LIC, license, len);
        }
    } else {
        syscfg_write(VM_DMA_MASTER_LIC, license, len);
    }
    app_protocol_set_info_group(DMA_HANDLER_ID, license);
    if (0) {
        app_protocol_set_info_group(DMA_HANDLER_ID, license);
        app_protocol_disconnect(NULL);
        app_protocol_ble_adv_switch(0);
        if (0 == get_esco_coder_busy_flag()) {
            app_protocol_ble_adv_switch(1);
        }
    }
}

extern void tws_dueros_rand_set_vm(u8 *data, u8 len);
static void dma_rx_tws_data_deal(u16 opcode, u8 *data, u16 len)
{
    switch (opcode) {
    case DMA_TWS_CMD_SYNC_LIC:
        APP_DMA_LOG(">>> DMA_TWS_CMD_SYNC_LIC \n");
        dma_tws_rx_license_deal(data, len);
        break;
    case DMA_TWS_LIB_INFO_SYNC:
        //dma_peer_recieve_data(data, len);
        tws_dueros_rand_set_vm(data, len);
        break;
    case DMA_TWS_TONE_INFO_SYNC:
        int index = -1;
        memcpy(&index, data, len);
        printf("slave sync tone index:%d", index);
        //dma_tone_status_update(index, 1);
        break;
    case DMA_TWS_CMD_SYNC_DMA_CONN_STATE:
        u8 state = data[0];
        u8 init_flag = data[1];
        printf("DMA tws sync_conn_state, state:%d, flag:%d", state, init_flag);
        set_dueros_pair_state(state, init_flag);
        break;
    }
}

static void dma_update_ble_addr()
{
    u8 comm_addr[6];

    printf("%s\n", __func__);

    tws_api_get_local_addr(comm_addr);
    le_controller_set_mac(comm_addr); //地址发生变化，更新地址
    app_protocol_ble_adv_switch(0);
    if (0 == get_esco_coder_busy_flag()) {
        //esco在用的时候开广播会影响质量
        app_protocol_ble_adv_switch(1);
    }
}

static void dma_bt_tws_event_handler(struct bt_event *bt)
{
    int role = bt->args[0];
    int phone_link_connection = bt->args[1];
    int reason = bt->args[2];

    switch (bt->event) {
    case TWS_EVENT_CONNECTED:
        app_protocal_update_tws_state_to_lib(USER_NOTIFY_STATE_TWS_CONNECT);
        if (dma_check_tws_is_master()) {
            if (!dma_pair_state()) {
                dma_update_ble_addr();
            }
            tws_conn_sync_conn_state(dma_pair_state(), 1);
            tws_conn_sync_connect_info();
        }
//#if DMA_PRODUCT_INFO_EN
        tws_conn_sync_lic();
//#endif
        break;
    case TWS_EVENT_CONNECTION_DETACH:
        app_protocal_update_tws_state_to_lib(USER_NOTIFY_STATE_BATTERY_LEVEL_UPDATE); //主动上报电量
        app_protocal_update_tws_state_to_lib(USER_NOTIFY_STATE_TWS_DISCONNECT);
        break;
    case TWS_EVENT_REMOVE_PAIRS:
        break;
    }
}
static void app_protocol_dma_tws_sync_deal(int cmd, int value)
{
    switch (cmd) {
    case APP_PROTOCOL_SYNC_DMA_TONE:
        APP_DMA_LOG("APP_PROTOCOL_SYNC_DMA_TONE:%d\n", value);
        //app_protocol_dma_tone_play(value, 0);
        break;
    }
}
#endif

static int dma_bt_connction_status_event_handler(struct bt_event *bt)
{
    switch (bt->event) {
    case BT_STATUS_FIRST_DISCONNECT:
    case BT_STATUS_SECOND_DISCONNECT:
        printf("phone disconned, cannel dma tone");
        //dma_tone_play_index = -1;
        break;
    case BT_STATUS_PHONE_INCOME:
    case BT_STATUS_PHONE_OUT:
    case BT_STATUS_PHONE_ACTIVE:
    case BT_STATUS_VOICE_RECOGNITION:
        break;
    }
    return 0;
}

int dma_sys_event_deal(struct sys_event *event)
{
    switch (event->type) {
    case SYS_BT_EVENT:
        if ((u32)event->arg == SYS_BT_EVENT_TYPE_CON_STATUS) {
            dma_bt_connction_status_event_handler(&event->u.bt);
        }
#if TCFG_USER_TWS_ENABLE
        else if (((u32)event->arg == SYS_BT_EVENT_FROM_TWS)) {
            dma_bt_tws_event_handler(&event->u.bt);
        }
#endif
        break;

    }

    return 0;

}

struct app_protocol_private_handle_t dma_private_handle = {
#if TCFG_USER_TWS_ENABLE
    .tws_rx_from_siblling = dma_rx_tws_data_deal,
    .tws_sync_func = app_protocol_dma_tws_sync_deal,
#endif
    .sys_event_handler = dma_sys_event_deal,
};
