/*
 * UART_Private.h
 *
 *  Created on: ? ???? ?????? ???? ??
 *      Author: Acer
 */

#ifndef INCLUDE_MCAL_UART_UART_PRIVATE_H_
#define INCLUDE_MCAL_UART_UART_PRIVATE_H_

#define UCSRA (*(volatile u8 *)0x2B)

#define UCSRB (*(volatile u8 *)0x2A)

#define UCSRC (*(volatile u8 *)0x40)

#define UBRRH (*(volatile u8 *)0x40)

#define UDR   (*(volatile u8 *)0x2C)

#define UBRRL (*(volatile u8 *)0x29)

#define BAUD_RATE_EQUATION (F_CPU/16/BAUDRATE_VALUE-1)

#endif /* INCLUDE_MCAL_UART_UART_PRIVATE_H_ */
