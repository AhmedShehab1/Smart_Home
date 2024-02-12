/*
 * Timers_Interface.h
 *
 *  Created on: ?? ???? ?????? ???? ??
 *      Author: Acer
 */

#ifndef INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_
#define INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_

#define NORMAL_MODE       0
#define PHASE_CORRECT_MODE     1
#define CTC_MODE       2
#define FAST_PWM_MODE       3

#define Five_Minutes 5000
void MTIMER0_voidInit (void);
void MTIMER0_voidSetPreloadValue (u8 A_u8NoOfTicks);
void MTIMER0_voidSetOVFCallBack (void(*A_PtrToFunc)(void));
void MTIMER0_voidSetCTCCallBack (void(*A_PtrToFunc)(void));
void MTIMER0_voidSetOCR0Value (u8 A_u8OCR0Value);
void MTIMER0_voidStopTimer (void);
void MTIMER0_voidSetOCR0Value (u8 A_u8OCR0Value);
void MTIMER1_voidSetOCR1AValue (u16 A_u16Value);
void MTIMER1_voidInit (void);
u16 MTIMER1_u16ReadTimerValue(void);
void MTIMER1_voidSetTimerValue(u16 A_u16Value);
void MTIMER1_voidInitSWICU();
void MTIMER1_voidSetOCR1BValue(u16 A_u16Value);
void MTIMER2_voidSetCTCCallBack(void (*A_PtrToFunction)(void));
void MTIMER2_voidInit(void);
#endif /* INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_ */
