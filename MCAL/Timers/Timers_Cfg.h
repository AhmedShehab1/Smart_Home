/*
 * Timers_Cfg.h
 *
 *  Created on: ?? ???? ?????? ???? ??
 *      Author: Acer
 */

#ifndef INCLUDE_MCAL_TIMERS_TIMERS_CFG_H_
#define INCLUDE_MCAL_TIMERS_TIMERS_CFG_H_

#define TIMER0_MODE FAST_PWM_MODE

#define TIMER1_MODE CTC_MODE
#define TIMER0_CLK 0b010
#define TIMER2_CLK 0b010
#define OCR0_VALUE 199

#define OCR2_VALUE 199

#define CTC_OC0_MODE 0b00
#define CTC_OC2_MODE 0b00


#define FAST_PWM_OC0_MODE 3

#endif /* INCLUDE_MCAL_TIMERS_TIMERS_CFG_H_ */
