#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "delay.h"

#define LED0 PBout(3)
#define LED1 PBout(4)
#define LED2 PBout(5)
#define LED3 PBout(6)
#define LED4 PBout(7)
#define LED5 PBout(8)
#define LED6 PBout(9)
#define LED7 PBout(10)

//#define LEDTEST PCout(13)

#define LEDTEST(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_13)				


void LED_Init(void);  				//LED�Ƴ�ʼ��
void LED_Init_PWM_Mode(void);	//LED�˿ڸ��� �Ա���ʾ������
void LED_Shine(void);					//LED����˸
void LED_Slide(void);					//LED��ˮ��
void LED_Turn(void);					//LED״̬��ת
void LED_Live(void);					//LED������

#endif
