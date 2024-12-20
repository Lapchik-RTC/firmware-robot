// регуляторы:

#define ENC_DIR_PLUS 1 // условный указатель направления вращения вала двигателя,
// который можно указывать вручную
#define ENC_DIR_MINUS -1 // условный указатель направления вращения вала двигателя,
// который можно указывать вручную
#define KOLVO_ENC_TICK 48 // количество тиков датчика холла за 1 полный оборот
#define GEAR_RATIO 47   // передаточное отношение редуктора

struct MotorParameters {
    int8_t INA;
    int8_t INB;
    int8_t PWM;
    float ENCA;
    float ENCB;
    float ENC_PPR;
    float ke;

    MotorParameters(int8_t INA, int8_t INB, int8_t PWM, float ENCA, float ENCB, float ENC_PPR, float ke) : INA(INA), INB(INB), PWM(PWM), ENCA(ENCA), ENCB(ENCB), ENC_PPR(ENC_PPR), ke(ke) {}
};

class Motor : public MotorParameters {
    public:
        // Конструктор принимает ссылку на "объект" MotorParameters
        Motor(MotorParameters&) :                                     // не уверен в правильности и корректности написания этой строчки
        MotorParameters(INA, INB, PWM, ENCA, ENCB, ENC_PPR, ke) {}    // Передаем параметры в структуру 
        float setSpeed_tick(float set);
        float setSpeed_rad(float set);
        float getSpeed_tick();
        float getSpeed_rad();
        float setAngle_tick(float set);
        float setAngle_rad(float set);
        float getAngle_tick();
        float getAngle_rad();
        void write_tick();
        void write_rad();
        float PID_tick(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut);
        float PID_rad(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut);

        float oldErrd = 0;

    private:
    // тут что-то от старого кода:

        // bool usePIFlag = 1;
        // PIreg piReg;
        // Saturation speedLim;
        // RateLimiter ULim;
        // FOD speedFilter;
        // uint64_t timer = 0;
        // float getpoint = 0;
        // int8_t motorDir;
        // int encCounter = 0;
        // float pulses2rad;
        // float goalSpeed = 0, realSpeed = 0, angle = 0;
};

float Motor::getSpeed_tick() {
    return tcocol_w_tick();
}
float Motor::getSpeed_rad() {
    return tcocol_w_rad();
}

float Motor::setSpeed_tick(float setKolvoSeconds) {
    float setSpeed = setSpeed + 1;                                     // надо настраивать

    return setSpeed;
}
float Motor::setSpeed_rad(float setPhiSeconds) {
    float setSpeed = setSpeed + 1;                                     // надо настраивать

    return setSpeed;
}

float Motor::getAngle_tick() {
    return tcocol_tick();
}
float Motor::getAngle_rad() {
    return tcocol_rad();
}

float Motor::setAngle_tick(float setKolvo) {
    // рассчитываем требуемое положение в тиках при данном отклонении
    float setpoint = setpoint + map(setKolvo, -1, 1, -1, 1);         // надо настраивать

    return setpoint;
}
float Motor::setAngle_rad(float setPhi) {
    // рассчитываем требуемое положение в радианах при данном отклонении
    float setpoint = setpoint + map(setPhi, -1, 1, -1, 1);          // надо настраивать     

    return setpoint;
}

float Motor::PID_tick(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut) {
    // настраиваемый ПИД регулятор для подсчёта в тиках
    float err = setpoint - tcocol_tick();
    static float integral = 0, oldErr = 0;
    static float dt = (micros() - dt);
    integral = constrain(integral + (float)err * dt * ki, minOut, maxOut);
    float D = (err - oldErr) / dt;
    oldErr = err;
    dt = micros();
    return constrain(err * kp + integral + D * kd, minOut, maxOut);
}
float Motor::PID_rad(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut) {
    // настраиваемый ПИД регулятор для подсчёта в радианах
    float err = setpoint - tcocol_rad();
    static float integral = 0, oldErr = 0;
    integral = constrain(integral + (float)err * dt * ki, minOut, maxOut);
    float D = (err - oldErr) / dt;
    oldErr = err;
    return constrain(err * kp + integral + D * kd, minOut, maxOut);
}

void Motor::write_tick() {
    float res = map(PID_tick(1, 1, 1, 1, 1, 1, 1, 1), -1, 1, -255, 255);
    tcocol(res);
}