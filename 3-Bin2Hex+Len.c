#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "1-Timer2Count.h"
#include "2-Count2Binary.h"
#include "3-Bin2Hex+Len.h"

//Need to use pointer to hex?? / Counter??
//Would this be any easier with C++


void Bin2Hex(int *hex, int *counter, int longpress) {
    *counter += 1;
    *hex += longpress * pow(2, *counter);
}


