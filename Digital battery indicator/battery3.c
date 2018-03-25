#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <util/delay.h>  
#include "uart.h"
#include "uart.c"
#include <avr/interrupt.h>



int readADC(int channel){
	
	int x;
	long val=0;
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIF); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

	ADMUX = channel;
	
	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	
	//ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running 4
	ADCSRA |= (1 << ADEN);  // Enable ADC
	
	ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
	
	
	 //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it
   ADCSRA|=(1<<ADIF);	
	
	return ADCH;
}


void main()
{
   
DDRC=0x0f;
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();
	uart_puts("START");//uart_putc('f');
	uart_puts("\n\r");
	
	_delay_ms(3000);
	int a,s,d,f,g,h;
	
	char str[10],str1[10],str2[2],str3[2],str4[2],str5[2];
	sbi(DDRA,0);
	cbi(PORTA,0);
	
while(1)
	
{

	//PORTC=0x0f;
	a= readADC(7);


	itoa(a,str,10);
	
	//uart_puts("mesure the ADC value and battery level");
	uart_puts("ADC value = ");
	uart_puts(str);

	uart_puts("\t");	
	
	s= (a*100)/256;
	itoa(s,str,10);
	uart_puts("Battery level = ");
	uart_puts(str);
	
	uart_puts("\n\r");
	uart_puts("\n\r");

	


	
	_delay_ms(1000);
	






}
}