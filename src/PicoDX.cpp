/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
//#include "libs/McuLib/lib/littleFS/lfs.h"
//#include "tusb.h"
//#include "pico/stdlib.h"

#include "usb_descriptors.h"
#include "picodx_hid.h"
#include "ControlHandler.h"
#include "pio_rotary_encoder.cpp"


//int btnPins[11] = {0,1,2,3,4,5,6,7,8,9,10};

int btnPins[11] = {4,6,8,10,12,14,16,18,20,22,27};
int ledPins[11] = {5,7,9,11,13,15,17,19,21,23,28};
int encoderPinA = 0; //pin B should be connected to GPIO1
//int encoderPinA2 = 2; //pin B should be connected to GPIO3

int RotaryEncoder::rotation = 0;

RotaryEncoder encoder(encoderPinA, false, false); // set pull up and pull down resistor for the encoder. Some encoder requires both to be turned off.
//RotaryEncoder encoder2(encoderPinA2, false, false);
ControlHandler dxInput(btnPins, 11, ledPins, 11);
//lfs_t lfs;
//lfs_file_t file;


picodx_hid hidHandler;
volatile uint16_t hidLightReport;
uint32_t last_send = 0;

void led_blinking_task(void);

/*------------- MAIN -------------*/
int main(void)
{
 

  tusb_init();

  //initialize encoder
  encoder.set_rotation(0);
  //encoder2.set_rotation(0);

  while (1)
  {
    // tinyusb device task
    tud_task(); 

    // poll inputs
    dxInput.poll_task();
    // set analog x value from encoder rotation
    dxInput.set_analog_x((uint8_t) encoder.get_rotation());
    //dxInput.set_analog_y((uint8_t) encoder2.get_rotation());
    // control lights
    dxInput.lights_task(&hidLightReport, true); 

    // send data every 1 ms when tud_hid is ready
    if (board_millis() - last_send > 1 && tud_hid_ready() ) {
      last_send = board_millis();
      hidHandler.sendReport(dxInput.get_report());
    }

  }

  return 0;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
 
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{

}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;

}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{

}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+


// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) itf;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  // TODO set LED based on CAPLOCK, NUMLOCK etc...
  /*
  (void) itf;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) bufsize;
  */
  // Handle lights HID report here (Report ID = 5, Type = 2)
  if (report_type == 0x02){
    if (bufsize == 2){
     hidLightReport = buffer[0] << 8 + buffer[1];
    }
  }
  else if (report_type == 0x06){

  }

}

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) 
{
	(void)itf;
	(void)rts;

	if (dtr) {
		tud_cdc_write_str("Connected\n");
	}
}
