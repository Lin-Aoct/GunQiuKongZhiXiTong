#include "control.h"	

//���ֵ�λ������
u8 Point[10][2]={{0,0},{40,35},{115,35},{190,35},
												{45,110},{117,110},{190,110},
												{45,185},{120,185},{193,185}};
//��Բ����
u8 Squre_Point[9][2]={{0,0},{120,50},{150,80},{180,110},
														{150,140},{120,170},{90,140},
														{60,110},{90,80}};

u8 Mode_Plus_2_Target_Side[4];	//�洢���Ӳ���2��Ŀ������

u8 max_target_PID = 60;					//������CCR�仯ֵ  50
u8 speed_max = 25;							//�ٶȻ�����ٶ����� 30

u8 Position_X, Position_Y;

int Last_X_target_PID, Last_Y_target_PID;			//�ϴ�λ�� PID ���ֵ����
int X_target_PID, Y_target_PID;								//��ǰ PID ���ֵ����

u8 target_point_X, target_point_Y;						//С������Ŀ��ֵ
u8 target_point_X_temp, target_point_Y_temp;	//С��Ŀ��ֵ����

int square_r = 50, square_current_x, square_current_y;
														
u16 count, count_spacing = 50, init_count, step;

u8 USART2_RX_DATA[2];	//λ����Ϣ���ձ���
u8 Action_Mode;				//��������
												
void TIM1_UP_IRQHandler(void)
{
	static u8 last_action_mode;		//�����ϴ�һ�ζ�������
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)	//���TIM1�Ƿ����ж�
	{
		//if(Action_Mode != last_action_mode)	Mode_Init();
		switch(Action_Mode)
		{
			case 100:	Mode_Stop(); break; 
			case 1: Mode_Base_1(); break;
			case 2: Mode_Base_2(); break;
			case 3: Mode_Base_3(); break;
			case 4: Mode_Base_4(); break;
			case 11: Mode_Plus_1(); break;
			case 12: Mode_Plus_1(); break;
			case 13: Mode_Draw_Square(); break;
			case 21: Mode_Go_Num(1); break;
			case 22: Mode_Go_Num(2); break;
			case 23: Mode_Go_Num(3); break;
			case 24: Mode_Go_Num(4); break;
			case 25: Mode_Go_Num(5); break;
			case 26: Mode_Go_Num(6); break;
			case 27: Mode_Go_Num(7); break;
			case 28: Mode_Go_Num(8); break;
			case 29: Mode_Go_Num(9); break;
			case 30: Mode_Go_Target_Point(target_point_X_temp, target_point_Y_temp); break;
			default: break;
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);			//���TIM1���жϴ�����λ
   }       	
}

/*
*===================================================================
*		˵����ֹͣ�˶� ��ָ�ƽ��
*		��������
*		���أ���
*===================================================================
*/
void Mode_Stop(void)
{
	Set_PWM(0, 0);
	Action_Mode = 0;
}

/*
*===================================================================
*		˵������������1 
*					��С�����������2 ����ʹС����������ͣ��������5��
*		��������
*		���أ���
*===================================================================
*/
void Mode_Base_1(void)
{
	Mode_Go_Num(2);
}

/*
*===================================================================
*		˵������������2
*					��15���� ����С�������1��������5 ������5ͣ��������2��
*		��������
*		���أ���
*===================================================================
*/
void Mode_Base_2(void)
{
	printf("%d, %d", count, step);
	if(step == 0) count = 101, step++;
	if(step == 1 && count>0) Mode_Go_Num(1), count--;	//��ʱ 1500ms
	if(step == 1 && count==0) Mode_Go_Num(5);
}

/*
*===================================================================
*		˵������������3
*					����С�������1��������4 ������4ͣ��������2��
*					Ȼ���ٽ�������5 С��������5ͣ��������2��
*					�����������������ʱ�䲻����20��
*		��������
*		���أ���
*===================================================================
*/
void Mode_Base_3(void)
{
	if(step == 0) count = 21, step++;									//׼����ʱ 300ms
	if(step == 1 && count>0) Mode_Go_Num(1), count--;	//����1
	if(step == 1 && count==0) count = 181, step++;			//׼����ʱ 2700ms
	if(step == 2 && count>0) Mode_Go_Num(4), count--;	//����4
	if(step == 2 && count==0) count = 181, step++;			//׼����ʱ 2700ms
	if(step == 3 && count>0) Mode_Go_Num(5);						//����5
}

/*
*===================================================================
*		˵������������4
*					��30���� ����С�������1��������9 ��������9ͣ��������2��
*		��������
*		���أ���
*===================================================================
*/
void Mode_Base_4(void)
{
	if(step == 0) count = 31, step++;									//׼����ʱ 450ms
	if(step == 1 && count>0) Mode_Go_Num(1), count--;	//����1
	if(step == 1 && count==0) step++;			//�ȴ���ʱ���
	if(step == 2) Mode_Go_Num(9);					//����9
}

