#pragma once

#include<Arduino.h>
#include "HardwareSerial.h"
#include <SLOVAR.h>
float Imas[6] = { 0, 0, 0, 0, 0, 0 };
 int num = 0;
struct DvigatelParams
{ 
  uint16_t motor_in_1;        // пин, отвечающий за направление
  uint16_t motor_in_2;        // пин, отвечающий за направление
  uint16_t motor_pwm;         // пин ШИМ
  int16_t motor_dir;         // условный указатель для управления направлением
  // вращения вала двигателя, то есть +-1
  uint16_t supply_voltage;    // подаваемое напряжение

  DvigatelParams(uint16_t motor_in_1, uint16_t motor_in_2, uint16_t motor_pwm, int16_t motor_dir, uint16_t supply_voltage){
    this->motor_in_1 = motor_in_1;
    this->motor_in_2 = motor_in_2;
    this->motor_pwm = motor_pwm;
    this->motor_dir = motor_dir;
    this->supply_voltage = supply_voltage;
  }
};

class Dvigatel  {
private:
  DvigatelParams dvigatelParams;
  
public:
  Dvigatel(DvigatelParams &dvigatelParams) : dvigatelParams(dvigatelParams) {
    this->dvigatelParams = dvigatelParams;
    dvigatel_init();
  }
  
  
  void dvigatel_init() {
    pinMode(this->dvigatelParams.motor_in_1, OUTPUT);
    pinMode(this->dvigatelParams.motor_in_2, OUTPUT);
    pinMode(this->dvigatelParams.motor_pwm,  OUTPUT);
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
    float u = w;
    //u = dvigatelParams.supply_voltage * constrain((w/ 8.0/*W_MAX*/), -1.0, 1.0);
    //float u = constrain(w, -8.0, 8.0);
    // int16_t pwm = 255.0 * constrain(u / dvigatelParams.supply_voltage, -1.0, 1.0) * dvigatelParams.motor_dir;
    int16_t pwm = 255.0 * (u / 8.0) * 1.0/*dvigatelParams.motor_dir*/;
    pwm = constrain(pwm, -255.0, 255.0);
    //Serial.print("pwm: ");
    //Serial.print(pwm);
    //Serial.print('\t');
   
    // if(dvigatelParams.motor_in_1 == 33 || dvigatelParams.motor_in_1 == 35) num = 1;
    // if(dvigatelParams.motor_in_1 == 32 || dvigatelParams.motor_in_1 == 34) num = 2;
    // if(dvigatelParams.motor_in_1 == 36 || dvigatelParams.motor_in_1 == 38) num = 3;
    // if(dvigatelParams.motor_in_1 == 39 || dvigatelParams.motor_in_1 == 37) num = 4;
    // if(dvigatelParams.motor_in_1 == 42 || dvigatelParams.motor_in_1 == 40) num = 5;
    // if(dvigatelParams.motor_in_1 == 41 || dvigatelParams.motor_in_1 == 43) num = 6;
    
    
    // Serial.print('\t');
    // Serial.print("pwm: ");
    // Serial.print(pwm);
    
    
    Serial.print('\t');
    Serial.print(pwm);
    Serial.print('\t');
    //Serial.print(num);
    if (pwm >= 0)
    {
      digitalWrite(this->dvigatelParams.motor_in_1, HIGH);
      digitalWrite(this->dvigatelParams.motor_in_2, LOW);
      analogWrite(this->dvigatelParams.motor_pwm, pwm);
    }
    else
    {
      digitalWrite(this->dvigatelParams.motor_in_1, LOW);
      digitalWrite(this->dvigatelParams.motor_in_2, HIGH);
      analogWrite(this->dvigatelParams.motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
    }
  }
};