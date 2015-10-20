
/***************************************************************************************
****************************************************************************************
* FILE		: led.h
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/10	  Initial Version
   
****************************************************************************************
****************************************************************************************/


#ifndef _LED_H_
#include "stm32f10x_gpio.h"
#define _LED_H_


#define RCC_HC154D_LED_GPIOPERIPH     RCC_APB2Periph_GPIOC
#define HC_LED_GPIO   GPIOC

#define HC154D_LED_A0    GPIO_Pin_6
#define HC154D_LED_A0_MASK  0xffffffbf

#define HC154D_LED_A1    GPIO_Pin_7
#define HC154D_LED_A1_MASK  0xffffff7f

#define HC154D_LED_A2    GPIO_Pin_8
#define HC154D_LED_A2_MASK  0xfffffeff

#define HC154D_LED_A3    GPIO_Pin_9
#define HC154D_LED_A3_MASK  0xfffffdff

#define HC154D_LED_GPIO_MASK   HC154D_LED_A0_MASK & HC154D_LED_A1_MASK & HC154D_LED_A2_MASK&HC154D_LED_A2_MASK
#define HC154_LED_SELECT(x)   HC_LED_GPIO->ODR =  (HC_LED_GPIO->ODR &  HC154D_LED_GPIO_MASK ) | (( x & 0x0f ) << 6 )



#define RCC_HC154D_RS485_GPIOPERIPH  RCC_APB2Periph_GPIOA 
#define HC_RS485_GPIO   GPIOA

#define HC154D_RS485_ADDR0    GPIO_Pin_0
#define HC154D_RS485_ADDR0_MASK  0xfffffffe

#define HC154D_RS485_ADDR1    GPIO_Pin_1
#define HC154D_RS485_ADDR1_MASK  0xffffffffd

#define HC154D_RS485_ADDR2    GPIO_Pin_2
#define HC154D_RS485_ADDR2_MASK  0xfffffffb

#define HC154D_RS485_ADDR3    GPIO_Pin_3
#define HC154D_RS485_ADDR3_MASK  0xfffffff7

#define HC154D_RS485_ADDR4    GPIO_Pin_4
#define HC154D_RS485_ADDR4_MASK  0xffffffef

#define HC154D_RS485_ADDR5    GPIO_Pin_5
#define HC154D_RS485_ADDR5_MASK  0xffffffdf

#define HC154D_RS485_ADDR6    GPIO_Pin_6
#define HC154D_RS485_ADDR6_MASK  0xffffffbf

#define HC154D_RS485_ADDR7    GPIO_Pin_7
#define HC154D_RS485_ADDR7_MASK  0xffffff7f

#define HC154D_RS485_MASK   HC154D_RS485_ADDR0_MASK & \
	                           HC154D_RS485_ADDR1_MASK & \
	                           HC154D_RS485_ADDR2_MASK & \
	                           HC154D_RS485_ADDR3_MASK & \
	                           HC154D_RS485_ADDR4_MASK & \
	                           HC154D_RS485_ADDR5_MASK & \
	                           HC154D_RS485_ADDR6_MASK & \
	                           HC154D_RS485_ADDR7_MASK 

#define HC_RS485_RX_EN_GPIO   GPIO_Pin_8
#define HC_RS485_RX_EN_GPIO_MASK 0xfffffEFf

#define HC154D_RS485_RX_SELECT(x)    HC_RS485_GPIO->ODR &= ( HC_RS485_RX_EN_GPIO_MASK) ;\ 
	                                   HC_RS485_GPIO->ODR = \
	                               (( HC_RS485_GPIO->ODR & HC154D_RS485_MASK ) | ( (x) & 0XFF ) ) 
#define HC154D_RS485_TX_ALL   HC_RS485_GPIO->ODR |= ( ~HC_RS485_RX_EN_GPIO_MASK) 

 void gpio_init(void) ;

#endif /*_LED_H_*/

