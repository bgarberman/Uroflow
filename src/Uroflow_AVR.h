//
// Created by Brett Garberman
//
// Written for Teensy 2.0 (ATMEGA32U4)
//

#define _BV(b) (1UL << (b))
#define _CV(b) !(1UL << (b))

#define WINDOW_SIZE  10

unsigned int adc_window[WINDOW_SIZE];
float adc_window_avg = 0;
int index_last = 0;


uint16_t movingAverage(uint16_t val) {

    adc_window_avg -= (adc_window[index_last] / (float) WINDOW_SIZE); //Removes last moving average value
    adc_window_avg += (val / (float) WINDOW_SIZE); //Inserts new moving average value

    adc_window[index_last] = val; //Inserts new value into moving average window

    index_last = ++index_last % WINDOW_SIZE; //Increment index

    return (uint16_t) adc_window_avg;
}


void ADC_init(uint8_t channel){
	ADMUX = _BV(REFS0) | channel; //Chooses reference voltage AREF & selects channel
	ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) //Enable prescaler of 128
	ADCSRA |= _BV(ADEN) | //Enable ADC
	ADCSRA |= _BV(ADIE) | _BV(ADATE); // ADC Interrupt enable & auto trigger enable
    ADCSRB = 0; //Free running mode

	memset(adc_sampler, 0x00, SAMPLE_SIZE * sizeof(unsigned int)); //Initializes moving average window

}

void Timer0_init(){
    //setup the input capture for the button
}

void Timer1_init(){ //Timer for ADC, with 50 Hz (20ms) sampling rate

    TCCR1A |= _BV(WGM12); //CTC Mode
    TCCR1B |= _BV(CS11); // 1/8 prescaler
    OCR1AL = 0b01000000;
    OCR1AH = 0b10011100; //Set OCR1A to 40000 ticks



    
}

void Timer3_init(){
 //timer for flush
}

void openValve(){

}

void closeValve(){

}

