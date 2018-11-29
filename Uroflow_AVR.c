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

ISR(ADC_VECT){

}

ISR(TIMER0_CAPT_vect){
	//open valve
	//start timer 1
	//disable ADC
}

ISR(TIMER1_OVERFLOW_vect){
	//check if its time to close valve
	//if so, close vale
	//re-enable ADC? or reset to do so? idk
}


int main(void){

	DDRB //analog input, button input, 2x flush outputs


	TCCR1B &= (1 << ICES1); //Input capture edge select (rising)
	ADC_init(0);
	sei()




}




