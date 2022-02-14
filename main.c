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
// Hex2Char Edit error func
// Sleep function for long pause

#include <avr/io.h>
#include <stdio.h>
#include "main.h"
#include "1-Timer2Count.h"    // First Level
#include "2-Count2Binary.h"   // Second Level
#include "3-Bin2Hex+Len.h"    // Third Level
#include "4-Hex2Char.h"       // Fourth Level

//PORTA.OUT |= 0b00100000; //Off
//PORTA.OUT &= 0b11011111; //On


int main(void) {
    initAVR();
    while (1) {
        if (TCA0.SINGLE.CNT * COUNTSEC > LONGPAUSE ) {           //if a long pause occurs the word ends
            letter = readTree(head, hex, 3);
            hex = 0;
            len = 0;
            sleep();
        }

        ButtonSwap();

        if (swapflag) {
            if (buttonon == 0) {                             // When Button swaps and ends on off, binary an
                int v = Count2Binary(count, 1);
                Bin2Hex(&hex, &len, v);
            }
            swapflag = 0;
        }
    }
}



void initAVR() {
    buttonon = 0;               // Button State
    portinprev = 0b01000000;    // Previous Clock cycle's port in
    count = 0;                  // Timer Count
    swapflag = 0;               // Set to 1 after Button swapped places
    len = 0;
    hex = 0;
    letter = '\0';

    head = createNode('\0');
    createTree(head);

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
