/*
 * app.c
 *
 *  Created on: DEC 23, 2023
 *      Author:Ahmed Abdelghafar
 */



#include "../Include/LIB/STD_TYPES.h"
#include "../Include/LIB/BIT_MATH.h"

#include "../Include/MCAL/DIO/DIO_Interface.h"
#include "../Include/MCAL/UART/UART_Interface.h"
#include "../Include/MCAL/TWI/TWI_interface.h"
#include "../Include/MCAL/Timers/Timers_Interface.h"
#include "../Include/MCAL/ADC/ADC_Interface.h"
#include "../Include/MCAL/GI/GI_interface.h"

#include "../Include/HAL/LED/LED_Interface.h"
#include "../Include/HAL/EEPROM/EEPROM_interface.h"

#include <util/delay.h>
#include <string.h>
#define F_CPU 8000000UL











u32 global_u32CheckTime;
void Timer2_CTC_ISR(void)
{
	global_u32CheckTime++;
}
void ADC_ISR(void)
{
	u16 local_u16DigitalValue, local_u16AnalogValue;
	local_u16DigitalValue = MADC_u16GetDigitalValue(ADC3);
	local_u16AnalogValue = (local_u16DigitalValue * 500UL) / 1024;
	if (local_u16AnalogValue >= 0 && local_u16AnalogValue < 256)
	{
		MTIMER0_voidSetOCR0Value(local_u16AnalogValue);
		_delay_ms(200);
	}
	if (global_u32CheckTime == Five_Minutes)
	{
		global_u32CheckTime = 0;
		local_u16DigitalValue = MADC_u16GetDigitalValue(ADC2);
		local_u16AnalogValue = (local_u16DigitalValue * 500) / 1024;
		if (local_u16AnalogValue < 20)
		{
			MTIMER1_voidSetOCR1BValue(0);
		}
		else if (local_u16AnalogValue >= 20 && local_u16AnalogValue < 25)
		{
			MTIMER1_voidSetOCR1BValue(9000);
		}
		else if (local_u16AnalogValue >= 25)
		{
			MTIMER1_voidSetOCR1BValue(19999);
		}
	}
}
u8 Pre_Defined_Users [10][2][12] = {
								 {"Ahmed", "Shehab"},
								 {"Ahmed", "Reda"},
								 {"Mahmoud", "Bahaa"},
								 {"Mohanad", "Fathy"},
								 {"Mazen", "Atlam"},
								 {"Sherif", "Gendy"},
								 {"Marwan", "Yasser"},
								 {"Anas", "El-Sheikh"},
								 {"Nasser", "Al-Ali"},
								 {"Abdulrahman", "Hossam"}
};

int main(void)
{
	u8 local_u8ReceivedData = 254, Provided_Data[12], i, User_Exists, Password_Incorrect = 4, Flag = 0;
	MDIO_voidInit();
	MUART_voidInit();
	MGI_voidEnable();
	MADC_voidSetCallBack(ADC_ISR);
	MTIMER0_voidInit();
	MTIMER2_voidInit();
	MTIMER2_voidSetCTCCallBack(Timer2_CTC_ISR);
	MADC_voidInit();
	MTIMER1_voidInit();
	while(1)
	{
		i = 0, local_u8ReceivedData = 254;
		MUART_voidSendStringSyncBlocking("Enter UserName :  ");
		while (i < sizeof(Provided_Data) && local_u8ReceivedData != 255)
		{
			local_u8ReceivedData = MUART_u8ReadByteSyncNonBlocking();
			Provided_Data[i] = local_u8ReceivedData;
			i++;
		}
		i = 0;
		while (i < 10)
		{
			if (strncmp(Pre_Defined_Users[i][0], Provided_Data, strlen(Pre_Defined_Users[i][0])) == 0)
			{
				break;
			}
			i++;
		}
		if (i == 10)
		{
			MUART_voidSendStringSyncBlocking("User Doesnt Exist, Please Try Again\r\n");
		}
		else
		{
			User_Exists = i;
			MUART_voidSendStringSyncNonBlocking("\r\nWelcome  ");
			MUART_voidSendStringSyncNonBlocking(Pre_Defined_Users[User_Exists][0]);
			MUART_voidSendStringSyncNonBlocking(" ! Please Enter Password Associated With Your Account\r\n");
			PasswordIncorrect:
			i = 0;
			local_u8ReceivedData = 254;
			while (i < sizeof(Provided_Data) && local_u8ReceivedData != 255)
				{
					local_u8ReceivedData = MUART_u8ReadByteSyncNonBlocking();
					Provided_Data[i] = local_u8ReceivedData;
					i++;
				}
			if (strncmp(Pre_Defined_Users[User_Exists][1], Provided_Data, strlen(Pre_Defined_Users[User_Exists][1])) == 0)
			{
				MUART_voidSendStringSyncNonBlocking("Authentication Approved\r\n");
				MUART_voidSendStringSyncNonBlocking("Press (1) To Toggle LED Or (0) To Open/Close Door\r\n");
				while (1)
				{
					local_u8ReceivedData = MUART_u8ReadByteSyncBlocking();
					if (local_u8ReceivedData == '1' || local_u8ReceivedData =='0')
					{
						while (local_u8ReceivedData == '1')
						{
							HLED_voidToggleLED(DIO_PORTA, PIN0);
							local_u8ReceivedData = MUART_u8ReadByteSyncNonBlocking();
						}
						while(local_u8ReceivedData == '0')
						{
							if (Flag == 0)
							{
								MTIMER1_voidSetOCR1AValue(2000);
								Flag = 1;
								local_u8ReceivedData = MUART_u8ReadByteSyncBlocking();
								continue;
							}
							if (Flag == 1)
							{
								MTIMER1_voidSetOCR1AValue(1000);
								Flag = 0;
							}
							local_u8ReceivedData = MUART_u8ReadByteSyncNonBlocking();
						}
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				MUART_voidSendStringSyncNonBlocking("Password Provided Is Incorrect\r\n");
				while (Password_Incorrect-- > 1)
				{
					 MUART_voidSendStringSyncNonBlocking("You Have ");
					 MUART_voidSendByteSyncBlocking(Password_Incorrect + 48);
					 MUART_voidSendStringSyncNonBlocking(" Remaining Chances\r\n");
					goto PasswordIncorrect;
				}
				MUART_voidSendStringSyncNonBlocking("Failed To Authenticate User \r\n Siren On\r\n");
				MDIO_voidSetPinValue(DIO_PORTA, PIN1, DIO_SET);
				_delay_ms(2000);
				MDIO_voidSetPinValue(DIO_PORTA, PIN1, DIO_RESET);
				_delay_ms(1200);
				Password_Incorrect = 4;
			}
		}
	}
}
