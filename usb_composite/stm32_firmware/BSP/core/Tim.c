
/***************************************************************************************
****************************************************************************************
* FILE		: Tim.c
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/11	  Initial Version
   
****************************************************************************************
****************************************************************************************/
#include "tim.h"
#include "stm32f10x_dma.h"  
#include "stm32f10x_usart.h"
#include "dma.h"
static void ConfigTimer4(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_DeInit(TIM4);
	  /* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = TIM4TIMER; //定时126ns
    TIM_TimeBaseStructure.TIM_Prescaler =2;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	TIM_ClearFlag(TIM4,TIM_FLAG_Update); 			
	TIM_Cmd(TIM4,DISABLE);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  
}

/*==================================================================
* Function	 : Time4OverflowHandle
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
volatile u8 Time4Overflowflag = 0 ;
void Time4OverflowHandle(void)
{
	Time4Overflowflag = 1 ;
}
/*==================================================================
* Function	 : Delayuint_84us
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
void Delayuint_126ns(u16 delay)
{
 	TIM_Cmd(TIM4,ENABLE) ;   
    while (delay){
		if (Time4Overflowflag) {  
		   Time4Overflowflag = 0; 
		   delay-- ;  
		}    
	}
	
	TIM_Cmd(TIM4,DISABLE) ;
    TIM4->CNT = 0 ;
}
/*==================================================================
* Function	 : ConfigTimer3
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
static  void ConfigTimer3(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_DeInit(TIM3);
	  /* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = TIM3TIMER; //2.5ms
    TIM_TimeBaseStructure.TIM_Prescaler =71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	TIM_ClearFlag(TIM3,TIM_FLAG_Update); 			
	TIM_Cmd(TIM3,DISABLE);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 
}
/*==================================================================
* Function	 : TMI3Process
* Description	: 
* Inputpara 	: 
* Outputpara   : 
==================================================================*/
volatile u8	Time3Overflowflag = 0;
void TMI3OverflowProcess()
{
	Time3Overflowflag =1;
}
/**********************Timer2 interface***********************************/
/*==================================================================
* Function	 : ConfigTimer2
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/


static void ConfigTimer2(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_DeInit(TIM2);
	  /* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = TIM2TIMER;   //定时6ms
    TIM_TimeBaseStructure.TIM_Prescaler =71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	TIM_ClearFlag(TIM2,TIM_FLAG_Update); 			
	TIM_Cmd(TIM2,DISABLE); 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  
}


/*==================================================================
* Function	 : Time2OverflowHandle
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================  */
volatile u8  TimeNoOutflag = 0;
void Time2OverflowHandle(void)
{
	if(TimeNoOutflag == 1){
		TimeNoOutflag = 0 ;
		USART_ITConfig(USART3, USART_IT_RXNE,ENABLE); 
	}
	else{  //DMA重新复位
		DMA_Cmd(DMA1_Channel3, DISABLE);
		DMA_SetCurrDataCounter(DMA1_Channel3, DMA_BUFFSIZE);
		DMA_Cmd(DMA1_Channel3, ENABLE);
		TIM_Cmd(TIM2,DISABLE); 
	}
}
/*==================================================================
* Function	 : uart3RecrHandle
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================  */
void uart3RecrHandle(void)
{
	TimeNoOutflag = 1;
	TIM_Cmd(TIM2,ENABLE); 
	USART_ITConfig(USART3, USART_IT_RXNE,DISABLE); 
}

/*==================================================================
* Function	 : init_tim
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
void init_tim(void)
{
	 ConfigTimer2();
	 ConfigTimer3();
	 ConfigTimer4();
}
