# PicoDX

A rhythm game controller board code for Raspberry Pi Pico.


## Installation
Will be written later

1. Compile the code / Download the PicoDX.uf2 file.
2. Connect the Pico to USB while holding the bootsel button.
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
1. Complete input handler class
2. Write HID Lighting handler class
3. Write the hardware handlers