#include "pid.h"

//float x_side_Kp = 0.0, x_side_Ki = 0.0, x_side_Kd = 0.0;		//X ��λ�û� PID��ز���
//float y_side_Kp = 0.0, y_side_Ki = 0.0, y_side_Kd = 0.0;			//Y ��λ�û� PID��ز���
//float x_speed_Kp = 0.0, x_speed_Ki = 0.0, x_speed_Kd = 0.0;					//PID��ز���
//float y_speed_Kp = 0.0, y_speed_Ki = 0.0, y_speed_Kd = 0.0;		//PID��ز���	

float x_side_Kp = 20.0, x_side_Ki = 0.1, x_side_Kd = 145.0;				//X��λ�û� PID����
float y_side_Kp = 20.0, y_side_Ki = 0.1, y_side_Kd = 150.0;				//Y��λ�û� PID����

float x_speed_Kp = -10.0, x_speed_Ki = 0.0, x_speed_Kd = 50.0;			//X���ٶȻ� PID����
float y_speed_Kp = -8.0, y_speed_Ki = 0.0, y_speed_Kd = 55.0;	//Y���ٶȻ� PID����

/*
*===================================================================
*		˵����X����ƽ��PID����
*		������current_side <float> ��ǰλ����Ϣ
*		���أ�X����λ�ÿ���PWM
*===================================================================
*/
int PID_Side_X(float current_side)
{
	float Differential, Bias;		//�����ֱ�����ƫ�����
	static float Last_Bias, Integration, Balance_Integration;  //��һ�ε�ƫ��ֵ

	Bias = current_side - target_point_X;  	//���㵱ǰƫ��ֵ 
	Differential = Bias - Last_Bias;  			//����ƫ��ı仯��	 
//	if(++Flag_Target > 30) 						//��Ƶ������ֿ���
//	{
//		Flag_Target = 0;
		Integration += Bias;
		if(Integration<-40) Integration = -40;	//�����޷�
		if(Integration>40)  Integration = 40;	
		Balance_Integration = Integration * x_side_Ki;  //���ֿ���
	//}		
	Last_Bias = Bias;  //���汾�ε�ƫ��ֵ
	return (int)(x_side_Kp * Bias)/100 + x_side_Kd*Differential/10 + Balance_Integration;   //����λ�ÿ��������
}

/*
*===================================================================
*		˵����Y����ƽ��PID����
*		������current_side <float> ��ǰλ����Ϣ
*		���أ�Y����λ�ÿ���PWM
*===================================================================
*/
int PID_Side_Y(float current_side)
{  
	float Differential, Bias;		//�����ֱ�����ƫ�����
	static float Last_Bias, Integration, Balance_Integration;  //��һ�ε�ƫ��ֵ

	Bias = current_side - target_point_Y;		//���㵱ǰƫ��ֵ  
	Differential = Bias - Last_Bias;  			//����ƫ��ı仯��	 
//	if(++Flag_Target > 30) 								//��Ƶ������ֿ���
//	{
//		Flag_Target = 0;
		Integration += Bias;
		if(Integration<-40) Integration = -40;					//�����޷�
		if(Integration>40)  Integration = 40;	
		Balance_Integration = Integration * y_side_Ki;	//���ֿ���
	//}		

	Last_Bias = Bias;  //���汾�ε�ƫ��ֵ
	return (int)(y_side_Kp * Bias)/100 + y_side_Kd*Differential/10 + Balance_Integration;   //����λ�ÿ��������
}

/*
*===================================================================
*		˵����X�����ٶȻ�PD����
*		������current_side <float> ��ǰλ����Ϣ
*		���أ�X�����ٶȿ���PWM
*===================================================================
*/
int PID_Speed_X(float current_side)
{
	float Differential, Bias;		//�����ֱ�����ƫ�����
	static float Last_Bias, Integration, Balance_Integration, last_side;  //��һ�ε�ƫ��ֵ
	int speed_now;
	
	speed_now = current_side - last_side;
	Bias = speed_now - speed_max;  		//�����ٶ�ƫ��
	Differential = Bias - Last_Bias;  //�����ٶ�ƫ��仯��	 

	Integration += Bias;										//�������� �ۼ����
	if(Integration<-40) Integration = -40;					//�����޷�
	if(Integration>40)  Integration = 40;	
	Balance_Integration = Integration * x_speed_Ki;	//���ֿ���
	
	Last_Bias = Bias;  					//���汾��ƫ��ֵ
	last_side = current_side;		//���汾��λ��ֵ
	return (int)(x_speed_Kp * Bias)/100 + x_speed_Kd*Differential/10 + Balance_Integration;   //�����ٶȿ��������
}

/*
*===================================================================
*		˵����Y�����ٶȻ�PD����
*		������current_side <float> ��ǰλ����Ϣ
*		���أ�Y�����ٶȿ���PWM
*===================================================================
*/
int PID_Speed_Y(float current_side)
{  
	float Differential, Bias;		//�����ֱ�����ƫ�����
	static float Last_Bias, Integration, Balance_Integration, last_side;  //��һ�ε�ƫ��ֵ
	int speed_now;
	
	speed_now = current_side - last_side;
	Bias = speed_now - speed_max;  		//�����ٶ�ƫ��
	Differential = Bias - Last_Bias;  //�����ٶ�ƫ��仯�� 

	Integration += Bias;										//�������� �ۼ����
	if(Integration<-40) Integration = -40;					//�����޷�
	if(Integration>40)  Integration = 40;	
	Balance_Integration = Integration * y_speed_Ki;	//���ֿ���

	Last_Bias = Bias;  					//���汾��ƫ��ֵ
	last_side = current_side;		//���汾��λ��ֵ
	return (int)(y_speed_Kp * Bias)/100 + y_speed_Kd*Differential/10 + Balance_Integration;   //�����ٶȿ��������
}
