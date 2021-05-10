#include "esp8266.h"




/*
*===================================================================
*		˵����ESP8266��ʼ��������͸��ģʽ
*		��������
*		���أ���
*===================================================================
*/
void esp8266_start_trans(void)
{
	u8 i;
	
	//esp8266_quit_trans();		//�˳�͸��ģʽ
	//delay_ms(100);
	//ESP6266_Send_Cmd((u8*)"+", (u8*)"OK", 0);
	//delay_ms(100);
	//printf("AT+SAVETRANSLINK=1,\"192.168.43.121\",15322,\"UDP\"");
//	
//	ESP6266_Send_Cmd((u8*)"AT+RST", (u8*)"OK", 300);				//ESP8266 ����  ��ʱ3S�ȴ������ɹ�
//	
//	ESP6266_Send_Cmd((u8*)"AT+CWMODE=1", (u8*)"OK", 20);		//���ù���ģʽ 1��station ģʽ | 2��AP ģʽ | 3������ AP+station ģʽ
//	
//	ESP6266_Send_Cmd((u8*)"AT+CWJAP=\"o2\",\"qwertyuiopp\"", (u8*)"OK", 300);	//ESP8266 ���� WIFI

//	printf("��������wifi...");

//	delay_ms(1000);
//	
//	ESP6266_Send_Cmd((u8*)"AT+CIPMUX=0", (u8*)"OK", 20);		//������������ 0����·����ģʽ | 1����·����ģʽ

//	ESP6266_Send_Cmd((u8*)"AT+CIPMODE=1", (u8*)"OK", 20);			//����͸��ģʽ  0����ʾ�ر� 1����ʾ����͸��

//	ESP6266_Send_Cmd((u8*)"AT+CIPSTART=\"UDP\",\"192.168.43.47\",15322", (u8*)"Linked", 30);	//���� UDP ����   ��������  Զ�̷�����IP��ַ  Զ�̷������˿ں� 43.47  43.102 

//	ESP6266_Send_Cmd((u8*)"AT+CIPSEND", (u8*)"OK", 20);			//����͸��ģʽ ֮���ֱ�ӷ�������

	//ESP6266_Send_Cmd((u8*)"AT+CIPSTA?", (u8*)"OK", 20);
	
	for(i=0;i<2;i++)
	{
		printf("HELLO FROM STM32");
		delay_ms(500);
	}
	printf("ESP8266 Ready");
	IS_ESP8266_READY = 1;

	//����TCP����  ������ֱ������ Ҫ���ӵ�ID��0~4   ��������  Զ�̷�����IP��ַ   Զ�̷������˿ں�
//	while(ESP6266_Send_Cmd("AT+CIPSTART=\"TCP\",\"47.107.145.82\",320","Linked",5000))
//	{
//		printf("��������Զ�̷�����...");
//	}
	
}

/*
*===================================================================
*		˵����ESP8266�˳�͸��ģʽ ��������3�� +
					ÿ�� + ��֮�䲻����10ms ����Ϊ���������η��� +
*		��������
*		���أ��˳��ɹ�1 | �˳�ʧ�� 0
*===================================================================
*/
u8 esp8266_quit_trans(void)
{
	u8 result;				//���淵�ؽ������
	USART_SendData(USART1, '+');
	USART_SendData(USART1, '+');
	USART_SendData(USART1, '+');
	delay_ms(200);		//�ȴ� 200ms �˳�
	result = ESP6266_Send_Cmd((u8*)"AT", (u8*)"OK", 20);		//�˳�͸���ж�.
	if(result)
		printf("�˳�͸��ģʽʧ��!");
	else
		printf("͸��ģʽ�˳��ɹ�!");
	return result;
}


//��ESP8266��������
//cmd:���͵������ַ���;ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��;waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����);1,����ʧ��
u8 ESP6266_Send_Cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART_RX_STA=0;
	printf("%c", cmd);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(esp8266_check_cmd(ack))
				{
					printf("ESP8266:%s",(u8*)ack);
					break;//�õ���Ч���� 
				}
				//USART_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 

////ESP8266���������,�����յ���Ӧ��
////str:�ڴ���Ӧ����
////����ֵ:0,û�еõ��ڴ���Ӧ����;����,�ڴ�Ӧ������λ��(str��λ��)
u8* esp8266_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART_RX_STA&0X8000)		//���յ�һ��������
	{
		USART_RX_BUF[USART_RX_STA&0X7FFF]=0;//��ӽ�����
		printf("%c",USART_RX_BUF[0]);
		strx=strstr((const char*)USART_RX_BUF,(const char*)str);
	}
	return (u8*)strx;
}


////��ESP8266��������
////cmd:���͵������ַ���;waittime:�ȴ�ʱ��(��λ:10ms)
////����ֵ:�������ݺ󣬷������ķ�����֤��

//char* esp8266_send_data(u8 *cmd,u16 waittime)
//{
//	char temp[20];
//	char *ack=temp;
//	USART2_RX_STA=0;
//	u2_printf("%s\r\n", cmd);	//��������
//	if(waittime)		//��Ҫ�ȴ�Ӧ��
//	{
//		while(--waittime)	//�ȴ�����ʱ
//		{
//			delay_ms(10);
//			if(USART2_RX_STA&0X8000)//���յ��ڴ���Ӧ����
//			{
//				USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;//��ӽ�����
//				ack=(char*)USART2_RX_BUF;
//				printf("������ָ��:%s\t",(u8*)ack);
//				USART2_RX_STA=0;
//				break;//�õ���Ч���� 
//			} 
//		}
//	}
//	return ack;
//} 
