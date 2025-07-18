#pragma once
#include <Arduino.h>
#include "Parameters.h"
#include "MotorDriver.h"
#include "EncFoo.h"

////////////////////////////////////////////////////////////////////
//
////////////////////////////   MOTOR   /////////////////////////////
//
////////////////////////////////////////////////////////////////////

MotorDriversSet MdrvSet = {
    .supply_voltage = SUPPLY_VOLTAGE,
    .Ts = Ts_s,
    .T_sec = 4.0*Ts_s,
    .maxU = MAX_U,
    .maxAccel = MAX_ACC
};
MotorConnect Mconnp[6] = {
    {.motor_in_1 = M1_IN1, .motor_in_2 = M1_IN2, .motor_pwm = M1_PWM, .enc_pin_a = E1_INA, .enc_pin_b = E1_INB},
    {.motor_in_1 = M2_IN1, .motor_in_2 = M2_IN2, .motor_pwm = M2_PWM, .enc_pin_a = E2_INA, .enc_pin_b = E2_INB},
    {.motor_in_1 = M3_IN1, .motor_in_2 = M3_IN2, .motor_pwm = M3_PWM, .enc_pin_a = E3_INA, .enc_pin_b = E3_INB},
    {.motor_in_1 = M4_IN1, .motor_in_2 = M4_IN2, .motor_pwm = M4_PWM, .enc_pin_a = E4_INA, .enc_pin_b = E4_INB},
    {.motor_in_1 = M5_IN1, .motor_in_2 = M5_IN2, .motor_pwm = M5_PWM, .enc_pin_a = E5_INA, .enc_pin_b = E5_INB},
    {.motor_in_1 = M6_IN1, .motor_in_2 = M6_IN2, .motor_pwm = M6_PWM, .enc_pin_a = E6_INA, .enc_pin_b = E6_INB}
};
MotorParams Mprm[6] = {
    {.motor_dir = M1_DIR, .enc_dir = E1_DIR, .ppr = E1_PPR, .get_AB = get_AB_enc1, REG_P_KP, REG_PI_KP, REG_PI_KI},
    {.motor_dir = M2_DIR, .enc_dir = E2_DIR, .ppr = E2_PPR, .get_AB = get_AB_enc2, REG_P_KP, REG_PI_KP, REG_PI_KI},
    {.motor_dir = M3_DIR, .enc_dir = E3_DIR, .ppr = E3_PPR, .get_AB = get_AB_enc3, REG_P_KP, REG_PI_KP, REG_PI_KI},
    {.motor_dir = M4_DIR, .enc_dir = E4_DIR, .ppr = E4_PPR, .get_AB = get_AB_enc4, REG_P_KP, REG_PI_KP, REG_PI_KI},
    {.motor_dir = M5_DIR, .enc_dir = E5_DIR, .ppr = E5_PPR, .get_AB = get_AB_enc5, REG_P_KP, REG_PI_KP, REG_PI_KI},
    {.motor_dir = M6_DIR, .enc_dir = E6_DIR, .ppr = E6_PPR, .get_AB = get_AB_enc6, REG_P_KP, REG_PI_KP, REG_PI_KI}
};
Motor Serv[6] = {
    {&MdrvSet, &Mconnp[0], &Mprm[0]},
    {&MdrvSet, &Mconnp[1], &Mprm[1]},
    {&MdrvSet, &Mconnp[2], &Mprm[2]},
    {&MdrvSet, &Mconnp[3], &Mprm[3]},
    {&MdrvSet, &Mconnp[4], &Mprm[4]},
    {&MdrvSet, &Mconnp[5], &Mprm[5]}
};

////////////////////////////////////////////////////////////////////
//
///////////////////////////   ENCODER   ////////////////////////////
//
////////////////////////////////////////////////////////////////////
ISR(PCINT0_vect)
{
    Serv[4].isr_handler();
}

ISR(PCINT1_vect)
{
    Serv[5].isr_handler();
}

ISR(PCINT2_vect)
{
    Serv[0].isr_handler();
    Serv[1].isr_handler();
    Serv[2].isr_handler();
    Serv[3].isr_handler();  
}
