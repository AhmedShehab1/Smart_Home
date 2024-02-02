/*
 * LED_Program.c
 *
 *  Created on: ?? ???? ???? ??
 *      Author: Acer
 */
#include "../Include/LIB/STD_TYPES.H"
#include "../Include/LIB/BIT_MATH.H"

#include "../Include/MCAL/DIO/DIO_Interface.h"


#include "../Include/HAL/LED/LED_Interface.h"
#include "../Include/HAL/LED/LED_Private.h"
#include "../Include/HAL/LED/LED_Cfg.h"

void HLED_voidTurnOn	(DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID)
{
MDIO_voidSetPinDirection(A_DIOPort,A_PINID,DIO_OUTPUT);
MDIO_voidSetPinValue(A_DIOPort,A_PINID,DIO_SET);

}
void HLED_voidTurnOff	(DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID)
{

	MDIO_voidSetPinValue(A_DIOPort,A_PINID,DIO_RESET);
}
void HLED_voidToggleLED	(DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID)
{
MDIO_voidTogglePinValue(A_DIOPort,A_PINID);
}
