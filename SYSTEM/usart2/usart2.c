#include "USART2.h"	  


//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART2_RX_BUF[USART2_MAX_REC_LEN];		//���ջ���
u8 USART2_TX_BUF[100]; 									//���ͻ���
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA = 0;       	//����״̬���	  
u8 IS_USART2_RX_HEAD = 0;			//��־�Ƿ��Ѿ����յ�����ͷ

/*
*===================================================================
*		˵��������2��ʼ������
*		��������
*		���أ���
*===================================================================
*/
void uart2_init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	//ʹ�� USART2 AFIO ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ�� USART2 GPIOA ʱ��
	
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 				//PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);						//��ʼ��GPIOA.2
   
  //USART2_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;							//PA.3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);								//��ʼ��GPIOA.3

  //USART2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
  //USART ����
	USART_InitStructure.USART_BaudRate = bound;									//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;					//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); 			//��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    	//ʹ�ܴ���2
}


/*
*===================================================================
*		˵��������2�жϷ������
*		��������
*		���أ���
*===================================================================
*/
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET || (USART2->SR & (1 << 3)))  	//�����ж� ��ȡSR�Ĵ�������λ��ֹ�������ش��� ORE 
	{	
		u8 current_data;
		static u8 data_index, last_data, last_last_data;
		//current_data = USART2 -> SR;
		current_data = USART2 -> DR;	//��ȡ��ǰ�ֽ�
		if(IS_USART2_RX_HEAD == 0)		//δ��ȡ������ͷ 0xff 0xfe
		{	
			if(last_data==0xfe && last_last_data==0xff) 
				IS_USART2_RX_HEAD=1, data_index=0;
		}
		if(IS_USART2_RX_HEAD == 1)	//�Ѿ���ȡ������ͷ 0xff 0xfe
		{	
			USART2_RX_BUF[data_index] = current_data;
			data_index++;															//����λ������1
			if(data_index == 2) IS_USART2_RX_HEAD=0;	//���յ�2�ֽ�����  �Ѿ��������  ׼�����½���
		}
		last_last_data = last_data;		//����ǰһ�ν��յ����ֽ�
		last_data = current_data;			//���汾�ν��յ����ֽ�
	}
}


void u2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}
