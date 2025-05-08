#include "dvig.h"

void motorDriver::encZero()
{
    counter = 0; tick = 0; phi = 0; I = 0;
}

void motorDriver::encoder_init()
{
        noInterrupts(); // приостанавливаем прерывания
        // Инициализация пинов энкодера
        pinMode(mParam.enc_pin_a, INPUT);
        pinMode(mParam.enc_pin_b, INPUT);
    
        // Настройка прерываний энкодера
        PCICR |= 0b00000111; // включаем прерывание на порту B и D
        PCMSK0 |= 0b11110000; // включаем пины PB4 -- PB7  (PCINT4 -- PCINT7)
        PCMSK1 |= 0b00000110;
        PCMSK2 |= 0b11111111; // включаем пины (PCINT16 -- PCINT23)
    
        // Настройка таблицы переходов
        table[0b00][0b10] = mParam.enc_dir;
        table[0b10][0b11] = mParam.enc_dir;
        table[0b11][0b01] = mParam.enc_dir;
        table[0b01][0b00] = mParam.enc_dir;
    
        table[0b00][0b01] = -mParam.enc_dir;
        table[0b01][0b11] = -mParam.enc_dir;
        table[0b11][0b10] = -mParam.enc_dir;
        table[0b10][0b00] = -mParam.enc_dir;
    
        interrupts();
}

void motorDriver::enc_tick() {
        
    w_moment_tick = ((counter * 1.0) / mParam.ppr);
    
    tick += counter; 
    phi += counter * mParam.tick_to_rad;

    w_moment_rad_s = (phi - I) / mParam.T_sec;
    I += w_moment_rad_s * mParam.Ts_sec;

    counter = 0;
}

void motorDriver::isr_handler() {
    noInterrupts();
    uint16_t enc = mParam.get_AB();
    
    counter += table[enc_old][enc];
    
    enc_old = enc;
    interrupts();
}

//////////////////////////////////////

void motorDriver::dvigatel_init() {
    pinMode(this->mParam.motor_in_1, OUTPUT);
    pinMode(this->mParam.motor_in_2, OUTPUT);
    pinMode(this->mParam.motor_pwm,  OUTPUT);
}

void motorDriver::update_voltage_in_V(float u) {
    int16_t pwm = 255.0 * (u / mParam.supply_voltage) * 1.0/*mParam.motor_dir*/;
    pwm = constrain(pwm, -255.0, 255.0);

    if (pwm >= 0)
    {
      digitalWrite(this->mParam.motor_in_1, HIGH);
      digitalWrite(this->mParam.motor_in_2, LOW);
      analogWrite(this->mParam.motor_pwm, pwm);
    }
    else
    {
      digitalWrite(this->mParam.motor_in_1, LOW);
      digitalWrite(this->mParam.motor_in_2, HIGH);
      analogWrite(this->mParam.motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
    }
}