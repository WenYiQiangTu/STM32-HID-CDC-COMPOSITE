
/***************************************************************************************
****************************************************************************************
* FILE		: crc.c
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/11	  Initial Version
   
****************************************************************************************
****************************************************************************************/
#include "crc.h"
/*==================================================================
* Function	 : calcrc_1byte
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
static void CRC_Reset(void)
{
  CRC->CR = 0x00000001;

}
/*==================================================================
* Function	 : calcrc_1byte
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
static void CRC_Init(void)
{
     
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);
     CRC_Reset(); 
}
/*==================================================================
* Function	 :static u32 CRC_CalculateCRC(u32 data)
* Description   : 
* Inputpara     :
* Outputpara   : 
==================================================================*/
static u32 CRC_CalculateCRC(u32 data)
{
  CRC_Reset();  
  CRC->DR = data;
  return CRC->DR;
}
/*==================================================================
* Function	 : CRC_CalculateBlockCRC
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
u32 CRC_CalculateBlockCRC(u8 pBuffer[], u32 BufferLength)
{
  u32 i;
  CRC_Reset();   
  for(i = 0;i < BufferLength;i++)
  CRC->DR = (u32)pBuffer[i];
  return CRC->DR;
}

