#ifndef CONTROL_HANDLER_H_
#define CONTROL_HANDLER_H_

#include <stdint.h>
#include "pico/stdlib.h"
#include "picodx_hid.h"

class ControlHandler{

private:
    void poll_buttons();
    void poll_analogs();
    picodxReport controlState;
    int btnCount;
    int * btnPtr;

public:
    ControlHandler(int * btnPins, int btnNum);
    void task_poll();
    picodxReport * get_report();

};
#endif
