/*
 * File:   avrtimer-code.c
 * Author: Nick Allison
 *
 * Created on February 11, 2022, 12:00 PM
 * Test
 */


#include <avr/io.h>
#include <stdio.h>



int count = 1.28; //count is in ms

int main(void) {

    // Enable PA5 as an output pin.
    PORTA.DIRSET = 0b00100000;

    // Enable PA6 as an input pin.
    PORTA.DIRCLR = 0b01000000;


    //PORTA.OUT |= 0b00100000; //Off
    //PORTA.OUT &= 0b11011111; //On

    PORTA.OUT |= 0b00100000; //Off

    // Set internal clock frequency to 1 MHz.
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00000000;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }

    // Configure the timer to increment every 256us.
    // - Divide the 1MHz clock by 256.
    TCA0.SINGLE.CTRLA = 0b00001101; // f = 3906.25 Hz, T = 256us

    // We will manually check the timer and reset the timer
    // so set the period to its max value to avoid an automatic
    // reset.
    TCA0.SINGLE.PER = 0xffff; //max timer time is 16.78s

    while (1) {
        count = 0;
        TCA0.SINGLE.CNT = 0;
        PORTA.OUT |= 0b00100000; //Off
        if(~PORTA.IN & 0b01000000) {
            TCA0.SINGLE.CNT = 0;
            while (1)
                if (PORTA.IN & 0b01000000) {
                    count = TCA0.SINGLE.CNT;
                    break;
                }
        }
        if (count != 0) {
            TCA0.SINGLE.CNT = 0;
            while (TCA0.SINGLE.CNT <= count){
                PORTA.OUT &= 0b11011111; //On
            }
        }

    }
}
