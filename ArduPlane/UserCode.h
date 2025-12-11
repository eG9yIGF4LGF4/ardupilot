#include <AP_VideoTX/AP_VideoTX_CLI.h>
#include "Plane.h"

#define AP_VTX_CLI_ENABLED 1 
#define USERHOOK_INIT userhook_init();                      // for code to be run once at startup
#define USERHOOK_FASTLOOP userhook_FastLoop();            // for code to be run at 100hz
#define USERHOOK_50HZLOOP userhook_50Hz();                  // for code to be run at 50hz
#define USERHOOK_MEDIUMLOOP userhook_MediumLoop();        // for code to be run at 10hz
#define USERHOOK_SLOWLOOP userhook_SlowLoop();            // for code to be run at 3.3hz
#define USERHOOK_SUPERSLOWLOOP userhook_SuperSlowLoop();  // for code to be run at 1hz
#define USERHOOK_AUXSWITCH 1                        // for code to handle user aux switches
#define USER_PARAMS_ENABLED 1           