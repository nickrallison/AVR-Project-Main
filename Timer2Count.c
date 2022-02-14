// Todo
// Turn into either main or its own func
//#define BUTTONDOWN ~PORTA.IN&0b01000000
//#define BUTTONUP PORTA.IN&0b01000000

#include <avr/io.h>
#include <stdio.h>

int Button2Count();

count = 0;                                      //Global Var


int main(void) {
    while (1) {                                 //Resets Count, Clock, and PortOut Every Cycle
        TCA0.SINGLE.CNT = 0;                    //
        PORTA.OUT |= 0b00100000;                //
        if(~PORTA.IN & 0b01000000) {            //if Button is held down
            TCA0.SINGLE.CNT = 0;
            while (1)
                if (PORTA.IN & 0b01000000) {
                    count = TCA0.SINGLE.CNT;
                    break;
                }
        }
        if (count != 0) {
            TCA0.SINGLE.CNT = 0;
            while (TCA0.SINGLE.CNT <= count){
                PORTA.OUT &= 0b11011111; //On
            }
        }
    }
}

int Button2Count() {
    if(~PORTA.IN & 0b01000000) {            //if Button is held down
        TCA0.SINGLE.CNT = 0;                //Sets Clock to zero
        while (1)                           //Loops until button released
            if (PORTA.IN & 0b01000000) {
                count = TCA0.SINGLE.CNT;    //Sets count equal to clock
                break;
            }
    }
    if (count != 0) {                       //After Previous part executes
        TCA0.SINGLE.CNT = 0;                //
        while (TCA0.SINGLE.CNT <= count){
            PORTA.OUT &= 0b11011111; //On
        }
    }
}
