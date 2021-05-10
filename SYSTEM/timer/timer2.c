#include "timer2.h"

/*
*===================================================================
*		˵����TIM2��ʼ�����ã��Ա����PWM���������
*					TIM2.3 -> ����  TIM2.4 -> �ҵ��
*		������Period: ��ʱ���Զ���װֵ   72000000/799 = 80KHZ
*					Prescaler: ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
*		���أ���
*===================================================================
*/
void MOTOR_PWM_Init(u16 Period, u16 Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);												//ʹ�� TIM2 ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	//ʹ�� GPIO ��ʱ�� �򿪸������޸ĸ��ù���

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;				//PA 2 3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    						//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = Period; 										//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler; 							//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 0������Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//����ʱ�ӷָ� TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 							//���� TIM_TimeBaseInitStruct ��ָ���Ĳ�����ʼ�� TIMx ��ʱ�������λ
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 						//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; 													//���ô�װ�벶��ȽϼĴ���������ֵ ռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 			//�������:TIM����Ƚϼ���

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
 
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��	

	TIM_Cmd(TIM2, ENABLE);  											//ʹ��TIM2
}

/*
*===================================================================
*		˵����TIM2 ռ�ձȵ��� ռ�ձ� = TIMx_CCRx / TIMx_ARR
*		������moto_l�����ֵ��  ��ֵ 0-100
*					moto_r�����ֵ��	��ֵ 0-100
*		���أ���
*===================================================================
*/
void MOTO_PWM_Out(u16 moto_l, u16 moto_r)
{
	TIM2->CCR4 = moto_l;
	TIM2->CCR3 = moto_r;

	//TIM_OCInitTypeDef TIM_OCInitSructure;
	
	//TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
	//TIM_OCInitSructure.TIM_OutputState= TIM_OutputState_Enable;

	//CH3 ����
	//TIM_OCInitSructure.TIM_Pulse = moto_l;//ռ�ձ�= ccr/100
	//TIM_OC3Init(TIM2, &TIM_OCInitSructure);//������ʼ��
	//TIM_OC3PolarityConfig(TIM2, TIM_OCPreload_Enable);//��ʼ���pwm
	
	//CH4 �ҵ��
	//TIM_OCInitSructure.TIM_Pulse = moto_r;//ռ�ձ�= ccr /100
	//TIM_OC4Init(TIM2, &TIM_OCInitSructure);//������ʼ��
	//TIM_OC4PolarityConfig(TIM2, TIM_OCPreload_Enable);	//��ʼ���pwm
	
	//TIM_ARRPreloadConfig(TIM2, ENABLE);			//�����Զ���װ
}
