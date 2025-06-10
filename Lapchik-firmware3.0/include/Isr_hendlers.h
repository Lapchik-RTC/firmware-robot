#pragma once
#include <Arduino.h>

uint8_t get_AB_enc2()
{
    return (((PINK) & 0b00000011) >> 0);
}

uint8_t get_AB_enc1()
{
    // Serial.println("enc_2");
    return (((PINK) & 0b00001100) >> 2);
}

uint8_t get_AB_enc3()
{
    // Serial.println("enc_3");
    return (((PINK) & 0b00110000) >> 4);
}

uint8_t get_AB_enc4()
{
    // Serial.println("enc_4");
    return (((PINK) & 0b11000000) >> 6);
}

uint8_t get_AB_enc5()
{
    // Serial.println("enc_5");
    return (((PINB) & 0b00110000) >> 4);
}

uint8_t get_AB_enc6()
{
    //  Serial.println("enc_6============================================");
    return (((PINJ) & 0b00000011) >> 0);
}
