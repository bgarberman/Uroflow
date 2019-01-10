//
// Created by Brett Garberman
//
// Written for Teensy 2.0 (ATMEGA32U4)
//

#define _BV(b) (1UL << (b))
#define _CV(b) !(1UL << (b))

#define WINDOW_SIZE  10


uint16_t movingAverage(uint16_t val);
void ADC_init();
void Timer0_init();
void Timer1_init();
void Timer3_init();
void openValve();
void closeValve();


