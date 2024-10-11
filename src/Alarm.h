#pragma once 

#include <stdint.h>
#include "pico/stdlib.h"

class Alarm{
    public:
        Alarm(){}
        
        void start(uint32_t interval) {
            interval_ms = interval;
            start_ts = millis();
        }

        bool has_elapsed() {
            return (millis() - start_ts) > interval_ms;
        }

        void reset(){
            start_ts = millis();
        }

        void set_interval_and_reset(uint32_t interval){
            interval_ms = interval;
            reset();
        }

    private:
        inline uint32_t millis(){
            return to_ms_since_boot(get_absolute_time());
        }

        uint32_t start_ts;
        uint32_t interval_ms;

};