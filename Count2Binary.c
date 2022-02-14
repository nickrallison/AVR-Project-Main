#include <stdio.h>
#include <stdlib.h>
#include "Timer2Count.h"
#include "Count2Binary.h"


int Count2Binary(int count, int press){
    if (press) {
        if (count * COUNTSEC > LONGPRESS)
            return 1;
        else
            return 0;
    }
    else {
        if (count * COUNTSEC > LONGPAUSE)
            return 1;
        else
            return 0;
    }
}
