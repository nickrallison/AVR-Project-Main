// Review Mallocs and mem
// Dealloc At end
// Test


// Todo
// Should Button2Count call Count2Binary or vice versa
// Top Down or Botton up?
// Should Timer2Count Return 0 when no button has been held down
// Only use Timer2PauseCount() after a button is pressed once
// How to incorperate Timer2PauseCount()
// #define BUTTONDOWN ~PORTA.IN&0b01000000
// #define BUTTONUP PORTA.IN&0b01000000
// Can I use Malloc to help memory
// Does comparing against the previous cycle slow it down too much
// Set Count to zero at beginning
// Make sure no bad signals sent during initialization
// Wait Mode after long pause
// Global Vars
// Implement Hex2Char in Main Setup

//WHAT TO DO BETWEEN PRESSES
//Sleep Command (END WORD)

#include <avr/io.h>
#include <stdio.h>
#include "main.h"
#include "Timer2Count.h"    // First Level
#include "Count2Binary.h"   // Second Level
#include "Bin2Hex+Len.h"    // Third Level
#include "Hex2Char.h"       // Fourth Level

//PORTA.OUT |= 0b00100000; //Off
//PORTA.OUT &= 0b11011111; //On


int main(void) {
    initAVR();
    while (1) {                                 //Resets Count, Clock, and PortOut Every Cycle
        if (TCA0.SINGLE.CNT * COUNTSEC > LONGPAUSE )
            char letter = readTree(head, hex, 3)

            ButtonSwap();

        if (swapflag) {
            if (buttonon == 0) {                             //Button off after swap (Button was just on)
                int v = Count2Binary(count, buttonon^1);
                Bin2Hex(&hex, &len, v);
            }
            swapflag = 0;
        }
    }
}



void initAVR() {
    buttonon = 0;
    portinprev = 1;
    count = 0;
    swapflag = 0;
    len = 0;

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
    TCA0.SINGLE.CNT = 0;
    PORTA.OUT |= 0b00100000;
}
