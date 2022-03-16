// Todo
// Should Button2Count call Count2Binary or vice versa
// Top Down or Bottom up?
// Should Timer2Count Return 0 when no button has been held down
// Only use Timer2PauseCount() after a button is pressed once
// How to incorperate Timer2PauseCount()
// #define BUTTONDOWN ~PORTA.IN&0b01000000
// #define BUTTONUP PORTA.IN&0b01000000
// Can I use Malloc to help memory
// Does comparing against the previous cycle slow it down too much
// Make sure no bad signals sent during initialization
// Global Vars
// Implement Hex2Char in Main Setup
// Hex2Char Edit error func
// Sleep function for long pause

// Fix 1 - Only finds presses and not releases

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
    unsigned int freq = 7813;
    unsigned int freqDesired = 256;
    unsigned int timerThreshold = detTimerThreshold(freq, freqDesired);
    unsigned int onFlag = 0;
    int buttonOn = 0;               // Button State
    int count = 0;                  // Timer Count
    int swapFlag = 0;               // Set to 1 after Button swapped places
    int len = 0;
    int hex = 0;
    char letter = 0;
    unsigned int clock;
    int portInPrev = 0b01000000;

    treenode *head = createNode('\0');
    createTree(head);

    initAVR();
    TCA0.SINGLE.CNT = 0;
    while (1) {
        PORTA.OUT &= 0b11101111;
        letter = 0;

        if (TCA0.SINGLE.CNT * COUNTSEC > LONGPAUSE ) {           //if a long pause occurs the word ends
            
            letter = readTree(head, hex, len);
            hex = 0;
            len = 0;
        }
        
        if (letter > 96) {
            TCA0.SINGLE.CNT = 0;

            while( TCA0.SINGLE.CNT <= freq) {
                PORTA.OUT &= 0b11101111;
                clock = TCA0.SINGLE.CNT;
                while( TCA0.SINGLE.CNT - clock <= timerThreshold) ;


                PORTA.OUT |= 0b00010000;
                clock = TCA0.SINGLE.CNT;
                while( TCA0.SINGLE.CNT - clock <= timerThreshold) ;

            }
        }
       

        ButtonSwap(&buttonOn, &count, &swapFlag, &portInPrev);

        if (swapFlag) { 
            //swapFlag = 0;
                                      // When Button swaps and ends on off, binary an
            //int v = Count2Binary(count, 1);
            //Bin2Hex(&hex, &len, v);
            
        }
    }
}



void initAVR() {


    // Set internal clock frequency to 8 MHz.
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00010100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    // Configure the timer to increment every 2us.
    // - Divide the 8MHz clock by 1024.
    // Freq now set to 7813Hz
    TCA0.SINGLE.CTRLA = 0b00001111;

    // We will manually check the timer and reset the timer
    // so set the period to its max value to avoid an automatic
    // reset.
    TCA0.SINGLE.PER = 0xffff;

    //Max timer time is 8.38s
    TCA0.SINGLE.CNT = 0;

    // Configure PA4 and PA5 as our output pin.
    PORTA.DIRSET = 0b00110000;

    // Enable PA6 as an input pin.
    PORTA.DIRCLR = 0b01000000;


    PORTA.OUT |= 0b00100000;
    PORTA.OUT &= 0b11101111;
}


unsigned int detTimerThreshold(unsigned int freq, unsigned int desiredFreq) {
    return freq/(2*desiredFreq);
}
