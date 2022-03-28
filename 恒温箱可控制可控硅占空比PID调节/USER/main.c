#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "ds18b20.h"
#include "exti.h"
#include "oled.h"
#include "beep.h"
#include "pid.h"
//ALIENTEK Mini STM32开发板范例代码23
//DS18B20数字温度传感器实验
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{
	u8 key=0;
	int Temp_Error=0;  //温度误差值定义
	int temp_Val=300;  //温度设定值定义
	int last_temperature = 0;  //上一次温度值保存
  u8 temperature_str[70]=""; //温度值转化显示的字符串
	delay_init();	    				 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);  //使能相应接口的时钟，以及RCC_APB2Periph_AFIO
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     //禁用JTAG
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
	OLED_Init();				//OLED显示初始化
	KEY_Init();					//按键初始化
	/* PI参数设置 */
	kp=100;
	ki=0.1;
	
 	while(DS18B20_Init())	//DS18B20初始化	
	{
		OLED_ShowString(0,0,(u8 *)"DS18B20 Error!");
 		delay_ms(200);
	}
	OLED_ShowString(0,0,(u8 *)"DS18B20 OK!");

	while(DS18B20_Get_Temp() == 850);
	last_temperature = DS18B20_Get_Temp();
	
	EXTIX_Init();          //外部中断初始化，用于过零检测上升沿
	TIM4_Int_Init(999,719);//100Khz的计数频率，计数到1000为0.01ms 
	while(1)
	{		   
		key=KEY_Scan(1);		//得到键值
		if(key == 4)
			temp_Val =temp_Val+10;				//设置温度加一度
		if(key == 2)
			temp_Val =temp_Val-10;				//设置温度减一度
	 	
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
