
#include "C:\!projects\lapchik\firmware-robot\Lapchik-firmware_autonomRe\lib\tsokol\regulatori_dlya_lapok\regulatori.h"

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