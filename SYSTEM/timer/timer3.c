#include "timer3.h"


/*
*===================================================================
*		˵����TIM3�ж����ȼ�����
*		��������
*		���أ���
*===================================================================
*/
void TIM3_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    													
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
*===================================================================
*		˵����TIM3���� ����1msΪ���ڵ��ж�
*		��������
*		���أ���
*===================================================================
*/
void TIM3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    TIM_DeInit(TIM3);
    TIM_TimeBaseStructure.TIM_Period = 65535;									//�Զ���װ�ؼĴ������ڵ�ֵ(����ֵ)	1000
    TIM_TimeBaseStructure.TIM_Prescaler= 359;									//ʱ��Ԥ��Ƶ�� 72M/360   	71
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		//������Ƶ����
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);							    		//�������жϱ�־ 
}

void TIM3_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  
   {
       TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
   }
}

