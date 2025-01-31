#pragma once
#include<Arduino.h>
//#include<SLOVAR>
#include"motor.h"
#include"encoder.h"

#define KP_PI 0.2//0.06
#define KI_PI 0//0.05//2.1//5
#define KP_P 1
#define KE 0.2



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
  inline float Preg(float err);
  
  public:
  float setPoint(float goalPos_tick, float phi);
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
    
    // Serial.print("\t err: ");
    // Serial.print(err);
    // Serial.print("\t P: ");
    // Serial.print(P+I);
    return P + I;
}

float ServoPrivod::setGoalSpeed(float goalSpd, float realSpd)
{
  float u = PIreg(goalSpd - realSpd);
  return u+(goalSpd*KE);
}

inline float ServoPrivod::Preg(float err){
  return err * kpP;
}

float ServoPrivod::setPoint(float phi0, float phi){
  float phi_err = phi0 - phi;
  float w0_raw = Preg(phi_err);
  float w0 = constrain(w0_raw,-8.0, 8.0/*-w_max, w_max*/);
  
  Serial.print("\t err(setPoint): ");
  Serial.print(w0);
  Serial.print('\t');
  
  return w0;

}