#include "Encoder.h"

Encoder::Encoder(EncoderParams encoderParams)
{
    this->encoderParams = encoderParams; 
    this->counter = 0;
    this->enc_old = 0;
    this->phi = 0;
    this->tick = 0;
    this->w_moment_rad_s = 0;
    this->w_moment_tick = 0;

    encoder_init();
}

void Encoder::encoder_init() 
{
    noInterrupts(); // приостанавливаем прерывания

    // Инициализация пинов энкодера
    pinMode(encoderParams.enc_pin_a, INPUT);
    pinMode(encoderParams.enc_pin_b, INPUT);

    // Настройка прерываний энкодера
    PCICR |= 0b00000111; // включаем прерывание на порту B и D
    PCMSK0 |= 0b11110000; // включаем пины PB4 -- PB7  (PCINT4 -- PCINT7)
    PCMSK1 |= 0b00000110;
    PCMSK2 |= 0b11111111; // включаем пины (PCINT16 -- PCINT23)

    // Настройка таблицы переходов
    table[0b00][0b10] = encoderParams.enc_dir;
    table[0b10][0b11] = encoderParams.enc_dir;
    table[0b11][0b01] = encoderParams.enc_dir;
    table[0b01][0b00] = encoderParams.enc_dir;

    table[0b00][0b01] = -encoderParams.enc_dir;
    table[0b01][0b11] = -encoderParams.enc_dir;
    table[0b11][0b10] = -encoderParams.enc_dir;
    table[0b10][0b00] = -encoderParams.enc_dir;

    interrupts();
}

void Encoder::isr_handler()
{
    noInterrupts();

    uint16_t enc = encoderParams.get_AB();
    counter += table[enc_old][enc];
    
    enc_old = enc;

    interrupts();
}

float Encoder::get_phi()
{
  return phi;
}

void Encoder::enc_tick() {
  
  w_moment_tick = ((counter * 1.0) / encoderParams.ppr);
  
  tick += counter; 
  phi += counter * encoderParams.tick_to_rad;

  w_moment_rad_s = (phi - I) / encoderParams.T_sec;
  I += w_moment_rad_s * encoderParams.Ts_sec;
  counter = 0;
}

float Encoder::get_tick()
{
    return tick;
}

float Encoder::get_w_moment_rad()
{
  return w_moment_rad_s;
}

float Encoder::get_w_moment_tick()
{
  return w_moment_tick;
}

void Encoder::encZero()
{
    counter = 0; tick = 0; phi = 0; I = 0;
}
