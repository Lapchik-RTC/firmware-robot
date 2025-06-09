#pragma once
#include <Arduino.h>
#define Ts_us              5000.0
#define Ts_s               5000*0.000001

// #define _TEST_KLV_ETC 1746.0

// #define KOLVO_ENC_TICK_1 _TEST_KLV_ETC/*1755.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот
// #define KOLVO_ENC_TICK_4 _TEST_KLV_ETC/*1745.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот
// #define KOLVO_ENC_TICK_5 _TEST_KLV_ETC/*1745.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот

// #define KOLVO_ENC_TICK_2 _TEST_KLV_ETC/*1750.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот
// #define KOLVO_ENC_TICK_3 _TEST_KLV_ETC/*1755.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот
// #define KOLVO_ENC_TICK_6 _TEST_KLV_ETC/*1748.0*/ // количество тиков датчика холла на 1 энкодере за 1 полный оборот

const uint16_t kolvTickRate[6] = {1746, 1824, 1746, 1746, 1746, 1746};

const uint16_t tick2rad[6] = 
{
    (2.0*M_PI)/(kolvTickRate[0]),
    (2.0*M_PI)/(kolvTickRate[1]),
    (2.0*M_PI)/(kolvTickRate[2]),
    (2.0*M_PI)/(kolvTickRate[3]),
    (2.0*M_PI)/(kolvTickRate[4]),
    (2.0*M_PI)/(kolvTickRate[5])
};
#define TIME_WITHOUT_HALL 1000
#define MAX_TICK_CORR 80

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
byte hallPin[6] = {30, 31, 28, 29, 26, 27};

#define PIreg_KP 1.0
#define PIreg_KI 0.01
#define Preg_KP 32.0



#define TC    2.0*M_PI
#define TS    2.7
#define PHIS  0.5
#define PHI0  0.0