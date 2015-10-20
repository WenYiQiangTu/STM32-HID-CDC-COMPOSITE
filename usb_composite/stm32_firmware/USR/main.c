#include "hw_config.h"
#include  "usb_lib.h"
#include "usb_pwr.h"
extern vu32 bDeviceState ;
extern __IO uint8_t PrevXferComplete ;
extern uint8_t Receive_Buffer_from_hid[16];

void test_hid_from_pc(void){
	static u32 cnt = 0 ;
	static u8 SendDatatoUSB[16] = {0x78,0x78,0x76} ;
   //发送的数据
    cnt ++ ;
  if(((PrevXferComplete) && (bDeviceState == CONFIGURED))&& cnt >= 2000000){
		PrevXferComplete = 0 ;
	 UserToPMABufferCopy((u8*)(SendDatatoUSB), ENDP3_TXADDR, 16);
	 *(SendDatatoUSB + 3 ) += 1  ;
	 *(SendDatatoUSB + 15 ) += 1 ;
     SetEPTxValid(ENDP3);
     cnt = 0 ;
   } 
 }

int main(void)
{
 
	Set_System();
	USB_Interrupts_Config();
	USB_Init();
	while(1){
	  if( 1 /*Receive_Buffer_from_hid[0] == 'a' */ ){
	  test_hid_from_pc();
	  }
	}
}
