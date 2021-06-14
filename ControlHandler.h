#ifndef CONTROL_HANDLER_H_
#define CONTROL_HANDLER_H_

#include <stdint.h>
#include "pico/stdlib.h"
#include "picodx_hid.h"

class ControlHandler{

private:
    int btnCount;
    int * btnPtr;
    void poll_buttons();
    void poll_analogs();
    picodxReport controlState;

public:
    ControlHandler(int * btnPins, int btnNum);
    void task_poll();
    picodxReport * get_report();

};
#endif
