#include "sys.h"


u16 printf_count = 65534, printf_count_temp = 0;	//���ڴ�ӡʱ����
u32 count_flag;					//Debug

u8 USART1_RX_DATA[4];		//�洢USART1���յ�������
u8 USART3_RX_DATA[4];		//�洢USART3���յ�������
u8 u1_action_mode = 0x25;			//����1����ָ�����
u8 u3_action_mode = 0x25;			//����3����ָ�����

int	main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����ж����ȼ�����
	delay_init();								//��ʱ������ʼ��
	//KEY_Init();								//������ʼ��
	uart_init(115200);					//USART1��ʼ��
	uart2_init(115200);					//USART2��ʼ��
	uart3_init(9600);						//USART3��ʼ��
	TIM1_Init(150, 7199);      	//TIM1 15ms �ж�	149, 7199
	TIM3_PWM_Init(1800, 799);   //���PWM��ʼ��   199,7199  9999, 143	1799, 800
	Set_PWM(0, 0);
	printf("��ʼ�����\n");

	while(1)
	{
		//SERVO_Test();
		//�ж��Ƿ��յ�����1����
		if(IS_USART1_RX_Success==1) 
		{
			memcpy(USART1_RX_DATA, USART1_RX_BUF, 4*sizeof(u8));	//��ȡ����1����������
			if(U1_Mode == 0)	//��ť����ģʽ
			{
				u1_action_mode = USART1_RX_DATA[0];
				printf("�յ�u1ָ�%x\n", u1_action_mode);
				switch(u1_action_mode)
				{
					case 0x0: Mode_Init(); Action_Mode=100; break;	//ֹͣ�˶�
					case 0x1: Mode_Init(); Action_Mode=1; break;		//��������1
					case 0x2: Mode_Init(); Action_Mode=2; break;		//��������2
					case 0x3: Mode_Init(); Action_Mode=3; break;		//��������3
					case 0x4: Mode_Init(); Action_Mode=4; break;		//��������4
					case 0x5: Mode_Init(); Action_Mode=11; break;		//���Ӳ���1
					case 0x6: Mode_Init(); Action_Mode=12; break;		//���Ӳ���2
					case 0x7: Mode_Init(); Action_Mode=13; break;		//���Ӳ���3
					case 0x20: Mode_Init();	Action_Mode=20; break;	//���Ӳ���2����Ŀ���
					case 0x21: Mode_Init(); Action_Mode=21; break;	//ȥ��1
					case 0x22: Mode_Init(); Action_Mode=22; break;	//ȥ��2
					case 0x23: Mode_Init(); Action_Mode=23; break;	//ȥ��3
					case 0x24: Mode_Init(); Action_Mode=24; break;	//ȥ��4
					case 0x25: Mode_Init(); Action_Mode=25; break;	//ȥ��5
					case 0x26: Mode_Init(); Action_Mode=26; break;	//ȥ��6
					case 0x27: Mode_Init(); Action_Mode=27; break;	//ȥ��7
					case 0x28: Mode_Init(); Action_Mode=28; break;	//ȥ��8
					case 0x29: Mode_Init(); Action_Mode=29; break;	//ȥ��9
					default: break;
				}
				u1_action_mode = 100;
			}
			else if(U1_Mode == 1)	//ҡ��ģʽ
			{
				target_point_X_temp = USART1_RX_DATA[0];
				target_point_Y_temp = USART1_RX_DATA[1];
				Mode_Init(); 
				Action_Mode=30;	//ȥָ����
				printf("ҡ�˶���ģʽ[x:%d, y:%d]", USART1_RX_DATA[0], USART1_RX_DATA[1]);
			}
			U1_Mode = 0;
			IS_USART1_RX_Success = 0;
		}
		
		
		//�ж��Ƿ��յ�����3����
		if(IS_USART3_RX_Success==1) 
		{
			memcpy(USART3_RX_DATA, USART3_RX_BUF, 4*sizeof(u8));	//��ȡ����1����������
			if(U3_Mode == 0)	//��ť����ģʽ
			{
				u3_action_mode = USART3_RX_DATA[0];
				printf("�յ�u3ָ�%x\n", u3_action_mode);
				switch(u3_action_mode)
				{
					case 0x0: Mode_Init(); Action_Mode=100; break;	//ֹͣ�˶�
					case 0x1: Mode_Init(); Action_Mode=1; break;		//��������1
					case 0x2: Mode_Init(); Action_Mode=2; break;		//��������2
					case 0x3: Mode_Init(); Action_Mode=3; break;		//��������3
					case 0x4: Mode_Init(); Action_Mode=4; break;		//��������4
					case 0x5: Mode_Init(); Action_Mode=11; break;		//���Ӳ���1
					case 0x6: Mode_Init(); Action_Mode=12; break;		//���Ӳ���2
					case 0x7: Mode_Init(); Action_Mode=13; break;		//���Ӳ���3
					case 0x20: Mode_Init();	Action_Mode=20; break;	//���Ӳ���2����Ŀ���
					case 0x21: Mode_Init(); Action_Mode=21; break;	//ȥ��1
					case 0x22: Mode_Init(); Action_Mode=22; break;	//ȥ��2
					case 0x23: Mode_Init(); Action_Mode=23; break;	//ȥ��3
					case 0x24: Mode_Init(); Action_Mode=24; break;	//ȥ��4
					case 0x25: Mode_Init(); Action_Mode=25; break;	//ȥ��5
					case 0x26: Mode_Init(); Action_Mode=26; break;	//ȥ��6
					case 0x27: Mode_Init(); Action_Mode=27; break;	//ȥ��7
					case 0x28: Mode_Init(); Action_Mode=28; break;	//ȥ��8
					case 0x29: Mode_Init(); Action_Mode=29; break;	//ȥ��9
					default: break;
				}
				u3_action_mode = 100;
			}
			else if(U3_Mode == 1)	//ҡ��ģʽ
			{
				target_point_X_temp = USART3_RX_DATA[0];
				target_point_Y_temp = USART3_RX_DATA[1];
				Mode_Init();
				Action_Mode=30;	//ȥָ����
				printf("u3ҡ�˶���ģʽ[x:%d, y:%d]", USART3_RX_DATA[0], USART3_RX_DATA[1]);
			}
			U3_Mode = 0;
			IS_USART3_RX_Success = 0;
		}
	}
}
