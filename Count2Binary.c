#include <stdio.h>
#include <stdlib.h>
#include "Timer2Count.h"
#include "Count2Binary.h"

void main(void) {

}

int Press2Bin(int count){
    if (count * COUNTSEC > LONGPRESS)
        return 1;
    else
        return 0;
}

int Hold2Bin(int count){
    if (count * COUNTSEC > LONGPAUSE)
        return 1;
    else
        return 0;
}

