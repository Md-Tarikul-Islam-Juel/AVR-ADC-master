/*
 * AVR_ADC_MASTER_JUEL.h
 *
 * Created: 11/24/2019 12:18:23 AM
 *  Author: juel
 */ 


#ifndef AVR_ADC_MASTER_JUEL_H_
#define AVR_ADC_MASTER_JUEL_H_



//-----------------This preprocessor ensure before compiling for the right board------------//
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
#else
	#error "no definitions available for this AVR"
#endif
//------------------------------------------------------------------------------------------//



//------------------------------------------------------------------------------------------//
#include <avr/io.h>

#define AREF 0                 // 0 0
#define AVCC 1                 // 0 1
#define INTERNAL 3             // 1 1
//------------------------------------------------------------------------------------------//



//------------------------------------All the function--------------------------------------//
void ADC_INIT(uint8_t prescaler,uint8_t Voltage_Reference);
void ADC_PRESCALER_SET(uint8_t prescaler);
void ADC_voltage_Reference(uint8_t Reference_Voltage);
uint16_t ADC_READ(uint8_t channel);
//------------------------------------------------------------------------------------------//



#endif /* AVR_ADC_MASTER_JUEL_H_ */