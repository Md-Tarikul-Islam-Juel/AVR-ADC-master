/*
 * AVR_ADC_MASTER_JUEL.h
 *
 *  Created: 12/07/2019 3:18:34 PM
 *  Author: Md. Tarikul Islam Juel
 *  Email: md.tarikulislamjuel@gmail.com
 */ 


#ifndef AVR_ADC_MASTER_JUEL_H_
#define AVR_ADC_MASTER_JUEL_H_



//-----------------This preprocessor ensure before compiling for the right MCU------------//
#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)
#elif defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)
#elif defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)
#elif defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)
#elif defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
#elif defined(__AVR_ATmega8535__)
#elif defined(__AVR_ATmega8__)
#elif defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)
#elif defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)
#elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny24A__)
#elif defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny44A__)
#elif defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny84A__)
#else
	#error "no definitions available for this AVR"
#endif




//-----------------------------------------------------------------------------------------------------//
#include <avr/io.h>

#define AREF 10                 
#define AVCC 11                 
#define INTERNAL 12             
#define INTERNAL1v1 13
#define INTERNAL2v56 14

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7
//-----------------------------------------------------------------------------------------------------//



//------------------------------------All the function--------------------------------------//
void ADC_INIT(uint8_t prescaler,uint8_t Voltage_Reference);// use this function from your main project
uint16_t analogRead(uint8_t channel);// use this function from your main project

void ADC_PRESCALER_SET(uint8_t prescaler);//This function is design for only inside this library
void ADC_voltage_Reference(uint8_t Reference_Voltage);//This function is design for only inside this library
//------------------------------------------------------------------------------------------//



#endif /* AVR_ADC_MASTER_JUEL_H_ */