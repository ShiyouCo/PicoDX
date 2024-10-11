#include "ControlHandler.h"

ControlHandler::ControlHandler(int * btnPins, int btnNum, int * ledPins, int ledNum){
    btnCount = btnNum;
	ledCount = ledNum;
    btnPtr = btnPins;
	ledPtr = ledPins;

	
	
	for (int i = 0; i < btnCount; i++){
		//initialize gpio pin
		gpio_init(btnPtr[i]);
		//set input pins for buttons
		gpio_set_dir(btnPtr[i], GPIO_IN);
		//set pull up
		gpio_set_pulls(btnPtr[i], true, false);


	}

	for (int i = 0; i < ledCount; i++){
		//initialize gpio pin
		gpio_init(ledPtr[i]);
		//set output pins for leds
		gpio_set_dir(ledPtr[i], GPIO_OUT);
		//turn off all LEDS
		gpio_put(ledPtr[i], false);
	}
}

picodxReport * ControlHandler::get_report(){

    return &controlState;

}

void ControlHandler::poll_task(){

	poll_buttons();

}

void ControlHandler::poll_buttons(){


	uint16_t buildBtn = 0;
	

	for (int i = btnCount - 1; i >= 0; i--){
		
		if (!gpio_get(btnPtr[i])){ //true
			buildBtn = (buildBtn << 1) | 1;
		}
		else
		{
			buildBtn <<= 1;
		}
		
	}

	controlState.buttons = buildBtn;
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
	for (int i = 0; i < ledCount; i++){
		int stateRead = (lightState >> i) & 0x01;
		if (stateRead != 0){
			gpio_put(ledPtr[i], true);

		}
		else{
			gpio_put(ledPtr[i], false);

		}
	}
}

void ControlHandler::lights_task(volatile uint16_t * hidLightState, bool isHIDMode){
	if (isHIDMode){
		set_lights(*hidLightState);
		
	}
	else{
		set_lights(controlState.buttons);
		
	}

}

void ControlHandler::set_turntable_0(bool isDigital, uint8_t value){
	
	if(isDigital){
		if(lastTTValue > value){
			set_analog_x(254); //set to max
			lastTTValue = value;
			TTAlarm.reset();
		}
		else if(lastTTValue < value){
			set_analog_x(0); //set to min
			lastTTValue = value;
			TTAlarm.reset();
		}
		else{
			if (TTAlarm.has_elapsed()){
				set_analog_x(127); //set to neutral
				lastTTValue = value;
				TTAlarm.reset();
			}
		}
	}
	else{
		set_analog_x(value);
	}
}