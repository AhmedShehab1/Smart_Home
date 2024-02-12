/*
 * ADC_Program.c
 *
 *  Created on:
 *      Author: Ahmed Abdelghafar
 */
#include "../Include/LIB/STD_TYPES.h"
#include "../Include/LIB/BIT_MATH.h"
#include <util/delay.h>

#include "../Include/MCAL/DIO/DIO_Interface.h"

// Include ADC
#include "../Include/MCAL/ADC/ADC_Interface.h"
#include "../Include/MCAL/ADC/ADC_Private.h"
#include "../Include/MCAL/ADC/ADC_Cfg.h"
#define NULL ((void *)0)

void (*ADC_CallBack)(void) = NULL;
void MADC_voidInit (void)
{
	SET_BIT(ADMUX, PIN6);
	CLR_BIT(ADMUX, PIN7);

	CLR_BIT(ADMUX, PIN5);

	SET_BIT(ADCSRA, PIN5); //Auto Trigger Enable
	/*Set PreScaler*/
	CLR_BIT(ADCSRA, PIN0);
	SET_BIT(ADCSRA, PIN1);
	SET_BIT(ADCSRA, PIN2);
	/*            */
	SET_BIT(ADCSRA, PIN7); //ADC Enable
	SET_BIT(ADCSRA, PIN3); //ADC Interrupt
	//Start Conversion
	SET_BIT(ADCSRA, PIN6);

}

u16 MADC_u16GetDigitalValue(ADC_Channels A_AdcChannel)
{
	u16 local_u16DigitalValue = 0;
	if(A_AdcChannel <= 31)
	{
		ADMUX &= ADC_CHANNEL_MASK;
		ADMUX |= A_AdcChannel;

		//Start Conversion
		//SET_BIT(ADCSRA, PIN6);

		//Polling On Flag
		//while(GET_BIT(ADCSRA, PIN4) == 0);

        //Clear INT. Flag
		//SET_BIT(ADCSRA, PIN4);

		//Read Conversion Value
		local_u16DigitalValue = ADCLH;

   }
//Return Result Of Conversion
return (local_u16DigitalValue);

}

void MADC_voidSetCallBack(void (*A_PtrToFunc)(void))
{
	if (A_PtrToFunc != NULL)
	{
		ADC_CallBack = A_PtrToFunc;
	}
}
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if (ADC_CallBack != NULL)
	{
		ADC_CallBack();
	}
}
