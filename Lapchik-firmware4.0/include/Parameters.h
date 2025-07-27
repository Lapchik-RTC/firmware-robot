#pragma once
#define Ts_us 4000
#define Ts_s (Ts_us / 1000000.0)



////////////////////////////////////////////////////////////////////
//
////////////////////////////   MOTOR   /////////////////////////////
//
////////////////////////////////////////////////////////////////////
#define M1_IN1 32
#define M1_IN2 34
#define M1_PWM 4
#define M1_DIR 1

#define M2_IN1 33
#define M2_IN2 35
#define M2_PWM 5
#define M2_DIR 1

#define M3_IN1 38
#define M3_IN2 36
#define M3_PWM 6
#define M3_DIR 1

#define M4_IN1 37
#define M4_IN2 39
#define M4_PWM 7
#define M4_DIR 1

#define M5_IN1 40
#define M5_IN2 42
#define M5_PWM 8
#define M5_DIR 1

#define M6_IN1 41
#define M6_IN2 43
#define M6_PWM 9
#define M6_DIR 1

////////////////////////////////////////////////////////////////////
//
///////////////////////////   ENCODER   ////////////////////////////
//
////////////////////////////////////////////////////////////////////

#define E1_INA 62
#define E1_INB 63
#define E1_DIR -1
#define E1_PPR 1830//1746//

#define E2_INA 64
#define E2_INB 65
#define E2_DIR -1
#define E2_PPR 1830//1746//1824//

#define E3_INA 66
#define E3_INB 67
#define E3_DIR 1
#define E3_PPR 1830//1746//

#define E4_INA 68
#define E4_INB 69
#define E4_DIR 1
#define E4_PPR 1830//1746

#define E5_INA 10
#define E5_INB 11
#define E5_DIR 1
#define E5_PPR 1830//1746//

#define E6_INA 14
#define E6_INB 15
#define E6_DIR 1
#define E6_PPR 1830//1746

////////////////////////////////////////////////////////////////////

#define SUPPLY_VOLTAGE 20.0
// #define T_s 1.0
#define MAX_U 17.0
#define MAX_ACC 9
#define REG_PI_KP 2.0//2.18//2.65
#define REG_PI_KI 0.005//0.5//0.78
#define REG_P_KP 1.6//3.5//2.0
#define KPD 0.0