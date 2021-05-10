#include "timer.h"


/*
*===================================================================
*		˵������ʱ��1��ʼ������
*		������period: ��ʱ���Զ���װֵ   72000000/799 = 80KHZ
*					prescaler: ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
*		���أ���
*===================================================================
*/
void TIM1_Init(u16 period, u16 prescaler)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 	//ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = period; 						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler; 			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 			//��ʼ��TIM1
 
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); 						//ʹ��TIM1�ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  	//TIM1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  											//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	TIM_Cmd(TIM1, ENABLE);  															//ʹ��TIM1����
}
