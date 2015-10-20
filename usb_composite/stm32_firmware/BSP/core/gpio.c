
/***************************************************************************************
****************************************************************************************
* FILE		: gpio.c
* Description	: 
*			  
* Copyright (c) 2015 by tuqiang. All Rights Reserved.
* 
* History:
* Version		Name       		Date             Description
    0.1		      tuqiang         2015/08/10	  Initial Version
   
****************************************************************************************
****************************************************************************************/
#include "gpio.h"

/*==================================================================
* Function	  : 74hc154d_gpio
* Description   : 
* Inputpara     : 
* Outputpara   : 
==================================================================*/
static void hc154d_gpio_led_init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure ;
   
   RCC_APB2PeriphClockCmd(RCC_HC154D_LED_GPIOPERIPH, ENABLE);
	  
	  
   GPIO_InitStructure.GPIO_Pin = HC154D_LED_A0| HC154D_LED_A1| HC154D_LED_A2|HC154D_LED_A3;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(HC_LED_GPIO, &GPIO_InitStructure);

   GPIO_ResetBits(HC_LED_GPIO,HC154D_LED_A0| HC154D_LED_A1| HC154D_LED_A2|HC154D_LED_A3)  ;

}
static void hc154d_gpio_RS485EN_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure ;
   
   RCC_APB2PeriphClockCmd(RCC_HC154D_RS485_GPIOPERIPH, ENABLE);
   GPIO_InitStructure.GPIO_Pin = HC154D_RS485_ADDR0|
   	                                 HC154D_RS485_ADDR1 | 
   	                                 HC154D_RS485_ADDR2 |
   	                                 HC154D_RS485_ADDR3 |
   	                                 HC154D_RS485_ADDR4 |
   	                                 HC154D_RS485_ADDR5 |
   	                                 HC154D_RS485_ADDR6 | 
   	                                 HC154D_RS485_ADDR7 |
   	                                 HC_RS485_RX_EN_GPIO;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(HC_RS485_GPIO, &GPIO_InitStructure);
   HC154D_RS485_RX_SELECT(0) ;
  
}


void gpio_init(void)
{
	hc154d_gpio_led_init();
	hc154d_gpio_RS485EN_init();
}


