#pragma once
#include<Arduino.h>
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

/// @brief функция выбора отрезка в зависимости от фазы 
/// @param t 
/// @param tc 
/// @param ts 
/// @param phis 
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


//////////////////////////////////////////////////////////////////

// class F_h
// {
//     public:
//     float t_c = 8;
//     float t_s = 4.6;
//     float phi_s = 1.5;
//     float phi_0 = 0;
//     void Phi0Stp(){phi_0 += M_PI;}
//     float tt = 0;
//     float ff(float vel)
//     {
//         if(tt < (-(t_s/2)))
//         {
//             fl(tt);
//         }
//         else if(tt > (-(t_s/2)))
//         {
//             fc(tt);
//         }
//         else if(tt > ((t_s/2)))
//         {
//             fr(tt);
//         }
//     }
    
//     private:
//     float d_x = (t_c - t_s)/2;
//     float d_y = M_PI - (phi_s/2);
//     float fc(float x) {return( x * (phi_s/t_s) );}
//     float fr0(float x) {return( x * (d_y/d_x) );}
//     float fr(float x) {return( fr0(x)+( fc(t_s/2)-fr0(t_s/2) ));}
//     float fl(float x) {return( -fr(-x) );}
//};

// float f(float angle)
// {
//     angle = (angle % (2*M_PI));
//     if (abs(angle) > M_PI) 
//         angle-= 2 * M_PI;

// }




// float fc_(float t, float phists) {
//     return t*phists;
// }

// float fr0_(float t, float dydx) {
//     return t*dydx;
// }

// float fr_(float t, float ts, float phists, float dydx) {
//     return fr0_(t, dydx) + (fc_(ts*float(0.5), phists) - fr0_(ts*float(0.5), dydx))/*Fcomp(ts, phists, dydx)*/;
// }

// float fl_(float t, float ts, float phists, float dydx) {
//     return -fr_(-t, ts, phists, dydx);
// }

// //////////////////////////////////////

// float Fc(float t, float tc, float phists, int i){
//     return ( fc_(t - (tc*i), phists)+M_PI ); 
// }

// float Fr0(float t, float tc, float dydx, float i){
//     return ( fr0_(t - (tc*i), dydx)+M_PI );
// }

// float Fr( float t, float tc, float ts, float phists, float dydx, int i){
//     return ( fr_(t - (tc*i), ts, phists, dydx) + M_PI );
// }

// float Fl( float t, float tc, float ts, float phists, float dydx, int i){
//     return ( fl_(t - (tc*i), ts, phists, dydx) + M_PI );
// }

// float F_shtrih(int t, int tc, float ts, float phiS, float phi0)
// { 
//     static int i = 0;
//     static float ts_i = ts;
//     static float tc_i = tc;
//     //tc_i = tc_i - (tc*i);
//     //ts_i = ts_i - ((tc*i)+ts/2);
//     //i = (t / tc_i) - (t % (int)tc_i);
//     float phists = phiS/ts_i;
//     float dydx = (M_PI - (phiS/2)) / ((tc_i-ts_i)/2);

//     float out;
//     t = t - (tc*i);
//     if(t < -(ts_i * 0.5)) 
//         out = fl_(t, tc_i, /*ts_i,*/ phists, dydx/*, i*/);
//     else if(t < (ts_i * 0.5)) 
//         out = fc_(t, /*tc_i,*/ phists/*, i*/);
//     else if(t < (ts_i * 0.5)) 
//         out = fr_(t, tc_i/*, ts_i*/, phists, dydx/*, i*/);
    
//     Serial.print("\ti: ");
//     Serial.print(i);
//     Serial.print('\t');
//     return out;
// }

//-------------------------------------------------------

    // public:
    // float t;
    // float tc = 7.3;
    // float ts = 4.4;
    // float phi_s = 1.6;
    // float phi_0 = 0;
    // float out;
    // float Fr0(float t)
    // {
    //     out = (t * ( ( M_PI-(phi_s/2) )/(  ) )) - (tc/2);        
    //     return out + M_PI;
    // }
    // float Fr(float t)
    // {
    //     out = t - (tc/2);
        
    //     return out + M_PI;
    // }
    // float Fc(float t)
    // {
    //     out = t - (tc/2);
    //     out = t * (phi_s/ts);
    //     return out + M_PI;
    // }

    // float Fl(float t)
    // {
    //     out = t - (tc/2);

    //     return out + M_PI;
    // }
    ////////////////////////////////////////////////////
    