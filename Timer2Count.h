//
// Created by nickr on 2022-02-14.
//

#ifndef AVR_PROJECT_MAIN_TIMER2COUNT_H
#define AVR_PROJECT_MAIN_TIMER2COUNT_H

#define FUNDFREQ 1000000
#define FREQDIV 256
#define COUNTSEC FREQDIV/FUNDFREQ
#define LONGESTTIME COUNTSEC*65536

int ButtonSwap();

int buttonon = 0;
int portinprev = 1;
int count = 0;
int swapflag = 0;

#endif AVR_PROJECT_MAIN_TIMER2COUNT_H
