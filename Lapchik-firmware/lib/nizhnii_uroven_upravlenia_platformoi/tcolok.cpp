#pragma once

#include <Arduino.h>
#include "tcokol.h"

#pragma once // полезная для оптимизации штука, но, когда напишем код полностью, надо будет понять, куда её написать

void tcocol(float w)
{
    encoder_tick();
    motor_tick(w);    // если угловая скорость будет в тиках/с
    // motor_rad(w);   // если угловая скорость будет в рад/с
}

// получение текущего угла поворота в радианах
float tcocol_rad() {
    return phi;
}

// получение текущего угла поворота в тиках
float tcocol_tick() {
    return tick;
}

// получение текущей скорости в радианах
float tcocol_w_rad() {
    return w_rad;
}

// получение текущей скорости в тиках
float tcocol_w_tick() {
    return w_tick;
}



// void loop()
// {
//   ///////// TIMER /////////
//   // Задание постоянной частоты главного цикла прогааммы
//   static uint32_t timer = micros();
//   while(micros() - timer < Ts_us)
//     ;
//   timer = micros();

//   ///////// SENSE /////////
//   // Считывание датчиков

//   const float pos0 = (analogRead(A1) - 512) / 50.0;
  
//   encoder_tick();

//   ///////// PLAN /////////
//   // Расчет управляющих воздействий

//   const float Kp_phi = 30;
//   const float vel0 = (pos0 - phi)*Kp_phi;

//   const float vel = velocity_estimator(phi);
  
//   const float err = vel0 - vel;
//   const float u = vel_pi_reg(err, SUPPLY_VOLTAGE);

//   ///////// ACT /////////
//   // Приведение управляющих воздействий в действие и логирование данных
//   motor_tick(u);

//   Serial.print(" pos0: " );
//   Serial.print(pos0);
//   Serial.print(" phi: " );
//   Serial.print(phi);
//   Serial.println();
// }