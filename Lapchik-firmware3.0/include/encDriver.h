#pragma once
#include <Arduino.h>
#include "SLOVAR.h"
#include "f.h"


struct EncoderParams
{
    byte pinA;
    byte pinB;
    int8_t dir;
    uint16_t tick2rad;
    uint16_t ppr;
    uint8_t (*eCond)(void);

    byte hallPin;
    float tickWhanHall;
};
class Encoder
{
    public:
    Encoder(EncoderParams *encParams):eParam(encParams)
    {
        // Отключение прерываний на время работы с регистрами
        noInterrupts();

        // Объявление пинов энкодера как входов
        pinMode(this->eParam->pinA, INPUT);
        pinMode(this->eParam->pinB, INPUT);

        PCICR |= 0b00000111; // включаем прерывание на порту B и D
        PCMSK0 |= 0b11110000; // включаем пины PB4 -- PB7  (PCINT4 -- PCINT7)
        PCMSK1 |= 0b00000110;
        PCMSK2 |= 0b11111111; // включаем пины (PCINT16 -- PCINT23)

        // Настройка таблицы переходов
        ett[0b00][0b01] = -this->eParam->dir;
        ett[0b01][0b11] = -this->eParam->dir;
        ett[0b11][0b10] = -this->eParam->dir;
        ett[0b10][0b00] = -this->eParam->dir;

        ett[0b00][0b10] = this->eParam->dir;
        ett[0b10][0b11] = this->eParam->dir;
        ett[0b11][0b01] = this->eParam->dir;
        ett[0b01][0b00] = this->eParam->dir;

        // Включение прерываний для запуска энкодера
        interrupts();
    }

    void Tick();

    void encZero(){ tick = 0; phi = 0.0; rotErr = 0.0; corr = 0.0;};

    float getPhi(){ return phi; }
    float getMPhi(){ return modc(phi, 2.0*M_PI); }
    int64_t getTick(){ return tick; }
    float getSpd() { return rSpd; }

    private:
    EncoderParams *eParam;

    int8_t ett[4][4] = {0};
    volatile int16_t counter = 0; // [ticks]
    int8_t encOld = 0, enc = 0;
    void isrHeandler();

    int64_t tick = 0;
    float phi = 0.0;

    uint16_t lastHallDetect = millis();
    float rotErr = 0.0, corr = 0.0;

    float rSpd = 0.0, I = 0.0;
}; 


void Encoder::isrHeandler()
{
    noInterrupts();
    // Считывание текущей фазы энкодера
    enc = eParam->eCond();
    interrupts();

    // Инкремент счетчика согласно таблице переходов
    counter += ett[encOld][enc];

    // Сохранение фазы энкодера
    encOld = enc;
}

void Encoder::Tick()
{
    // Отключение прерываний для чтения 16 битного числа
    noInterrupts();
    int16_t counter_buff = counter;
    counter = 0;
    interrupts();

    if( (digitalRead(eParam->hallPin) == 0) && (millis() - lastHallDetect > TIME_WITHOUT_HALL) )
    {
        rotErr += ( eParam->tickWhanHall - (modc(tick, eParam->ppr)) );
        lastHallDetect = millis();
    }
    corr = constrain(rotErr, -MAX_TICK_CORR, MAX_TICK_CORR);
    counter_buff += corr;
    rotErr -= corr;

    tick += counter_buff;
    phi += counter_buff * eParam->tick2rad;
    rSpd = (phi - I) / Ts_s;
    I = rSpd * Ts_s;
}