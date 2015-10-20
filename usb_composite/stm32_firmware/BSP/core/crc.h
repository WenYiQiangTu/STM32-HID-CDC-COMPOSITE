
/***************************************************************************************
****************************************************************************************
* FILE		: crc.h
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/11	  Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef _CRC_H_
#define _CRC_H_


#include "stm32f10x_crc.h"

u32 CRC_CalculateBlockCRC(u8 pBuffer[], u32 BufferLength) ;


#endif /*_CRC_H_*/

