#pragma onse
#include <Arduino.h>
#include "SLOVAR.h"
#include "f.h"
#include "motorDriver.h"
#include "encDriver.h"

class Dvigatel
{
    public:
    Dvigatel(Motor *_motor, Encoder *_encoder): motor(_motor), encoder(_encoder){}

    void setSpd(float vel);
    void setPos(float pos);

    private:
    Motor *motor;
    Encoder *encoder;

    float PIreg(float err);
    float Preg(float err);
    float I = 0.0;

};

void Dvigatel::setPos(float pos)
{
    float phi = encoder->getPhi();
    float phi_err = pos - phi;

    phi_err = modc(phi_err, 2*M_PI);

    float w0 = Preg(phi_err);
    setSpd(w0);
}

void Dvigatel::setSpd(float vel)
{
    float realSpd = encoder->getSpd();
    float u = PIreg(vel - realSpd);
    motor->update_voltage_in_V(u);
}

float Dvigatel::PIreg(float err)
{
    float P = err * PIreg_KP;
     
    float u = P + I;

    if (u == constrain(u, -SUPPLY_VOLTAGE, SUPPLY_VOLTAGE) || (err * u) < 0)
        I += err * Ts_s * PIreg_KI;

    return constrain(u, -SUPPLY_VOLTAGE, SUPPLY_VOLTAGE);
}

float Dvigatel::Preg(float err)
{
    return constrain(err * Preg_KP, -SUPPLY_VOLTAGE, SUPPLY_VOLTAGE);
}