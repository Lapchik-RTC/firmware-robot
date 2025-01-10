// Encoder.h

struct EncoderParams
{
    int8_t (*get_AB)();
    //.....
};

class ENC
{
private:
    int counter;
    float angle;
    EncoderParams en_par;
public:
    ENC(EncoderParams en_par_)
    {
        en_par = en_par_;
    }
    void init();
    void tick();
    void isr_handler();
}

void ENC::init()
{
    // pinMode()
    // ett = ...
    // interrupts();
}

void ENC::tick()
{
    noInterrupts();
    int counter_buf = count;
    interrupts();

    angle += counter_buf * TICKS_TO_RAD;
}

void ENC::isr_handler()
{
    int8_t AB = (*en_par.get_AB)(); //...

    int8_t dir = AB;

    counter += dir;
}

// Devices.h
//  or
// Globals.h

int8_t get_AB_enc1()
{
    return ((*ENC_PORT) & ENC_MASK) >> ENC_SHIFT;
}

int8_t get_AB_enc2()
{
    return digitalRead(2) << 1 | digitalRead(56);
}

EncoderParams enpar1 = {.get_AB = get_AB_enc1};
EncoderParams enpar2 = {.get_AB = get_AB_enc2};
EncoderParams enpar3, enpar4, enpar5, enpar6;

ENC enc1(enpar1), enc2(enpar2), enc3(enpar3), enc4(enpar4), enc5(enpar5), enc6(enpar6);

ISR(PCINT0_vec)
{
    enc1.isr_handler();
    enc2.isr_handler();
    enc3.isr_handler();
    enc4.isr_handler();
}

ISR(PCINT1_vec)
{
    enc5.isr_handler();
    enc6.isr_handler();
}
