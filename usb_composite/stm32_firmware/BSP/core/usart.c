
/***************************************************************************************
****************************************************************************************
* FILE		: usart.c
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/12	  Initial Version
   
****************************************************************************************
****************************************************************************************/


#include "usart.h"
/*==================================================================
* Function	   : void USART3_Config(void)
* Description  : 
* Inputpara    : 
* Outputpara   : 
==================================================================*/
void USART3_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

	/* config USART3 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    /* USART3 GPIO config */
   /* Configure USART3 Tx (PB.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	    
  /* Configure USART3 Rx (PB.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure); 

  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  //�����жϴ�
  USART_Cmd(USART3, ENABLE);// ʹ�ܴ���3
}
/*==================================================================
* Function	 : USART1_Config
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
static void USART1_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

	/* config USART1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* USART1 GPIO config */
   /* Configure USART1 Tx (PA.9) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;//GPIO_Mode_AF_PP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure); 

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
  USART_Cmd(USART1, ENABLE);
 }


/*==================================================================
* Function	 : init_usart
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
void init_usart(void)
{
	USART1_Config() ;
	USART3_Config() ;
}
/*==================================================================
* Function	   : void usart_send_bytes(USART_TypeDef* USARTx,struct Usart_tx * p_usart_tx,uint8_t * p,uint8_t Len)
* Description  : ����copy�����ڴ��ڷ���
* Inputpara    : 
* Outputpara   : 
==================================================================*/
void usart_send_bytes(USART_TypeDef* USARTx,struct Usart_tx * p_usart_tx,uint8_t * p,uint8_t Len)
{
	u8 i = 0 ;
	p_usart_tx ->send_cnt = 0 ;
	p_usart_tx ->flag &= ~SEND_OVER ; 
	//���ͳ���
	p_usart_tx ->send_length = Len >= USART_BUFF_SIZE ? USART_BUFF_SIZE : Len ;  
	//���뻺����
	for(i = 0 ; i < p_usart_tx ->send_length ; i++){
		p_usart_tx ->send_buf[i] = *(p + i) ;
	}
	//����1byte ����
	USART_SendData(USARTx,(p_usart_tx ->send_buf[p_usart_tx->send_cnt++] ));	
	//�򿪷�������ж�
	USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
}
/*==================================================================
* Function	   : void usart_handle_tx_process(USART_TypeDef* USARTx)
* Description  : ���ڷ����ж�
* Inputpara    : 
* Outputpara   : 
==================================================================*/
void usart_handle_tx_process(USART_TypeDef* USARTx,struct Usart_tx * p_usart_tx)
{
	USART_SendData(USARTx,(p_usart_tx ->send_buf[p_usart_tx->send_cnt++] ));	
	//�Ƿ������
	if( p_usart_tx->send_cnt >=  p_usart_tx->send_length )
	{
		p_usart_tx->flag |= SEND_OVER ; 
		USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
	}
}

/*==================================================================
* Function	 : usart_handle_rx_process
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
void usart_handle_rx_process(USART_TypeDef* USARTx,
                                           struct Usart_rx *p_usart_rx,void *data,
	                                             void *p_call_back (struct Usart_rx *p_usart_rx,void *data))
{
   //��ֹ�������buff
   if (p_usart_rx->rec_cnt > USART_BUFF_SIZE )  p_usart_rx->rec_cnt = 0 ;
   //����1���ֽڵ�����
   p_usart_rx->rec_buf[p_usart_rx->rec_cnt++]= USARTx->DR ; 
   //������Ӧ��Ӧ�ô�����
   if(p_call_back) 
   	  *p_call_back(p_usart_rx,data);  
 }