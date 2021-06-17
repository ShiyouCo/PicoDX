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

void ControlHandler::poll_task(){

	poll_buttons();

}

void ControlHandler::poll_buttons(){
	
	for (int i = 0; i < btnCount; i++){
		bool btnRead = gpio_get(btnPtr[i]);
		if (!btnRead){
			controlState.buttons |= ((uint16_t)0x01 << btnPtr[i]);
		}
		else
		{
			controlState.buttons &= ~((uint16_t)0x01 << btnPtr[i]);
		}
	}

}

void ControlHandler::set_analog_x(uint8_t value){
	controlState.xAxis = value % 255;
}

void ControlHandler::set_analog_y(uint8_t value){
	controlState.yAxis = value % 255;
}

void ControlHandler::set_analog_z(uint8_t value){
	controlState.zAxis = value % 255;
}

void ControlHandler::set_lights(uint16_t lightState){
	// control hardware side here
}

void ControlHandler::lights_task(volatile uint16_t * hidLightState, bool isHIDMode){
	if (isHIDMode){
		set_lights(*hidLightState);
	}
	else{
		set_lights(controlState.buttons);
	}

}