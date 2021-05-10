#include "wave.h"


u8 Limiti_Distance = 20;		//��Сͣ������ ��λ cm
u16 Distance = 0;						//�ϰ������
u8 OB_L =0,OB_M=0,OB_R=0;		//�ϰ���λ�ñ��

/*
*===================================================================
*		˵�����������˿ڳ�ʼ�� PB9 - TRIG | PB8 - ECH0
*		��������
*		���أ���
*===================================================================
*/
void WAVE_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	       
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = WAVE_TRIG_PIN;					   	//PB9 - TRIG
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     	//��Ϊ�������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	                 	//��ʼ������ GPIO 
	
	GPIO_InitStructure.GPIO_Pin = WAVE_ECHO_PIN;				    	//PB8 - ECH0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			//��Ϊ��������ģʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM3_Configuration();					//��ʱ�� TIM3 ����
	TIM3_NVIC_Configuration();		//��ʱ�� TIM3 �жϳ�ʼ��
	
}

/*
*===================================================================
*		˵������������� ����һ�� >10us �����壬�������ظߵ�ƽʱ����
*					�Ӷ���������룬���� TIM3 ��¼ʱ��
*		��������
*		���أ�distance ���룬��λ cm
*===================================================================
*/
u16 WAVE_Get_Distance(void)
{
	u16 distance;		//��������С����
  Wave_ON();  		//��>10uS�ĸߵ�ƽ
  delay_us(20);		//��ʱ20uS
  Wave_OFF();			//��Ϊ�͵�ƽ
  
  while(!Wave_State());	    //�ȴ��ߵ�ƽ
  TIM_Cmd(TIM3, ENABLE);    //���� TIM3 ʱ�� ��ʱ�Ա�֪���ź�����ʱ��
  while(Wave_State());	    //�ȴ��͵�ƽ
  TIM_Cmd(TIM3, DISABLE);		//TIM3 ʧ��
  //distance = (TIM_GetCounter(TIM3) * 34)/2;	//������� ����cm
	distance = TIM_GetCounter(TIM3)*5*34/2000;	//������� ����cm
  TIM_SetCounter(TIM3, 0);	//��ʱ��2 TIM3 ����ֵ����
  return distance;					//���ؾ���
}


/*
*===================================================================
*		˵����С������
*		��������
*		���أ���
*===================================================================
*/
void Wave_Find_Way(void)
{
	Distance = WAVE_Get_Distance();		//��ȡ����
	if(Distance < 800)		//��ֹͻȻ��������
	{
		if((Distance < Limiti_Distance) && (Distance != 0))
		{
			Car_Stop();						//ͣ��
			OB_M = 1;							//����м����ϰ���
			Car_Turn_Left();			//��ת
			delay_ms(250);										//���Եȴ� 250ms ת���ұ�
			Car_Stop();						//ͣ��
			Distance = WAVE_Get_Distance();		//�����Ҷ��Ƿ����ϰ���
			//�����߾���
			if((Distance < Limiti_Distance) && (Distance != 0))
			{
				OB_L = 1;					//���������ϰ���
				Car_Turn_Left();	//��ת
				delay_ms(500);		//���Եȴ� 500ms 180�� ת��
				Car_Stop();						//ͣ��
				Distance = WAVE_Get_Distance();		//�����Ҷ��Ƿ����ϰ���
				//����ұ߾���
				if((Distance < Limiti_Distance) && (Distance != 0))
				{
					OB_R = 1;					//���������ϰ���
					Car_Turn_Right();	//��ת
					delay_ms(250);		//���Եȴ� 250ms 90�� ��ת��
					Car_Go();				//����
				}
				else	//�Ҳ��пռ���
				{
					Car_Go();
					return;
				}
			}
			else	//����пռ���
			{
				Car_Go();
				return;
			}
		}
	}
}
