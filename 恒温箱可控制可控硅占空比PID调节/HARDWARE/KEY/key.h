#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) //��ȡ����0
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) //��ȡ����1
#define KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//��ȡ����2 
#define KEY4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//��ȡ����3

 

#define KEY1_PRES 	1	//KEY0����
#define KEY2_PRES	  2	//KEY1����
#define KEY3_PRES  	3	//KEY2����
#define KEY4_PRES   4	//KEY3����


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
