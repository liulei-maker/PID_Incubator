#ifndef __OLED_H
#define	__OLED_H

#include "stm32f10x.h"   


#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_5)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_5)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_4)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_4)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_3)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_3)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)
 		     
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_8)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_8)

#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý

extern void OLED_Clear(void);
extern void OLED_Init(void);
extern void OLED_ShowChar(u8 x,u8 y,u8 chr);
extern void OLED_ShowString(u8 x,u8 y,u8 *chr);
extern void OLED_Show_num(u8 x, u8 y, u8 num);
extern void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
extern void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N);




#endif
