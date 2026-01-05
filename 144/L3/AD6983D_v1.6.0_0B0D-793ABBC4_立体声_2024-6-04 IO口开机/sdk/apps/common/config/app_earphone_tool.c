#include "config_tool.h"
#include "event.h"
#include "boot.h"
#include "ioctl_cmds.h"
#include "board_config.h"
#include "app_online_cfg.h"
#include "asm/crc16.h"
#include "online_db_deal.h"

#define LOG_TAG_CONST       APP_EARPHONE_TOOL
#define LOG_TAG             "[APP_EARPHONE_TOOL]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

struct earphone_tool_info {
    /*PC往小机发送的DATA*/
    R_QUERY_BASIC_INFO 		r_basic_info;
    R_QUERY_FILE_SIZE		r_file_size;
    R_QUERY_FILE_CONTENT	r_file_content;
    R_PREPARE_WRITE_FILE	r_prepare_write_file;
    R_READ_ADDR_RANGE		r_read_addr_range;
    R_ERASE_ADDR_RANGE      r_erase_addr_range;
    R_WRITE_ADDR_RANGE      r_write_addr_range;
    R_ENTER_UPGRADE_MODE    r_enter_upgrade_mode;

    /*小机返回PC发送的DATA*/
    S_QUERY_BASIC_INFO 		s_basic_info;
    S_QUERY_FILE_SIZE		s_file_size;
    S_PREPARE_WRITE_FILE    s_prepare_write_file;
};

static struct earphone_tool_info info = {
    .s_basic_info.protocolVer = PROTOCOL_VER_AT_OLD,
};

#define TEMP_BUF_SIZE	256

#define EQ_CONFIG_ID        0x0005

extern const char *sdk_version_info_get(void);
extern u8 *sdfile_get_burn_code(u8 *len);

static u8 local_packet[TEMP_BUF_SIZE];
const char error_return[] = "FA";	//表示失败
const char ok_return[] = "OK";		//表示成功
const char er_return[] = "ER";		//表示不能识别的命令
static u32 size_total_write = 0;

extern void doe(u16 k, void *pBuf, u32 lenIn, u32 addr);
extern int norflash_erase(u32 cmd, u32 addr);

#ifdef ALIGN
#undef ALIGN
#endif

#define ALIGN(a, b) \
	({ \
	 int m = (u32)(a) & ((b)-1); \
	 int ret = (u32)(a) + (m?((b)-m):0);	 \
	 ret;\
	 })

static u32 earphone_encode_data_by_user_key(u16 key, u8 *buff, u16 size, u32 dec_addr, u8 dec_len)
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

static u8 parse_seq = 0;
static void ci_send_packet_new(u32 id, u8 *packet, int size)
{
#if APP_ONLINE_DEBUG
    app_online_db_ack(parse_seq, packet, size);
#endif/*APP_ONLINE_DEBUG*/
}

int app_earphone_tool_event_handler(u8 event, u8 *packet, u8 size);
int cfg_app_online_parse(u8 *packet, u8 size, u8 *ext_data, u16 ext_size)
{
    u8 *buf = NULL;
    buf = (u8 *)malloc(256);
    if (buf == NULL) {
        log_error("buf malloc err!");
        return 0;
    }
    u16 _size;
    parse_seq = ext_data[1];
    buf[0] = size + 1;
    memcpy(buf + 1, ext_data, ext_size);
    memcpy(buf + 1 + ext_size, packet, size);
    u32 event = (packet[0] | (packet[1] << 8) | (packet[2] << 16) | (packet[3] << 24));
    _size = size + 3;
    app_earphone_tool_event_handler(event, buf, _size);
    free(buf);
    return 0;
}

