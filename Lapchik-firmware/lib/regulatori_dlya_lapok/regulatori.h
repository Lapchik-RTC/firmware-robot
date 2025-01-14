#pragma once
#include<Arduino.h>
//#include<SLOVAR>
#include"tcokol.h"
struct MotorControlParams
{
  float Ts;
  int ppr;
  //reg params
  float kpPI;
  float ki;
  float maxI;
  float kpP;
  //kalibr params
  byte csPin;
  int csEdge;
  float kalibrSpeed;
};

///////////////////////   ServoPrivod   ///////////////////////
class ServoPrivod: MotorControlParams
{
  public:
  ServoPrivod(MotorControlParams *mconp, Dvigatel *motor, Encoder *enc);
  void setAngle(float goalAngle);//rad
  inline void setGoalSpeed(float goalSpeed);//rad/s
  float getRealSpeed();

  private:
  float realSpeed, realAngle;
  Dvigatel *motor;
  Encoder *enc;
  
  void kalibrovka();
  float PIreg(float err);
  inline float Preg(float err);
};

ServoPrivod::ServoPrivod(MotorControlParams *mconp, Dvigatel *motor, Encoder *enc)
:MotorControlParams(*mconp)
{
 this->motor = motor;
 this->enc = enc;
 enc->tick = 0;
 kalibrovka();
}

///////////////// kalibrovka /////////////////
void ServoPrivod::kalibrovka()
{
  while (analogRead(csPin) < csEdge)
  {
    for(int i = 0; i < kalibrSpeed; i + 0.2)
    {
      setGoalSpeed(i);
    }
  }
  setGoalSpeed(0);
  enc->tick = 0;
  this->realAngle = 0;
}

///////////////// REGULATORI /////////////////
float ServoPrivod::PIreg(float err)
{
    static float P, I = 0;
    P = err * kpPI;
    I = I + err * ki * Ts_s;
    if (I > maxI) { I = maxI; }
    return P + I;
}

inline float ServoPrivod::Preg(float err)
{
  return err * kpP;
}

///////////////// SET /////////////////
inline void ServoPrivod::setGoalSpeed(float goalSpeed)
{
  float u = PIreg(goalSpeed - getRealSpeed());
  motor->update_speed_in_rad(u);
}

void ServoPrivod::setAngle(float goalAng)
{
  
}

///////////////// GET /////////////////
float ServoPrivod::getRealSpeed(){
  static int count = 0;
  static int32_t encCounter = 0;
  static int32_t timer = millis();
  
  timer = millis();
  while (millis() - timer < 10) {
    noInterrupts();
    count = enc->tick;
    enc->tick = 0;
    interrupts();
    encCounter += count;
  }
  realSpeed = 200.0 * M_PI * (encCounter * 1.0 / this->ppr);/*ENC_PPR450*/  //скорость в радиранах за 10 милисекунд
  encCounter = 0.0;
  timer = millis();
  return realSpeed;
}