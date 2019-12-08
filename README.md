

# AVR-ADC-master Library
![](https://img.shields.io/badge/release-v%201.1.0-blue)

<<<<<<< HEAD
This library is designed for the Atmel AVR microcontroller. The most interesting part of this library is, 
who are familiar with Arduino ADC, they can use it like an Arduino ADC library.


**Contents**

- [AVR-ADC-master Library](#avr-adc-master-library)
  * [Supported AVR chip list](#supported-avr-chip-list)
  * [Two main function:](#two-main-function)
  * [Function 1: (ADC initialization)](#function-1-adc-initialization)
  * [Function 2: (ADC data read)](#function-2-adc-data-read)
  * [Example:](#example)
    + [CODE:](#code)
    + [SIMULATION:](#simulation)
  * [ADC Channel Map:](#adc-channel-map)
  * [ADC Voltage Reference Map:](#adc-voltage-reference-map)
- [Limitation:](#limitation)

=======
This library is designed for the Atmel AVR microcontroller. The interesting part of this library is who are familiar with Arduino ADC, they can use it like an Arduino ADC library.

**Contents**

- [AVR-ADC-master Library](#avr-adc-master-library)
  * [Supported AVR chip list](#supported-avr-chip-list)
  * [Two main function:](#two-main-function)
  * [Function 1: (ADC initialization)](#function-1-adc-initialization)
  * [Function 2: (ADC data read)](#function-2-adc-data-read)
  * [Example:](#example)
    + [CODE:](#code)
    + [SIMULATION:](#simulation)
  * [ADC Channel Map:](#adc-channel-map)
  * [ADC Voltage Reference Map:](#adc-voltage-reference-map)
- [Limitation:](#limitation)

>>>>>>> ea756c48803f4e3d2fe2ce25394a0992ded21b07
 
## Supported AVR chip list

| ATmega series   | ATtiny series  |
|-----------------|----------------|
| 1\) ATmega16    | 13\) ATtiny24  |
| 2\) ATmega32    | 14\) ATtiny44  |
| 3\) ATmega164   | 15\) ATtiny84  |
| 4\) ATmega324   |                |
| 5\) ATmega644   |                |
| 6\) ATmega1284  |                |
| 7\) ATmega8     |                |
| 8\) ATmega48    |                |
| 9\) ATmega88    |                |
| 10\) ATmega168  |                |
| 11\) ATmega328  |                |
| 12\) ATmega8535 |                |


## Two main function:
        1) void ADC_INIT(uint8_t prescaler,uint8_t Voltage_Reference);
        2) uint16_t analogRead(uint8_t channel);

## Function 1: (ADC initialization)
      ADC_INIT(prescaler,Voltage_Reference); 
     
      prescaler:(2,4,8,16,32,64,128)
         ADC needs sampling frequency which should be less than 250KHz.This sampling frequency 
         provided by system clock frequency(16MHz,8MHz) after frequency divider. For example,
         we use a 16MHz external clock, now we need sampling frequency less than 250MHz.So,
         16MHz/128=125KHz which is less than 250MHz.
      
      Voltage_reference:(AREF,AVCC,INTERNAL,INTERNAL1v1,INTERNAL2v56)
         ADC needs a reference voltage for sampling or identifies target voltage resolution.
         
         
         ===================================================================================
         AREF= Use external voltage source(below 5v) to provide voltage reference.
         
         AVCC= ADC internally use chip main power supply as voltage reference.
         
         INTERNAL= ADC use Internal predefine voltage reference.  
                   In this library, this parameter depends on the chip. If any chip support 
                   internal 2.56v only that means INTERNAL parameter select 2.56v. If any 
                   chip support internal 1.1v only that means INTERNAL parameter select 1.1v.
                   On the other hand, if any chip supports both 1.1v & 2.56v that time, the 
                   INTERNAL parameter selects the only 2.56v.
        
         INTERNAL1v1= ADC internally select predefine internal 1.1v reference voltage.
                      of course, the target chip has to support internal 1.1v voltage reference.
                     
         INTERNAL2v56= ADC internally select predefine internal 2.56v reference voltage.
                       of course, the target chip has to support internal 2.56v voltage reference.
         ===================================================================================
      
      
      NB:
      It is not mandatory to use ADC_INIT() because,
       
      1) By default reference voltage AVCC has been selected.
      2) By default Prescaler 128 has been selected.
       
      if you want to change them, then you have to use ADC_INIT() otherwise you can ignore 
      this function.
       
       


## Function 2: (ADC data read)
      analogRead(uint8_t channel);
      
      channel:(0,1,2,3,4,5,6,7) or (A0,A1,A2,A3,A4,A5,A6,A7)
      which channel you want to use to read analog data. For example, Atmega32A has 
      portA (ADC0:ADC7).
      
     
      
## Example:
### CODE:

      #ifndef F_CPU
      #define F_CPU 16000000UL
      #endif

      #include <avr/io.h>
      #include "lib/AVR_ADC_MASTER_JUEL.h"

      int main(void)
      {
            uint16_t DATA;
            DDRD |=(1<<PD0);//pin PD0 set as OUTPUT 

            //ADC_INIT(128,AREF);// ADC Initialization 

            while(1)

            {	DATA = analogRead(0);//ADC data read from pin ADC0 [ADC0 set as INPUT]

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
      
### SIMULATION:
![](https://codimd.s3.shivering-isles.com/demo/uploads/upload_b5c6d85c773f2622eb9f3ddd52a79b17.png)          
> Figure: ATmega32 ADC simulation using Proteus.


## ADC Channel Map:

|            | **A0** | **A1** | **A2** | **A3** | **A4** | **A5** | **A6** | **A7** |
|:----------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|
<<<<<<< HEAD
| ATmega8    | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌  |
| ATmega16   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
| ATmega32   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
| ATmega48   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌  |
| ATmega88   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌  |
| ATmega164  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
| ATmega168  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌  |
| ATmega324  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
| ATmega328  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌  |
| ATmega644  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
| ATmega1284 | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
| ATmega8535 | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
| ATtiny24   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
| ATtiny44   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
| ATtiny84   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔   | ✔  |
=======
| ATmega8    | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌     |
| ATmega16   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
| ATmega32   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
| ATmega48   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌     |
| ATmega88   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌     |
| ATmega164  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
| ATmega168  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌     |
| ATmega324  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
| ATmega328  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ❌   | ❌     |
| ATmega644  | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
| ATmega1284 | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
| ATmega8535 | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
| ATtiny24   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
| ATtiny44   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
| ATtiny84   | ✔      | ✔      | ✔      | ✔      | ✔      | ✔      | ✔    | ✔      |
>>>>>>> ea756c48803f4e3d2fe2ce25394a0992ded21b07


## ADC Voltage Reference Map:

|            | AREF | AVCC | INTERNAL | INTERNAL1v1 | INTERNAL2v56 |
|:----------:|:----:|:----:|:--------:|:-----------:|:------------:|
| ATmega8    | ✔    | ✔    | 2.56v    | ❌         | ❌           |
| ATmega16   | ✔    | ✔    | 2.56v    | ❌         | ❌           |
| ATmega32   | ✔    | ✔    | 2.56v    | ❌         | ❌           |
| ATmega48   | ✔    | ✔    | 1.1v     | ❌         | ❌           |
| ATmega88   | ✔    | ✔    | 1.1v     | ❌         | ❌           |
<<<<<<< HEAD
| ATmega164  | ✔    | ✔    | 2.56v    | ✔         | ✔           |
| ATmega168  | ✔    | ✔    | 1.1v     | ❌         | ❌           |
| ATmega324  | ✔    | ✔    | 2.56v    | ✔         | ✔           |
| ATmega328  | ✔    | ✔    | 1.1v     | ❌         | ❌           |
| ATmega644  | ✔    | ✔    | 2.56v    | ✔         | ✔           |
| ATmega1284 | ✔    | ✔    | 2.56v    | ✔         | ✔           |
=======
| ATmega164  | ✔    | ✔    | 2.56v    | ✔          | ✔            |
| ATmega168  | ✔    | ✔    | 1.1v     | ❌         | ❌           |
| ATmega324  | ✔    | ✔    | 2.56v    | ✔          | ✔            |
| ATmega328  | ✔    | ✔    | 1.1v     | ❌         | ❌           |
| ATmega644  | ✔    | ✔    | 2.56v    | ✔          | ✔            |
| ATmega1284 | ✔    | ✔    | 2.56v    | ✔          | ✔            |
>>>>>>> ea756c48803f4e3d2fe2ce25394a0992ded21b07
| ATmega8535 | ✔    | ✔    | 2.56v    | ❌         | ❌           |
| ATtiny24   | ✔    | ✔    | 1.1v     | ❌         | ❌           |
| ATtiny44   | ✔    | ✔    | 1.1v     | ❌         | ❌           |
| ATtiny84   | ✔    | ✔    | 1.1v     | ❌         | ❌           |


⚠ ⚠ ⚠  Warning  ⚠ ⚠ ⚠
For ATtiny24,44,84 please avoid (A0 or ADC0) channel for ADC read[analogread(A0)] while
using AREF(External voltage reference).Because (A0 or ADC0) pin use as External voltage
reference. In the other case(AVCC, INTERNAL), you can use this channel(A0 or ADC0) for 
ADC read.

# Limitation:
     1) This library doesn't support differential channels, only single-ended Input support.
     2) By default free Running mode on[Special FunctionIO Register – SFIOR ], no other mode support.

