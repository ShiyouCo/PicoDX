#ifndef PICODX_SETTING_H_
#define PICODX_SETTING_H_

#include <stdint.h>

enum lightMode{
    HID = 0,
    REACTIVE = 1
};

enum analogMode{
    ANALOG = 0,
    DIGITAL = 1
};

class PicoDXSetting{
    private:
        lightMode light = HID;
        analogMode analog = ANALOG;
    public:
        //constructor
        PicoDXSetting();
        lightMode getLightMode();
        lightMode setLightMode();

        analogMode getAnalogMode();
        analogMode setAnalogMode();

        void saveSetting();
        void loadSetting();

        void getSettings();

};

#endif