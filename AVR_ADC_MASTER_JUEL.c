/*
 * AVR_ADC_MASTER_JUEL.c
 *
 * Created: 11/24/2019 12:18:34 AM
 *  Author: juel
 *
 *	  ====================== Register ======================
 *	  ADMUX= REF1---REF0---ADLAR---MUX4--MUX3---MUx2---MUX1---MUX0
 *	  ADCSRA=ADEN---ADSC---ADATE---ADIF---ADIE---ADPS2---ADPS1---ADPS0
 *        ADC Data register
 *
 *
 *   	 ===================ADC_INI()   step===================
 *
 *    	 1) ADC enable	--------------------------------------ADEN=1
 *  	 2) set prescaler------------------------------------ADPS2,ADPS1,ADPS0 [set 3 bit combination for prescaler]		
 *   	 3) reference voltage select-------------------------REFS1,REFS0 [set 2 bit combination for reference voltage]
 *   	 4) left adjust of for data register-----------------ADLAR
 *
 *
 *	 ===================ADC_READ()   step===================
 *
 *	  5) Channel selection-------------------------------MUX4:MUX0[avr atmega32]-----------MUX3:MUX0[avr atmega328]
 *	  6) Start conversion enable-------------------------ADSC=1
 *	  7) Return received register data-------------------ADCH,ADCL,ADCW
 */ 

#include "AVR_ADC_MASTER_JUEL.h"


//################################################################################################################################################################################
//==============================================================|   ADC_INIT() Start	|=========================================================================================
//################################################################################################################################################################################

//	------------possible parameter---------
//	prescaler = 2,4,8,16,32,64,128
//      Voltage_Reference = AREF,AVCC,INTERNAL

