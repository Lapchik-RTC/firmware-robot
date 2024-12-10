#pragma once
#define MAX_SPEED         8.0
#define MOTORS_KE         0.8   /*!< [V/rad/s] */
#define Ts_us             4000 /*!< sample time [microseconds]*/
#define Ts_s              ((float)Ts_us * 0.000001)
//???
#define MOTORS_TIME_CONSTANT                    0.030
#define MOTORS_Tu                               Ts_s*4
#define MOTORS_ABS_OPTIMUM_SETTING              4.0
//???
#define MOTORS_PI_KI      (MOTORS_KE/(MOTORS_ABS_OPTIMUM_SETTING*MOTORS_Tu))
#define MOTORS_PI_GAIN    (MOTORS_PI_KI*MOTORS_TIME_CONSTANT)
