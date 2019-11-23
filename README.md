# AVR-ADC-master

## Supported AVR chip list
      -----Tested-------
      1) Atmega32A
      2) Atmega328P




## Two main function:
        1) void ADC_INIT(uint8_t prescaler,uint8_t Voltage_Reference); 
        2) uint16_t ADC_READ(uint8_t channel);

## Function 1:(ADC initialization)
      ADC_INIT(prescaler,Voltage_Reference); 
     
      prescaler:(2,4,8,16,32,64,128)
      ADC need sampling frequency which should be less then 250KHz.This sampling frequency provided by
      system clock frequency(16MHz,8MHz) after frequency divider.For example we use 16MHz external clock,
      now we need sampling frequency less then 250MHz.So,16MHz/128=125KHz which is less then 250MHz.
      
      Voltage_reference:(AREF,AVCC,INTERNAL)
      ADC need a reference voltage for sampling or identify target voltage resolution.
      
## Function 2:(ADC data read)
      ADC_READ(uint8_t channel);
      
      channel:(0,1,2,3,4,5,6,7)
      which channel you want to use to read analog data. For examople Atmega32A has portA (ADC0:ADC7).
      
      
