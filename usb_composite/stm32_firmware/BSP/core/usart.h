
/***************************************************************************************
****************************************************************************************
* FILE		: usart.h
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/11	  Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef _USART_H_
#define _USART_H_
#include "stm32f10x_usart.h"

#define USART_BUFF_SIZE  16

#define SEND_OVER 0x80
#define IS_USART_SEND_OVER(x) (x)->flag & SEND_OVER
#define SET_USART_SEND_OVER_BIT(x)  (x)->flag |= SEND_OVER
#define RESET_USART_SEND_OVER_BIT(x) (x)->flag &= ~SEND_OVER 
struct Usart_tx{
	u8 send_buf[USART_BUFF_SIZE] ;
	u8 send_length ;
	u8 send_cnt ;
	u8 flag ;
};
#define REC_OVER 0X80
struct Usart_rx{
    u8 rec_buf[USART_BUFF_SIZE];
	u8 rec_cnt ;
	u8 flag ;
};


void init_usart(void) ;
void usart_send_bytes(USART_TypeDef* USARTx,struct Usart_tx * p_usart_tx,uint8_t * p,uint8_t Len) ;

void usart_handle_tx_process(USART_TypeDef* USARTx,struct Usart_tx * p_usart_tx) ;

void usart_handle_rx_process(USART_TypeDef* USARTx,
                                           struct Usart_rx *p_usart_rx,void *data,
	                                             void *p_call_back (struct Usart_rx *p_usart_rx,void *data));

#endif /*_USART_H_*/

