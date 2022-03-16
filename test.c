/*
 * File:   variable-square-wave.c
 * Author: gmessier
 *
 * Created on February 3, 2022, 11:20 AM
 */


#include <avr/io.h>

int main(void) {

    // Set internal clock frequency to 1 MHz.
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00000000;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    // Configure the timer to increment every 2us.
    // - Divide the 1MHz clock by 1024.
    // Freq now set to 976.6Hz
    TCA0.SINGLE.CTRLA = 0b00001111;

    // We will manually check the timer and reset the timer
    // so set the period to its max value to avoid an automatic
    // reset.
    TCA0.SINGLE.PER = 0xffff;

    // Set the time step to 256ms.
    unsigned int timerThreshold = 250;
    unsigned int onFlag = 0;
    // Configure PA4 as our output pin.
    PORTA.DIRSET = 0b00010000;

    // Enable PA6 as an input pin.
    PORTA.DIRCLR = 0b01000000;

    while (1) {
        TCA0.SINGLE.CNT = 0;
        PORTA.OUT |= 0b00010000;
        if (!(PORTA.IN & 0b01000000)) {
            TCA0.SINGLE.CNT = 0;
            PORTA.OUT &= 0b11101111;
            while( TCA0.SINGLE.CNT <= 4*timerThreshold) ;
        }
    }
}
