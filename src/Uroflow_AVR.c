//
// Created by Brett Garberman
//
// Written for Teensy 2.0 (ATMEGA32U4)
//

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "uart.h"
#include "Uroflow_AVR.h"


uint16_t reading = 0;
int newSample = 0;
int currentVal = 0;
int lastVal = 0;
int difference = 0;
float derivative = 0;


uint16_t movingAverage(uint16_t val) {

    adc_window_avg -= (adc_window[index_last] / (float) WINDOW_SIZE); //Removes last moving average value
    adc_window_avg += (val / (float) WINDOW_SIZE); //Inserts new moving average value

    adc_window[index_last] = val; //Inserts new value into moving average window

    index_last = ++index_last % WINDOW_SIZE; //Increment index

    return (uint16_t) adc_window_avg;
}


void ADC_init(){
	ADMUX &= 0x1F; //Clears lower 5 bits to choose ADC0
	ADMUX = _BV(REFS0); //Chooses reference voltage AREF & selects channel
	ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); //Enable prescaler of 128
	ADCSRA |= _BV(ADEN); //Enable ADC
	ADCSRA |= _BV(ADIE) | _BV(ADATE); // ADC Interrupt enable & auto trigger enable
    ADCSRB = 0; //Free running mode

	memset(adc_window, 0x00, SAMPLE_SIZE * sizeof(unsigned int)); //Initializes moving average window
    unsigned int adc_window[WINDOW_SIZE];
    float adc_window_avg = 0;
    int index_last = 0;

}

void Timer0_init(){ //Timer for flush

    int overflows = 0;
    TIMSK0 |= _BC(TOIE0); //Enables overflow interrupt
}

void Timer1_init(){ //Timer for ADC, with 50 Hz (20ms) sampling rate

    TCCR1A |= _BV(WGM12); //CTC Mode
    OCR1AL = 0b01000000;
    OCR1AH = 0b10011100; //Set OCR1A to 40000 ticks
    TCCR1B |= _BV(CS11); // Starts timer at 1/8 prescaler
}

void Timer3_init(){ //Input capture for flush button on IPC3

    TIMSK3 |= _BV(ICIE3); //Enables input capture interrupt
    TCCR3B |= _BV(ICES3); //Input capture edge select(rising edge)
}

void openValve(){

    PORTB |= _BV(1):
    PORTB &= _CV(2);
}

void closeValve(){

    PORTB &= _CV(1):
    PORTB |= _BV(2);
}

ISR(ADC_VECT){
	
	reading = ADC;
	newSample = 1;
}

ISR(TIMER0_OVERFLOW_vect){ //Times flush

	overflows++;
	if (overflows > 609){ //Waits 10 seconds
		closeValve();
		overflows = 0;
		TCCR1B |= _BV(CS11); // Starts timer at 1/8 prescaler
		TCCR0B &= 0x00; // Stops timer 0	
	}
}


ISR(TIMER3_CAPT_vect){ //Initiates flush

	TCCR1B &= 0x00; //Stops timer 1
	valveOpen();
	TCCR0B |= _BV(CS00) | _BV(CS02); // Starts timer 0 at 1/1024 prescaler
}


int main(void){

	DDRB |= _BV(1) | _BV(2); //Flush outputs
	DDRC &= _CV(7) //Button input 
	
	ADC_init(0);
	uart_init();
	Timer0_init();
	Timer1_init();
	Timer3_init();
	sei()

	ADCSRA |= _BV(ADSC) | //Start ADC Conversions

	if (newSample) {
		
		currentVal = movingAverage(reading); //Filter new reading
		currentVal = currentVal; //Convert to volume

		difference = (currentVal - lastVal); //Take derivative
		derivative = difference / .05;
		
		lastVal = currentVal; //Store current value
		printf(derivative); //Transmit flow rate

		newSample = 0;
	}
}


