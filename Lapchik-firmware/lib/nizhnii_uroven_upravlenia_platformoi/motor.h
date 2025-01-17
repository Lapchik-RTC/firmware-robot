#pragma once

#include<Arduino.h>
#include "HardwareSerial.h"
#include <SLOVAR.h>


struct DvigatelParams
{ 
  uint16_t motor_in_1;        // пин, отвечающий за направление
  uint16_t motor_in_2;        // пин, отвечающий за направление
  uint16_t motor_pwm;         // пин ШИМ
  uint16_t motor_dir;         // условный указатель для управления направлением
  // вращения вала двигателя, то есть +-1
  uint16_t supply_voltage;    // подаваемое напряжение

  DvigatelParams(uint16_t motor_in_1, uint16_t motor_in_2, uint16_t motor_pwm, uint16_t motor_dir, uint16_t supply_voltage){
    this->motor_in_1 = motor_in_1;
    this->motor_in_2 = motor_in_2;
    this->motor_pwm = motor_pwm;
    this->motor_dir = motor_dir;
    this->supply_voltage = supply_voltage;
  }
};

class Dvigatel {
private:
  DvigatelParams dvigatelParams;
  
public:
  Dvigatel(DvigatelParams &dvigatelParams) : dvigatelParams(dvigatelParams) {
    this->dvigatelParams = dvigatelParams;
    dvigatel_init();
  }
  
  
  void dvigatel_init() {
    pinMode(dvigatelParams.motor_in_1, OUTPUT);
    pinMode(dvigatelParams.motor_in_2, OUTPUT);
    pinMode(dvigatelParams.motor_pwm,  OUTPUT);
  }

  // void update_speed_in_tick(float w) {
  //   float wMax = 1 / Ts_s_IN_SEC;
  //   float u = 0;
  //   u = dvigatelParams.supply_voltage*constrain((w/wMax), -1.0, 1.0);
  //   const int16_t pwm = 255.0 * constrain(u / dvigatelParams.supply_voltage, -1.0, 1.0) * dvigatelParams.motor_dir;

  //   if (pwm >= 0)
  //   {
  //     digitalWrite(dvigatelParams.motor_in_1, HIGH);
  //     digitalWrite(dvigatelParams.motor_in_2, LOW);
  //     analogWrite(dvigatelParams.motor_pwm, pwm);
  //   }
  //   else
  //   {
  //     digitalWrite(dvigatelParams.motor_in_1, LOW);
  //     digitalWrite(dvigatelParams.motor_in_2, HIGH);
  //     analogWrite(dvigatelParams.motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
  //   }
  // }

  void update_speed_in_rad(float w) {
    float wMax = (6.2831853071*7,33333333333333333) / Ts_s_IN_SEC;
    float u = 0;
    u = dvigatelParams.supply_voltage*constrain((w/wMax), -1.0, 1.0);
    const int16_t pwm = 255.0 * constrain(u / dvigatelParams.supply_voltage, -1.0, 1.0) * dvigatelParams.motor_dir;

    if (pwm >= 0)
    {
      digitalWrite(dvigatelParams.motor_in_1, HIGH);
      digitalWrite(dvigatelParams.motor_in_2, LOW);
      analogWrite(dvigatelParams.motor_pwm, pwm);
    }
    else
    {
      digitalWrite(dvigatelParams.motor_in_1, LOW);
      digitalWrite(dvigatelParams.motor_in_2, HIGH);
      analogWrite(dvigatelParams.motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
    }
  }
};