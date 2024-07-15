#ifndef CONTROL_HANDLER_H_
#define CONTROL_HANDLER_H_

#include <stdint.h>
#include "pico/stdlib.h"
#include "picodx_hid.h"
#include "alarm.h"

class ControlHandler{

private:
    int btnCount;
    int * btnPtr;
    int ledCount;
    int * ledPtr;
    Alarm TTAlarm;
    uint8_t lastTTValue;

    //Polls buttons state
    void poll_buttons();
    //Sets light display
    void set_lights(uint16_t lightState);
    //Container for controller state
    picodxReport controlState;
    

public:
    //Constructor
    ControlHandler(int * btnPins, int btnNum, int * ledPins, int ledNum);
    //Call every cycle to poll controller's state
    void poll_task();
    //Get report
    picodxReport * get_report();
    //Call every cycle to control lights
    void lights_task(volatile uint16_t * hidLightState, bool isHIDMode);
    //Set analog x value
    void set_analog_x(uint8_t value);
    //Set analog y value
    void set_analog_y(uint8_t value);
    //Set analog z value
    void set_analog_z(uint8_t value);
    //Set turntables
    void set_turntable_0(bool isDigital, uint8_t value);

};
#endif
