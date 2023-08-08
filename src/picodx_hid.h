#include <stdint.h>
#include "tusb.h"
#ifndef PICODX_HID_H_
#define PICODX_HID_H_


typedef struct picodxReport{
    uint16_t buttons;
    uint8_t xAxis;
    uint8_t yAxis;
    uint8_t zAxis;

} picodxReport;

class picodx_hid{

public:
    picodx_hid();
    void sendReport(picodxReport * report);
};

#endif