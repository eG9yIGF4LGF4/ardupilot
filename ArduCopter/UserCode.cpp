#include <AP_VideoTX/AP_VideoTX_CLI.h>
#include "Copter.h"

#ifdef USERHOOK_INIT
void Copter::userhook_init()
{
    
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

void Copter::userhook_auxSwitch1(const RC_Channel::AuxSwitchPos ch_flag) 
{
    #if AP_VTX_CLI_ENABLED

    auto cli = AP_VideoTX_CLI::get_singleton();
    cli->set_parameters();

    #endif
}

void Copter::userhook_auxSwitch2(const RC_Channel::AuxSwitchPos ch_flag)
{

}

void Copter::userhook_auxSwitch3(const RC_Channel::AuxSwitchPos ch_flag)
{

}
