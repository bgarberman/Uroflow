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
	ADCSRA |= _BV(ADEN) | _BV(ADSC) | // Enable ADC & start conversion, 
	ADCSRA |= _BV(ADIE) | _BV(ADATE); // ADC Interrupt enable & auto trigger enable
    ADCSRB = 0; //Free running mode

	memset(adc_sampler, 0x00, SAMPLE_SIZE * sizeof(unsigned int)); //Initializes moving average window

}