/*全封装与发送*/
void all_assemble_package_send_to_pc(u8 id, u8 sq, u8 *buf, u32 len)
{
    u8 *send_buf = NULL;
    send_buf = (u8 *)malloc(TEMP_BUF_SIZE);
    if (send_buf == NULL) {
        log_error("send_buf malloc err!");
        return;
    }

    u16 crc16_data;

    send_buf[0] = 0x5A;
    send_buf[1] = 0xAA;
    send_buf[2] = 0xA5;

    /*L*/
    send_buf[5] = 2 + len;

    /*T*/
    send_buf[6] = id;

    /*SQ*/
    send_buf[7] = sq;

    /*组包完成*/
    memcpy(send_buf + 8, buf, len);

    /*添加CRC16*/
    crc16_data = CRC16(&send_buf[5], len + 3);
    send_buf[3] = crc16_data & 0xff;
    send_buf[4] = (crc16_data >> 8) & 0xff;

    /* printf_buf(send_buf, len + 8); */

#if TCFG_ONLINE_ENABLE
    ci_uart_write(send_buf, len + 8);
#endif

    free(send_buf);
}

/*二次组包与发送*/
void assemble_package_send_to_pc(u8 *buf, u32 len)
{
    u8 *send_buf = NULL;
    send_buf = (u8 *)malloc(TEMP_BUF_SIZE);
    if (send_buf == NULL) {
        log_error("send_buf malloc err!");
        return;
    }
    u16 crc16_data;

    send_buf[0] = 0x5A;
    send_buf[1] = 0xAA;
    send_buf[2] = 0xA5;

    /*添加CRC16*/
    crc16_data = CRC16(buf, len);
    send_buf[3] = crc16_data & 0xff;
    send_buf[4] = (crc16_data >> 8) & 0xff;

    /*组包完成*/
    memcpy(send_buf + 5, buf, len);

    /* printf_buf(send_buf, len + 5); */

#if APP_ONLINE_DEBUG
    //SPP协议
    ci_send_packet_new(EQ_CONFIG_ID, send_buf + 8, len - 3);
#elif TCFG_ONLINE_ENABLE
    //异步串口协议
    ci_uart_write(send_buf, len + 5);
#endif

    free(send_buf);
}

/*6个byte的校验码数组转为字符串*/
void hex2text(u8 *buf, u8 *out)
{
    sprintf(out, "%02x%02x-%02x%02x%02x%02x", buf[5], buf[4], buf[3], buf[2], buf[1], buf[0]);
}

extern void nvram_set_boot_state(u32 state);
extern void hw_mmu_disable(void);
extern void ram_protect_close(void);

AT(.volatile_ram_code)
void earphone_tool_go_mask_usb_updata()
{
    local_irq_disable();
    ram_protect_close();
    hw_mmu_disable();
    nvram_set_boot_state(2);

    JL_CLOCK->PWR_CON |= (1 << 4);
    /* chip_reset(); */
    /* cpu_reset(); */
    while (1);
}

static void timeout_to_cpu_reset(void *priv)
{
    extern void cpu_reset();
    cpu_reset();
}

