#pragma once

#include<Arduino.h>
#include "encoder.h"
#include "motor.h"
#include "regulatori.h"
//#pragma once

uint8_t get_AB_enc1()
{
    // Serial.println("enc_1");
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
    // Serial.println("enc_6");
    return (((PINB) & 0b11000000) >> 6);
}


// Encoder
EncoderParams enc_params_2 {
    .enc_pin_a = 64,    //8 // A10
    .enc_pin_b = 65,    //9 // A11
    .enc_dir = -1,
    .ppr = KOLVO_ENC_TICK_2,
    .tick_to_rad = TICK_TO_RAD_2,
    .get_AB = get_AB_enc2
};

EncoderParams enc_params_1 {
    .enc_pin_a = 62,    // A10
    .enc_pin_b = 63,    // A11
    .enc_dir = -1,
    .ppr = KOLVO_ENC_TICK_1,
    .tick_to_rad = TICK_TO_RAD_1,
    .get_AB = get_AB_enc1
};

EncoderParams enc_params_3 {
    .enc_pin_a = 66,    // A12
    .enc_pin_b = 67,    // A13
    .enc_dir = 1,
    .ppr = KOLVO_ENC_TICK_3,
    .tick_to_rad = TICK_TO_RAD_3,
    .get_AB = get_AB_enc3
};

EncoderParams enc_params_4 {
    .enc_pin_a = 68,    // A14
    .enc_pin_b = 69,    // A15
    .enc_dir = 1,
    .ppr = KOLVO_ENC_TICK_4,
    .tick_to_rad = TICK_TO_RAD_4,
    .get_AB = get_AB_enc4
};

EncoderParams enc_params_5 {
    .enc_pin_a = 10,    // 10
    .enc_pin_b = 11,    // 11
    .enc_dir = 1,
    .ppr = KOLVO_ENC_TICK_5,
    .tick_to_rad = TICK_TO_RAD_5,
    .get_AB = get_AB_enc5
};

EncoderParams enc_params_6 {
    .enc_pin_a = 12,    // 12
    .enc_pin_b = 13,    // 13
    .enc_dir = 1,
    .ppr = KOLVO_ENC_TICK_6,
    .tick_to_rad = TICK_TO_RAD_6,
    .get_AB = get_AB_enc6
};

// EncoderParams enc_params_1 = {.get_AB = get_AB_enc1};
// EncoderParams enc_params_2 = {.get_AB = get_AB_enc2};
// EncoderParams enc_params_3 = {.get_AB = get_AB_enc3};
// EncoderParams enc_params_4 = {.get_AB = get_AB_enc4};
// EncoderParams enc_params_5 = {.get_AB = get_AB_enc5};
// EncoderParams enc_params_6 = {.get_AB = get_AB_enc6};


Encoder enc_1(enc_params_1), enc_2(enc_params_2), enc_3(enc_params_3), enc_4(enc_params_4), enc_5(enc_params_5), enc_6(enc_params_6);




ISR(PCINT0_vect)
{
    enc_5.isr_handler();
    enc_6.isr_handler();
}

ISR(PCINT2_vect)
{
    enc_1.isr_handler();
    enc_2.isr_handler();
    enc_3.isr_handler();
    enc_4.isr_handler();  
}





// Motor
DvigatelParams dvigatel_params_1 {
    .motor_in_1 = 33,
    .motor_in_2 = 35,
    .motor_pwm = 5,
    .motor_dir = 1,
    .supply_voltage = 12
};

DvigatelParams dvigatel_params_2 {
    .motor_in_1 = 32,
    .motor_in_2 = 34,
    .motor_pwm = 4,
    .motor_dir = 1,
    .supply_voltage = 12
};

DvigatelParams dvigatel_params_3 {
    .motor_in_1 = 38,
    .motor_in_2 = 36,
    .motor_pwm = 6,
    .motor_dir = 1,
    .supply_voltage = 12
};

DvigatelParams dvigatel_params_4 {
    .motor_in_1 = 37,
    .motor_in_2 = 39,
    .motor_pwm = 7,
    .motor_dir = 1,
    .supply_voltage = 12
};

DvigatelParams dvigatel_params_5 {
    .motor_in_1 = 40,
    .motor_in_2 = 42,
    .motor_pwm = 8,
    .motor_dir = 1,
    .supply_voltage = 12
};

DvigatelParams dvigatel_params_6 {
    .motor_in_1 = 41,
    .motor_in_2 = 43,
    .motor_pwm = 9,
    .motor_dir = 1,
    .supply_voltage = 12
};

Dvigatel dvigatel_1(dvigatel_params_2), 
dvigatel_2(dvigatel_params_1), 
dvigatel_3(dvigatel_params_3), 
dvigatel_4(dvigatel_params_4), 
dvigatel_5(dvigatel_params_5), 
dvigatel_6(dvigatel_params_6);

/////////////////////////////////////////////////////////
/*MotorControlParams mconp = 
{
    .Ts = Ts_s,
    .ppr = 1
};*/
MotorControlParams mctrlp//структура общая
{
  .Ts = Ts_s,
  .kpPI = 0.1,//0.0001,
  .ki = 0.000001,//0.00001,
  .maxI = 480,
  .kpP = 1.0,
  .kalibrSpeed = 1
};

///////////////// SET /////////////////
void ServoPrivod::setGoalSpeed(float goalSpeed)
{
  //enc.enc_tick();
  float u = PIreg(goalSpeed - enc_5.get_w_moment_rad()/*getRealSpeed()*/);
  motor.update_speed_in_rad(u);

  Serial.print("\t wMoment: ");
  Serial.print(enc_5.get_w_moment_rad());
  Serial.print('\n');
}


ServoPrivod serv1(&mctrlp, dvigatel_1, enc_1, 0);
ServoPrivod serv2(&mctrlp, dvigatel_2, enc_2, 1);
ServoPrivod serv3(&mctrlp, dvigatel_3, enc_3, 2);
ServoPrivod serv4(&mctrlp, dvigatel_4, enc_4, 3);
ServoPrivod serv5(&mctrlp, dvigatel_5, enc_5, 4);
ServoPrivod serv6(&mctrlp, dvigatel_6, enc_6, 5);
