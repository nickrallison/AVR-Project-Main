
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

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

//PORTA.OUT |= 0b00100000; //Off
//PORTA.OUT &= 0b11011111; //On


int main(void) {
    unsigned int freq = 7813;
    unsigned int freqDesired = 256;
    unsigned int timerThreshold = detTimerThreshold(freq, freqDesired);
    unsigned int onFlag = 0;
    int buttonOn = 0;               // Button State
    int portInPrev = 0b01000000;    // Previous Clock cycle's port in
    int count = 0;                  // Timer Count
    int swapFlag = 0;               // Set to 1 after Button swapped places
    int len = 0;
    int hex = 0;
    char letter = 0;
    unsigned int clock = 0;

    treenode *head = createNode('\0');
    createTree(head);

    initAVR();
    TCA0.SINGLE.CNT = 0;
    while (1) { /*
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
        if (TCA0.SINGLE.CNT * COUNTSEC > LONGPAUSE ) {           //if a long pause occurs the word ends
            letter = readTree(head, hex, len);
            hex = 0;
            len = 0;
        }


        ButtonSwap(&buttonOn, &count, &swapFlag, &portInPrev);

        if (swapFlag) {
            if (buttonOn == 0) {                             // When Button swaps and ends on off, binary an
                int v = Count2Binary(count, 1);
                Bin2Hex(&hex, &len, v);
            }
            swapFlag = 0;
                 }*/
        TCA0.SINGLE.CNT = 0;
        //clock = TCA0.SINGLE.CNT;
        while (TCA0.SINGLE.CNT < 7000);
        PORTA.OUT |= 0b11111111; 
        
        TCA0.SINGLE.CNT = 0;
        //clock = TCA0.SINGLE.CNT;
        while (TCA0.SINGLE.CNT < 7000);
        PORTA.OUT &= 0b00000000;
        
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

    // Configure PA4 and PA5 as our output pins.
    PORTA.DIRSET = 0b00110000;

    // Enable PA6 as an input pin.
    PORTA.DIRCLR = 0b01000000;


    PORTA.OUT |= 0b00100000;
}


unsigned int detTimerThreshold(unsigned int freq, unsigned int desiredFreq) {
    return freq/(2*desiredFreq);
}

void ButtonSwap(int *buttonon, int *count, int *swapflag, int *portInPrev) {

    if((PORTA.IN & 0b01000000)^(*portInPrev & 0b01000000)) {   //if port in doesnt match previous value
        *portInPrev = (PORTA.IN & 0b01000000);
        *buttonon ^= 1;                                          //Might need to use pointers
        *count = TCA0.SINGLE.CNT;
        *swapflag = 1;
    }
}

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

void Bin2Hex(int *hex, int *counter, int longpress) {
    *counter += 1;
    *hex += longpress * pow(2, *counter);
}


treenode *createNode(char letter) {
    treenode* result = malloc(sizeof(treenode));
    if (result != NULL) {
        result->left = NULL;
        result->right = NULL;
        result->c = letter;
    }
    return result;
}

char readTree(treenode *head, int hexi, int leni) {
    char letteri = '\0';
    if (leni == 0)
        return head->c;
    if (hexi % 2 == 1)

    {
        if (head->right == NULL)
            //error();
            letteri = readTree(head->right, hexi >> 1, leni - 1);
    }

    else
    {
        if (head->left == NULL)
            //error();
            letteri = readTree(head->left, hexi >> 1, leni - 1);
    }
    return letteri;
}


void createTree(treenode *head) {
    head->left = createNode('E');
    head->right = createNode('T');
    head->left->left = createNode('I');
    head->left->right = createNode('A');
    head->right->left = createNode('N');
    head->right->right = createNode('M');
    head->left->left->left = createNode('S');
    head->left->left->right = createNode('U');
    head->left->right->left = createNode('R');
    head->left->right->right = createNode('W');
    head->right->left->left = createNode('D');
    head->right->left->right = createNode('K');
    head->right->right->left = createNode('G');
    head->right->right->right = createNode('O');
    head->left->left->left->left = createNode('H');
    head->left->left->left->right = createNode('V');
    head->left->left->right->left = createNode('F');
    head->left->right->left->left = createNode('L');
    head->left->right->right->left = createNode('P');
    head->left->right->right->right = createNode('J');
    head->right->left->left->left = createNode('B');
    head->right->left->left->right = createNode('X');
    head->right->left->right->left = createNode('C');
    head->right->left->right->right = createNode('Y');
    head->right->right->left->left = createNode('Z');
    head->right->right->left->right = createNode('Q');
}
