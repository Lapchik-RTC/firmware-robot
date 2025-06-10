#pragma once
// #define MAX_SPEED         8.0
// #define MOTORS_KE         0.8   /*!< [V/rad/s] */
#define Ts_s              2100.0
#define Ts_s_IN_SEC       2100*0.000001
// #define MOTORS_PI_KI      0.00001
// #define MOTORS_PI_KP      0/*0.0001*/
// #define MOTORS_PI_MAX_I   200.01
// #define ENC_PPR 465.0
// #define GEAR_RATIO 47   // передаточное отношение редуктора

// #define _TEST_KLV_ETC 1746.0

// #define KOLVO_ENC_TICK_1 _TEST_KLV_ETC/*1755.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот
// #define KOLVO_ENC_TICK_4 _TEST_KLV_ETC/*1745.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот
// #define KOLVO_ENC_TICK_5 _TEST_KLV_ETC/*1745.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот

// #define KOLVO_ENC_TICK_2 _TEST_KLV_ETC/*1750.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот
// #define KOLVO_ENC_TICK_3 _TEST_KLV_ETC/*1755.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот
// #define KOLVO_ENC_TICK_6 _TEST_KLV_ETC/*1748.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот

//uint32_t kolvTickRate[6] = {1746, 1824, 1746, 1746, 1746, 1746};
const uint32_t kolvTickRate[6] = {1825, 1824, 1824, 1826, 1746, 1825};

// #define TICK_TO_RAD_1 ((2.0*M_PI)/(KOLVO_ENC_TICK_1)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
// #define TICK_TO_RAD_2 ((2.0*M_PI)/(KOLVO_ENC_TICK_2)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
// #define TICK_TO_RAD_3 ((2.0*M_PI)/(KOLVO_ENC_TICK_3)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
// #define TICK_TO_RAD_4 ((2.0*M_PI)/(KOLVO_ENC_TICK_4)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
// #define TICK_TO_RAD_5 ((2.0*M_PI)/(KOLVO_ENC_TICK_5)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
// #define TICK_TO_RAD_6 ((2.0*M_PI)/(KOLVO_ENC_TICK_6)) // коэфф. пересчета в угол с учётом количества тиков 1 экодера на полный оборот
// #define TICK_TO_TICK 1
#define W_MAX (2.0*M_PI)*7.33333333333 // 7.(3) -- об/сек для двигателей по документации
#define SUPPLY_VOLTAGE 24 //12 // подаваемое напряжение~

///////////////////////////////////////////////////
#define CS_PIN_1      A4
#define CS_PIN_2      A2
#define CS_PIN_3      A0
#define CS_PIN_4      A1
#define CS_PIN_5      A3
#define CS_PIN_6      A5
byte csPin[6] = {A4, A2, A0, A1, A3, A5};
#define TRIG_CUR_1    180
#define TRIG_CUR_2    180
#define TRIG_CUR_3    190
#define TRIG_CUR_4    180
#define TRIG_CUR_5    180/*150*/
#define TRIG_CUR_6    180
byte trigCur[6] = {180, 180, 190, 180, 180, 180};
///////////////////////////////////////////////////
// #define HALL_PIN_1    30
// #define HALL_PIN_2    31
// #define HALL_PIN_3    28
// #define HALL_PIN_4    29
// #define HALL_PIN_5    26
// #define HALL_PIN_6    27
byte hallPin[6] = {30, 31, 28, 29, 26, 27};
// #define KP_PI 1
// #define KI_PI 0.01
// #define KP_P 32
// #define KE 0.2

// #define KP_PI 1.5
// #define KI_PI 0.00
// #define KP_P 27
// #define KE 0.2

// #define KE 0.2
#define KP_PI0 0.9
#define KI_PI0 0.0
#define  KP_P0 5

#define KP_PI1 0.9
#define KI_PI1 0.0
#define  KP_P1 5

#define KP_PI2 0.4
#define KI_PI2 0.0
#define  KP_P2 5

#define KP_PI3 0.9
#define KI_PI3 0.0
#define  KP_P3 5

#define KP_PI4 0.25
#define KI_PI4 0.0
#define  KP_P4 5

#define KP_PI5 0.25
#define KI_PI5 0.0
#define  KP_P5 5

float posStatic[6] = {0,0,0,0,0,0};