void ADC_INIT(uint8_t prescaler, uint8_t Voltage_Reference)
{

	
	#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)\
		|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)\ 
		|| defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
		|| defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
		|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
		|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)\
		|| defined(__AVR_ATmega8535__)\
		|| defined(__AVR_ATmega8__)\
		|| defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)\
		|| defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)\
		|| defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)\
		|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
	
		ADCSRA |= (1<<ADEN); // ADC Enable
		ADC_PRESCALER_SET(prescaler); // set sampling frequency by prescaler bit
		ADC_voltage_Reference(Voltage_Reference); //set voltage reference //by default AVCC has been selected
		ADMUX &= ~(1<<ADLAR); //left adjust off // Though by default left adjust off // this line use for more convenient for future developer
	#endif
}
//################################################################################################################################################################################
//==============================================================|   ADC_INIT() End	|=============================================================================================
//################################################################################################################################################################################



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//==========================================================|   ADC_PRESCALER_SET() Start	|=====================================================================================
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// This function selects sampling frequency of ADC by selecting the prescaler bit
// if we set ADC Prescaler 128 means (Division Factor 128 to maintain ADC sampling frequency below 250KHz)(16MHz/128=125KHz)
void ADC_PRESCALER_SET(uint8_t prescaler)
{
	
	#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)\
		|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)\
		|| defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
		|| defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
		|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
		|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)\
		|| defined(__AVR_ATmega8535__)\
		|| defined(__AVR_ATmega8__)\
		|| defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)\
		|| defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)\
		|| defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)\
		|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
			ADCSRA &= (~(1<<ADPS2)) & (~(1<<ADPS1)) & (~(1<<ADPS0)) ; // clear ADPS2:ADPS0 for initialization
	
		switch(prescaler)
		{
			case 2:ADCSRA |= (1<<ADPS0);//-----------------------------------  0 0 1
			break;
			case 4:ADCSRA |= (1<<ADPS1);//-----------------------------------  0 1 0
			break;
			case 8:ADCSRA |= (1<<ADPS1) | (1<<ADPS0);//----------------------  0 1 1
			break;
			case 16:ADCSRA |= (1<<ADPS2);//----------------------------------  1 0 0
			break;
			case 32:ADCSRA |= (1<<ADPS2) | (1<<ADPS0);//---------------------  1 0 1
			break;
			case 64:ADCSRA |= (1<<ADPS2) | (1<<ADPS1);//---------------------  1 1 0
			break;
			case 128:ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);//-------  1 1 1
			break;
			default:ADCSRA &= (~(1<<ADPS2)) & (~(1<<ADPS1)) & (~(1<<ADPS0));// 0 0 0
		}
	#endif
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//==========================================================|   ADC_PRESCALER_SET() End  |=======================================================================================
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//======================================================|   ADC_voltage_Reference() Start  |======================================================================================
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//This function selects the voltage reference
//by default AVCC has been selected
void ADC_voltage_Reference(uint8_t Reference_Voltage)
{
	
	#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)\
		|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)\
		|| defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
		|| defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
		|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
		|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)\
		|| defined(__AVR_ATmega8535__)\
		|| defined(__AVR_ATmega8__)\
		|| defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)\
		|| defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)\
		|| defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)\
		||defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
		ADMUX &= (~(1<<REFS0)) & (~(1<<REFS1)); // clear REFS1:REFS0 for initialization
		ADMUX |= (1<<REFS0); // Default AVCC has been set
	
		if(Reference_Voltage==AREF){ADMUX &= (~(1<<REFS0)) & (~(1<<REFS1));}
		else if (Reference_Voltage==AVCC){ADMUX |= (1<<REFS0);}
		else if (Reference_Voltage==INTERNAL){ADMUX |= (1<<REFS1) | (1<<REFS0);}
		else{ADMUX |= (1<<REFS0);}
	#endif
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//======================================================|   ADC_voltage_Reference() End  |=======================================================================================
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//################################################################################################################################################################################
//===========================================================|   ADC_READ() Start	|=============================================================================================
//################################################################################################################################################################################
uint16_t ADC_READ(uint8_t channel)
{
	
	
	#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)\
		|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)\
		|| defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
		|| defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
		|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
		|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)\
		|| defined(__AVR_ATmega8535__)
		ADMUX &= (~(1<<MUX4)) & (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); // set channel ADC0 default
		switch(channel)
		{
			case 0:ADMUX &= (~(1<<MUX4)) & (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); //---------- 0 0 0 0 0
			break;
			case 1:ADMUX |= (1<<MUX0);//-------------------------------------------------------------------------- 0 0 0 0 1
			break;
			case 2:ADMUX |= (1<<MUX1);//-------------------------------------------------------------------------- 0 0 0 1 0
			break;
			case 3:ADMUX |= (1<<MUX1) | (1<<MUX0);//-------------------------------------------------------------- 0 0 0 1 1
			break;
			case 4:ADMUX |= (1<<MUX2);//-------------------------------------------------------------------------- 0 0 1 0 0
			break;
			case 5:ADMUX |= (1<<MUX2) | (1<<MUX0);//-------------------------------------------------------------- 0 0 1 0 1
			break;
			case 6:ADMUX |= (1<<MUX2) | (1<<MUX1);//-------------------------------------------------------------- 0 0 1 1 0
			break;
			case 7:ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0);//-------------------------------------------------- 0 0 1 1 1
			break;
			default:ADMUX &= (~(1<<MUX4)) & (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); // set channel ADC0 default
		}
		ADCSRA |=(1<<ADSC); // ADC conversion start
	
		while((ADCSRA & (1<<ADIF)) == 0){}; // wait for end conversion ( after conversion ADIF bit will be set automatically )
		//uint8_t high,low;
		//high=ADCH;
		//low=ADCL;
		return ADCW;// when conversion finished all data will be stored in ADCW
	
	
	
	
	
	
	#elif defined(__AVR_ATmega8__)\
		|| defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)\
		|| defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)\
		|| defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)\
		||defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
		ADMUX &=  (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); // set channel ADC0 default
	
		switch(channel)
		{
			case 0:ADMUX &=  (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); //---------- 0 0 0 0 0
			break;
			case 1:ADMUX |= (1<<MUX0);//-------------------------------------------------------------------------- 0 0 0 0 1
			break;
			case 2:ADMUX |= (1<<MUX1);//-------------------------------------------------------------------------- 0 0 0 1 0
			break;
			case 3:ADMUX |= (1<<MUX1) | (1<<MUX0);//-------------------------------------------------------------- 0 0 0 1 1
			break;
			case 4:ADMUX |= (1<<MUX2);//-------------------------------------------------------------------------- 0 0 1 0 0
			break;
			case 5:ADMUX |= (1<<MUX2) | (1<<MUX0);//-------------------------------------------------------------- 0 0 1 0 1
			break;
			case 6:ADMUX |= (1<<MUX2) | (1<<MUX1);//-------------------------------------------------------------- 0 0 1 1 0
			break;
			case 7:ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0);//-------------------------------------------------- 0 0 1 1 1
			break;
			default:ADMUX &= (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); // set channel ADC0 default
		}
		ADCSRA |=(1<<ADSC); // ADC conversion start
	
		while((ADCSRA & (1<<ADIF)) == 0){}; // wait for end conversion ( after conversion ADIF bit will be set automatically )
		//uint8_t high,low;
		//high=ADCH;
		//low=ADCL;
		return ADCW;// when conversion finished all data will be stored in ADCW
	
	
	
	#else
		#error "No processor type defined!"
	#endif
}
//################################################################################################################################################################################
//==============================================================|   ADC_READ() End	|=============================================================================================
//################################################################################################################################################################################
