/*
 * ATtiny24.c
 *
 * Created: 12/7/2019 11:07:47 AM
 *  Author: Md. Tarikul Islam Juel
 */ 


#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#include <avr/io.h>
#include "lib/AVR_ADC_MASTER_JUEL.h"


int main(void)
{
	uint16_t DATA;
	DDRB |=(1<<PB2);//pin PD0 set as OUTPUT

	//ADC_INIT(128,AREF);
	
	while(1)

	{	DATA = analogRead(A1);//pin ADC1 set as INPUT


		if (DATA>=512)
		{
			PORTB |=(1<<PB2);
		}
		else
		{
			PORTB &= ~(1<<PB2);
		}
		
	}

}