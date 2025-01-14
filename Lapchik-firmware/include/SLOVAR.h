#pragma once
#define MAX_SPEED         8.0
#define MOTORS_KE         0.8   /*!< [V/rad/s] */
#define Ts_s              4000.0
#define Ts_s_IN_SEC       4000*0.000001
#define MOTORS_PI_KI      0.00001
#define MOTORS_PI_KP      0.0001
#define MOTORS_PI_MAX_I   200
#define ENC_PPR 465
#define KOLVO_ENC_TICK 48 // количество тиков датчика холла за 1 полный оборот
#define GEAR_RATIO 47   // передаточное отношение редуктора
#define TICK_TO_RAD ((2.0*M_PI)/(KOLVO_ENC_TICK * GEAR_RATIO)) // будет нужно, если будем использовать угол,
// а не тики
#define TICK_TO_TICK 1
#define SUPPLY_VOLTAGE 12 // подаваемое напряжение