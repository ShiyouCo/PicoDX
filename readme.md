# PicoDX

A rhythm game controller board code for Raspberry Pi Pico.

## Features

1. 11 Buttons
2. HID Lighting and Reactive Lights mode (WIP)
3. Supports Infinitas and IIDX Ultimate Mobile
4. Analog and Digital Turntable modes (WIP)
5. WS2812B LED Strips for buttons and TT (WIP)

## GPIO Assignments

This is the default assignments of Raspberry Pi Pico's GPIO Pins. You can modify these assignments in the PicoDX.cpp file, but you must build the source code yourself.

|Pico GPIO  |Function|
|:---------:|--------|
|4          |Button 1|
|6          |Button 2|
|8          |Button 3|
|10         |Button 4|
|12         |Button 5|
|14         |Button 6|
|16         |Button 7|
|18         |Button 8|
|20         |Button 9|
|22         |Button 10|
|27         |Button 11|
|5          |LED 1|
|7          |LED 2|
|9          |LED 3|
|11         |LED 4|
|13         |LED 5|
|15         |LED 6|
|17         |LED 7|
|19         |LED 8|
|21         |LED 9|
|23         |LED 10|
|28         |LED 11|
|0          |Encoder Input A|
|1          |Encoder Input B|



## Installation

1. Compile the code / Download the PicoDX.uf2 file.
2. Connect the Pico to a USB port while holding the BOOTSEL button.
3. Copy the uf2 file into the RPI-RP2 drive.
4. The Pico will restart and should show up as a controller.

## Building
Make sure you've setup the rapsberry pi pico SDK on your environment. Clone the repo, and then inside the root folder of the repository :

``` bash
mkdir build
cd ./build
cmake ..
make
```


## ToDo
1. Test encoder function
2. Write light hardware controller
3. Implement littleFS for configurations
4. Write button combination handlers