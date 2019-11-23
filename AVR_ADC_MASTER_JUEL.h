/*
 * AVR_ADC_MASTER_JUEL.h
 *
 * Created: 11/24/2019 12:18:23 AM
 *  Author: juel
 */ 


#ifndef AVR_ADC_MASTER_JUEL_H_
#define AVR_ADC_MASTER_JUEL_H_



//-----------------This preprocessor ensure before compiling for the right board------------//
#if defined (__AVR_ATmega32__) || defined (__AVR_ATmega32A__)
#elif defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
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