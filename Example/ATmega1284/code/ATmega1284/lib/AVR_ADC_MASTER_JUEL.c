/*
 * AVR_ADC_MASTER_JUEL.c
 *
 *  Created: 12/07/2019 3:18:34 PM
 *  Author: Md. Tarikul Islam Juel
 *  Email: md.tarikulislamjuel@gmail.com
 *
 *	  ====================== Register ======================
 *    ATmega16,32,164,324,644,1284,8535:
 *					ADMUX= REF1---REF0---ADLAR---MUX4--MUX3---MUx2---MUX1---MUX0  ----------------------[ADC Multiplexer Selection Register]
 *				    ADCSRA=ADEN---ADSC---ADATE---ADIF---ADIE---ADPS2---ADPS1---ADPS0--------------------[ADC Control and Status Register A]
 *				    ADC Data register-------------------------------------------------------------------[The ADC Data Register – ADCL and ADCH]
 *
 *	  ATmega8,48,88,168,328:
 *					ADMUX= REF1---REF0---ADLAR---x--MUX3---MUx2---MUX1---MUX0  -------------------------[ADC Multiplexer Selection Register]
 *				    ADCSRA=ADEN---ADSC---ADFR---ADIF---ADIE---ADPS2---ADPS1---ADPS0---------------------[ADC Control and Status Register A]
 *				    ADC Data register-------------------------------------------------------------------[The ADC Data Register – ADCL and ADCH]
 *
 *    ATtiny24,44,84:
 *					ADMUX= REF1---REF0---MUX5---MUX4--MUX3---MUx2---MUX1---MUX0  -----------------------[ADC Multiplexer Selection Register]
 *				    ADCSRA=ADEN---ADSC---ADATE---ADIF---ADIE---ADPS2---ADPS1---ADPS0--------------------[ADC Control and Status Register A]
 *                  ADCSRB= BIN---ACME---x---ADLAR---x---ADTS2---ADTS1---ADTS0 -------------------------[ADC Control and Status Register B]
 *				    ADC Data register-------------------------------------------------------------------[The ADC Data Register – ADCL and ADCH]
 *
 *
 *    =================== ADC_INI()  step ===================
 *    1) ADC enable	--------------------------------------ADEN=1
 *    2) set prescaler------------------------------------ADPS2,ADPS1,ADPS0 [set 3 bit combination for prescaler]		
 *	  3) reference voltage select-------------------------REFS1,REFS0 [set 2 bit combination for reference voltage]
 *	  4) left adjust of for data register-----------------ADLAR
 *
 *
 *	 =================== analogRead()  step ===================
 *	  5) Channel selection-------------------------------MUX4:MUX0[AVR ATmega32]-----MUX3:MUX0[AVR ATmega328]-----MUX5:MUX0[AVR ATtiny24]
 *	  6) Start conversion enable-------------------------ADSC=1
 *	  7) Return received register data-------------------ADCH,ADCL,ADCW
 */ 

#include "AVR_ADC_MASTER_JUEL.h"

uint8_t ADC_SINGLE_INIT=1;// This variable is use to ensure only one execution of the ADC_INIT() 

//################################################################################################################################################################################
//==============================================================|   ADC_INIT() Start	|=========================================================================================
//################################################################################################################################################################################

//	------------possible parameter---------
//	prescaler = 2,4,8,16,32,64,128
//  Voltage_Reference = AREF,AVCC,INTERNAL,INTERNAL1v1,INTERNAL2v56

