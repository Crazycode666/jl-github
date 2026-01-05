#include "config_tool.h"
#include "boot.h"
#include "ioctl_cmds.h"
#include "app_online_cfg.h"

#define LOG_TAG_CONST       APP_EARPHONE_TOOL
#define LOG_TAG             "[APP_EARPHONE_TOOL]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

struct spp_earphone_tool_info {
    R_PREPARE_WRITE_FILE	r_prepare_write_file;
    R_READ_ADDR_RANGE		r_read_addr_range;
    R_ERASE_ADDR_RANGE      r_erase_addr_range;
    R_WRITE_ADDR_RANGE      r_write_addr_range;
    R_ENTER_UPGRADE_MODE    r_enter_upgrade_mode;

    S_PREPARE_WRITE_FILE    s_prepare_write_file;
    void (*ci_send_packet_new)(EQ_CFG *eq_cfg, u32 id, u8 *packet, int size);
};
static struct spp_earphone_tool_info info;

#define EQ_CONFIG_ID        0x0005

static u32 encode_data_by_user_key(u16 key, u8 *buff, u16 size, u32 dec_addr, u8 dec_len)
{
    u16 key_addr;
    u16 r_len;

    while (size) {
        r_len = (size > dec_len) ? dec_len : size;
        key_addr = (dec_addr >> 2)^key;
        doe(key_addr, buff, r_len, 0);
        buff += r_len;
        dec_addr += r_len;
        size -= r_len;
    }

    return dec_addr;
}

void ci_send_callback(void (*ci_send_packet_new)(EQ_CFG *eq_cfg, u32 id, u8 *packet, int size))
{
    info.ci_send_packet_new = ci_send_packet_new;
}

