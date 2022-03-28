#include "pid.h"
#include "oled.h"
#include "led.h"
#include "usart.h"

float kp,ki;
int Temp_Out=100;
void Regulate_Temperature(int Current_Temp,int Set_Temp)
{
	u8 str[70]="";
	static int Temp_Integral=0;//�¶Ȼ���
	int Temp_Error;//�¶����
	u8 i;
	Temp_Error=Set_Temp-Current_Temp;
	if(Temp_Error>(-100)&&Temp_Error<100)
	Temp_Integral+=Temp_Error;
	Temp_Out=(Temp_Error*kp+Temp_Integral*ki)/10+100;
//Temp_Out   �ض�ʱ��
	if(Temp_Out<PID_MIN)  Temp_Out=PID_MIN;//�޷�
	if(Temp_Out>PID_MAX)  Temp_Out=PID_MAX;	
//	sprintf(str,"��ͨʱ��:%d     ��ǰ�²�:%d   ����:%d   \r\n",Temp_Out,Temp_Error,Temp_Integral);
//	printf(str);
//	sprintf(str,"��ͨʱ��:%d     ��ǰ�²�:%d   ����:%d   \r\n",Temp_Out,Temp_Error,Temp_Integral);
//	printf(str);
}
	
	