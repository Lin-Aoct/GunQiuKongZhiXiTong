#ifndef __WAVE_H
#define __WAVE_H
#include "sys.h"
#include "timer3.h"

#define WAVE_TRIG_PIN GPIO_Pin_9		//�궨�� ������ TRIG����
#define WAVE_ECHO_PIN GPIO_Pin_8    //�궨�� ������ ECHO����

#define Wave_ON()  GPIO_SetBits(GPIOB, WAVE_TRIG_PIN)								//������ TRIG ��������ߵ�ƽ
#define Wave_OFF() GPIO_ResetBits(GPIOB, WAVE_TRIG_PIN)							//������ TRIG ��������͵�ƽ
#define Wave_State()  GPIO_ReadInputDataBit(GPIOB, WAVE_ECHO_PIN)		//��ȡ������ ECHO ���ŵ�ƽ

void WAVE_Init(void);					//�������˿ڳ�ʼ��
u16 WAVE_Get_Distance(void);	//��������������	
void Wave_Find_Way(void);

#endif

