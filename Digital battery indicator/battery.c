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
	uart_puts("initialized");//uart_putc('f');
	
	
	int a,s,d,f,g,h;
	
	char str[10],str1[10],str2[2],str3[2],str4[2],str5[2];
	sbi(DDRA,0);
	cbi(PORTA,0);
	
while(1)
	
{

	//PORTC=0x0f;
	a= readADC(1);


	itoa(a,str,10);
	//uart_puts(str);

	uart_puts("\n\r");
	uart_puts("\n\r");

	


	if(a>250)
	{
	uart_puts("\n\r");
	uart_puts("BATTERY LEVEL = 100%");
	}
	
	if((a<250)&&(a>230))
	{
	uart_puts("\n\r");
	uart_puts("BATTERY LEVEL = 92%");
	}
	
	if((a<230)&&(a>200))
	{
	uart_puts("\n\r");
	uart_puts("BATTERY LEVEL = 85%");
	}
	
	if((a<200)&&(a>180))
	{
	uart_puts("\n\r");
	uart_puts("BATTERY LEVEL = 75%");
	}
	
	if((a<180)&&(a>150))
	{
	uart_puts("\n\r");
	uart_puts("BATTERY LEVEL = 65%");
	}
	
	if((a<150)&&(a>130))
	{
	uart_puts("\n\r");
	uart_puts("BATTERY LEVEL = 50%");
	}
	
	if((a<130)&&(a>100))
	{
	uart_puts("\n\r");
	uart_puts("BATTERY LEVEL = 45%");
	}
	
	if((a<100)&&(a>70))
	{
	uart_puts("\n\r");
	uart_puts("BATTERY LEVEL = 35%");
	}
	
	if((a<70)&&(a>50))
	{
	uart_puts("\n\r");
	uart_puts("BATTERY LEVEL = 30%");
	}
	
	
	if((a<50)&&(a>20))
	{
	uart_puts("BATTERY LEVEL = 20%");
	uart_puts("\n\r");
	uart_puts("BATTERY LOW");
	}
	
	if((a<20)&&(a>10))
	{
	uart_puts("BATTERY LEVEL = 10%");
	uart_puts("\n\r");
	uart_puts("BATTERY LOW");
	}
	
	_delay_ms(1000);
	






}
}