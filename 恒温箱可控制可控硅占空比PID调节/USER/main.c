#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "ds18b20.h"
#include "exti.h"
#include "oled.h"
#include "beep.h"
#include "pid.h"
//ALIENTEK Mini STM32�����巶������23
//DS18B20�����¶ȴ�����ʵ��
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

int main(void)
{
	u8 key=0;
	int Temp_Error=0;  //�¶����ֵ����
	int temp_Val=300;  //�¶��趨ֵ����
	int last_temperature = 0;  //��һ���¶�ֵ����
  u8 temperature_str[70]=""; //�¶�ֵת����ʾ���ַ���
	delay_init();	    				 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);  //ʹ����Ӧ�ӿڵ�ʱ�ӣ��Լ�RCC_APB2Periph_AFIO
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     //����JTAG
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	OLED_Init();				//OLED��ʾ��ʼ��
	KEY_Init();					//������ʼ��
	/* PI�������� */
	kp=100;
	ki=0.1;
	
 	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		OLED_ShowString(0,0,(u8 *)"DS18B20 Error!");
 		delay_ms(200);
	}
	OLED_ShowString(0,0,(u8 *)"DS18B20 OK!");

	while(DS18B20_Get_Temp() == 850);
	last_temperature = DS18B20_Get_Temp();
	
	EXTIX_Init();          //�ⲿ�жϳ�ʼ�������ڹ�����������
	TIM4_Int_Init(999,719);//100Khz�ļ���Ƶ�ʣ�������1000Ϊ0.01ms 
	while(1)
	{		   
		key=KEY_Scan(1);		//�õ���ֵ
		if(key == 4)
			temp_Val =temp_Val+10;				//�����¶ȼ�һ��
		if(key == 2)
			temp_Val =temp_Val-10;				//�����¶ȼ�һ��
	 	
		temperature=DS18B20_Get_Temp();
		if(abs(temperature - last_temperature)>5)
			continue;
		
		sprintf((char *)temperature_str,"Set_T:%.1f C  ",temp_Val/10.0);
		OLED_ShowString(0,0,temperature_str);
		
		sprintf((char *)temperature_str,"Temp :%.1f C  ",temperature/10.0);
		OLED_ShowString(0,2,temperature_str);

		Regulate_Temperature(temperature,temp_Val);	
		sprintf((char *)temperature_str,"T_Out:%.1f",(Temp_Out-70)*0.12);
		OLED_ShowString(0,4,temperature_str);
		
//		sprintf((char *)temperature_str,"%.1f#",temperature/10.0);
//		printf(temperature_str);
		last_temperature = temperature;
		delay_ms(100);
	}
}
