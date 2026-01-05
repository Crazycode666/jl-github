#ifndef __USB_STORAGE_H__
#define __USB_STORAGE_H__

#include "system/task.h"
#include "device/device.h"
#include "usb/scsi.h"
#include "usb_bulk_transfer.h"
#include "usb/host/usb_host.h"

#define UDISK_READ_AHEAD_ENABLE      1   //使能U盘预读功能
#define UDISK_READ_AHEAD_BLOCK_NUM  16  //U盘预读扇区数量
#define     check_usb_read_ahead(ret)    \
    if(ret < 0) {\
        log_error("func:%s,line:%d,lba:%d,ret:%d\n", __func__, __LINE__, lba, ret);\
        goto __exit;\
    }   //检查函数返回值，0:正确    非0:错误

/**@enum    usb_sta
  * @brief  USB设备当前状态
  */
typedef enum usb_sta {
    DEV_IDLE = 0,
    DEV_INIT,
    DEV_OPEN,
    DEV_READ,
    DEV_WRITE,
    DEV_CLOSE,
    DEV_SUSPEND,
} USB_STA ;

struct udisk_end_desc {
    u8 host_epout;
    u8 target_epout;
    u8 host_epin;
    u8 target_epin;
#if HUSB_MODE
    u16 rxmaxp;
    u16 txmaxp;
#endif
};

#define ENABLE_DISK_HOTPLUG  0
struct mass_storage {
    OS_MUTEX mutex;

    struct usb_scsi_cbw cbw;
    struct usb_scsi_csw csw;
    struct request_sense_data sense;

    char *name;
    struct read_capacity_data capacity[2];
    u8 lun;
    u8 curlun;

    u8 dev_status;
    u8 suspend_cnt;
    u8 read_only;

    u32 remain_len;
    u32 prev_lba;
#if UDISK_READ_AHEAD_ENABLE
    u8 udisk_read_ahead_en;
    u8 *udisk_read_ahead_buf; ///<U盘512byte大小BUFFER指针
    u32 udisk_read_ahead_lba_last; ///<异步模式上一次地址
#endif
#if ENABLE_DISK_HOTPLUG
    u8 media_sta_cur;  //for card reader, card removable
    u8 media_sta_prev;

    int test_unit_ready_tick;
#endif
};

enum usb_async_mode {
    BULK_ASYNC_MODE_EXIT = 0, //取消异步模式
    BULK_ASYNC_MODE_SEM_PEND, //异步预读等待信号量
};

#define MASS_LBA_INIT    (-2)

int usb_msd_parser(struct usb_host_device *host_dev, u8 interface_num, const u8 *pBuf);
int _usb_stor_async_wait_sem(struct usb_host_device *host_dev);

#endif
