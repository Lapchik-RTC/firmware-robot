#pragma once
#define MAX_SPEED         8.0
#define MOTORS_KE         0.8   /*!< [V/rad/s] */
#define Ts_s              4000.0
#define Ts_s_IN_SEC       4000*0.000001
#define MOTORS_PI_KI      0.00001
#define MOTORS_PI_KP      0/*0.0001*/
#define MOTORS_PI_MAX_I   200.01
#define ENC_PPR 465.0
#define GEAR_RATIO 47   // передаточное отношение редуктора

#define KOLVO_ENC_TICK_1 1755.0 // количество тиков датчика холла на 1 энкодере за 1 полный оборот
#define KOLVO_ENC_TICK_4 1745.0 // количество тиков датчика холла на 1 энкодере за 1 полный оборот
#define KOLVO_ENC_TICK_5 1745.0 // количество тиков датчика холла на 1 энкодере за 1 полный оборот

#define KOLVO_ENC_TICK_2 1750.0 // количество тиков датчика холла на 1 энкодере за 1 полный оборот
#define KOLVO_ENC_TICK_3 1755.0 // количество тиков датчика холла на 1 энкодере за 1 полный оборот
#define KOLVO_ENC_TICK_6 1748.0 // количество тиков датчика холла на 1 энкодере за 1 полный оборот

#define TICK_TO_RAD_1 ((2.0*M_PI)/(KOLVO_ENC_TICK_1)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
#define TICK_TO_RAD_2 ((2.0*M_PI)/(KOLVO_ENC_TICK_2)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
#define TICK_TO_RAD_3 ((2.0*M_PI)/(KOLVO_ENC_TICK_3)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
#define TICK_TO_RAD_4 ((2.0*M_PI)/(KOLVO_ENC_TICK_4)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
#define TICK_TO_RAD_5 ((2.0*M_PI)/(KOLVO_ENC_TICK_5)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
#define TICK_TO_RAD_6 ((2.0*M_PI)/(KOLVO_ENC_TICK_6)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
#define TICK_TO_TICK 1
#define W_MAX (2.0*M_PI)*7.33333333333 // 7.(3) -- об/сек для двигателей по документации
#define SUPPLY_VOLTAGE 12 // подаваемое напряжение~

///////////////////////////////////////////////////
// #define CS_PIN_1 A1
// #define CS_PIN_2 A1
// #define CS_PIN_3 A1
// #define CS_PIN_4 A1
// #define CS_PIN_5 A1
// #define CS_PIN_6 A1

// #define TRIG_CUR_1 1
// #define TRIG_CUR_2 1
// #define TRIG_CUR_3 1
// #define TRIG_CUR_4 1
// #define TRIG_CUR_5 1
// #define TRIG_CUR_6 1
uint8_t csPins[6] = 
{
    A4,
    A2,
    A0,
    A1,
    A3,
    A5
};
uint8_t trigCurr[6] = 
{
    A1,
    A1,
    A1,
    A1,
    A1,
    A1
};