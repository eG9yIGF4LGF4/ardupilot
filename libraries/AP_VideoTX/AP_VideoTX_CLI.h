#pragma once 

#include <cstring>
#include <GCS_MAVLink/GCS.h>
#include <AP_Vehicle/AP_Vehicle.h>
#include <RC_Channel/RC_Channel.h>

#define VTX_CLI_COMMANDS_COUNT 8
#define VTX_CLI_PARAM(i, suffix) std::strcat(std::strncat((char*)"VTX_CLI", l64a(i), 1), suffix) 

typedef struct __attribute__((__packed__))
{
    uint8_t rc;
    uint8_t begin;
    uint8_t band;
    uint8_t channel;
    uint8_t power;
    uint8_t end;

    bool enabled(uint16_t pwm)
    {    
        return this->begin >= pwm || this->end <= pwm;
    }

    bool enabled()
    {    
        uint16_t val;

        if(RC_Channels::get_singleton()->get_pwm(this->rc, val)) {
            return enabled(val);
        }
        
        return false;
    }
    
} VTX_CLI_COMMAND_OPTIONS;

class AP_VideoTX_CLI 
{
    private:
        VTX_CLI_COMMAND_OPTIONS* vtxCliOptions;
        VTX_CLI_COMMAND_OPTIONS* vtxCliOptionsDefault;
        bool vtxCliOptionsInitialized;

    public:
        AP_VideoTX_CLI(/* args */);

        bool initVtxCliCommandOptions();
        void set_parameters();
        VTX_CLI_COMMAND_OPTIONS* getVtxCliCommandOptions();
        VTX_CLI_COMMAND_OPTIONS* getVtxCliCommandOptionsAll();
        
        static AP_VideoTX_CLI* instance;
        static void set_singleton(AP_VideoTX_CLI* c)
        {
            AP_VideoTX_CLI::instance = c;
        }

        static AP_VideoTX_CLI* get_singleton();
};

