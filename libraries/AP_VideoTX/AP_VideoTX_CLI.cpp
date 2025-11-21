#include "AP_VideoTX_CLI.h"

AP_VideoTX_CLI* AP_VideoTX_CLI::instance;

AP_VideoTX_CLI::AP_VideoTX_CLI(/* args */)
{
    this->vtxCliOptionsInitialized = instance != nullptr;

    if(!this->vtxCliOptionsInitialized) {
        this->vtxCliOptionsInitialized = false;

        this->vtxCliOptionsDefault = new VTX_CLI_COMMAND_OPTIONS();

        this->vtxCliOptionsDefault->band = 0;
        this->vtxCliOptionsDefault->begin = 0;
        this->vtxCliOptionsDefault->end = 0;
        this->vtxCliOptionsDefault->power = 0;
        this->vtxCliOptionsDefault->channel = 0;
        this->vtxCliOptionsDefault->rc = 0;
 
        this->vtxCliOptions = (VTX_CLI_COMMAND_OPTIONS*)malloc(sizeof(VTX_CLI_COMMAND_OPTIONS)*VTX_CLI_COMMANDS_COUNT);
    
        AP_VideoTX_CLI::set_singleton(this);
    }
}

VTX_CLI_COMMAND_OPTIONS* AP_VideoTX_CLI::getVtxCliCommandOptionsAll()
{
    return AP_VideoTX_CLI::vtxCliOptions;
}


VTX_CLI_COMMAND_OPTIONS* AP_VideoTX_CLI::getVtxCliCommandOptions()
{
    //GCS_SEND_TEXT(((MAV_SEVERITY_INFO, "AP_VideoTX_CLI::getVtxCliCommandOptions() begin");

    AP_VideoTX_CLI::initVtxCliCommandOptions();

    uint16_t pwm = 0;

    for(int i = 0; i < VTX_CLI_COMMANDS_COUNT; i++) {
        auto o = vtxCliOptions[i];
        
        if(RC_Channels::get_singleton()->get_pwm(o.rc, pwm)) {    
            if(o.enabled(pwm)) {
                return &AP_VideoTX_CLI::vtxCliOptions[i];
            }
        }
    }

    //GCS_SEND_TEXT(((MAV_SEVERITY_INFO, "AP_VideoTX_CLI::getVtxCliCommandOptions() end");

    return AP_VideoTX_CLI::vtxCliOptionsDefault;
} 

bool AP_VideoTX_CLI::initVtxCliCommandOptions()
{
    if(!vtxCliOptionsInitialized) {
        //GCS_SEND_TEXT(((MAV_SEVERITY_INFO, "AP_VideoTX_CLI initVtxCliCommandOptions() begin");

        float val;

        for(int i = 0; i < 8; i++) {
            auto o = new VTX_CLI_COMMAND_OPTIONS();

            o->band = AP::param()->get(VTX_CLI_PARAM(i, "_BAND"), val) ? val : 0;
            o->begin = AP::param()->get(VTX_CLI_PARAM(i, "_BEGIN"), val) ? val : 0;
            o->channel = AP::param()->get(VTX_CLI_PARAM(i, "_CHANNEL"), val) ? val : 0;
            o->power = AP::param()->get(VTX_CLI_PARAM(i, "_POWER"), val) ? val : 0;
            o->end = AP::param()->get(VTX_CLI_PARAM(i, "_END"), val) ? val : 0;
            o->rc = AP::param()->get(VTX_CLI_PARAM(i, "_RC"), val) ? val : 0;

            memcpy((void*)(vtxCliOptions + i*sizeof(VTX_CLI_COMMAND_OPTIONS)), (void*)o, sizeof(VTX_CLI_COMMAND_OPTIONS));
        }

        vtxCliOptionsInitialized = true;

        //GCS_SEND_TEXT(((MAV_SEVERITY_INFO, "AP_VideoTX_CLI::initVtxCliCommandOptions() end");

    }

    return vtxCliOptionsInitialized;
}

AP_VideoTX_CLI* AP_VideoTX_CLI::get_singleton()
{
    return (AP_VideoTX_CLI*)instance;
}

void AP_VideoTX_CLI::set_parameters()
{
    //GCS_SEND_TEXT(((MAV_SEVERITY_INFO, "AP_VideoTX_CLI::set_parameters() begin");

    initVtxCliCommandOptions();
    AP_Vehicle* vehicle = AP_Vehicle::get_singleton();
    AP_VideoTX* vtx = &vehicle->vtx;
    RC_Channels* rc = RC_Channels::get_singleton();

    for(int i = 0; i < 8; i++) {
        uint16_t pwm = 0;
        auto options = &getVtxCliCommandOptionsAll()[i];
        
        if(rc->get_pwm(options->rc, pwm)) {
            if(options->enabled()) {
                if(options->band != 0) vtx->set_band(options->band);

                if(options->channel != 0) vtx->set_channel(options->channel);
        
                if(options->power != 0) vtx->change_power(options->power);
            }
        }
    }

    //GCS_SEND_TEXT(((MAV_SEVERITY_INFO, "AP_VideoTX_CLI::set_parameters() end");
}