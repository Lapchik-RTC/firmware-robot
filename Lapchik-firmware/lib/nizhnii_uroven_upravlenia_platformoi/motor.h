#pragma once

#include<Arduino.h>

struct DvigatelParams
{ 
  uint16_t motor_in_1;        // пин, отвечающий за направление
  uint16_t motor_in_2;        // пин, отвечающий за направление
  uint16_t motor_pwm;         // пин ШИМ
  int16_t motor_dir;         // условный указатель для управления направлением
  // вращения вала двигателя, то есть +-1
  uint16_t supply_voltage;    // подаваемое напряжение
};

class Dvigatel {
private:
  DvigatelParams dvigatelParams;
  
public:
  Dvigatel(DvigatelParams &dvigatelParams) {
    this->dvigatelParams = dvigatelParams;
    dvigatel_init();
  }
  
  void dvigatel_init() {
    pinMode(this->dvigatelParams.motor_in_1, OUTPUT);
    pinMode(this->dvigatelParams.motor_in_2, OUTPUT);
    pinMode(this->dvigatelParams.motor_pwm,  OUTPUT);
  }

  void update_voltage_in_V(float u) {
    int16_t pwm = 255.0 * (u / dvigatelParams.supply_voltage) * 1.0/*dvigatelParams.motor_dir*/;
    pwm = constrain(pwm, -255.0, 255.0);

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