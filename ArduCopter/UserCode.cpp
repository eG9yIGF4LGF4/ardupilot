#include <GCS_MAVLink/GCS.h>
#include "Copter.h"

#ifdef USERHOOK_INIT
void Copter::userhook_init()
{
    // put your initialisation code here
    // this will be called once at start-up
}
#endif

#ifdef USERHOOK_FASTLOOP
void Copter::userhook_FastLoop()
{
    // put your 100Hz code here
}
#endif

#ifdef USERHOOK_50HZLOOP
void Copter::userhook_50Hz()
{
    // put your 50Hz code here
}
#endif

#ifdef USERHOOK_MEDIUMLOOP
void Copter::userhook_MediumLoop()
{
    // put your 10Hz code here
}
#endif

#ifdef USERHOOK_SLOWLOOP
void Copter::userhook_SlowLoop()
{
    // put your 3.3Hz code here
}
#endif

#ifdef USERHOOK_SUPERSLOWLOOP
void Copter::userhook_SuperSlowLoop()
{
    // put your 1Hz code here
}
#endif

#ifdef USERHOOK_AUXSWITCH

void Copter::userhook_auxSwitch1(const RC_Channel::AuxSwitchPos ch_flag)
{
    // put your aux switch #1 handler here (CHx_OPT = 47)
    GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Set VTX Channel and Frequency #1");

    auto power = 3; 
    auto band = vtx.BAND_A;
    auto ch = 6;

    vtx.set_band(band);
    vtx.set_channel(ch);
    vtx.change_power(power);
}

void Copter::userhook_auxSwitch2(const RC_Channel::AuxSwitchPos ch_flag)
{
    GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Set VTX Channel and Frequency #2 begin");
    
    float val;
    uint16_t chn = AP::param()->get("VTX_CONTROL_BAND", val) ? (uint16_t)val : 0;
    uint16_t pwm = 0;

    // if(chn == 0) {
    //     for(int i = 1; i <= 16; i++)
    //     {
    //         float val;
    //         char* name = (char*)malloc(64);
    //         asprintf(&name, "RC%d_OPTION", i);

    //         if(AP::param()->get(name, val))
    //         {
    //             //GCS_SEND_TEXT(MAV_SEVERITY_INFO, "  Read param %s (%d)", name, (int)val);
    //             if(option == (int)val) 
    //             {
    //                 chn = (uint16_t)val;
    //                 break;
    //             }
    //         }
    //     }
    // }

    if(chn == 0) return;

    int band = 0;
    auto rc_pwm = rc().get_pwm(chn, pwm) ? pwm : 900;

    if(rc_pwm <= 1050) { band = 0; } else 
    if(rc_pwm <= 1200) { band = 1; } else
    if(rc_pwm <= 1300) { band = 2; } else 
    if(rc_pwm <= 1450) { band = 3; } else
    if(rc_pwm <= 1600) { band = 4; } else
    if(rc_pwm <= 1750) { band = 5; } else
    if(rc_pwm <= 1900) { band = 6; } else
    if(rc_pwm <= 2100) { band = 7; };

    vtx.set_band(band);
    vtx.set_configured_band(band);
    vtx.set_configuration_finished(true);
    vtx.announce_vtx_settings();

    GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Set VTX Channel and Frequency #2 end");
}

void Copter::userhook_auxSwitch3(const RC_Channel::AuxSwitchPos ch_flag)
{
    // put your aux switch #3 handler here (CHx_OPT = 49)
    GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Set VTX Channel and Frequency #3 begin");
    
    float val;    
    uint16_t chn = AP::param()->get("VTX_CONTROL_CHAN", val) ? (uint16_t)val : 0;
    uint16_t pwm = 0;

    // if(chn == 0)
    // {
    //     for(int i = 1; i <= 16; i++)
    //     {
    //         float val;
    //         char* name = (char*)malloc(64);
    //         asprintf(&name, "RC%d_OPTION", i);

    //         if(AP::param()->get(name, val))
    //         {
    //             //GCS_SEND_TEXT(MAV_SEVERITY_INFO, "  Read param %s (%d)", name, (int)val);
    //             if(option == (int)val) 
    //             {
    //                 chn = (uint16_t)val;
    //                 break;
    //             }
    //         }
    //     }
    // }

    if(chn == 0) return;

    auto rc_pwm = rc().get_pwm(chn, pwm) ? pwm : 900;
    auto ch = 0;

    if(rc_pwm <= 1050) { ch = 0; } else 
    if(rc_pwm <= 1200) { ch = 1; } else
    if(rc_pwm <= 1300) { ch = 2; } else 
    if(rc_pwm <= 1450) { ch = 3; } else
    if(rc_pwm <= 1600) { ch = 4; } else
    if(rc_pwm <= 1750) { ch = 5; } else
    if(rc_pwm <= 1900) { ch = 6; } else
    if(rc_pwm <= 2100) { ch = 7; };

    vtx.set_channel(ch);
    vtx.set_configured_channel(ch);
    vtx.set_configuration_finished(true);
    vtx.announce_vtx_settings();

    GCS_SEND_TEXT(MAV_SEVERITY_INFO, "Set VTX Channel and Frequency #3 end");
}
#endif
