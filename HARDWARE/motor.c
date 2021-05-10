#include "motor.h"

u8 MOTOR_LEFT_PWM = 75, MOTOR_RIGHT_PWM = 60;		//���ҵ�� PWM


//***************************���õ������IO��***************************//
void MOTO_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;																					//����һ�� GPIO_InitTypeDef ���͵Ľṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);                                	  /*����GPIO������ʱ��*/																   
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	GPIO_InitStructure.GPIO_Pin = MOTO_Pin1 | MOTO_Pin2 | MOTO_Pin3 | MOTO_Pin4;	/*ѡ��Ҫ���Ƶ�GPIO����*/	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              /*��������ģʽΪͨ���������*/   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             /*������������Ϊ50MHz */ 
	GPIO_Init(MOTO_PORT, &GPIO_InitStructure);                                    /*���ÿ⺯������ʼ��GPIO*/
	
	GPIO_InitStructure.GPIO_Pin = MOTO_Pin_STBY;																	/*ѡ��Ҫ���Ƶ�GPIO����*/	
	GPIO_Init(MOTO_PORT, &GPIO_InitStructure);                                    /*���ÿ⺯������ʼ��GPIO*/
	GPIO_SetBits(GPIOB, MOTO_Pin_STBY);
}

//***************************���ҵ����ǰת��***************************//
//ֻҪ����INx()��״̬�Ϳ��Ըı���ת������
//��������
void Set_MOTOR_Left(char state)
{
	if(state == GO)		//����ǰ��
	{
		IN1(0);
		IN2(1);
	}
	if(state == BACK)	//��������
	{
		IN1(1);
		IN2(0);
	}
	if(state == STOP)	//����ͣת
	{
	  IN1(1);
		IN2(1);
	}
}


//�ҵ������
void Set_MOTOR_Right(char state)
{
	if(state == GO)		//�ҵ��ǰ��
	{
		IN3(1);
		IN4(0);
	}
	if(state == BACK)	//�ҵ������
	{
		IN3(0);
		IN4(1);
	}
	if(state == STOP)//�ҵ��ͣת
	{
	  IN3(1);
		IN4(1);
	}
}


void Car_Go(void)
{
	Set_MOTOR_Left(GO);
	Set_MOTOR_Right(GO);
}

//***************************���ҵ�����ת��***************************//
void Car_Back(void)
{
	Set_MOTOR_Left(BACK);
	Set_MOTOR_Right(BACK);
}

//***************************С��ԭ����ת***************************//
void Car_Turn_Right(void)
{
	Set_MOTOR_Left(GO);
	Set_MOTOR_Right(BACK);
}

//***************************С��ԭ����ת***************************//
void Car_Turn_Left(void)
{
	Set_MOTOR_Left(BACK);
	Set_MOTOR_Right(GO);
}

//***************************ͣ��***************************//
void Car_Stop(void)
{
	Set_MOTOR_Left(STOP);
	Set_MOTOR_Right(STOP);
}



void Speed_Up(void)
{
	if(MOTOR_LEFT_PWM != 0 && MOTOR_LEFT_PWM <100)
		MOTOR_LEFT_PWM++;
	if(MOTOR_RIGHT_PWM != 0 && MOTOR_RIGHT_PWM <100)
		MOTOR_RIGHT_PWM++;
}

void Speed_Down(void)
{
	if(MOTOR_LEFT_PWM > 1)		//��С�ٶȼ�Ϊ1
		MOTOR_LEFT_PWM--;
	if(MOTOR_RIGHT_PWM > 1)
		MOTOR_RIGHT_PWM--;
}
