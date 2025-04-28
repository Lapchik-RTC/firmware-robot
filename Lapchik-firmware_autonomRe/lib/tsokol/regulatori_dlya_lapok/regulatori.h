#pragma once
#include<Arduino.h>
// #include "SLOVAR.h"
#include "C:\!projects\lapchik\firmware-robot\Lapchik-firmware_autonomRe\lib\tsokol\nizhnii_uroven_upravlenia_platformoi\encoder.h"
#include "C:\!projects\lapchik\firmware-robot\Lapchik-firmware_autonomRe\lib\tsokol\nizhnii_uroven_upravlenia_platformoi\Dvigatel.h"
#include "C:\!projects\lapchik\firmware-robot\Lapchik-firmware_autonomRe\include\SLOVAR.h"
#include "orkestr/f.h"

struct MotorControlParams//структура общая
{
  float Ts_sec;
  float kpPI;
  float ki;
  float maxU; // Максимальное напряжение на двигателе
  float kpP;
  float maxVel; // Максимальная угловая скорость
  float kalibrSpeed;
};

///////////////////////   ServoPrivod   ///////////////////////
class ServoPrivod
{
private:
  float realSpeed, realAngle;
  MotorControlParams params;
  Dvigatel *motor;
  Encoder *enc;
  float I;
  float PIreg(float err);
  float Preg(float err);
  
public:
  ServoPrivod(MotorControlParams mconp, Dvigatel *motor, Encoder *enc) {
    this->params = mconp;
    this->motor = motor;
    this->enc = enc;
  }
  void setGoalPos(float goalPos_tick, bool legDownEven = 0);
  void setGoalSpeed(float goalSpeed);//rad/s
};