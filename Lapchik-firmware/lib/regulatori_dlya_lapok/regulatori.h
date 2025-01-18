#pragma once
#include<Arduino.h>
//#include<SLOVAR>
#include"motor.h"
#include"encoder.h"
//#pragma once
// struct MotorConRegParams//структура для каждого
// {
//   byte csPin;
//   int csKalibr;
//   int *enc;
//   int ppr;
// };


struct MotorControlParams//структура общая
{
  float Ts;
  float kpPI;
  float ki;
  float maxI;
  float kpP;
  float kalibrSpeed;
};

///////////////////////   ServoPrivod   ///////////////////////
class ServoPrivod: public MotorControlParams, public Dvigatel, public Encoder
{
  public:
  ServoPrivod(MotorControlParams *mconp, /*MotorConRegParams *mcrp, */Dvigatel &motor, Encoder &enc);
  
  void setAngle(float goalAngle);//rad
  inline void setGoalSpeed(float goalSpeed);//rad/s
  float getRealSpeed();
  float getRealAngle();

  private:
  float realSpeed, realAngle;
  Dvigatel &motor;
  Encoder &enc;
  //int32_t *globalEnc;
  float ppr = 440.0;
  //void kalibrovka();
  float PIreg(float err);
  inline float Preg(float err);
  //float modc(float in, float modder);
};

ServoPrivod::ServoPrivod(MotorControlParams *mconp,/* MotorConRegParams *mcrp,*/ Dvigatel &motor, Encoder &enc)
:MotorControlParams(*mconp), Dvigatel(motor), Encoder(enc)

//,
//MotorConRegParams(*mcrp)
{
 //this->motor = motor;
 //this->enc = enc;
 //this->globalEnc = enc;
 //kalibrovka();
}

///////////////// kalibrovka /////////////////
/*void ServoPrivod::kalibrovka()
{
  while (analogRead(csPin) < csEdge)
  {
    setGoalSpeed(-kalibrSpeed);
  }
  for(int i = 0; i < kalibrSpeed; i + 0.2)
  {
    setGoalSpeed(-i);
  }
  setGoalSpeed(0);
  enc->tick = 0;
  this->realAngle = 0;
}
*/
///////////////// REGULATORI /////////////////
float ServoPrivod::PIreg(float err)
{
    static float P, I = 0;
    P = err * kpPI;
    I = I + err * ki * Ts;
    if (I > maxI) { I = maxI; }
    return P + I;
}

inline float ServoPrivod::Preg(float err)
{
  return err * kpP;
}
/*
float modc(float in, float modder)
{
    in = in + modder;
    while(in > modder * 0.5)
    {
        in = in - modder;
    }
    return in;
}
*/
///////////////// SET /////////////////
inline void ServoPrivod::setGoalSpeed(float goalSpeed)
{
  float u = PIreg(goalSpeed - enc.get_w_moment_rad()/*getRealSpeed()*/);
  motor.update_speed_in_rad(u);
}

void ServoPrivod::setAngle(float goalAng)
{
  //realSpeed = getRealSpeed();
  //if(enc->get_tick() % ppr == 0){enc = 0;}
  //realAngle = (enc->get_tick() / ppr) * 2 * M_PI;
  float u = Preg(goalAng - enc.get_phi());
  setGoalSpeed(u);  
}

///////////////// GET /////////////////
// float ServoPrivod::getRealSpeed()
// {
//   static int count = 0;
//   static int32_t encCounter = 0;
//   static int32_t timer = millis();
  
//   timer = millis();
//   while (millis() - timer < 10) {
//     noInterrupts();
//     count = enc.get_tick();
//     enc.get_tick = 0;
//     interrupts();
//     encCounter += count;
//   }
//   realSpeed = 200.0 * M_PI * (encCounter * 1.0 / ppr);/*ENC_PPR450*/  //скорость в радиранах за 10 милисекунд
//  // enc += encCounter;
//   encCounter = 0.0;
//   timer = millis();
//   return realSpeed;
// }

// float ServoPrivod::getRealAngle()
// {
  
// }