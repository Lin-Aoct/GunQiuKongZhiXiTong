#include "USART3.h"	  


//#if EN_USART3_RX   //���ʹ���˽���
//����3�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
//u8 USART3_RX_BUF[USART3_REC_LEN];     //���ջ���,���USART3_REC_LEN���ֽ�.
u8 USART3_TX_BUF[100]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART3_RX_STA=0;       //����״̬���	  

u8 IS_USART3_RX_HEAD;		//��־�Ƿ���յ�����ͷ
u8 IS_USART3_RX_Success=0;
u8 USART3_RX_BUF[4];		//USART3���ջ���
u8 U3_Mode;
 
 
void uart3_init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);	//ʹ�� USART3 AFIO ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ�� USART3 GPIOA ʱ��
	
	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 				//PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);						//��ʼ��GPIOB.10
   
  //USART3_RX	  GPIOB.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;						//PB.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);								//��ʼ��GPIOB.11

  //USART3 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
  //USART ����
	USART_InitStructure.USART_BaudRate = bound;									//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;					//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									//�շ�ģʽ

  USART_Init(USART3, &USART_InitStructure); 			//��ʼ������3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	//�������ڽ����ж�
  USART_Cmd(USART3, ENABLE);                    	//ʹ�ܴ���3
}


/*
*===================================================================
*		˵��������3�жϷ������
*		��������
*		���أ���
*===================================================================
*/
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
	{	  
		u8 current_data;
		static u8 data_index, last_data, last_last_data;
		current_data = USART3 -> DR;
		//printf("u3�ж�[%d]",current_data);
		if(IS_USART3_RX_HEAD == 0)	//δ��ȡ������ͷ 0xff 0xfe
		{	
			if(last_data==0xfe && last_last_data==0xff) 
				IS_USART3_RX_HEAD=1, data_index=0;
		}
		if(IS_USART3_RX_HEAD == 1)	//�Ѿ���ȡ������ͷ 0xff 0xfe
		{	
			if(current_data == 0xfd && U3_Mode == 0)
				U3_Mode=1;
			else if(U3_Mode == 1)
			{
				USART3_RX_BUF[data_index] = current_data;
				data_index++;															//����λ������һ
				if(data_index == 2) IS_USART3_RX_HEAD=0, IS_USART3_RX_Success=1;	//���յ�2�ֽ����� ׼�����½���
			}
			else
			{
				USART3_RX_BUF[data_index] = current_data;
				data_index++;															//����λ������һ
				if(data_index == 1) IS_USART3_RX_HEAD=0, IS_USART3_RX_Success=1;	//���յ�1�ֽ����� ׼�����½���
			}
		}
		last_last_data = last_data;		//����ǰһ�ν��յ���λ
		last_data = current_data;			//���汾�ν��յ���λ
	}
	
	
	
	
	
	
	
//	u8 Res;
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//	{
//		Res =USART_ReceiveData(USART3);		//��ȡ���յ�������
//		
//		if((USART3_RX_STA&0x8000)==0)			//����δ���
//		{
//			if(USART3_RX_STA&0x4000)				//���յ���0x0d
//			{
//				if(Res!=0x0a)USART3_RX_STA=0;	//���մ���,���¿�ʼ
//				else USART3_RX_STA|=0x8000;		//��������� 
//			}
//			else //��û�յ�0x0D
//			{	
//				if(Res==0x0d)USART3_RX_STA|=0x4000;
//				else
//				{
//					USART_RX_BUF[USART3_RX_STA&0X3FFF]=Res ;						//��λ�� ��ǰ14λ�õ���Ч�ֽڳ���
//					USART3_RX_STA++;
//					if(USART3_RX_STA>(USART_REC_LEN-1))USART3_RX_STA=0;	//�������ݴ���,���¿�ʼ����	  
//				}		 
//			}
//		}   		 
//	} 
}


/*
*===================================================================
*		˵��������3�������ݺ���
*		������ch��Ҫ���͵��ַ���ָ��
*		���أ���
*===================================================================
*/
//void u3_printf(unsigned char *ch)
//{      
//	while(*ch!='\0')
//	{ 
//		while(USART_GetFlagStatus(USART3,USART_FLAG_TC ) == RESET);	
//		USART_SendData(USART3,*ch);
//		ch++;
//	}
//}

void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}


