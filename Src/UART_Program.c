/*
 * UART_Program.c
 *
 *  Created on: DEC 23, 2023
 *      Author:Ahmed Abdelghafar
 */
#include <util/delay.h>
#include "../Include/LIB/STD_TYPES.h"
#include "../Include/LIB/BIT_MATH.h"


#include "../Include/MCAL/UART/UART_Interface.h"
#include "../Include/MCAL/UART/UART_Private.h"
#include "../Include/MCAL/UART/UART_Cfg.h"

#define F_CPU 8000000UL
#define NULL 0

static void (*FuncPtr[3]) (void) = {NULL,NULL,NULL};
void MUART_voidInit(void)
{
	u16 local_u16BaudRate = BAUD_RATE_EQUATION;

	//Set BaudRate
	UBRRL = (u8) local_u16BaudRate;
	UBRRH = (u8) (local_u16BaudRate >> 8);

	CLR_BIT(UCSRB,2);
//configuration of Various Settings
	UCSRC = CONC_BIT(1,0,0,0,0,1,1,0);
//Enabling Transmitter & Receiver
	SET_BIT(UCSRB,3);
	SET_BIT(UCSRB,4);
}

void MUART_voidSendByteSyncBlocking(u8 A_u8DataByte)
{
	while(GET_BIT(UCSRA, 5) == 0);

	UDR = A_u8DataByte;

	while(GET_BIT(UCSRA, 5) == 0);

	SET_BIT(UCSRA,6);
}

void MUART_voidSendByteSyncNonBlocking(u8 A_u8DataByte)
{
	u32 local_u32TimeOut = 0;

 	 while(GET_BIT(UCSRA,5)==0)
 	 {
        local_u32TimeOut++;
        if(local_u32TimeOut == NON_BLOCKING_TIME_OUT)
        {
        	break;
        }
 	 }
 	 if(local_u32TimeOut != NON_BLOCKING_TIME_OUT)
 	 {
 		 local_u32TimeOut = 0;
 		 UDR = A_u8DataByte;
 		while(GET_BIT(UCSRA,5)==0)
 		 	 {
 		        local_u32TimeOut++;
 		        if(local_u32TimeOut == NON_BLOCKING_TIME_OUT)
 		        {
 		        	break;
 		        }
 		 	 }
 		SET_BIT(UCSRA,6);
 	 }
}

void MUART_voidSendStringSyncNonBlocking(u8 *A_pu8String)
{
	while(*A_pu8String > 0)
	{
		MUART_voidSendByteSyncNonBlocking(*A_pu8String++);
	}
}

void MUART_voidSendStringSyncBlocking(u8 *A_pu8String)
{
	while(*A_pu8String > 0)
	{
		MUART_voidSendByteSyncBlocking(*A_pu8String++);
	}
}

u8 MUART_u8ReadByteSyncBlocking(void)
{
	//Wait For RX Flag To Receive New Data
	while(GET_BIT(UCSRA,7)==0);

	return UDR;
}

void MUART_voidSendByteAsync(u8 A_u8DataByte)
{
	if(GET_BIT(UCSRA,5)==0)
	{
		UDR = A_u8DataByte;
	}
}


u8 MUART_u8ReadByteAsync(void)
{
	//Used With Interrupt
 return UDR;
}

u8 MUART_u8ReadByteSyncNonBlocking(void)
{
	u8 local_u8ReceivedData = NO_VALUE_RETURNED;//
	u32 local_u32TimeOut = 0;
	while(GET_BIT(UCSRA,7)==0)
	{
		local_u32TimeOut++;
		if(local_u32TimeOut == NON_BLOCKING_TIME_OUT)
		{
			break;
		}
	}
	if(local_u32TimeOut != NON_BLOCKING_TIME_OUT)
	{
		local_u8ReceivedData = UDR;
	}
	//Will Return 255 If No Data Was Received
   return (local_u8ReceivedData);
}

void MUART_voidSetCallBack(UART_INTERRUPT_e A_InterruptSource , void (*A_PToFunc)(void))
{
	if((A_InterruptSource <= UART_TX_INTERRUPT)&&(A_PToFunc != NULL))
	{
		FuncPtr [A_InterruptSource] = A_PToFunc;
	}
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	if(FuncPtr[UART_RX_INTERRUPT] != NULL)
	{
		FuncPtr[UART_RX_INTERRUPT]();
	}
}

void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
	if(FuncPtr[UART_UDRE_INTERRUPT] != NULL)
		{
			FuncPtr[UART_UDRE_INTERRUPT]();
		}
}

void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
	if(FuncPtr[UART_TX_INTERRUPT] != NULL)
			{
				FuncPtr[UART_TX_INTERRUPT]();
			}
}
