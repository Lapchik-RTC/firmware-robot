#pragma once
#include<Arduino.h>
//#include<SLOVAR>
#include"motor.h"
#include"encoder.h"


struct MotorControlParams//структура общая
{
  float Ts_sec;
  float kpPI;
  float ki;
  float maxI;
  float kpP;
  float kalibrSpeed;
};

///////////////////////   ServoPrivod   ///////////////////////
class ServoPrivod: public MotorControlParams, public Dvigatel, public Encoder
{
  private:
  float realSpeed, realAngle;
  Dvigatel &motor;
  Encoder &enc;
  float &I;
  float PIreg(float err);
  //inline float Preg(float err);

  public:
  ServoPrivod(MotorControlParams *mconp, Dvigatel &motor, Encoder &enc, float &I) 
  : MotorControlParams(*mconp), Dvigatel(motor), Encoder(enc), I(I) {
    
  }
  float setGoalSpeed(float goalSpeed, float realSpd);//rad/s
};

///////////////// REGULATORI /////////////////
float ServoPrivod::PIreg(float err)
{
    float P = err * kpPI;
    I += err * 1.0 * Ts_sec*ki;
    //I = I*ki;
    I = min(I, maxI)*1.0;
    // Imas[this->ImasNum] += err * ki * Ts;
    //if (I > maxI) { I = I/2.0; }
    
    Serial.print("\t err: ");
    Serial.print(err);
    Serial.print("\t P: ");
    Serial.print(P+I);
    return P + I;
}

float ServoPrivod::setGoalSpeed(float goalSpd, float realSpd)
{
  float u = PIreg(goalSpd - realSpd);
  return u;
}







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// struct localSlovar{
//   byte inA;
//   byte inB;
//   byte pwmPin;
//   int ppr;
//   int dir;
// };
// struct globalSlovar{
//   float maxSpeed;
//   float kp;
//   float ki;
//   float Ts;
// };
// /// @brief CLASS 2   ////////////////////////////////////////////////////////////
// class Lapka: localSlovar, globalSlovar, Encoder
// {
//   public:
//   Lapka(localSlovar *ls, globalSlovar *gs, Encoder &enc)
//   :localSlovar(*ls), globalSlovar(*gs), Encoder(enc)
//   {
//     pinMode(inA, 1);
//     pinMode(inB, 1);
//     this->enc = enc;
//   }

//   private:
//   Encoder &enc;
//   void power(float u);
//   void serv(float err);

// };

// void Lapka::power(float u)
// {
//     float pwm = 255 * (u / maxSpeed)*dir;
//     digitalWrite(inA, (pwm > 0));
//     digitalWrite(inB, !(pwm > 0));
//     analogWrite(pwmPin, min(abs(pwm), 255));
// }

// void Lapka::serv(float err)
// {
//   int p = err * kp;
//   float u = p;
//   return u
// }