//void USART_printf ( USART_TypeDef * USARTx, char * Data, ... )
//{
//	const char *s;
//	int d;   
//	char buf[16];
//	
//	va_list ap;
//	va_start(ap, Data);
// 
//	while ( * Data != 0 )     // �ж��Ƿ񵽴��ַ���������
//	{				                          
//		if ( * Data == 0x5c )  //'\'
//		{									  
//			switch ( *++Data )
//			{
//				case 'r':							          //�س���
//				USART_SendData(USARTx, 0x0d);
//				Data ++;
//				break;
// 
//				case 'n':							          //���з�
//				USART_SendData(USARTx, 0x0a);	
//				Data ++;
//				break;
// 
//				default:
//				Data ++;
//				break;
//			}			 
//		}
//		
//		else if ( * Data == '%')
//		{									  //
//			switch ( *++Data )
//			{				
//				case 's':										  //�ַ���
//				s = va_arg(ap, const char *);
//				
//				for ( ; *s; s++) 
//				{
//					USART_SendData(USARTx,*s);
//					while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
//				}
//				
//				Data++;
//				
//				break;
// 
//				case 'd':			
//					//ʮ����
//				d = va_arg(ap, int);
//				
//				itoa(d, buf, 10);
//				
//				for (s = buf; *s; s++) 
//				{
//					USART_SendData(USARTx,*s);
//					while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
//				}
//				
//				Data++;
//				
//				break;
//				
//				default:
//				Data++;
//				
//				break;
//				
//			}		 
//		}
//		
//		else USART_SendData(USARTx, *Data++);
//		
//		while ( USART_GetFlagStatus ( USARTx, USART_FLAG_TXE ) == RESET );
//		
//	}
//}














////���ڽ��ջ����� 	
//u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
//u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�

////ͨ���жϽ�������2���ַ�֮���ʱ������10ms�������ǲ���һ������������.
////���2���ַ����ռ������10ms,����Ϊ����1����������.Ҳ���ǳ���10msû�н��յ�
////�κ�����,���ʾ�˴ν������.
////���յ�������״̬
////[15]:0,û�н��յ�����;1,���յ���һ������.
////[14:0]:���յ������ݳ���
//vu16 USART3_RX_STA=0;   	

//void USART3_IRQHandler(void)
//{
//	u8 res;	      
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//���յ�����
//	{	 
//		
//				u8 temp;
//				static u8 count,last_data,last_last_data;
//				temp=USART3->DR;
//				  LED = 0; 
//					if(Usart_Flag==0)
//						{	
//						if(last_data==0xfe&&last_last_data==0xff) 
//						Usart_Flag=1,count=0;	
//						}
//					 if(Usart_Flag==1)
//						{	
//							Urxbuf[count]=temp;     
//							count++;                
//							if(count==2)Usart_Flag=0;
//						}
//						last_last_data=last_data;
//						last_data=temp;
//		
//		
//		res =USART_ReceiveData(USART3);		 
//		if((USART3_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
//		{ 
//			if(USART3_RX_STA<USART3_MAX_RECV_LEN)	//�����Խ�������
//			{
//				TIM_SetCounter(TIM2,0);//���������          				//���������
//				if(USART3_RX_STA==0) 				//ʹ�ܶ�ʱ��3���ж� 
//				{
//					TIM_Cmd(TIM2,ENABLE);//ʹ�ܶ�ʱ��3
//				}
//				USART3_RX_BUF[USART3_RX_STA++]=res;	//��¼���յ���ֵ	 
//			}
//			else 
//			{
//				USART3_RX_STA|=1<<15;				//ǿ�Ʊ�ǽ������
//			} 
//		}
//	}  				 											 
//}   



////��ʼ��IO ����3
////pclk1:PCLK1ʱ��Ƶ��(Mhz)
////bound:������	  
//void usart3_init(u32 bound)
//{  
//	NVIC_InitTypeDef NVIC_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOBʱ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //����3ʱ��ʹ��

// 	USART_DeInit(USART3);  //��λ����3
//		 //USART3_TX   PB10
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//  GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
//   
//    //USART3_RX	  PB11
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11
//	
//	USART_InitStructure.USART_BaudRate = bound;//������һ������Ϊ9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
//  
//	USART_Init(USART3, &USART_InitStructure); //��ʼ������	3
//  

//	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
//	
//	//ʹ�ܽ����ж�
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�   
//	
//	//�����ж����ȼ�
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//	
//	
//	TIM2_Int_Init(1000-1,7200-1);		//10ms�ж�
//	USART3_RX_STA=0;		//����
//	TIM_Cmd(TIM2,DISABLE);			//�رն�ʱ��3

//}

////����3,printf ����
////ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
//void u3_printf(char* fmt,...)  
//{  
//	u16 i,j; 
//	va_list ap; 
//	va_start(ap,fmt);
//	vsprintf((char*)USART3_TX_BUF,fmt,ap);
//	va_end(ap);
//	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
//	for(j=0;j<i;j++)							//ѭ����������
//	{
//	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
//		USART_SendData(USART3,USART3_TX_BUF[j]); 
//	} 
//}
