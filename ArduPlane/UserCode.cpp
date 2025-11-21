#include <AP_VideoTX/AP_VideoTX_CLI.h>
#include "Plane.h"

#ifdef USERHOOK_INIT
void Plane::userhook_init()
{
    
}
#endif

#ifdef USERHOOK_FASTLOOP
void Plane::userhook_FastLoop()
{
    // put your 100Hz code here
}
#endif

#ifdef USERHOOK_50HZLOOP
void Plane::userhook_50Hz()
{
    // put your 50Hz code here
}
#endif

#ifdef USERHOOK_MEDIUMLOOP
void Plane::userhook_MediumLoop()
{
    // put your 10Hz code here
}
#endif

#ifdef USERHOOK_SLOWLOOP
void Plane::userhook_SlowLoop()
{
    // put your 3.3Hz code here
}
#endif

#ifdef USERHOOK_SUPERSLOWLOOP
void Plane::userhook_SuperSlowLoop()
{
    // put your 1Hz code here
}
#endif

#ifdef USERHOOK_AUXSWITCH

void Plane::userhook_auxSwitch1(const RC_Channel::AuxSwitchPos ch_flag) 
{
    #if AP_VTX_CLI_ENABLED

    auto cli = AP_VideoTX_CLI::get_singleton();
    cli->set_parameters();

    #endif
}

void Plane::userhook_auxSwitch2(const RC_Channel::AuxSwitchPos ch_flag)
{
}

void Plane::userhook_auxSwitch3(const RC_Channel::AuxSwitchPos ch_flag)
{
}

#endif
