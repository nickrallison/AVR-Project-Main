#include <avr/io.h>
#include <stdio.h>
#include "1-Timer2Count.h"
#include "2-Count2Binary.h"
#include "main.h"

void ButtonSwap(int *buttonon, int *count, int *swapflag, int *portInPrev) {
    
    unsigned int clock;
    
    if((PORTA.IN & 0b01000000)^(*portInPrev & 0b01000000)) {   //if port in doesnt match previous value
        *portInPrev = (PORTA.IN & 0b01000000);
        *buttonon ^= 1;                                          //Might need to use pointers
        *count = TCA0.SINGLE.CNT;
        *swapflag = 1;
    }
    PORTA.OUT &= 0b11011111;
    clock = TCA0.SINGLE.CNT;
    while( TCA0.SINGLE.CNT - clock <= 7812) ;


    PORTA.OUT |= 0b00100000;
    clock = TCA0.SINGLE.CNT;
    while( TCA0.SINGLE.CNT - clock <= 7812) ;
    
}
