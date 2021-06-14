#include "ControlHandler.h"

ControlHandler::ControlHandler(int * btnPins, int btnNum){
    btnCount = btnNum;
    btnPtr = btnPins;
	
	for (int i = 0; i < btnCount; i++){
		//initialize gpio pin
		gpio_init(btnPtr[i]);
		//set input pins for buttons
		gpio_set_dir(btnPtr[i], GPIO_IN);
		//set pull up
		gpio_set_pulls(btnPtr[i], true, false);
	}
}

picodxReport * ControlHandler::get_report(){
    return &controlState;
}

void ControlHandler::task_poll(){
	poll_buttons();
	poll_analogs();
    //controlState.buttons = 0x5555;
    controlState.xAxis = 0;
    controlState.yAxis = 0;
    controlState.zAxis = 0; 
}

void ControlHandler::poll_buttons(){
	static uint32_t pinState = gpio_get_all();
	for (int i = 0; i < btnCount; i++){
		controlState.buttons |= ((pinState >> btnPtr[i]) && 0x1) << i; 
	}
}

void ControlHandler::poll_analogs(){
}