#include <avr/io.h>
#include <stdio.h>
#include "Timer2Count.h"
#include "Count2Binary.h"

int ButtonSwap() {
    if((PORTA.IN & 0b01000000) ^ (portinprev & 0b01000000)) { //if port in doesnt match previous value
        buttonon ^ 1;
        count = TCA0.SINGLE.CNT;
        TCA0.SINGLE.CNT = 0;
        swapflag = 1;
    }
    portinprev = PORTA.IN
}
