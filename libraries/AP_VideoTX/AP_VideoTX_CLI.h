#pragma once 

#include <cstring>
#include <GCS_MAVLink/GCS.h>
#include <AP_Vehicle/AP_Vehicle.h>
#include <RC_Channel/RC_Channel.h>

#define VTX_CLI_NUM_COMMANDS 8

class VTX_CLI_Command {
public:
    AP_Int8  rc_channel;
    AP_Int16 pwm_begin;
    AP_Int16 pwm_end;
    AP_Int8  band;
    AP_Int8  channel;
    AP_Int8  power;

    static const struct AP_Param::GroupInfo var_info[];

    bool in_range(uint16_t pwm) const {
        return (pwm >= pwm_begin) && (pwm < pwm_end);
    }

    bool is_active() const {
        if (rc_channel < 0) {
            return false;
        }
        
        RC_Channels* rc = RC_Channels::get_singleton();
        if (rc == nullptr) {
            return false;
        }
        
        RC_Channel* ch = rc->channel((uint8_t)rc_channel.get());
        if (ch == nullptr) {
            return false;
        }
        
        return in_range(ch->get_radio_in());
    }

    bool is_configured() const {
        return rc_channel >= 0 && pwm_begin > 0 && pwm_end > 0;
    }
};

class AP_VideoTX_CLI 
{
    public:
        AP_VideoTX_CLI(/* args */);

        CLASS_NO_COPY(AP_VideoTX_CLI);

        // bool initVtxCliCommandOptions();
        // void set_parameters();
        // VTX_CLI_COMMAND_OPTIONS* getVtxCliCommandOptions();
        // VTX_CLI_COMMAND_OPTIONS* getVtxCliCommandOptionsAll();
        
        static const struct AP_Param::GroupInfo var_info[];

        static AP_VideoTX_CLI* _singleton;
        static AP_VideoTX_CLI* get_singleton()
        {
            return _singleton;
        }

        VTX_CLI_Command commands[VTX_CLI_NUM_COMMANDS];

        void handle_commands();
    private:
        // VTX_CLI_COMMAND_OPTIONS* vtxCliOptions;
        // VTX_CLI_COMMAND_OPTIONS* vtxCliOptionsDefault;
        bool vtxCliOptionsInitialized;
};



// #define VTX_CLI_COMMANDS_COUNT 8
// #define VTX_CLI_ROW(i) "VTX_CLI"#i
// #define VTX_CLI_PARAM(i, suffix) VTX_CLI_ROW(i)#suffix
// typedef struct __attribute__((__packed__))
// {
//     uint8_t rc;
//     uint8_t begin;
//     uint8_t band;
//     uint8_t channel;
//     uint8_t power;
//     uint8_t end;

//     bool enabled(uint16_t pwm)
//     {    
//         return this->begin >= pwm || this->end <= pwm;
//     }

//     bool enabled()
//     {    
//         uint16_t val;

//         if(RC_Channels::get_singleton()->get_pwm(this->rc, val)) {
//             return enabled(val);
//         }
        
//         return false;
//     }
    
// } VTX_CLI_COMMAND_OPTIONS;
