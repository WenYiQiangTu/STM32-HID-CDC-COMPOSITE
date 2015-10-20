
/***************************************************************************************
****************************************************************************************
* FILE		: tim.h
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/11	  Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef _TIM_H_
#define _TIM_H_

#include "stm32f10x_tim.h"
	
#define TIM4TIMER       (3)  
#define TIM3TIMER       (2499)    
#define TIM2TIMER       (5999)      

volatile u8  TimeNoOutflag ;
volatile u8	Time3Overflowflag ;
volatile u8 Time4Overflowflag  ;

void init_tim(void) ;
void Time4OverflowHandle(void) ;
void Delayuint_126ns(u16 delay) ;
void TMI3OverflowProcess(void );
void Time2OverflowHandle(void) ;
void uart3RecrHandle(void) ;



#endif /*_TIM_H_*/

