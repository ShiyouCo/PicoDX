#include "ControlHandler.h"

ControlHandler::ControlHandler(int * btnPins, int btnNum){
    btnCount = btnNum;
    btnPtr = btnPins;
}

picodxReport * ControlHandler::get_report(){
    return &controlState;
}

void ControlHandler::task_poll(){
    controlState.buttons = 0x5555;
    controlState.xAxis = 0;
    controlState.yAxis = 0;
    controlState.zAxis = 0; 
    /*
    for (int i = 0; i < btnCount; i++){
        controlState.buttons = controlState.buttons || btnPtr[0] << i;
    }
    */
}