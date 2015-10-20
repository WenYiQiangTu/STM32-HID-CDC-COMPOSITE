
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
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  //��DMAʱ��
    DMA_DeInit(DMA1_Channel3);                         //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)SRC_USART3_DR;   //ԴͷBUF ���� (&(USART1->DR)) 
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)p_dma_rx->DR3_RxBuff1;   //Ŀ��BUF ����Ҫд���ĸ�������֮��
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //������Դͷ//��������Ϊ���ݴ����Ŀ�ĵػ�����Դ
    DMA_InitStructure.DMA_BufferSize = DMA_BUFFSIZE;       //DMA����Ĵ�С ��λ���±��趨
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�Ĵ���������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�ڴ��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //�����ֽ�Ϊ��λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;//�ڴ��ֽ�Ϊ��λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;//4���ȼ�֮һ��(������) VeryHigh/High/Medium/Low
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//���ڴ浽�ڴ�
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);    //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��1�Ĵ���
    DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);//DMA1��������ж�
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); //ʹ��USART3�Ľ���DMA����
    DMA_Cmd(DMA1_Channel3, ENABLE);   //��ʽ����DMA

	p_dma_rx->flag &= ~BUF_NO ;//Ŀǰѡ�����buff1������
	p_dma_rx->flag &= ~BUF_OK ;//buf��û������
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
	
	p_dma_rx->flag ^= BUF_NO  ;  //��Ӧλȡ��
    p_dma_rx->flag |= BUF_OK ; //  ������׼����
    process :
	   DMA_Cmd(DMA1_Channel3, DISABLE);
	   DMA_InitStructure.DMA_MemoryBaseAddr = (u32)p_donthavedata;
       DMA_Init(DMA1_Channel3, &DMA_InitStructure);
	   DMA_Cmd(DMA1_Channel3, ENABLE);
}

