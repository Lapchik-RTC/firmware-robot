#pragma once
#include<Arduino.h>
float modc(float in, float modder)
{
    in = in + modder;
    while(in > modder * 0.5)
    {
        in = in - modder;
    }
    while(in < -modder * 0.5)
    {
        in = in + modder;
    }
    return in;
}

inline float Fc(float t, float phists) {
    return t*phists;
}

inline float Fr0(float t, float dydx) {
    return t*dydx;
}

inline float Fcomp(float ts, float phists, float dydx) {
    return Fc(ts*float(0.5), phists) - Fr0(ts*float(0.5), dydx);
}

inline float Fr(float t, float ts, float phists, float dydx) {
    return Fr0(t, dydx) + Fcomp(ts, phists, dydx);
}

inline float Fl(float t, float ts, float phists, float dydx) {
    return -Fr(-t, ts, phists, dydx);
}

/// @brief функция выбора отрезка в зависимости от фазы 
/// @param t - фаза(рад.)
/// @param tc - период функции(с.)
/// @param ts - период центрального отрезка(с.)
/// @param phis - 2 PI
/// @param phi0
/// @return 
inline float Ffull(float t, float tc, float ts, float phis, float phi0) {

    t = modc(t, tc);
    float out;
    float phists = phis/ts;
    if(t < -ts*float(0.5))
    {
        float dydx = (float(2*M_PI) - phis) / (tc - ts);
        out = Fl(t, ts, phists, dydx);
    }
    else if(t < ts*float(0.5))
    {
        out = Fc(t, phists);
    }
    else
    {
        float dydx = (float(2*M_PI) - phis) / (tc - ts);
        out = Fr(t, ts, phists, dydx);
    }
    return out + phi0;
}


/////////////////