void ADC_INIT(uint8_t prescaler, uint8_t Voltage_Reference)
{
	ADC_SINGLE_INIT=0; //when ADC_INIT() call by user so we dont need to again execute ADC_INIT() inside the analogRead()
	
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
	
	
	#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny24A__)\
	    || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny44A__)\
	    || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny84A__)
			ADCSRA |= (1<<ADEN); // ADC Enable
			ADC_PRESCALER_SET(prescaler); // set sampling frequency by prescaler bit
			ADC_voltage_Reference(Voltage_Reference); //set voltage reference //by default AVCC has been selected
			ADCSRB &= ~(1<<ADLAR); //left adjust off // Though by default left adjust off // this line use for more convenient for future developer
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
		|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)\
		|| defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny24A__)\
		|| defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny44A__)\
		|| defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny84A__)
			ADCSRA &= (~(1<<ADPS2)) & (~(1<<ADPS1)) & (~(1<<ADPS0)) ; // clear ADPS2:ADPS0 for initialization
	
			switch(prescaler)
			{
				case 0:ADCSRA |= (1<<ADPS0);//-----------------------------------  0 0 0 --------------------- 2
				break;
				case 2:ADCSRA |= (1<<ADPS0);//-----------------------------------  0 0 1 --------------------- 2
				break;
				case 4:ADCSRA |= (1<<ADPS1);//-----------------------------------  0 1 0 --------------------- 4
				break;
				case 8:ADCSRA |= (1<<ADPS1) | (1<<ADPS0);//----------------------  0 1 1 --------------------- 8
				break;
				case 16:ADCSRA |= (1<<ADPS2);//----------------------------------  1 0 0 --------------------- 16
				break;
				case 32:ADCSRA |= (1<<ADPS2) | (1<<ADPS0);//---------------------  1 0 1 --------------------- 32
				break;
				case 64:ADCSRA |= (1<<ADPS2) | (1<<ADPS1);//---------------------  1 1 0 --------------------- 64
				break;
				case 128:ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);//-------  1 1 1 --------------------- 124
				break;
				default:ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);//----------1 1 1 --------------------- 128
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
		|| defined(__AVR_ATmega8535__)\
		|| defined(__AVR_ATmega8__)\
		|| defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)\
		|| defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)\
		|| defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)\
		|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
		    //----------------INTERNAL---------------
			//-------------0 1(reserved)-------------
			//ATmega16=2.56v           ATmega48=1.1v
			//ATmega32=2.56v           ATmega88=1.1v
			//ATmega8535=2.56v         ATmega168=1.1v
			//ATmega8=2.56v            ATmega328=1.1v
			
			if(Reference_Voltage==AREF){ADMUX &= (~(1<<REFS1)) & (~(1<<REFS0));}//------------------------ 0 0 -------- AREF
			else if (Reference_Voltage==AVCC){ADMUX &= (~(1<<REFS1));ADMUX |= (1<<REFS0);}//-------------- 0 1 -------- AVCC
			else if (Reference_Voltage==INTERNAL){ADMUX |= (1<<REFS1) | (1<<REFS0);}//-------------------- 1 1 -------- INTERNAL 2.56v or 1.1v and (1 0 reserved)
			else{ADMUX &= (~(1<<REFS1));ADMUX |= (1<<REFS0);}//------------------------------------------- 0 1 -------- AVCC
	#endif
	
	
	
	#if defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
		|| defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
		|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
		|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
			//-----DUAL(1.1v & 2.56v) mode internal voltage reference supported
			//-------------INTERNAL1v1---------------INTERNAL2v56--------------
			//INTERNAL means by default 2.56v selected
			
			if(Reference_Voltage==AREF){ADMUX &= (~(1<<REFS1)) & (~(1<<REFS0));}//------------------------ 0 0 -------- AREF
			else if (Reference_Voltage==AVCC){ADMUX &= (~(1<<REFS1));ADMUX |= (1<<REFS0);}//-------------- 0 1 -------- AVCC
			else if (Reference_Voltage==INTERNAL1v1){ADMUX |= (1<<REFS1);ADMUX &= (~(1<<REFS0));}//------- 1 0 -------- INTERNAL1v1----- 1.1v
			else if (Reference_Voltage==INTERNAL2v56){ADMUX |= (1<<REFS1) | (1<<REFS0);}//---------------- 1 1 -------- INTERNAL2v56---- 2.56v 
			else if (Reference_Voltage==INTERNAL){ADMUX |= (1<<REFS1) | (1<<REFS0);}//-------------------- 1 1 -------- INTERNAL-------- 2.56v
			else{ADMUX &= (~(1<<REFS1));ADMUX |= (1<<REFS0);}//------------------------------------------- 0 1 -------- AVCC
	#endif
	
	
	
	#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny24A__)\
		|| defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny44A__)\
		|| defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny84A__)
			 //----------------INTERNAL---------------
			 //-------------1 1(reserved)-------------
			 //ATtiny24=1.1v
			 //ATtiny44=1.1v
			 //ATtiny84=1.1v
			 
			 //NB:ATmega24,44,84:
			 //	 when external(AREF) will be selected as reference .please avoid A0 channel for ADC read because A0 use as external(AREF) reference pin
			 
			if(Reference_Voltage==AVCC){ADMUX &= (~(1<<REFS1)) & (~(1<<REFS0));}  //---------------------- 0 0 -------- AVCC
			else if (Reference_Voltage==AREF){ADMUX &= (~(1<<REFS1));ADMUX |= (1<<REFS0);}//-------------- 0 1 -------- AREF
			else if (Reference_Voltage==INTERNAL){ADMUX |= (1<<REFS1);ADMUX &= ~(1<<REFS0);}//------------ 1 0 -------- INTERNAL---------1.1v
			else{ADMUX &= (~(1<<REFS1)) & (~(1<<REFS0));}//----------------------------------------------- 0 1 -------- AVCC
	#endif
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//======================================================|   ADC_voltage_Reference() End  |=======================================================================================
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//################################################################################################################################################################################
//===========================================================|   analogRead() Start	|=============================================================================================
//################################################################################################################################################################################
uint16_t analogRead(uint8_t channel)
{	
	if(ADC_SINGLE_INIT==1)
	{
		ADC_INIT(128, AVCC); // we set [ADC_SINGLE_INIT= 0] inside the ADC_INIT() function to ensure only one execution of ADC_INIT()
							 // by default we set prescaler= 128
							 // by default we set Reference voltage= AVCC
	}
	
	
	#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)\
		|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)\
		|| defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
		|| defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
		|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
		|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)\
		|| defined(__AVR_ATmega8535__)
			ADMUX &= (~(1<<MUX4)) & (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); // clear MUX4:MUX0 for initialization & set channel ADC0 default
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
			ADMUX &=  (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); // clear MUX3:MUX0 for initialization & set channel ADC0 default
	
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
		
		
		
		
			
	#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny24A__)\
		  || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny44A__)\
		  ||defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny84A__)
			ADMUX &= (~(1<<MUX5)) & (~(1<<MUX4)) & (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); // clear MUX3:MUX0 for initialization
			ADMUX |= (1<<MUX0);// set channel ADC1 default
			
			switch(channel)
			{
				case 0:ADMUX &= (~(1<<MUX5)) &  (~(1<<MUX4)) & (~(1<<MUX3)) & (~(1<<MUX2)) & (~(1<<MUX1)) & (~(1<<MUX0)); //--------0 0 0 0 0 0
				break;
				case 1:ADMUX |= (1<<MUX0);//----------------------------------------------------------------------------------------0 0 0 0 0 1
				break;
				case 2:ADMUX |= (1<<MUX1);//----------------------------------------------------------------------------------------0 0 0 0 1 0
				break;
				case 3:ADMUX |= (1<<MUX1) | (1<<MUX0);//----------------------------------------------------------------------------0 0 0 0 1 1
				break;
				case 4:ADMUX |= (1<<MUX2);//----------------------------------------------------------------------------------------0 0 0 1 0 0
				break;
				case 5:ADMUX |= (1<<MUX2) | (1<<MUX0);//----------------------------------------------------------------------------0 0 0 1 0 1
				break;
				case 6:ADMUX |= (1<<MUX2) | (1<<MUX1);//----------------------------------------------------------------------------0 0 0 1 1 0
				break;
				case 7:ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0);//----------------------------------------------------------------0 0 0 1 1 1
				break;
				default:ADMUX |= (1<<MUX0); // set channel ADC1 default-----NB:ATmega24,44,84:----when external(AREF) will be selected as reference .please avoid A0 channel for ADC read because A0 use as external(AREF) reference pin.so we set A1 by default.
				
				
				
				
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
//==============================================================|   analogRead() End	|=============================================================================================
//################################################################################################################################################################################
