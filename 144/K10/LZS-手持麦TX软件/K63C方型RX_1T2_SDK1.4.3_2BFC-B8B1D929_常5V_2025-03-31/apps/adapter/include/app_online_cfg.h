#ifndef ONLINE_CONFIG_H
#define ONLINE_CONFIG_H


#define CI_UART         0
#define CI_TWS          1

typedef struct _eq_online_gain {
    u8 mic_gain_boost;
    u8 mic_gain;
    u8 dac_gain;
} eq_online_gain;
extern eq_online_gain var_gain;
void ci_data_rx_handler(u8 type);
u32 eq_cfg_sync(u8 priority);
#endif