/*
*===================================================================
*		˵������������1
*					��40 ���ڿ���С�������1 ���� �Ⱥ��������2������6
*					ֹͣ������9 ������9 ��ͣ��ʱ�䲻����2 ��
*		��������
*		���أ���
*===================================================================
*/
void Mode_Plus_1(void)
{
	if(step == 0) count = 31, step++;										//׼����ʱ 450ms
	if(step == 1 && count > 0) Mode_Go_Num(2), count--;	//����2
	if(step == 1 && count == 0) count = 181, step++;		//׼����ʱ 2700ms
	if(step == 2 && count > 0) Mode_Go_Num(6), count--;	//����6
	if(step == 2 && count == 0) step++;									//׼����ʱ 2700ms
	if(step == 3) Mode_Go_Num(9);												//����9
}


/*
*===================================================================
*		˵�����˶���ָ���������λ��
*		������num	<u8>	Ŀ��λ�����
*		���أ���
*===================================================================
*/
void Mode_Go_Num(u8 num)
{
	target_point_X = Point[num][0];
	target_point_Y = Point[num][1];
	
	if(IS_USART2_RX_HEAD == 0) memcpy(USART2_RX_DATA, USART2_RX_BUF, 2*sizeof(u8));				 //�жϵ�ǰ�Ƿ����ڽ�������
	Position_X = USART2_RX_DATA[0];
	Position_Y = USART2_RX_DATA[1];

	if(Position_Y!=253||Position_X!=253)			//��⵽С��
	{
		X_target_PID = PID_Side_X(Position_X);
		Y_target_PID = PID_Side_Y(Position_Y);

		X_target_PID -= PID_Speed_X(Position_X);
		Y_target_PID -= PID_Speed_Y(Position_Y);
		PID_Limit(&X_target_PID, &Y_target_PID);	//������޷� ��ֹ����
		Set_PWM(X_target_PID, Y_target_PID);			//������
	}
}

/*
*===================================================================
*		˵�����ӵ�1�˶�����9
*		��������
*		���أ���
*===================================================================
*/
void Mode_Go_1_To_9(void)
{
	//�����ּ���1~9
	if(count<count_spacing) target_point_X = Point[5][0], target_point_Y = Point[5][1];
	else if(count>=count_spacing && count<2*count_spacing) target_point_X = Point[1][0], target_point_Y = Point[1][1];
	else if(count>=2*count_spacing && count<3*count_spacing) target_point_X = Point[2][0], target_point_Y = Point[2][1];
	else if(count>=3*count_spacing && count<4*count_spacing) target_point_X = Point[3][0], target_point_Y = Point[3][1];
	else if(count>=4*count_spacing && count<5*count_spacing) target_point_X = Point[6][0], target_point_Y = Point[6][1];
	else if(count>=5*count_spacing && count<6*count_spacing) target_point_X = Point[5][0], target_point_Y = Point[5][1];
	else if(count>=6*count_spacing && count<7*count_spacing) target_point_X = Point[4][0], target_point_Y = Point[4][1];
	else if(count>=7*count_spacing && count<8*count_spacing) target_point_X = Point[7][0], target_point_Y = Point[7][1];
	else if(count>=8*count_spacing && count<9*count_spacing) target_point_X = Point[8][0], target_point_Y = Point[8][1];
	else if(count>=9*count_spacing && count<10*count_spacing) target_point_X = Point[9][0], target_point_Y = Point[9][1];
	else if(count>=10*count_spacing && count<11*count_spacing) target_point_X = Point[5][0], target_point_Y = Point[5][1];
	else count=0;
	count++;

	if(IS_USART2_RX_HEAD == 0) memcpy(USART2_RX_DATA, USART2_RX_BUF, 2*sizeof(u8));				 //�жϵ�ǰ�Ƿ����ڽ�������
	Position_X = USART2_RX_DATA[0];
	Position_Y = USART2_RX_DATA[1];

	if(Position_Y!=253||Position_X!=253)			//��⵽С��
	{
		X_target_PID = PID_Side_X(Position_X);
		Y_target_PID = PID_Side_Y(Position_Y);

		X_target_PID -= PID_Speed_X(Position_X);
		Y_target_PID -= PID_Speed_Y(Position_Y);
		PID_Limit(&X_target_PID, &Y_target_PID);	//������޷� ��ֹ����
		Set_PWM(X_target_PID, Y_target_PID);			//������
	}
	//printf("����:%d, %d\t PID:%d, %d\t count:%d\n", Position_X, Position_Y, X_target_PID, Y_target_PID, count);
}

