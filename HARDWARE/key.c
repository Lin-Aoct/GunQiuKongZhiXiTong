#include "key.h"

/*
*===================================================================
*		˵������ʼ����ť����Ϊ�������� PA -- 4 5 6 7
*		��������
*		���أ���
*===================================================================
*/
void KEY_Init(void)
{
//	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��
//	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ��

//	GPIOA->CRH&=0X0FF00FF0;
//	GPIOA->CRH|=0X80088008;
//	GPIOA->ODR|=153<<8;

//	AFIO -> EXTICR[1] = 0x1111;				//PB4 ����Ϊ�ⲿ�ж�
//	EXTI -> FTSR |= 240;								//���� INT0~INT4 �����ź�Ϊ�½���
//	EXTI -> IMR |= 240;								//���� INT0~INT4 �ж��ź�
//	NVIC -> ISER[0] |= (240<<6);				//ʹ�� INT0~INT4

	//NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	//EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE); 	//���������˿�PB��ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 				//�˿�����Ϊ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);								//��ʼ���˿�
	
//	/* �ж�Line4���� */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//�½��ش���ģʽ
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);														//����ָ���Ĳ�����ʼ�� EXTI �Ĵ���
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//�����ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);													//����ָ���Ĳ�����ʼ�� NVIC �Ĵ���

//	/* �ж�Line5���� */
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);
//	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//�½��ش���ģʽ
//	EXTI_Init(&EXTI_InitStructure);														//����ָ���Ĳ�����ʼ�� EXTI �Ĵ���
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//�����ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);													//����ָ���Ĳ�����ʼ�� NVIC �Ĵ���
//	
//	/* �ж�Line6���� */
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
//	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//�½��ش���ģʽ
//	EXTI_Init(&EXTI_InitStructure);														//����ָ���Ĳ�����ʼ�� EXTI �Ĵ���
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//�����ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);													//����ָ���Ĳ�����ʼ�� NVIC �Ĵ���

//	/* �ж�Line7���� */
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);
//	EXTI_InitStructure.EXTI_Line = EXTI_Line7;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//�½��ش���ģʽ
//	EXTI_Init(&EXTI_InitStructure);														//����ָ���Ĳ�����ʼ�� EXTI �Ĵ���
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	//��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//�����ȼ�0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);													//����ָ���Ĳ�����ʼ�� NVIC �Ĵ���
}

/*
*===================================================================
*		˵��������0�жϴ�����
*		��������
*		���أ���
*===================================================================
*/
//void EXTI4_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
//	{
//		LED_Init_PWM_Mode();	//����Ϊ����ģʽ
//		LED_Live();		//��ʾ������
//		LED_MODE = 1;	//����LED����ʾģʽ �Ա�ѭ��
//		EXTI_ClearITPendingBit(EXTI_Line4);		//����жϱ�־λ
//	}
//}

///*
//*===================================================================
//*		˵�������� 1-3 �жϴ�����
//*		��������
//*		���أ���
//*===================================================================
//*/
//void EXTI9_5_IRQHandler(void)
//{
//	u32 Temp = 0x00; 
//  Temp = EXTI -> PR;	//��ȡ�ж�Դ
//  switch(Temp)
//  {
//		case 0x20:		//����1�ж� Line5
//			LED_Init();
//			LED_Slide();
//			LED_Slide();
//			LED_MODE = 2;
//			printf("�ж�Line5");
//      EXTI_ClearITPendingBit(EXTI_Line5);		//����жϱ�־λ
//      break;
//    case 0x40:		//����2�ж� Line6
//			LED_Init();
//			LED_Shine();
//			LED_Shine();
//			LED_Shine();
//			LED_MODE = 3;
//			printf("�ж�Line6");
//      EXTI_ClearITPendingBit(EXTI_Line6);		//����жϱ�־λ
//      break;
//    case 0x80:		//����3�ж� Line7
//			LED_Init();
//			LED_Slide();
//			LED_Slide();
//			LED_MODE = 4;
//			printf("�ж�Line7");
//      EXTI_ClearITPendingBit(EXTI_Line7);		//����жϱ�־λ
//      break;
//    default: EXTI_ClearITPendingBit(Temp); break;
//	}
//}

/*
*===================================================================
*		˵��������ɨ�躯�������а������£����ض�Ӧ�����ı��
*		������i������
*		���أ��������
*===================================================================
*/
u8 KEY_Scan(u8 i)
{	 
	static u8 key_up=1;	//�������ɿ���־
	if(i)key_up=1;  		//֧������		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		delay_ms(120);			//��ʱ 120ms ȥ���� 
		key_up=0;
		if(KEY0==0)return 0;
		else if(KEY1==0)return 1;
		else if(KEY2==0)return 2;
		else if(KEY3==0)return 3;
	}
	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)	key_up=1; 
 	return 100;					//�ް�������
}
