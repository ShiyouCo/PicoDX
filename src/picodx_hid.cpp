#include "picodx_hid.h"

picodx_hid::picodx_hid(){


}

void picodx_hid::sendReport(picodxReport * report){
    uint8_t hidReport[5];
    hidReport[0] = (report->buttons) & 0xff;
    uint8_t btnNext = report->buttons >> 8;
    hidReport[1] = btnNext & 0xff;
    hidReport[2] = report->xAxis;
    hidReport[3] = report->yAxis;
    hidReport[4] = report->zAxis;
    tud_hid_report(4, &hidReport, sizeof(hidReport));
};