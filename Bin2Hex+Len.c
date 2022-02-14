#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Timer2Count.h"
#include "Count2Binary.h"
#include "Bin2Hex+Len.h"

//Need to use pointer to hex?? / Counter??
//Would this be any easier with C++


void Bin2Hex(int *hex, int *counter, int longpress) {
    if (longpress != 0) {
        *counter += 1;
        *hex += longpress * pow(2, *counter);
    }
}


