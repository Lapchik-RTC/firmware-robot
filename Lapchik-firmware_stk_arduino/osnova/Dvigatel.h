#pragma once
#include<Arduino.h>

struct DvigatelParams
{ 
  uint16_t motor_in_1;        // пин, отвечающий за направление
  uint16_t motor_in_2;        // пин, отвечающий за направление
  uint16_t motor_pwm;         // пин ШИМ
  int16_t  motor_dir;         // условный указатель для управления направлением
  // вращения вала двигателя, то есть +-1
  uint16_t supply_voltage;    // подаваемое напряжение
};

class Dvigatel {
private:
  DvigatelParams dvigatelParams;
  
public:
  Dvigatel(DvigatelParams dvigatelParams);

  void update_voltage_in_V(float u);
};