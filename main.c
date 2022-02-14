// Todo
// Turn into either main or its own func

#include <avr/io.h>
#include <stdio.h>
#include "main.h"

//PORTA.OUT |= 0b00100000; //Off
//PORTA.OUT &= 0b11011111; //On


int main(void) {

    initAVR();

    while (1) {
        int count = 0; //To find total time, each count is equal to 256us, multiply by 256e-6s
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

void initAVR() {
    PORTA.DIRSET = 0b00100000;          // Enable PA5 as an output pin.
    PORTA.DIRCLR = 0b01000000;          // Enable PA6 as an input pin.
    PORTA.OUT |= 0b00100000;            //Off

    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00000000;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;                               // Set internal clock frequency to 1 MHz.
    }

    TCA0.SINGLE.CTRLA = 0b00001101; // Configure the timer to increment every 256us.
    // - Divide the 1MHz clock by 256.
    // f = 3906.25 Hz, T = 256us

    TCA0.SINGLE.PER = 0xffff;       //Max timer due to 2 byte counter
    //Max timer time is 16.78s
}
