#pragma once

#include<Arduino.h>
//#include"SLOVAR.h"
#include "Encoder.h"
#include "Dvigatel.h"
#include "regulatori.h"

uint8_t get_AB_enc1()
{
    return (((PINK) & 0b00000011) >> 0);
}

uint8_t get_AB_enc2()
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


// Encoder
EncoderParams enc_params_2 {
    .enc_pin_a = 64,    //8 // A10
    .enc_pin_b = 65,    //9 // A11
    .enc_dir = -1,
    .ppr = KOLVO_ENC_TICK_2,
    .tick_to_rad = TICK_TO_RAD_2,
    .get_AB = get_AB_enc2,
    .Ts_sec = Ts_s_IN_SEC,
    .T_sec = Ts_s_IN_SEC,
};

EncoderParams enc_params_1 {
    .enc_pin_a = 62,    // A10
    .enc_pin_b = 63,    // A11
    .enc_dir = -1,
    .ppr = KOLVO_ENC_TICK_1,
    .tick_to_rad = TICK_TO_RAD_1,
    .get_AB = get_AB_enc1,
    .Ts_sec = Ts_s_IN_SEC,
    .T_sec = Ts_s_IN_SEC,
};

EncoderParams enc_params_3 {
    .enc_pin_a = 66,    // A12
    .enc_pin_b = 67,    // A13
    .enc_dir = 1,
    .ppr = KOLVO_ENC_TICK_3,
    .tick_to_rad = TICK_TO_RAD_3,
    .get_AB = get_AB_enc3,
    .Ts_sec = Ts_s_IN_SEC,
    .T_sec = Ts_s_IN_SEC,
};

EncoderParams enc_params_4 {
    .enc_pin_a = 68,    // A14
    .enc_pin_b = 69,    // A15
    .enc_dir = 1,
    .ppr = KOLVO_ENC_TICK_4,
    .tick_to_rad = TICK_TO_RAD_4,
    .get_AB = get_AB_enc4,
    .Ts_sec = Ts_s_IN_SEC,
    .T_sec = Ts_s_IN_SEC,
};

EncoderParams enc_params_5 {
    .enc_pin_a = 10,    // 10
    .enc_pin_b = 11,    // 11
    .enc_dir = 1,
    .ppr = KOLVO_ENC_TICK_5,
    .tick_to_rad = TICK_TO_RAD_5,
    .get_AB = get_AB_enc5,
    .Ts_sec = Ts_s_IN_SEC,
    .T_sec = Ts_s_IN_SEC,
};

EncoderParams enc_params_6 {
    .enc_pin_a = 14,    // 12
    .enc_pin_b = 15,    // 13
    .enc_dir = 1,
    .ppr = KOLVO_ENC_TICK_6,
    .tick_to_rad = TICK_TO_RAD_6,
    .get_AB = get_AB_enc6,
    .Ts_sec = Ts_s_IN_SEC,
    .T_sec = Ts_s_IN_SEC,
};


Encoder encod[6] = {
    {enc_params_1},
    {enc_params_2},
    {enc_params_3},
    {enc_params_4},
    {enc_params_5},
    {enc_params_6}
};
/*
Encoder enc_1(enc_params_1),
        enc_2(enc_params_2),
        enc_3(enc_params_3),
        enc_4(enc_params_4),
        enc_5(enc_params_5),
        enc_6(enc_params_6);
*/


ISR(PCINT0_vect)
{
    encod[4].isr_handler();
    // enc_6.isr_handler();
}
ISR(PCINT1_vect)
{
    encod[5].isr_handler();
}

ISR(PCINT2_vect)
{
    encod[0].isr_handler();
    encod[1].isr_handler();
    encod[2].isr_handler();
    encod[3].isr_handler();  
}





// Motor

DvigatelParams dvigatel_params_2 {
    .motor_in_1 = 33,
    .motor_in_2 = 35,
    .motor_pwm = 5,
    .motor_dir = 1,
    .supply_voltage = SUPPLY_VOLTAGE
};