/*
*===================================================================
*		˵����ȥĿ���
*		������x	<u8>	Ŀ���x
					y	<u8>	Ŀ���y
*		���أ���
*===================================================================
*/
void Mode_Go_Target_Point(u8 x, u8 y)
{
	target_point_X = x;
	target_point_Y = y;

	if(IS_USART2_RX_HEAD == 0) memcpy(USART2_RX_DATA, USART2_RX_BUF, 2*sizeof(u8));	//�жϵ�ǰ�Ƿ����ڽ�������
	Position_X = USART2_RX_DATA[0];
	Position_Y = USART2_RX_DATA[1];

	if(Position_Y!=253||Position_X!=253)			//��⵽С��
	{
		X_target_PID = PID_Side_X(Position_X);
		Y_target_PID = PID_Side_Y(Position_Y);

		X_target_PID -= PID_Speed_X(Position_X);
		Y_target_PID -= PID_Speed_Y(Position_Y);
		PID_Limit(&X_target_PID, &Y_target_PID);	//������޷� ��ֹ����
		Set_PWM(X_target_PID, Y_target_PID);			//������
	}
}

/*
*===================================================================
*		˵������Բ
*		��������
*		���أ���
*===================================================================
*/
void Mode_Draw_Square(void)
{
	if(step == 0) square_current_x = Point[5][0]-square_r, step++;
	if(step==1)
	{
		if(count == 2)
		{
			count=0;
			square_current_x++;
			square_current_y = sqrt((square_r*square_r)-((square_current_x-Point[5][0])*(square_current_x-Point[5][0]))) + Point[5][0];
			if(square_current_x == Point[5][0]+square_r) step++;
		}
	}
	if(step==2)
	{
		if(count == 2)
		{
			count=0;
			square_current_x--;
			square_current_y = -sqrt((square_r*square_r)-((square_current_x-Point[5][0])*(square_current_x-Point[5][0]))) + Point[5][0];
			if(square_current_x == Point[5][0]-square_r) step--;
		}
	}
	count++;
	target_point_X = square_current_x, target_point_Y = square_current_y;
	
//	if(count<count_spacing) target_point_X = Squre_Point[1][0], target_point_Y = Squre_Point[1][1];
//	else if(count>=count_spacing && count<2*count_spacing) target_point_X = Squre_Point[2][0], target_point_Y = Squre_Point[2][1];
//	else if(count>=2*count_spacing && count<3*count_spacing) target_point_X = Squre_Point[3][0], target_point_Y = Squre_Point[3][1];
//	else if(count>=3*count_spacing && count<4*count_spacing) target_point_X = Squre_Point[4][0], target_point_Y = Squre_Point[4][1];
//	else if(count>=4*count_spacing && count<5*count_spacing) target_point_X = Squre_Point[5][0], target_point_Y = Squre_Point[5][1];
//	else if(count>=5*count_spacing && count<6*count_spacing) target_point_X = Squre_Point[6][0], target_point_Y = Squre_Point[6][1];
//	else if(count>=6*count_spacing && count<7*count_spacing) target_point_X = Squre_Point[7][0], target_point_Y = Squre_Point[7][1];
//	else if(count>=7*count_spacing && count<8*count_spacing) target_point_X = Squre_Point[8][0], target_point_Y = Squre_Point[8][1];
//	else count=0;
//	count++;

	if(IS_USART2_RX_HEAD == 0) memcpy(USART2_RX_DATA, USART2_RX_BUF, 2*sizeof(u8));				 //�жϵ�ǰ�Ƿ����ڽ�������
	Position_X = USART2_RX_DATA[0];
	Position_Y = USART2_RX_DATA[1];

	if(Position_Y!=253||Position_X!=253)				//��⵽С��
	{
		X_target_PID = PID_Side_X(Position_X);
		Y_target_PID = PID_Side_Y(Position_Y);

		X_target_PID -= PID_Speed_X(Position_X);
		Y_target_PID -= PID_Speed_Y(Position_Y);
		PID_Limit(&X_target_PID, &Y_target_PID);	//������޷� ��ֹ����
		Set_PWM(X_target_PID, Y_target_PID);			//������
	}
	//printf("����:%d, %d\t PID:%d, %d\t count:%d\n", Position_X, Position_Y, X_target_PID, Y_target_PID, count);
}

/*
*===================================================================
*		˵����PID������޷�
*		������*pid	<int>	�����ָ���ַ
*		���أ���
*===================================================================
*/
void PID_Limit(int *x_pid, int *y_pid)
{
	if(*x_pid < -max_target_PID) *x_pid = -max_target_PID;	
	if(*x_pid > max_target_PID)  *x_pid = max_target_PID;	 
	if(*y_pid < -max_target_PID) *y_pid = -max_target_PID;	
	if(*y_pid > max_target_PID)  *y_pid = max_target_PID;	
}

void Mode_Init(void)
{
	count = 0;
	step = 0;
}
