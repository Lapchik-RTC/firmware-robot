// #ifndef TCOKOL_CPP
// #define TCOKOL_CPP
// //#include <Arduino.h>
// #include "tcokol.h"

// //#pragma once // полезная для оптимизации штука, но, когда напишем код полностью, надо будет понять, куда её написать

// Dvigatel dvigatel_1;
// Dvigatel dvigatel_2;
// Dvigatel dvigatel_3;
// Dvigatel dvigatel_4;
// Dvigatel dvigatel_5;
// Dvigatel dvigatel_6;


// void dvigatels_init() {
//     EncoderParams encoderParams_1(A8, A9, PIND, 0b00000011, 0, 1, 2);
//     MotorParams motorParams_1();
//     Encoder encoder_1(encoderParams_1);
//     Motor motor_1(motorParams_1);
//     Dvigatel dvigatel_1(encoder_1, motor_1);

//     EncoderParams encoderParams_2(A10, A11, PIND, 0b00001100, 2, 1, 2);
//     MotorParams motorParams_2();
//     Encoder encoder_2(encoderParams_2);
//     Motor motor_2(motorParams_2);
//     Dvigatel dvigatel_2(encoder_2, motor_2);

//     EncoderParams encoderParams_3(A12, A13, PIND, 0b00110000, 4, 1, 2);
//     MotorParams motorParams_3();
//     Encoder encoder_3(encoderParams_3);
//     Motor motor_3(motorParams_3);
//     Dvigatel dvigatel_3(encoder_3, motor_3);

//     EncoderParams encoderParams_4(A14, A15, PIND, 0b11000000, 6, 1, 2);
//     MotorParams motorParams_4();
//     Encoder encoder_4(encoderParams_4);
//     Motor motor_4(motorParams_4);
//     Dvigatel dvigatel_4(encoder_4, motor_4);

//     EncoderParams encoderParams_5(10, 11, PINB, 0b00001100, 2, 1, 0);
//     MotorParams motorParams_5();
//     Encoder encoder_5(encoderParams_5);
//     Motor motor_5(motorParams_5);
//     Dvigatel dvigatel_5(encoder_5, motor_5);

//     EncoderParams encoderParams_6(12, 13, PINB, 0b00110000, 4, 1, 0);
//     MotorParams motorParams_6();
//     Encoder encoder_6(encoderParams_6);
//     Motor motor_6(motorParams_6);
//     Dvigatel dvigatel_6(encoder_6, motor_6);

// }
// #endif