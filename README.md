# AVR-ADC-master Library
AVR ADC master library

## Supported AVR chip list
     | -----------------Tested-----------------|
     | 1) Atmega16             7)  ATmega8     |
     | 2) ATmega32             8)  ATmega48    |
     | 3) ATmega164            9)  ATmega88    |
     | 4) ATmega324            10) ATmega168   |
     | 5) ATmega644            11) ATmega328   |
     | 6) ATmega1284           12) ATmega8535  |
     |-----------------------------------------|



## Two main function:
        1) void ADC_INIT(uint8_t prescaler,uint8_t Voltage_Reference); 
        2) uint16_t ADC_READ(uint8_t channel);

## Function 1: (ADC initialization)
      ADC_INIT(prescaler,Voltage_Reference); 
     
      prescaler:(2,4,8,16,32,64,128)
      ADC need sampling frequency which should be less then 250KHz.This sampling frequency provided by
      system clock frequency(16MHz,8MHz) after frequency divider.For example we use 16MHz external clock,
      now we need sampling frequency less then 250MHz.So,16MHz/128=125KHz which is less then 250MHz.
      
      Voltage_reference:(AREF,AVCC,INTERNAL)
      ADC need a reference voltage for sampling or identify target voltage resolution.
      
## Function 2: (ADC data read)
      ADC_READ(uint8_t channel);
      
      channel:(0,1,2,3,4,5,6,7)
      which channel you want to use to read analog data. For examople Atmega32A has portA (ADC0:ADC7).
      
## Example:

      #ifndef F_CPU
      #define F_CPU 16000000UL
      #endif


      #include <avr/io.h>
      #include "lib/AVR_ADC_MASTER_JUEL.h"


      int main(void)
      {
            uint16_t DATA;
            DDRD |=(1<<PD0);//pin PD0 set as OUTPUT 

            ADC_INIT(128,AVCC);// ADC Initialization 


            while(1)

            {	DATA = ADC_READ(0);//ADC data read from pin ADC0 [ADC0 set as INPUT]


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
      
# Limitation:
     1) This library doesn't support differential channels,only single ended Input support.
     2) By default free Running mode on[Special FunctionIO Register – SFIOR ],no other mode suport.

