#include "audio_vbass_demo.h"
#include "app_config.h"
#include "audio_eff_default_parm.h"

#if AUDIO_VBASS_CONFIG
VirtualBass_TOOL_SET vbass_parm[mode_add];

extern u32 __app_movable_slot2_start[];
extern u32 __app_movable_slot3_start[];
extern u8 __movable_region2_start[];
extern u8 __movable_region3_start[];
static u8 *audio_vbass_code_run_addr = NULL;
static u32 *start_of_region = NULL; // 记录当前代码所在区域的起始地址

void audio_vbass_code_movable_load()
{
#if AUDIO_EFFECTS_VBASS_AT_RAM
    int code_size = __movable_region3_start - __movable_region2_start;
    printf("code_size:%d\n", code_size);
    mem_stats();
    if (code_size && audio_vbass_code_run_addr == NULL) {
        audio_vbass_code_run_addr = phy_malloc(code_size);
    }
    if (audio_vbass_code_run_addr) {
        printf("audio_vbass_code_run_addr:0x%x", audio_vbass_code_run_addr);
        code_movable_load(__movable_region2_start, code_size, audio_vbass_code_run_addr, __app_movable_slot2_start, __app_movable_slot3_start, &start_of_region);
        mem_stats();
    }
#endif
}

void audio_vbass_code_movable_unload()
{
#if AUDIO_EFFECTS_VBASS_AT_RAM
    if (audio_vbass_code_run_addr) {
        mem_stats();
        code_movable_unload(__movable_region2_start, __app_movable_slot2_start, __app_movable_slot3_start, &start_of_region);
        phy_free(audio_vbass_code_run_addr);
        audio_vbass_code_run_addr = NULL;
        mem_stats();
    }
#endif
}

vbass_hdl *audio_vbass_open_demo(u32 vbass_name, u32 sample_rate, u8 ch_num)
{
    audio_vbass_code_movable_load();
    VirtualBassParam parm = {0};
    u8 tar = 0;
#if defined(LINEIN_MODE_SOLE_EQ_EN) && LINEIN_MODE_SOLE_EQ_EN
    if (vbass_name == AEID_AUX_VBASS) {
        tar = 1;
    }
#endif

    u8 bypass  = vbass_parm[tar].is_bypass;
    parm.ratio = vbass_parm[tar].parm.ratio;
    parm.boost = vbass_parm[tar].parm.boost;
    parm.fc    = vbass_parm[tar].parm.fc;
    parm.channel = ch_num;
    parm.SampleRate = sample_rate;
    //printf("vbass ratio %d, boost %d, fc %d, channel %d, SampleRate %d\n", parm.ratio, parm.boost, parm.fc,parm.channel, parm.SampleRate);
    vbass_hdl *vbass = audio_vbass_open(vbass_name, &parm);
    audio_vbass_bypass(vbass_name, bypass);
    clock_add(DEC_VBASS_CLK);
    return vbass;
}


void audio_vbass_close_demo(vbass_hdl *vbass)
{
    if (vbass) {
        audio_vbass_close(vbass);
        vbass = NULL;
    }
    clock_remove(DEC_VBASS_CLK);
    audio_vbass_code_movable_unload();
}



void audio_vbass_update_demo(u32 vbass_name, VirtualBassUdateParam *parm, u32 bypass)
{
    audio_vbass_parm_update(vbass_name, parm);
    audio_vbass_bypass(vbass_name, bypass);
}



#endif
