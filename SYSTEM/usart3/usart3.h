#ifndef __USART3_H
#define __USART3_H
#include "sys.h" 
#include "stdio.h"
#include "stdarg.h"


#define USART3_REC_LEN		200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1			//ʹ�ܣ�1��/��ֹ��0������1����

extern u8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART3_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         				//����״̬���	

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart3_init(u32 bound);
//void u3_printf(unsigned char *ch);
void u3_printf(char* fmt,...);

#endif
