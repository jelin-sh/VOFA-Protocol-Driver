#include "gd32f30x.h"
#include "Vofa.h"

void Vofa_SendDataCallBack(Vofa_HandleTypedef* handle,uint8_t* data,uint16_t length)
{
	uint16_t i;
	for(i = 0;i<length;i++)
	{
		usart_data_transmit(USART1,data[i]);
		while(RESET == usart_flag_get(USART1,USART_FLAG_TBE));
	}	
}

uint8_t Vofa_GetDataCallBack(Vofa_HandleTypedef* handle)
{
	return usart_data_receive(USART1);
}