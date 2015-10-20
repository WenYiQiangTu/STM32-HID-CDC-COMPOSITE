
/***************************************************************************************
****************************************************************************************
* FILE		: dma.c
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/11	  Initial Version
   
****************************************************************************************
****************************************************************************************/


#include "dma.h"
#include "crc.h"
#include "stdarg.h"
#define CRCDATA(buff)	\
                (buff[DMA_BUFFSIZE-4] ) | (buff[DMA_BUFFSIZE-3]<<8)|	\
			    (buff[DMA_BUFFSIZE-2]<<16) | (buff[DMA_BUFFSIZE-1]<<24 )  
/*==================================================================
* Function	 : USART3_DMAToBuf1init
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
DMA_InitTypeDef DMA_InitStructure;
void USART3_DMAToBuf1init(struct Dma_rx *p_dma_rx)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  //开DMA时钟
    DMA_DeInit(DMA1_Channel3);                         //将DMA的通道1寄存器重设为缺省值
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)SRC_USART3_DR;   //源头BUF 既是 (&(USART1->DR)) 
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)p_dma_rx->DR3_RxBuff1;   //目标BUF 既是要写在哪个个数组之中
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //外设作源头//外设是作为数据传输的目的地还是来源
    DMA_InitStructure.DMA_BufferSize = DMA_BUFFSIZE;       //DMA缓存的大小 单位在下边设定
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址寄存器不递增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//内存地址递增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //外设字节为单位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;//内存字节为单位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;//4优先级之一的(高优先) VeryHigh/High/Medium/Low
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//非内存到内存
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);    //根据DMA_InitStruct中指定的参数初始化DMA的通道1寄存器
    DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);//DMA1传输完成中断
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); //使能USART3的接收DMA请求
    DMA_Cmd(DMA1_Channel3, ENABLE);   //正式允许DMA

	p_dma_rx->flag &= ~BUF_NO ;//目前选择的是buff1。。。
	p_dma_rx->flag &= ~BUF_OK ;//buf中没有数据
}
/*==================================================================
* Function	 : DMA1_Channel3process
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/

 void DMA1_Channel3process(struct Dma_rx *p_dma_rx)
{
    static u32 error = 0;
    //
	u8 * const phavedata = WHICH_BUFF_HAS_DATA(p_dma_rx) ;
	u8 * const p_donthavedata = WHICH_BUFF_HASNT_DATA(p_dma_rx) ;
    if ( CRC_CalculateBlockCRC(phavedata,DMA_BUFFSIZE -4 ) != (CRCDATA(phavedata)) ){
	   error++ ;
	  // goto process ;  //
	}
	
	p_dma_rx->flag ^= BUF_NO  ;  //相应位取反
    p_dma_rx->flag |= BUF_OK ; //  有数据准备好
    process :
	   DMA_Cmd(DMA1_Channel3, DISABLE);
	   DMA_InitStructure.DMA_MemoryBaseAddr = (u32)p_donthavedata;
       DMA_Init(DMA1_Channel3, &DMA_InitStructure);
	   DMA_Cmd(DMA1_Channel3, ENABLE);
}

