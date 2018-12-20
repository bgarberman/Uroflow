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
#include "uart.h"
#include "Uroflow_AVR.h"

int reading = 0;
int newSample = 0;
int currentVal = 0;
int lastVal = 0;
int difference = 0;
float derivative = 0;

ISR(ADC_VECT){
	//store new reading in 'reading'
	newSample = 1;
}

ISR(TIMER0_CAPT_vect){ //Handles flush initiation

	ADCSRA &= _CV(ADEN) //Disable ADC
	//open valve
	//start timer 1
}

ISR(TIMER1_OVERFLOW_vect){
//Delete this ISR. Timer 1 overflow is meant to trigger ADC reading.
}

ISR(TIMER3_OVERFLOW_vect){ //Ends flush

	//check if its time to close valve
	//if so, close vale
	//re-enable ADC? or reset to do so? idk
}


int main(void){

	DDRB //analog input, button input, 2x flush outputs
	
	ADC_init(0);
	uart_init();
	Timer0_init();
	Timer1_init();
	Timer3_init();
	sei()

	ADCSRA |= _BV(ADSC) | //Start ADC Conversions

	if (newSample) {
		//take new adc value
		//filter it & store in currentVal
		//convert to volume 
		//derivative it (current - last)/SAMPLE_RATE
		//set lastVal equal to currentVal
		//transmit derivative

		newSample = 0;

	}




}