DvigatelParams dvigatel_params_1 {
    .motor_in_1 = 32,
    .motor_in_2 = 34,
    .motor_pwm = 4,
    .motor_dir = 1,
    .supply_voltage = SUPPLY_VOLTAGE
};

DvigatelParams dvigatel_params_3 {
    .motor_in_1 = 38,
    .motor_in_2 = 36,
    .motor_pwm = 6,
    .motor_dir = 1,
    .supply_voltage = SUPPLY_VOLTAGE
};

DvigatelParams dvigatel_params_4 {
    .motor_in_1 = 37,
    .motor_in_2 = 39,
    .motor_pwm = 7,
    .motor_dir = 1,
    .supply_voltage = SUPPLY_VOLTAGE
};

DvigatelParams dvigatel_params_5 {
    .motor_in_1 = 40,
    .motor_in_2 = 42,
    .motor_pwm = 8,
    .motor_dir = 1,
    .supply_voltage = SUPPLY_VOLTAGE
};

DvigatelParams dvigatel_params_6 {
    .motor_in_1 = 41,
    .motor_in_2 = 43,
    .motor_pwm = 9,
    .motor_dir = 1,
    .supply_voltage = SUPPLY_VOLTAGE
};

Dvigatel dvig[6] = {
    {dvigatel_params_1},
    {dvigatel_params_2},
    {dvigatel_params_3},
    {dvigatel_params_4},
    {dvigatel_params_5},
    {dvigatel_params_6}
};
/*Dvigatel dvigatel_1(dvigatel_params_2), 
dvigatel_2(dvigatel_params_1), 
dvigatel_3(dvigatel_params_3), 
dvigatel_4(dvigatel_params_4), 
dvigatel_5(dvigatel_params_5), 
dvigatel_6(dvigatel_params_6);
*/
/////////////////////////////////////////////////////////
// inline void encUpd()
// {
//     enc_1.enc_tick();
//     enc_2.enc_tick();
//     enc_3.enc_tick();
//     enc_4.enc_tick();
//     enc_5.enc_tick();
//     enc_6.enc_tick();
// }



#define KP_PI 1//0.06
#define KI_PI 0.01//0.05//2.1//5
#define KP_P 32
#define KE 0.2

MotorControlParams mctrlp//структура общая
{
  .Ts_sec = Ts_s_IN_SEC,
  .kpPI = KP_PI,//0.0001,
  .ki = KI_PI,//00079,//0.00001,
  .maxU = SUPPLY_VOLTAGE/2,
  .kpP = KP_P,
  .maxVel = 16.0,
  .kalibrSpeed = 1
};

MotorControlParams mctrlp3//структура общая
{
  .Ts_sec = Ts_s_IN_SEC,
  .kpPI = KP_PI,//0.0001,
  .ki = KI_PI,//00079,//0.00001,
  .maxU = SUPPLY_VOLTAGE/2,
  .kpP = KP_P,
  .maxVel = 16.0,
  .kalibrSpeed = 1
};

ServoPrivod serv[6] = {
    {mctrlp, &dvig[0], &encod[0]},
    {mctrlp, &dvig[1], &encod[1]},
    {mctrlp3, &dvig[2], &encod[2]},
    {mctrlp, &dvig[3], &encod[3]},
    {mctrlp, &dvig[4], &encod[4]},
    {mctrlp, &dvig[5], &encod[5]}
};
/*
ServoPrivod serv1(mctrlp, &dvigatel_1, &enc_1);
ServoPrivod serv2(mctrlp, &dvigatel_2, &enc_2);
ServoPrivod serv3(mctrlp, &dvigatel_3, &enc_3);
ServoPrivod serv4(mctrlp, &dvigatel_4, &enc_4);
ServoPrivod serv5(mctrlp, &dvigatel_5, &enc_5);
ServoPrivod serv6(mctrlp, &dvigatel_6, &enc_6);
*/

