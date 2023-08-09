#include "picodx_config.h"

Picodx_config::Picodx_config(){
    for (int i = 0; i < 12; i++){
        RgbValues[i] = Picodx_Rgb();
    }

}

short Picodx_config::getPropertyValue(property property){
    short value = propertyBitField & (0x01 << property);
    return value;
}

void Picodx_config::setPropertyValue(property property, int value){
    propertyBitField |= (value << property);
};


void Picodx_config::getRgbValue(rgbIdent rgbNum, uint8_t * rgbArray){
    
    rgbArray[0] = RgbValues[rgbNum].getR();
    rgbArray[1] = RgbValues[rgbNum].getG();
    rgbArray[2] = RgbValues[rgbNum].getB();
}

void Picodx_config::setRgbValue(rgbIdent rgbNum, uint8_t * rgbArray){
    RgbValues[rgbNum].setRgb(rgbArray[0], rgbArray[1], rgbArray[2]);
}

// ==================================
// Picodx_Rgb Class
// ==================================

Picodx_Rgb::Picodx_Rgb(){
    Red = 0;
    Green = 0;
    Blue = 0;
}

Picodx_Rgb::Picodx_Rgb(uint8_t r, uint8_t g, uint8_t b){
    Red = r;
    Green = g;
    Blue = b;
}

void Picodx_Rgb::setRgb(uint8_t r, uint8_t g, uint8_t b){
    Red = r;
    Green = g;
    Blue = b;
}

uint8_t Picodx_Rgb::getR(){
    return Red;
}

uint8_t Picodx_Rgb::getG(){
    return Green;
}

uint8_t Picodx_Rgb::getB(){
    return Blue;
}