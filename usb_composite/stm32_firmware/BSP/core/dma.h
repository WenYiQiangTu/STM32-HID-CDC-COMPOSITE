
/***************************************************************************************
****************************************************************************************
* FILE		: dma.h
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/11	  Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef _DMA_H_
#define _DMA_H_
#include "stm32f10x_dma.h"

#define BUFFSIZE   (1<<7)
#define SRC_USART3_DR    (&(USART3->DR))        //串口接收寄存器作为源头
#define DMA_BUFFSIZE 84
#define BUF_OK 0x02
#define BUF_NO 0x01 
#define IS_DMA_BUF_HAVE_DATA(x) (x)->flag & BUF_OK 
#define SET_DMA_BUF_HAVE_DATA_FALG(x)  (x)->flag |= BUF_OK
#define RESET_DMA_BUF_HAVE_DATA_FALG(x)  (x)->flag &= ~ BUF_OK
struct Dma_rx{
   u8 DR3_RxBuff1[BUFFSIZE];	//4k内存
   u8 DR3_RxBuff2[BUFFSIZE];	//4k内存
   u8 flag ;
};
#define WHICH_BUFF_HAS_DATA(x)  ( (x)->flag & BUF_NO) ? (x)->DR3_RxBuff2 :(x)->DR3_RxBuff1  
#define WHICH_BUFF_HASNT_DATA(x) ( (x)->flag & BUF_NO) ? (x)->DR3_RxBuff1 :(x)->DR3_RxBuff2  
extern void USART3_DMAToBuf1init(struct Dma_rx *p_dma_rx) ;
extern void DMA1_Channel3process(struct Dma_rx *p_dma_rx) ;


#endif /*_DMA_H_*/