int app_earphone_tool_event_handler(u8 event, u8 *packet, u8 size)
{
    u8 *buf = NULL;
    u8 *buf_temp = NULL;
    u8 *buf_temp_0 = NULL;
    u32 erase_cmd;
    int write_len;
    u8 crc_temp_len, sdkname_temp_len;
    char proCrc_fw[32] = {0};
    char sdkName_fw[32] = {0};
    const struct tool_interface *p;

    /* printf_buf(packet, size); */

    buf = (u8 *)malloc(TEMP_BUF_SIZE);
    if (buf == NULL) {
        log_error("buf malloc err!");
        return 0;
    }
    buf_temp_0 = (u8 *)malloc(TEMP_BUF_SIZE);
    if (buf_temp_0 == NULL) {
        free(buf);
        log_error("buf_temp_0 malloc err!");
        return 0;
    }

    buf_temp_0 = (u8 *)ALIGN(buf_temp_0, 4);
    memset(buf_temp_0, 0, 256);
    memcpy(buf_temp_0 + 1, packet, size);

    /*数据进行分发*/
    list_for_each_tool_interface(p) {
        if (p->id == packet[1]) {
            p->tool_message_deal(buf_temp_0 + 2, size - 1);
            free(buf_temp_0);
            free(buf);
            return 0;
        }
    }

    memset(buf, 0, TEMP_BUF_SIZE);

    switch (event) {
    case ONLINE_SUB_OP_QUERY_BASIC_INFO:
        /* log_info("event_ONLINE_SUB_OP_QUERY_BASIC_INFO\n"); */

        /*获取校验码*/
        u8 *p = sdfile_get_burn_code(&crc_temp_len);
        memcpy(info.s_basic_info.progCrc, p + 8, 6);
        /* printf_buf(info.s_basic_info.progCrc, 6); */
        hex2text(info.s_basic_info.progCrc, proCrc_fw);
        /* log_info("crc:%s\n", proCrc_fw); */

        /*获取固件版本信息*/
        sdkname_temp_len = strlen(sdk_version_info_get());
        memcpy(info.s_basic_info.sdkName, sdk_version_info_get(), sdkname_temp_len);
        memcpy(sdkName_fw, info.s_basic_info.sdkName, sdkname_temp_len);
        log_info("version:%s\n", sdk_version_info_get());

        struct flash_head flash_head_for_pid_vid;

        for (u8 i = 0; i < 5; i++) {
            norflash_read(NULL, (u8 *)&flash_head_for_pid_vid, 32, 0x1000 * i);
            doe(0xffff, (u8 *)&flash_head_for_pid_vid, 32, 0);
            if (flash_head_for_pid_vid.crc == 0xffff) {
                continue;
            } else {
                log_info("flash head addr = 0x%x\n", 0x1000 * i);
                break;
            }
        }

        struct flash_head _head;
        struct flash_head *temp_p = &_head;
        memcpy(temp_p, &flash_head_for_pid_vid, 32);

        /*获取PID*/
        memset(info.s_basic_info.pid, 0, sizeof(info.s_basic_info.pid));
        memcpy(info.s_basic_info.pid, temp_p->pid, sizeof(info.s_basic_info.pid));
        for (u8 i = 0; i < sizeof(info.s_basic_info.pid); i++) {
            if (~info.s_basic_info.pid[i] == 0x00) {
                info.s_basic_info.pid[i] = 0x00;
            }
        }
        /* printf_buf(info.s_basic_info.pid, 16); */

        /*获取VID*/
        memset(info.s_basic_info.vid, 0, sizeof(info.s_basic_info.vid));
        memcpy(info.s_basic_info.vid, temp_p->vid, 4);
        /* printf_buf(info.s_basic_info.vid, 16); */

        /*第一次组包*/
        buf[0] = 1 + 1 + sizeof(info.s_basic_info.protocolVer) + sizeof(proCrc_fw) + sizeof(sdkName_fw) + 32;
        buf[1] = REPLY_STYLE;
        buf[2] = packet[2];
        buf[3] = info.s_basic_info.protocolVer & 0xff;
        buf[4] = (info.s_basic_info.protocolVer >> 8) & 0xff;
        memcpy(buf + 5, proCrc_fw, sizeof(proCrc_fw));
        memcpy(buf + 5 + sizeof(proCrc_fw), sdkName_fw, sizeof(sdkName_fw));
        memcpy(buf + 5 + sizeof(proCrc_fw) + sizeof(sdkName_fw), info.s_basic_info.pid, 16);
        memcpy(buf + 5 + sizeof(proCrc_fw) + sizeof(sdkName_fw) + 16, info.s_basic_info.vid, 16);

        /* printf_buf(buf, buf[0] + 1); */

        /*二次组包添加报头与CRC16并发送*/
        assemble_package_send_to_pc(buf, buf[0] + 1);
        break;
    case ONLINE_SUB_OP_QUERY_FILE_SIZE:
        /* log_info("event_ONLINE_SUB_OP_QUERY_FILE_SIZE\n"); */

        /*读取文件ID*/
        info.r_file_size.file_id = (packet[7] | (packet[8] << 8) | \
                                    (packet[9] << 16) | (packet[10] << 24));

        if (info.r_file_size.file_id <= CFG_EQ_FILEID) {
            /*根据名字获取文件句柄*/
            FILE *cfg_fp = NULL;

            if ((info.r_file_size.file_id == CFG_TOOL_FILEID)) {
                cfg_fp = fopen(CFG_TOOL_FILE, "r");
                log_info("open cfg_tool.bin\n");
            } else if ((info.r_file_size.file_id == CFG_OLD_EQ_FILEID)) {
                cfg_fp = fopen(CFG_OLD_EQ_FILE, "r");
                log_info("open old eq_cfg_hw.bin\n");
            } else if ((info.r_file_size.file_id == CFG_OLD_EFFECT_FILEID)) {
                cfg_fp = fopen(CFG_OLD_EFFECT_FILE, "r");
                log_info("open effects_cfg.bin\n");
            } else if ((info.r_file_size.file_id == CFG_EQ_FILEID)) {
                cfg_fp = fopen(CFG_EQ_FILE, "r");
                log_info("open eq_cfg_hw.bin\n");
            }

            if (cfg_fp == NULL) {
                log_error("file open error!\n");
                goto _exit_;
            }

            /*根据文件句柄获取文件属性*/
            struct vfs_attr attr;
            fget_attrs(cfg_fp, &attr);

            log_info("file addr:%x,file size:%d\n", attr.sclust, attr.fsize);
            info.s_file_size.file_size = attr.fsize;

            /*第一次组包*/
            buf[0] = 1 + 1 + sizeof(info.s_file_size.file_size);//长度
            buf[1] = REPLY_STYLE;//包的类型
            buf[2] = packet[2];//回复序列号

            /*小端格式*/
            buf[6] = (info.s_file_size.file_size >> 24) & 0xff;
            buf[5] = (info.s_file_size.file_size >> 16) & 0xff;
            buf[4] = (info.s_file_size.file_size >> 8) & 0xff;
            buf[3] = info.s_file_size.file_size & 0xff;

            /*二次组包添加报头与CRC16并发送*/
            assemble_package_send_to_pc(buf, buf[0] + 1);

            fclose(cfg_fp);
        }
        break;
    case ONLINE_SUB_OP_QUERY_FILE_CONTENT:
        /* log_info("event_ONLINE_SUB_OP_QUERY_FILE_CONTENT\n"); */

        /*读取文件的ID*/
        info.r_file_content.file_id = (packet[7] | (packet[8] << 8) | \
                                       (packet[9] << 16) | (packet[10] << 24));
        /*读取文件的偏移*/
        info.r_file_content.offset = (packet[11] | (packet[12] << 8) | \
                                      (packet[13] << 16) | (packet[14] << 24));
        /*读取文件的大小*/
        info.r_file_content.size = (packet[15] | (packet[16] << 8) | \
                                    (packet[17] << 16) | (packet[18] << 24));

        if (info.r_file_content.file_id <= CFG_EQ_FILEID) {
            /*根据名字获取文件句柄*/
            FILE *cfg_fp = NULL;

            if ((info.r_file_content.file_id == CFG_TOOL_FILEID)) {
                cfg_fp = fopen(CFG_TOOL_FILE, "r");
                log_info("open cfg_tool.bin\n");
            } else if ((info.r_file_content.file_id == CFG_OLD_EQ_FILEID)) {
                cfg_fp = fopen(CFG_OLD_EQ_FILE, "r");
                log_info("open old eq_cfg_hw.bin\n");
            } else if ((info.r_file_content.file_id == CFG_OLD_EFFECT_FILEID)) {
                cfg_fp = fopen(CFG_OLD_EFFECT_FILE, "r");
                log_info("open effects_cfg.bin\n");
            } else if ((info.r_file_content.file_id == CFG_EQ_FILEID)) {
                cfg_fp = fopen(CFG_EQ_FILE, "r");
                log_info("open eq_cfg_hw.bin\n");
            }

            if (cfg_fp == NULL) {
                log_error("file open error!\n");
                goto _exit_;
            }

            /*根据文件句柄获取文件属性*/
            struct vfs_attr attr;
            fget_attrs(cfg_fp, &attr);

            /* log_info("file addr:%x,file size:%d\n", attr.sclust, attr.fsize); */
            if (info.r_file_content.size > attr.fsize) {
                fclose(cfg_fp);
                log_error("reading size more than actual size!\n");
                break;
            }

            /*逻辑地址转换成flash物理地址*/
            u32 flash_addr = sdfile_cpu_addr2flash_addr(attr.sclust);
            /* log_info("flash_addr:0x%x", flash_addr); */

            /*读取文件内容*/
            buf_temp = (char *)malloc(info.r_file_content.size);
            norflash_read(NULL, (void *)buf_temp, info.r_file_content.size, flash_addr + info.r_file_content.offset);
            /* printf_buf(buf_temp, info.r_file_content.size); */

            /*第一次组包*/
            buf[0] = 1 + 1 + info.r_file_content.size;
            buf[1] = REPLY_STYLE;
            buf[2] = packet[2];
            memcpy(buf + 3, buf_temp, info.r_file_content.size);

            /*二次组包添加报头与CRC16并发送*/
            assemble_package_send_to_pc(buf, buf[0] + 1);

            if (buf_temp) {
                free(buf_temp);
            }

            fclose(cfg_fp);
        }
        break;
    case ONLINE_SUB_OP_PREPARE_WRITE_FILE:
        /* log_info("event_ONLINE_SUB_OP_PREPARE_WRITE_FILE\n"); */

        info.r_prepare_write_file.file_id = (packet[7] | (packet[8] << 8) | \
                                             (packet[9] << 16) | (packet[10] << 24));

        info.r_prepare_write_file.size = (packet[11] | (packet[12] << 8) | \
                                          (packet[13] << 16) | (packet[14] << 24));

        if (info.r_prepare_write_file.file_id <= CFG_EQ_FILEID) {
            /*根据名字获取文件句柄*/
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
                log_error("file open error!\n");
                goto _exit_;
            }
            /*根据文件句柄获取文件属性*/
            struct vfs_attr attr;
            fget_attrs(cfg_fp, &attr);

            /* log_info("file addr:%x,file size:%d\n", attr.sclust, attr.fsize); */
            if (info.r_prepare_write_file.size > attr.fsize) {
                //fclose(cfg_fp);
                //log_error("preparing to write size more than actual size!\n");
                //break;
            }

            /*获取文件实际大小*/
            info.s_prepare_write_file.file_size = attr.fsize;
            /* log_info("file_size = %d\n", info.s_prepare_write_file.file_size); */

            /*逻辑地址转换成flash物理地址*/
            info.s_prepare_write_file.file_addr = sdfile_cpu_addr2flash_addr(attr.sclust);
            /* log_info("file_flash_addr:0x%x\n", info.s_prepare_write_file.file_addr); */

            /*获取flash擦除单元*/
            info.s_prepare_write_file.earse_unit = boot_info.vm.align * 256;
            /* log_info("earse_unit = %d\n", info.s_prepare_write_file.earse_unit); */

            /*第一次组包*/
            buf[0] = 1 + 1 + sizeof(info.s_prepare_write_file.file_size) * 3;
            buf[1] = REPLY_STYLE;
            buf[2] = packet[2];

            buf[6] = (info.s_prepare_write_file.file_addr >> 24) & 0xff;
            buf[5] = (info.s_prepare_write_file.file_addr >> 16) & 0xff;
            buf[4] = (info.s_prepare_write_file.file_addr >> 8) & 0xff;
            buf[3] = info.s_prepare_write_file.file_addr & 0xff;

            buf[10] = (info.s_prepare_write_file.file_size >> 24) & 0xff;
            buf[9] 	= (info.s_prepare_write_file.file_size >> 16) & 0xff;
            buf[8] 	= (info.s_prepare_write_file.file_size >> 8) & 0xff;
            buf[7] 	= info.s_prepare_write_file.file_size & 0xff;

            buf[14] = (info.s_prepare_write_file.earse_unit >> 24) & 0xff;
            buf[13] = (info.s_prepare_write_file.earse_unit >> 16) & 0xff;
            buf[12] = (info.s_prepare_write_file.earse_unit >> 8) & 0xff;
            buf[11] = info.s_prepare_write_file.earse_unit & 0xff;

            /*二次组包添加报头与CRC16并发送*/
            assemble_package_send_to_pc(buf, buf[0] + 1);

            fclose(cfg_fp);
        }
        break;
    case ONLINE_SUB_OP_READ_ADDR_RANGE:
        /* log_info("event_ONLINE_SUB_OP_READ_ADDR_RANGE\n"); */

        /*要读取的flash物理地址*/
        info.r_read_addr_range.addr = (packet[7] | (packet[8] << 8) | \
                                       (packet[9] << 16) | (packet[10] << 24));
        /* log_info("reading flash addr:0x%x\n", info.r_read_addr_range.addr); */

        /*要读取的大小*/
        info.r_read_addr_range.size = (packet[11] | (packet[12] << 8) | \
                                       (packet[13] << 16) | (packet[14] << 24));
        /* log_info("reading size = %d\n", info.r_read_addr_range.size); */

        /*读取文件内容*/
        buf_temp = (char *)malloc(info.r_read_addr_range.size);
        norflash_read(NULL, (void *)buf_temp, info.r_read_addr_range.size, info.r_read_addr_range.addr);
        /* printf_buf(buf_temp, info.r_read_addr_range.size); */

        /*第一次组包*/
        buf[0] = 1 + 1 + info.r_read_addr_range.size;
        buf[1] = REPLY_STYLE;
        buf[2] = packet[2];
        memcpy(buf + 3, buf_temp, info.r_read_addr_range.size);

        /*二次组包添加报头与CRC16并发送*/
        assemble_package_send_to_pc(buf, buf[0] + 1);

        if (buf_temp) {
            free(buf_temp);
        }
        break;
    case ONLINE_SUB_OP_ERASE_ADDR_RANGE:
        /* log_info("event_ONLINE_SUB_OP_ERASE_ADDR_RANGE\n"); */

        /*要擦除的flash物理起始地址*/
        info.r_erase_addr_range.addr = (packet[7] | (packet[8] << 8) | \
                                        (packet[9] << 16) | (packet[10] << 24));
        /* log_info("erasing flash start addr:0x%x\n", info.r_erase_addr_range.addr); */

        /*要擦除的大小，会保证按earse_unit对齐，即总是erase_unit的倍数*/
        info.r_erase_addr_range.size = (packet[11] | (packet[12] << 8) | \
                                        (packet[13] << 16) | (packet[14] << 24));
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
            memcpy(buf + 3, error_return, sizeof(error_return));
            log_error("erase error!");
            break;
        }

        for (u8 i = 0; i < (info.r_erase_addr_range.size / info.s_prepare_write_file.earse_unit); i ++) {
            extern int norflash_erase(u32 cmd, u32 addr);
            u8 ret = norflash_erase(erase_cmd, info.r_erase_addr_range.addr + (i * info.s_prepare_write_file.earse_unit));
            if (ret) {
                memcpy(buf + 3, error_return, sizeof(error_return));
                log_error("erase error!");
            } else {
                memcpy(buf + 3, ok_return, sizeof(ok_return));
                log_info("erase success");
            }
        }

        /*第一次组包*/
        buf[0] = 1 + 1 + sizeof(error_return);
        buf[1] = REPLY_STYLE;
        buf[2] = packet[2];

        /*二次组包添加报头与CRC16并发送*/
        assemble_package_send_to_pc(buf, buf[0] + 1);
        break;
    case ONLINE_SUB_OP_WRITE_ADDR_RANGE:
        /* log_info("event_ONLINE_SUB_OP_WRITE_ADDR_RANGE\n"); */

        /*要写入的flash物理起始地址*/
        info.r_write_addr_range.addr = (packet[7] | (packet[8] << 8) | \
                                        (packet[9] << 16) | (packet[10] << 24));
        /*要写入的大小*/
        info.r_write_addr_range.size = (packet[11] | (packet[12] << 8) | \
                                        (packet[13] << 16) | (packet[14] << 24));

        /*读取要写入文件的内容*/
        buf_temp = (char *)malloc(info.r_write_addr_range.size);
        memcpy(buf_temp, packet + 15, info.r_write_addr_range.size);
        /* printf_buf(buf_temp, info.r_write_addr_range.size); */

        earphone_encode_data_by_user_key(boot_info.chip_id, buf_temp, info.r_write_addr_range.size, info.r_write_addr_range.addr - boot_info.sfc.sfc_base_addr, 0x20);

        write_len = norflash_write(NULL, buf_temp, info.r_write_addr_range.size, info.r_write_addr_range.addr);

        if (write_len != info.r_write_addr_range.size) {
            memcpy(buf + 3, error_return, sizeof(error_return));
            log_error("write error!");
        } else {
            memcpy(buf + 3, ok_return, sizeof(ok_return));
        }

        buf[0] = 1 + 1 + sizeof(error_return);
        buf[1] = REPLY_STYLE;
        buf[2] = packet[2];

        /*二次组包添加报头与CRC16并发送*/
        assemble_package_send_to_pc(buf, buf[0] + 1);

        if (buf_temp) {
            free(buf_temp);
        }

        if (info.r_prepare_write_file.file_id == CFG_TOOL_FILEID) {
            size_total_write += info.r_write_addr_range.size;

            /* log_info("size_total_write = %d\n", size_total_write); */
            /* log_info("erasing size = %d\n", info.r_erase_addr_range.size); */

            if (size_total_write >= info.r_erase_addr_range.size) {
                size_total_write = 0;
                log_info("cpu_reset\n");
                delay_2ms(10);
                sys_timeout_add(NULL, timeout_to_cpu_reset, 1000);
            }
        }
        break;
    case ONLINE_SUB_OP_ENTER_UPGRADE_MODE:
        /* log_info("event_ONLINE_SUB_OP_ENTER_UPGRADE_MODE\n"); */
        earphone_tool_go_mask_usb_updata();
        break;
    default:
        log_error("unrecognized command ! ! !\n");
        /*return ER to pc*/
