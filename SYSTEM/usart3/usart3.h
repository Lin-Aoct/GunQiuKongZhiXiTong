#ifndef __USART3_H
#define __USART3_H
#include "sys.h" 


#define USART3_REC_LEN		200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1			//ʹ�ܣ�1��/��ֹ��0������1����

//extern u16 USART3_RX_STA;         				//����״̬���	

void uart3_init(u32 bound);
//void u3_printf(unsigned char *ch);
void u3_printf(char* fmt,...);

#endif
