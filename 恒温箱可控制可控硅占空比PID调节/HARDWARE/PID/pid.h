#ifndef __PID_H
#define __PID_H
#include "sys.h"
extern float kp,ki;
extern int Temp_Out;
#define PID_MAX 900
#define PID_MIN 70

void Regulate_Temperature(int Current_Temp,int Set_Temp);
#endif



