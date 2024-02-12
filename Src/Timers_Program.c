/*
 * Timers_Program.c
 *
 *  Created on:
 *      Author: Ahmed Abdelghafar
 */

#include "../Include/LIB/STD_TYPES.h"
#include "../Include/LIB/BIT_MATH.h"


#include "../Include/MCAL/Timers/Timers_Interface.h"
#include "../Include/MCAL/Timers/Timers_Private.h"
#include "../Include/MCAL/Timers/Timers_Cfg.h"
#include "../Include/MCAL/DIO/DIO_Interface.h"
#define NULL ((void *)0)
void (*TIMER0_OVF_CALLBACK)(void) = NULL;
void (*TIMER0_CTC_CALLBACK)(void) = NULL;
void (*TIMER2_CTC_CALLBACK)(void) = NULL;
void MTIMER0_voidInit (void)
{
#if TIMER0_MODE == NORMAL_MODE
    CLR_BIT(TCCR0,3);
    CLR_BIT(TCCR0,6);
//Enable OVF Interrupt
    SET_BIT(TIMSK,0);
    CLR_BIT(TIMSK,1);

    TCCR0 &= 0b11111000;
    TCCR0 |= TIMER0_CLK;
#elif TIMER0_MODE == PHASE_CORRECT_MODE

#elif TIMER0_MODE == CTC_MODE
    SET_BIT(TCCR0,3);
    CLR_BIT(TCCR0,6);

    SET_BIT(TIMSK,1);
    CLR_BIT(TIMSK,0);
//Set OCR0 Value
    OCR0 = OCR0_VALUE;
//Starting Timer By Setting Its Clock
    TCCR0 &= 0b11001000;
    TCCR0 |= (TIMER0_CLK | (CTC_OC0_MODE << 4));

#elif TIMER0_MODE == FAST_PWM_MODE
//Set WaveForm Generation Mode To Fast PWM
SET_BIT(TCCR0,PIN3);
SET_BIT(TCCR0,PIN6);
//Disable All Interrupts
CLR_BIT(TIMSK,PIN1);
CLR_BIT(TIMSK,PIN0);
//Set OCR0 Value
OCR0 = OCR0_VALUE;
//Set OC0 Pin Mode
TCCR0 &= TIMER0_CLK_OC0_MASK;
TCCR0 |= (TIMER0_CLK | (FAST_PWM_OC0_MODE << 4));
#endif
}
void MTIMER0_voidSetCTCCallBack(void(*A_PtrToFunc)(void))
{
	if (A_PtrToFunc != NULL)
	{
		TIMER0_CTC_CALLBACK = A_PtrToFunc;
	}
}
void MTIMER0_voidSetOCR0Value(u8 A_u8OCR0Value)
{
	OCR0 = A_u8OCR0Value;
}

void MTIMER0_voidSetPreloadValue(u8 A_u8NoOfTicks)
{
	TCNT0 = A_u8NoOfTicks;
}

void MTIMER0_voidStopTimer(void)
{
	//Remove Clock Source
	TCCR0 &= 0b11111000;
}

void MTIMER0_voidSetOVFCallBack(void (*A_PtrToFunc)(void))
{

	if (A_PtrToFunc != NULL)
	{
		TIMER0_OVF_CALLBACK = A_PtrToFunc;
	}

}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if (TIMER0_OVF_CALLBACK != NULL)
	{
		(*TIMER0_OVF_CALLBACK)();
	}
}
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if(TIMER0_CTC_CALLBACK != NULL)
	{
		TIMER0_CTC_CALLBACK();
	}
}


void MTIMER1_voidInit (void)
{
	//Select Timer 1 Mode => 14
	CLR_BIT(TCCR1A,PIN0);
	SET_BIT(TCCR1A,PIN1);
	SET_BIT(TCCR1B,PIN3);
	SET_BIT(TCCR1B,PIN4);
	//Non Inverting Mode for OC1A
	CLR_BIT(TCCR1A,PIN6);
	SET_BIT(TCCR1A,PIN7);
	//Non Inverting Mode for OC1B
	CLR_BIT(TCCR1A,PIN4);
	SET_BIT(TCCR1A,PIN5);
	ICR1 = 19999;

	OCR1A = 0;
	OCR1B = 0;
	//Start Timer
	CLR_BIT(TCCR1B,PIN0);
	SET_BIT(TCCR1B,PIN1);
    CLR_BIT(TCCR1B,PIN2);
}

void MTIMER1_voidSetOCR1AValue (u16 A_u16Value)
{
	OCR1A = A_u16Value;
}

void MTIMER1_voidSetOCR1BValue(u16 A_u16Value)
{
	OCR1B = A_u16Value;
}
void MTIMER1_voidInitSWICU()
{
	//Start Timer By Setting Its Clock Pre-Scalar
	  	CLR_BIT(TCCR1B,PIN0);
		SET_BIT(TCCR1B,PIN1);
	    CLR_BIT(TCCR1B,PIN2);
}

void MTIMER1_voidSetTimerValue(u16 A_u16Value)
{
	TCNT1 = A_u16Value;
}

u16 MTIMER1_u16ReadTimerValue(void)
{
	return TCNT1;
}

void MTIMER2_voidInit(void)
{
	#if TIMER1_MODE == NORMAL_MODE

	#elif TIMER1_MODE == PHASE_CORRECT_MODE

	#elif TIMER1_MODE == CTC_MODE
		//Set Waveform Generation --> CTC
		SET_BIT(TCCR2, 3);
		CLR_BIT(TCCR2, 6);
		//Set OCR2 Value
		OCR2 = OCR2_VALUE;
		// Enable Compare Match Interrupt
		SET_BIT(TIMSK, 7);
		CLR_BIT(TIMSK, 6);
		//Start Timer By Setting Prescaler
		TCCR2 &= 0b11111000;
		TCCR2 |= (TIMER2_CLK | (CTC_OC2_MODE << 4));
	#elif TIMER1_MODE == FAST_PWM_MODE

	#endif
}
void MTIMER2_voidSetCTCCallBack(void (*A_PtrToFunction)(void))
{
	if (A_PtrToFunction != NULL)
	{
		TIMER2_CTC_CALLBACK = A_PtrToFunction;
	}
}
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	if (TIMER2_CTC_CALLBACK != NULL)
	{
		(*TIMER2_CTC_CALLBACK)();
	}
}