_exit_:
        memcpy(buf + 3, er_return, sizeof(er_return));
        buf[0] = 1 + 1 + sizeof(er_return);
        buf[1] = REPLY_STYLE;
        buf[2] = packet[2];
        assemble_package_send_to_pc(buf, buf[0] + 1);
        break;
    }

    free(buf_temp_0);
    free(buf);

    return 0;
}

void app_earphone_eq_tool_message_deal(u8 *buf, u32 len)
{
    u8 cmd = buf[8];
    switch (cmd) {
    case ONLINE_SUB_OP_QUERY_BASIC_INFO:
    case ONLINE_SUB_OP_QUERY_FILE_SIZE:
    case ONLINE_SUB_OP_QUERY_FILE_CONTENT:
    case ONLINE_SUB_OP_PREPARE_WRITE_FILE:
    case ONLINE_SUB_OP_READ_ADDR_RANGE:
    case ONLINE_SUB_OP_ERASE_ADDR_RANGE:
    case ONLINE_SUB_OP_WRITE_ADDR_RANGE:
    case ONLINE_SUB_OP_ENTER_UPGRADE_MODE:
        app_earphone_tool_event_handler(cmd, &buf[5], buf[5] + 1);
        break;
    default:
        app_earphone_tool_event_handler(DEFAULT_ACTION, &buf[5], buf[5] + 1);
        break;
    }
}

void online_cfg_tool_data_deal(void *buf, u32 len)
{
    u8 *data_buf = buf;
    u16 crc16_data;

    /* printf_buf(buf, len); */

    if (len < 8) {
        log_error("Data length is too short, receive an invalid message!\n");
        return;
    }

    if ((data_buf[0] != 0x5a) || (data_buf[1] != 0xaa) || (data_buf[2] != 0xa5)) {
        log_error("Header check error, receive an invalid message!\n");
        return;
    }

    crc16_data = (data_buf[4] << 8) | data_buf[3];
    if (crc16_data != CRC16(data_buf + 5, len - 5)) {
        log_error("CRC16 check error, receive an invalid message!\n");
        return;
    }

    app_earphone_eq_tool_message_deal(buf, len);
}

int spp_cfg_init(void)
{
#if APP_ONLINE_DEBUG
    app_online_db_register_handle(0x12, cfg_app_online_parse);
#endif
    return 0;
}

