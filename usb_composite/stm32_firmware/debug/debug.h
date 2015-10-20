
/***************************************************************************************
****************************************************************************************
* FILE		: debug.h
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/12	  Initial Version
   
****************************************************************************************
****************************************************************************************/
#ifndef _DEBUG_H_
#define _DEBUG_H_
#include"stm32f10x_usart.h"
//****functions**************************
void USART_debug_config(void) ;
void USART_debug_printf(USART_TypeDef* USARTx, uint8_t *Data,...) ;

//******************define*******************


//****调试接口的配配置*******
#define DEBUG_TERMINAL  USART1
//#define  OBJECT_DEBUG


//******调试参数*************
#define OJECT_DEBUG_ON  0x01
#define OBJECT_DEBUG_HALT  0X02

//调试终端的初始化
#ifdef OBJECT_DEBUG
#define OJECT_DEBUG_INIT    USART_debug_config();
#else  
#define OJECT_DEBUG_INIT 
#endif
//调试信息打印
#ifdef OBJECT_DEBUG  
#define OBJECT_DEBUG_PLATFORM(message )   USART_debug_printf( DEBUG_TERMINAL, message)

#define OBJECT_DEBUG_DAG(debug,message) \
                       do {\
                         if( debug & OJECT_DEBUG_ON ) \
							OBJECT_DEBUG_PLATFORM(message ) ; \
						 if (debug & OBJECT_DEBUG_HALT ) \
						   while (1) ;  \
					   }while(0)
#else 
#define   OBJECT_DEBUG_DAG(debug,message)  
#endif
#endif /*_DEBUG_H_*/

