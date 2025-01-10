#pragma once
#include<Arduino.h>

EncoderParams enc_params_1 {
    .enc_pin_a = 62,    // A8
    .enc_pin_b = 63,    // A9
    .enc_dir = 1
};

EncoderParams enc_params_2 {
    .enc_pin_a = 64,    // A10
    .enc_pin_b = 65,    // A11
    .enc_dir = 1
};

EncoderParams enc_params_3 {
    .enc_pin_a = 66,    // A12
    .enc_pin_b = 67,    // A13
    .enc_dir = 1
};

EncoderParams enc_params_4 {
    .enc_pin_a = 68,    // A14
    .enc_pin_b = 69,    // A15
    .enc_dir = 1
};

EncoderParams enc_params_5 {
    .enc_pin_a = 10,    // 10
    .enc_pin_b = 11,    // 11
    .enc_dir = 1
};

EncoderParams enc_params_6 {
    .enc_pin_a = 12,    // 12
    .enc_pin_b = 13,    // 13
    .enc_dir = 1
};

EncoderParams enc_params_1 = {.get_AB = get_AB_enc1};
EncoderParams enc_params_2 = {.get_AB = get_AB_enc2};
EncoderParams enc_params_3 = {.get_AB = get_AB_enc3};
EncoderParams enc_params_4 = {.get_AB = get_AB_enc4};
EncoderParams enc_params_5 = {.get_AB = get_AB_enc5};
EncoderParams enc_params_6 = {.get_AB = get_AB_enc6};


Encoder enc_1(enc_params_1), enc_2(enc_params_2), enc_3(enc_params_3), enc_4(enc_params_4), enc_5(enc_params_5), enc_6(enc_params_6);


int8_t get_AB_enc1()
{
    return (((PIND) & 0b00000011) >> 0);
}

int8_t get_AB_enc2()
{
    return (((PIND) & 0b00001100) >> 2);
}

int8_t get_AB_enc3()
{
    return (((PIND) & 0b00110000) >> 4);
}

int8_t get_AB_enc4()
{
    return (((PIND) & 0b11000000) >> 6);
}

int8_t get_AB_enc5()
{
    return (((PINB) & 0b00110000) >> 4);
}

int8_t get_AB_enc6()
{
    return (((PINB) & 0b11000000) >> 6);
}

ISR(PCINT0_vect)
{
    enc1.isr_handler();
    enc2.isr_handler();
    enc3.isr_handler();
    enc4.isr_handler();
}

ISR(PCINT2_vect)
{
    enc5.isr_handler();
    enc6.isr_handler();
}