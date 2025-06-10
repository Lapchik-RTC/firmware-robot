#pragma once

#include<Arduino.h>

struct motorParams
{ 
  uint16_t motor_in_1;        // пин, отвечающий за направление
  uint16_t motor_in_2;        // пин, отвечающий за направление
  uint16_t motor_pwm;         // пин ШИМ
  int16_t motor_dir;         // условный указатель для управления направлением
  // вращения вала двигателя, то есть +-1
  uint16_t supply_voltage;    // подаваемое напряжение
};

class Motor {
private:
  motorParams* dvParam;
  
public:
  Motor(motorParams *dvigatelParams) : dvParam(dvigatelParams) 
  {
    dvigatel_init();
  }
  
  void dvigatel_init() {
    pinMode(this->dvParam->motor_in_1, OUTPUT);
    pinMode(this->dvParam->motor_in_2, OUTPUT);
    pinMode(this->dvParam->motor_pwm,  OUTPUT);
  }

  void update_voltage_in_V(float u) {
    int16_t pwm = 255.0 * (u / dvParam->supply_voltage) * 1.0/*dvParam->motor_dir*/;
    pwm = constrain(pwm, -255.0, 255.0);
    
    
    if (pwm >= 0)
    {
      digitalWrite(this->dvParam->motor_in_1, HIGH);
      digitalWrite(this->dvParam->motor_in_2, LOW);
      analogWrite(this->dvParam->motor_pwm, pwm);
    }
    else
    {
      digitalWrite(this->dvParam->motor_in_1, LOW);
      digitalWrite(this->dvParam->motor_in_2, HIGH);
      analogWrite(this->dvParam->motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
    }
  }
};