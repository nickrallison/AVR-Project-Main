#include <avr/io.h>
#include <stdio.h>
#include "1-Timer2Count.h"
#include "2-Count2Binary.h"
#include "main.h"

void ButtonSwap() {
    if((PORTA.IN & 0b01000000) ^ (portinprev & 0b01000000)) {   //if port in doesnt match previous value
        buttonon ^= 1;                                          //Might need to use pointers
        count = TCA0.SINGLE.CNT;
        TCA0.SINGLE.CNT = 0;
        swapflag = 1;
        portinprev = PORTA.IN;
    }
}
