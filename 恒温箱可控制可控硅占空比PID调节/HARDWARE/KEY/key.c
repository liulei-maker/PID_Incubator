#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEKÕ½½¢STM32¿ª·¢°å
//°´¼üÇý¶¯´úÂë	   
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ÐÞ¸ÄÈÕÆÚ:2012/9/3
//°æ±¾£ºV1.0
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//°´¼ü³õÊ¼»¯º¯Êý
void KEY_Init(void) //IO³õÊ¼»¯
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB,ENABLE);//Ê¹ÄÜPORTA,PORTEÊ±ÖÓ

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ÉèÖÃ³ÉÉÏÀ­ÊäÈë
 	GPIO_Init(GPIOC,&GPIO_InitStructure);        //³õÊ¼»¯GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//KEY0-KEY2
 	GPIO_Init(GPIOB,&GPIO_InitStructure);        //³õÊ¼»¯GPIOE2,3,4	
	
}
//°´¼ü´¦À íº¯Êý
//·µ»Ø°´¼üÖµ
//mode:0,²»Ö§³ÖÁ¬Ðø°´;1,Ö§³ÖÁ¬Ðø°´;
//0£¬Ã»ÓÐÈÎºÎ°´¼ü°´ÏÂ
//1£¬KEY0°´ÏÂ
//2£¬KEY1°´ÏÂ
//3£¬KEY2°´ÏÂ 
//4£¬KEY3°´ÏÂ WK_UP
//×¢Òâ´Ëº¯ÊýÓÐÏìÓ¦ÓÅÏÈ¼¶,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;//°´¼ü°´ËÉ¿ª±êÖ¾
	if(mode)key_up=1;  //Ö§³ÖÁ¬°´
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//È¥¶¶¶¯ 
		key_up=0;
		if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
	}else if(KEY4==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
 	return 0;// ÎÞ°´¼ü°´ÏÂ
}