const char _error_return[] = "FA";	//表示失败
const char _ok_return[] = "OK";		//表示成功
u8 check_online_update(u32 event, u8 *packet, u8 size)
{
    u8 *buf = NULL;
    u8 *buf_temp = NULL;
    u32 erase_cmd;
    int write_len;

    /* printf_buf(packet, size); */

    buf = (u8 *)malloc(256);
    if (buf == NULL) {
        log_error("buf malloc err!");
        return 0;
    }

    switch (event) {
    case ONLINE_SUB_OP_PREPARE_WRITE_FILE:
        /* log_info("event_ONLINE_SUB_OP_PREPARE_WRITE_FILE\n"); */

        info.r_prepare_write_file.file_id = (packet[4] | (packet[5] << 8) | (packet[6] << 16) | (packet[7] << 24));

        info.r_prepare_write_file.size = (packet[8] | (packet[9] << 8) | (packet[10] << 16) | (packet[11] << 24));

        if (info.r_prepare_write_file.file_id <= CFG_EQ_FILEID) {
            FILE *cfg_fp = NULL;

            if ((info.r_prepare_write_file.file_id == CFG_TOOL_FILEID)) {
                cfg_fp = fopen(CFG_TOOL_FILE, "r");
                log_info("open cfg_tool.bin\n");
            } else if ((info.r_prepare_write_file.file_id == CFG_OLD_EQ_FILEID)) {
                cfg_fp = fopen(CFG_OLD_EQ_FILE, "r");
                log_info("open old eq_cfg_hw.bin\n");
            } else if ((info.r_prepare_write_file.file_id == CFG_OLD_EFFECT_FILEID)) {
                cfg_fp = fopen(CFG_OLD_EFFECT_FILE, "r");
                log_info("open effects_cfg.bin\n");
            } else if ((info.r_prepare_write_file.file_id == CFG_EQ_FILEID)) {
                cfg_fp = fopen(CFG_EQ_FILE, "r");
                log_info("open eq_cfg_hw.bin\n");
            }

            if (cfg_fp == NULL) {
                memcpy(buf, _error_return, sizeof(_error_return));
                if (info.ci_send_packet_new) {
                    info.ci_send_packet_new(get_eq_cfg_hdl(), EQ_CONFIG_ID, buf, sizeof(_error_return));
                }
                log_error("file open error!\n");
                break;
            }
            struct vfs_attr attr;
            fget_attrs(cfg_fp, &attr);

            /* log_info("file addr:%x,file size:%d\n", attr.sclust, attr.fsize); */
            if (info.r_prepare_write_file.size > attr.fsize) {
                //fclose(cfg_fp);
                //log_error("preparing to write size more than actual size!\n");
                //break;
            }

            info.s_prepare_write_file.file_size = attr.fsize;
            log_info("file_size = %d\n", info.s_prepare_write_file.file_size);

            info.s_prepare_write_file.file_addr = sdfile_cpu_addr2flash_addr(attr.sclust);
            log_info("file_flash_addr:0x%x\n", info.s_prepare_write_file.file_addr);

            info.s_prepare_write_file.earse_unit = boot_info.vm.align * 256;
            log_info("earse_unit = %d\n", info.s_prepare_write_file.earse_unit);

            buf[3] = (info.s_prepare_write_file.file_addr >> 24) & 0xff;
            buf[2] = (info.s_prepare_write_file.file_addr >> 16) & 0xff;
            buf[1] = (info.s_prepare_write_file.file_addr >> 8) & 0xff;
            buf[0] = info.s_prepare_write_file.file_addr & 0xff;

            buf[7] = (info.s_prepare_write_file.file_size >> 24) & 0xff;
            buf[6] 	= (info.s_prepare_write_file.file_size >> 16) & 0xff;
            buf[5] 	= (info.s_prepare_write_file.file_size >> 8) & 0xff;
            buf[4] 	= info.s_prepare_write_file.file_size & 0xff;

            buf[11] = (info.s_prepare_write_file.earse_unit >> 24) & 0xff;
            buf[10] = (info.s_prepare_write_file.earse_unit >> 16) & 0xff;
            buf[9] = (info.s_prepare_write_file.earse_unit >> 8) & 0xff;
            buf[8] = info.s_prepare_write_file.earse_unit & 0xff;

            if (info.ci_send_packet_new) {
                info.ci_send_packet_new(get_eq_cfg_hdl(), EQ_CONFIG_ID, buf, sizeof(info.s_prepare_write_file.file_size) * 3);
            }
            fclose(cfg_fp);
        }
        break;
    case ONLINE_SUB_OP_READ_ADDR_RANGE:
        /* log_info("event_ONLINE_SUB_OP_READ_ADDR_RANGE\n"); */

        info.r_read_addr_range.addr = (packet[4] | (packet[5] << 8) | (packet[6] << 16) | (packet[7] << 24));
        /* log_info("reading flash addr:0x%x\n", info.r_read_addr_range.addr); */

        info.r_read_addr_range.size = (packet[8] | (packet[9] << 8) | (packet[10] << 16) | (packet[11] << 24));
        /* log_info("reading size = %d\n", info.r_read_addr_range.size); */

        buf_temp = (char *)malloc(info.r_read_addr_range.size);
        norflash_read(NULL, (void *)buf_temp, info.r_read_addr_range.size, info.r_read_addr_range.addr);
        /* printf_buf(buf_temp, info.r_read_addr_range.size); */

        memcpy(buf, buf_temp, info.r_read_addr_range.size);

        if (info.ci_send_packet_new) {
            info.ci_send_packet_new(get_eq_cfg_hdl(), EQ_CONFIG_ID, buf, info.r_read_addr_range.size);
        }
        if (buf_temp) {
            free(buf_temp);
        }
        break;
    case ONLINE_SUB_OP_ERASE_ADDR_RANGE:
        /* log_info("event_ONLINE_SUB_OP_ERASE_ADDR_RANGE\n"); */

        info.r_erase_addr_range.addr = (packet[4] | (packet[5] << 8) | (packet[6] << 16) | (packet[7] << 24));
        /* log_info("erasing flash start addr:0x%x\n", info.r_erase_addr_range.addr); */

        info.r_erase_addr_range.size = (packet[8] | (packet[9] << 8) | (packet[10] << 16) | (packet[11] << 24));
        /* log_info("erasing size = %d\n", info.r_erase_addr_range.size); */

        /* log_info("earse_unit = %d\n", info.s_prepare_write_file.earse_unit); */
        switch (info.s_prepare_write_file.earse_unit) {
        case 256:
            erase_cmd = IOCTL_ERASE_PAGE;
            break;
        case (4*1024):
            erase_cmd = IOCTL_ERASE_SECTOR;
            break;
        case (64*1024):
            erase_cmd = IOCTL_ERASE_BLOCK;
            break;
defualt:
            memcpy(buf, _error_return, sizeof(_error_return));
            log_error("erase error!");
            break;
        }

        for (u8 i = 0; i < (info.r_erase_addr_range.size / info.s_prepare_write_file.earse_unit); i ++) {
            extern int norflash_erase(u32 cmd, u32 addr);
            u8 ret = norflash_erase(erase_cmd, info.r_erase_addr_range.addr + (i * info.s_prepare_write_file.earse_unit));
            if (ret) {
                memcpy(buf, _error_return, sizeof(_error_return));
                log_error("erase error!");
            } else {
                memcpy(buf, _ok_return, sizeof(_ok_return));
                log_info("erase success");
            }
        }

        if (info.ci_send_packet_new) {
            info.ci_send_packet_new(get_eq_cfg_hdl(), EQ_CONFIG_ID, buf, sizeof(_error_return));
        }
        break;
    case ONLINE_SUB_OP_WRITE_ADDR_RANGE:
        /* log_info("event_ONLINE_SUB_OP_WRITE_ADDR_RANGE\n"); */

        info.r_write_addr_range.addr = (packet[4] | (packet[5] << 8) | (packet[6] << 16) | (packet[7] << 24));
        /* log_info("writing flash addr:0x%x\n", info.r_write_addr_range.addr); */

        info.r_write_addr_range.size = (packet[8] | (packet[9] << 8) | (packet[10] << 16) | (packet[11] << 24));
        /* log_info("writing flash size:%d\n", info.r_write_addr_range.size); */

        buf_temp = (char *)malloc(info.r_write_addr_range.size);
        memcpy(buf_temp, packet + 12, info.r_write_addr_range.size);
        /* printf_buf(buf_temp, info.r_write_addr_range.size); */
        encode_data_by_user_key(boot_info.chip_id, buf_temp, info.r_write_addr_range.size, info.r_write_addr_range.addr - boot_info.sfc.sfc_base_addr, 0x20);

        write_len = norflash_write(NULL, buf_temp, info.r_write_addr_range.size, info.r_write_addr_range.addr);

        if (write_len != info.r_write_addr_range.size) {
            memcpy(buf, _error_return, sizeof(_error_return));
            log_error("write error!");
        } else {
            memcpy(buf, _ok_return, sizeof(_ok_return));
        }

        if (info.ci_send_packet_new) {
            info.ci_send_packet_new(get_eq_cfg_hdl(), EQ_CONFIG_ID, buf, sizeof(_error_return));
        }
        if (buf_temp) {
            free(buf_temp);
        }
        break;
    default:
        free(buf);
        return 0;
        break;
    }
    free(buf);
    return 1;
}

