#include"regulatori.h"
//////////////   Motor   //////////////
Motor::Motor(MotorConnectParams *mconp, MotorControlParams *mctrlp):MotorConnectParams(*mconp), MotorControlParams (*mctrlp)
{
    pinMode(INA, 1);
    pinMode(INB, 1);
}

Motor::PI