#include <stdint.h>
#include <string.h>

#ifndef PICODX_CONFIG_H_
#define PICODX_CONFIG_H_


/*
#define TTMODE_BIT 0
#define LIGHTMODE_BIT 1
#define RAINBOWMODE_BIT1 2
#define RAINBOWMODE_BIT2 3
*/

class Picodx_config{

    enum rgbIdent{RGB1, RGB2, RGB3, RGB4, RGB5, RGB6, RGB7, RGB8, RGB9, RGB10, RGB11, RGBTT, RGBMAX};

    enum property{
        RAINBOWMODE = 0, RAINBOWMODE2, // 2 bits
        TTMODE, // 0 = Analog, 1 = Digital
        LIGHTMODE // = 0 Reactive, 1 = HID
    };

private:
    Picodx_Rgb RgbValues[RGBMAX];
    uint8_t propertyBitField;

public:
    Picodx_config();
    short getPropertyValue(property property);
    void setPropertyValue(property property, int value);

    void getRgbValue(rgbIdent rgbNum, uint8_t * rgbArray);
    void setRgbValue(rgbIdent rgbNum, uint8_t * rgbArray);

    void loadConfigFromFile();
    void saveConfigToFile();
};

class Picodx_Rgb{
private:
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;

public:
    Picodx_Rgb();
    Picodx_Rgb(uint8_t r, uint8_t g, uint8_t b);
    void setRgb(uint8_t r, uint8_t g, uint8_t b);
    uint8_t getR();
    uint8_t getG();
    uint8_t getB();

};

#endif