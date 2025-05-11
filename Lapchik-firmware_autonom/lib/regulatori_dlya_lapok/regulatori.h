#pragma once
#include<Arduino.h>
#include"Dvigatel.h"
#include"encoder.h"
#include "f.h"

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

///////////////// REGULATORI /////////////////
float ServoPrivod::PIreg(float err)
{
    float P = err * params.kpPI;
     
    float u = P + I;

    if (u == constrain(u, -params.maxU, params.maxU) || (err * u) < 0)
        I += err * params.Ts_sec * params.ki;

    return constrain(u, -params.maxU, params.maxU);
}

float ServoPrivod::Preg(float err){
  return constrain(err * params.kpP, -params.maxVel, params.maxVel);
}

void ServoPrivod::setGoalSpeed(float goalSpd)
{
  enc->enc_tick();
  float realSpd = enc->get_w_moment_rad();
  float u = PIreg(goalSpd - realSpd);
  motor->update_voltage_in_V(u);
}

void ServoPrivod::setGoalPos(float phi0, bool legDownEven = 0){
  float phi = enc->get_phi();
  float phi_err = phi0 - phi;
  phi_err = fmod(phi_err, 2*M_PI);
  
  if(perehodFix){
    phi_err = modc(phi_err, 2*M_PI);
  }
  if(legDownEven)
  {
    phi_err = modc(phi_err + M_PI, 2*M_PI);
  }
  float w0 = Preg(phi_err);

  setGoalSpeed(w0);
}