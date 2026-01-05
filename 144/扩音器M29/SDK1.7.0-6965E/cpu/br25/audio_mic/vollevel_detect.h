#include "system/includes.h"
#include "app_config.h"

typedef  struct _LOUDNESS_M_STRUCT_ {
    int mutecnt;
    int rms;
    int counti;
    int maxval;
    int countperiod;
    int inv_counterpreiod;
    int errprintfcount0;
    short print_cnt;
    short print_dest;
    int dclevel;
    int rms_print;
    int maxval_print;
    u8 index;
} LOUDNESS_M_STRUCT;



void  loudness_meter_init(LOUDNESS_M_STRUCT *loud_obj, int sr, int print_dest, u8 index);
void  loudness_meter_short(LOUDNESS_M_STRUCT *loud_obj, short *data, int len);


#if 0
//sample
LOUDNESS_M_STRUCT loudness_adc;
loudness_meter_init(&loudness_adc, sr, 50);

while (1)
{
    loudness_meter_short(&loudness_adc, datain, points);
}

#endif

