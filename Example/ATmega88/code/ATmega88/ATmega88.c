/*
 * A.c
 *
 * Created: 11/17/2019 2:33:46 PM
 * Author : Md.Tarikul Islam Juel
 * md.tarikulislamjuel@gmail.com
 */ 


#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#include <avr/io.h>
#include "lib/AVR_ADC_MASTER_JUEL.h"


int main(void)
{
	uint16_t DATA;
	DDRD |=(1<<PD0);//pin PD0 set as OUTPUT 

	//ADC_INIT(128,AREF);
	
	while(1)

	{	DATA = analogRead(A0);//pin ADC0 set as INPUT


		if (DATA>=512)
		{
			PORTD |=(1<<PD0);
		}
		else
		{
			PORTD &= ~(1<<PD0);
		}
		
	}

}

