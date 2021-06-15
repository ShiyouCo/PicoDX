# PicoDX

A rhythm game controller board code for Raspberry Pi Pico.


## Wirings

WIP

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
1. Write encoder functions and analog reports
2. Write light hardware controller