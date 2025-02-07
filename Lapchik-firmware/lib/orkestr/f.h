#pragma once

float modc(float in, float modder)
{
    in = in + modder;
    while(in > modder * 0.5)
    {
        in = in - modder;
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
//////////////////////////////////////////////////////////////////

struct F_h
{
    public:
    float t_c = 8;
    float t_s = 4.6;
    float phi_s = 1.5;
    float phi_0 = 0;
    void Phi0Stp(){phi_0 += M_PI;}
    float tt = 0;
    float ff(float vel)
    {
        if(tt < (-(t_s/2)))
        {}
        else if(tt > (-(t_s/2)))
        {}
        else if(tt > ((t_s/2)))
        {}
    }
    private:
    float d_x;
    float d_y;
    float fc(float x) {return( x * (phi_s/t_s) );}
    float fr0(float x) {return( x * (d_y/d_x) );}
    float fr(float x) {return( fr0(x)+( fc(t_s/2)-fr0(t_s/2) ));}
    float fl(float x) {return( -fr(-x) );}
};


// inline float Fc(float t, float phists) {
//     return t*phists;
// }

// inline float Fr0(float t, float dydx) {
//     return t*dydx;
// }

// inline float Fcomp(float ts, float phists, float dydx) {
//     return Fc(ts*float(0.5), phists) - Fr0(ts*float(0.5), dydx);
// }

// inline float Fr(float t, float ts, float phists, float dydx) {
//     return Fr0(t, dydx) + Fcomp(ts, phists, dydx);
// }

// inline float Fl(float t, float ts, float phists, float dydx) {
//     return -Fr(-t, ts, phists, dydx);
// }

// inline float Ffull(float t, float tc, float ts, float phis, float phi0) {

//     t = modc(t, tc);
//     float out;
//     float phists = phis/ts;
//     if(t < -ts*float(0.5))
//     {
//         float dydx = (float(2*M_PI) - phis) / (tc - ts);
//         out = Fl(t, ts, phists, dydx);
//     }
//     else if(t < ts*float(0.5))
//     {
//         out = Fc(t, phists);
//     }
//     else
//     {
//         float dydx = (float(2*M_PI) - phis) / (tc - ts);
//         out = Fr(t, ts, phists, dydx);
//     }
//     return out + phi0;
// }