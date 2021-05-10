#include "led.h"

u16 LED_GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|
									 GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;	//LED��Pin


/*
*===================================================================
*		˵����LED�ƶ˿ڳ�ʼ�� PB -- 3 4 5 6 7 8 9 10
*		��������
*		���أ���
*===================================================================
*/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;									//GPIO��ʼ���ṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);	//ʹ��GPIO��ʱ�ӣ��򿪸������޸ĸ��ù���
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);											//��Ϊ PB3 PB4 ��ԭ����Ҫ��ӳ��  �ر�JTAG  ʹ��SWD
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|
																GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;	//GPIO �˿�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //�ٶ�50MHZ
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��
	GPIO_WriteBit(GPIOB,LED_GPIO_Pin,(BitAction)1);				//��ȫ��
}

/*
*===================================================================
*		˵����LED�ƶ˿�����Ϊ�������ģʽ�������PWM PB -- 3 4 5 6 7 8 9 10
*		��������
*		���أ���
*===================================================================
*/
void LED_Init_PWM_Mode(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 |RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);	//ʹ�� GPIO ��ʱ�ӣ��򿪸���AFIO���޸ĸ��ù���

	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2 | GPIO_PartialRemap2_TIM2, ENABLE);	//�ض��� GPIO �ڶ�ʱ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10;	//PB 3 10	TIM2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    			//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;	//PB 4 5	TIM3
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 	//PB 6 7 8 9 TIM4
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
*===================================================================
*		˵����LEDȫ��˸һ��
*		��������
*		���أ���
*===================================================================
*/
void LED_Shine(void)
{
	GPIO_WriteBit(GPIOB,LED_GPIO_Pin,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, LED_GPIO_Pin))));
	delay_ms(200);
	GPIO_WriteBit(GPIOB,LED_GPIO_Pin,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, LED_GPIO_Pin))));
	delay_ms(200);
}

/*
*===================================================================
*		˵����LED��ˮ��
*		��������
*		���أ���
*===================================================================
*/
void LED_Slide(void)
{
		GPIOB -> BSRR = 0x0000FFFF;			//LED��ȫ��
		GPIO_WriteBit(GPIOB,GPIO_Pin_3,(BitAction)0); delay_ms(100); GPIO_WriteBit(GPIOB,GPIO_Pin_3,(BitAction)1);
		GPIO_WriteBit(GPIOB,GPIO_Pin_4,(BitAction)0); delay_ms(100); GPIO_WriteBit(GPIOB,GPIO_Pin_4,(BitAction)1);
		GPIO_WriteBit(GPIOB,GPIO_Pin_5,(BitAction)0); delay_ms(100); GPIO_WriteBit(GPIOB,GPIO_Pin_5,(BitAction)1);
		GPIO_WriteBit(GPIOB,GPIO_Pin_6,(BitAction)0); delay_ms(100); GPIO_WriteBit(GPIOB,GPIO_Pin_6,(BitAction)1);
		GPIO_WriteBit(GPIOB,GPIO_Pin_7,(BitAction)0); delay_ms(100); GPIO_WriteBit(GPIOB,GPIO_Pin_7,(BitAction)1);
		GPIO_WriteBit(GPIOB,GPIO_Pin_8,(BitAction)0); delay_ms(100); GPIO_WriteBit(GPIOB,GPIO_Pin_8,(BitAction)1);
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)0); delay_ms(100); GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)1);
		GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)0); delay_ms(100); GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)1);
}

/*
*===================================================================
*		˵����LED״̬��ת
*		��������
*		���أ���
*===================================================================
*/
void LED_Turn(void)
{
	GPIO_WriteBit(GPIOB,LED_GPIO_Pin,(BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, LED_GPIO_Pin))));
}

/*
*===================================================================
*		˵����LED������Ч��
*		��������
*		���أ���
*===================================================================
*/
void LED_Live(void)
{
	u8 flag=1, up_flag=1;
	u16 led_val=0;
	while(flag)
	{
//	  TIM4->CCR1=i;
//		TIM4->CCR2=i;
//		TIM4->CCR3=i;
//		TIM4->CCR4=i;
		if(led_val < 499 && up_flag) led_val += 2;
		else
		{
			led_val--;
			up_flag=0;
			if(led_val==0) flag=0;
		}

		TIM_SetCompare2(TIM2,led_val);	//��0��ֵ
		TIM_SetCompare1(TIM3,led_val);	//��1��ֵ
		TIM_SetCompare2(TIM3,led_val);	//��2��ֵ
		TIM_SetCompare1(TIM4,led_val);	//��3��ֵ
		TIM_SetCompare2(TIM4,led_val);	//��4��ֵ
		TIM_SetCompare3(TIM4,led_val);	//��5��ֵ
		TIM_SetCompare4(TIM4,led_val);	//��6��ֵ
		TIM_SetCompare3(TIM2,led_val);	//��7��ֵ
		delay_ms(5);
	}

}
