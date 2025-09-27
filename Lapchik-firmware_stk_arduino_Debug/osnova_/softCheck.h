#pragma once
#include "SLOVAR.h"
#include "obekti.h"
// void uCheck(int n = 0)
// {
//     switch (n)
//     {
//     case -1:
//         for(float j = 0.0; j < 200.0; j+=0.1)
//         {
//             for(int i = 0; i < 6; i++)
//                 dvig[i].update_voltage_in_V(j); 
//         }
//         for(float j = 200.0; j > 0.0; j-=0.1)
//         {
//             for(int i = 0; i < 6; i++)
//                 dvig[i].update_voltage_in_V(j);
//         }

//     case 0:
//         for(int i = 0; i < 6; i++)
//         {
//             for(float j = 0.0; j < 200.0; j+=0.1)
//             {
//                 dvig[i].update_voltage_in_V(j);
//             }
//             for(float j = 200.0; j > 0.0; j-=0.1)
//             {
//                 dvig[i].update_voltage_in_V(j);
//             }
//         }
//         break;

//     case 1:
//         for(float j = 0.0; j < 200.0; j+=0.1)
//         {
//             dvig[0].update_voltage_in_V(j);
//         }
//         for(float j = 200.0; j > 0.0; j-=0.1)
//         {
//             dvig[0].update_voltage_in_V(j);
//         }
    

//     case 2:
//         for(float j = 0.0; j < 200.0; j+=0.1)
//         {
//             dvig[1].update_voltage_in_V(j);
//         }
//         for(float j = 200.0; j > 0.0; j-=0.1)
//         {
//             dvig[1].update_voltage_in_V(j);
//         }
    
//     case 3:
//         for(float j = 0.0; j < 200.0; j+=0.1)
//         {
//             dvig[2].update_voltage_in_V(j);
//         }
//         for(float j = 200.0; j > 0.0; j-=0.1)
//         {
//             dvig[2].update_voltage_in_V(j);
//         }

//     case 4:
//         for(float j = 0.0; j < 200.0; j+=0.1)
//         {
//             dvig[3].update_voltage_in_V(j);
//         }
//         for(float j = 200.0; j > 0.0; j-=0.1)
//         {
//             dvig[3].update_voltage_in_V(j);
//         }

//     case 5:
//         for(float j = 0.0; j < 200.0; j+=0.1)
//         {
//             dvig[4].update_voltage_in_V(j);
//         }
//         for(float j = 200.0; j > 0.0; j-=0.1)
//         {
//             dvig[4].update_voltage_in_V(j);
//         }
    
//     case 6:
//         for(float j = 0.0; j < 200.0; j+=0.1)
//         {
//             dvig[5].update_voltage_in_V(j);
//         }
//         for(float j = 200.0; j > 0.0; j-=0.1)
//         {
//             dvig[5].update_voltage_in_V(j);
//         }

//     default:
//         break;
//     }
// }