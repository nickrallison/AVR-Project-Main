
// Todo
// FIX TREE TO ERROR OUT WITH BAD INPUT
// FIX TIMER SETTINGS

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"


//PORTA.OUT |= 0b00100000; //Off
//PORTA.OUT &= 0b11011111; //On


int main(void) {
    
    unsigned int freq = 3906;
    unsigned int freqDesiredBase = 65;
    unsigned int timerThreshold[26];
    unsigned int onFlag = 0;
    int buttonOn = 0;               // Button State
    int portInPrev = 0b01000000;    // Previous Clock cycle's port in
    int count = 0;                  // Timer Count
    int swapFlag = 0;               // Set to 1 after Button swapped places
    int len = 0;
    int hex = 0;
    char letter = 0;
    unsigned int clock = 0;
    unsigned int mem1 = 0;
    for (int i = 0; i < 26; i++) {
        timerThreshold[i] = detTimerThreshold(freq, freqDesiredBase * pow(2, i / 6.0));
    }

    treenode *head = createNode('\0');
    createTree(head);

    initAVR();
    TCA0.SINGLE.CNT = 0;
    while (1) { 
        PORTA.OUT &= 0b11101111;
        letter = 0;

        if (TCA0.SINGLE.CNT > LONGPAUSE * FREQ ) {           //if a long pause occurs the word ends

            letter = readTree(head, hex, len);
            
            PORTA.OUT &= 0b11110111;                    //
            clock = TCA0.SINGLE.CNT;                    //
            while( TCA0.SINGLE.CNT - clock <= 100) ;   //GREEN
                                                        //
                                                        //
            PORTA.OUT |= 0b00001000;                    //
            clock = TCA0.SINGLE.CNT;                    //
            while( TCA0.SINGLE.CNT - clock <= 100) ;   //
           
            
            hex = 0;
            len = 0;
            TCA0.SINGLE.CNT = 0;
        }

        if (letter != 0) {
            TCA0.SINGLE.CNT = 0;

            while( TCA0.SINGLE.CNT <= FREQ) {
                PORTA.OUT &= 0b11001111;
                clock = TCA0.SINGLE.CNT;
                while( TCA0.SINGLE.CNT - clock <= timerThreshold[letter - 65]) ;


                PORTA.OUT |= 0b00110000;
                clock = TCA0.SINGLE.CNT;
                while( TCA0.SINGLE.CNT - clock <= timerThreshold[letter - 65]) ;

            }
        }


        ButtonSwap(&buttonOn, &count, &swapFlag, &portInPrev);

        if (swapFlag) {
            if (buttonOn == 1) {
                mem1 = count;
            }
            if (buttonOn == 0) {      

                int v = Count2Binary(count - mem1, 1);
                Bin2Hex(&hex, &len, v);
            }
            swapFlag = 0;
           
        }
        
        
    }
}

void initAVR() {


    // Set internal clock frequency to 4 MHz.
    CCP = 0xd8;
    CLKCTRL.OSCHFCTRLA = 0b00001100;
    while( CLKCTRL.MCLKSTATUS & 0b00000001 ){
        ;
    }
    // Configure the timer to increment every 2us.
    // - Divide the 4MHz clock by 1024.
    // Freq now set to 3906Hz
    TCA0.SINGLE.CTRLA = 0b00001111;

    // We will manually check the timer and reset the timer
    // so set the period to its max value to avoid an automatic
    // reset.
    TCA0.SINGLE.PER = 0xffff;

    //Max timer time is 16.77s
    TCA0.SINGLE.CNT = 0;

    // Configure PA3, PA4 and PA5 as our output pins.
    PORTA.DIRSET = 0b00111000;

    // Enable PA6 as an input pin.
    PORTA.DIRCLR = 0b01000000;


    PORTA.OUT |= 0b00101000;
}


unsigned int detTimerThreshold(unsigned int freq, unsigned int desiredFreq) {
    return freq/(2*desiredFreq);
}

void ButtonSwap(int *buttonon, int *count, int *swapflag, int *portInPrev) {

    if((PORTA.IN & 0b01000000)^(*portInPrev & 0b01000000)) {   //if port in doesnt match previous value
        *portInPrev = (PORTA.IN & 0b01000000);
        *buttonon ^= 0b00000001;                                          //Might need to use pointers
        *count = TCA0.SINGLE.CNT;
        *swapflag = 1;
        TCA0.SINGLE.CNT = 0;
    }
}

int Count2Binary(int count, int press){
    unsigned int clock = 0;
    
    if (press) {
        if (count > (FREQ / 100.0)) {

                PORTA.OUT &= 0b11011111;
                clock = TCA0.SINGLE.CNT;
                while (TCA0.SINGLE.CNT - clock < 1500);
                PORTA.OUT |= 0b00100000; 
                
            return 1;
        }
        else {
            
                PORTA.OUT &= 0b11011111;
                clock = TCA0.SINGLE.CNT;
                while (TCA0.SINGLE.CNT - clock < 400);
                PORTA.OUT |= 0b00100000; 
                
            return 0;
        }
    }
    else {
        if (count > LONGPAUSE * FREQ) 
            return 1;
        else
            return 0;
    }
}

void Bin2Hex(int *hex, int *len, int longpress) {
    
    *hex += longpress * pow(2, *len);
    *len += 1;
   
}


treenode *createNode(char letter) {
    treenode* result = (treenode*) malloc(sizeof(treenode));
    if (result != NULL) {
        result->left = NULL;
        result->right = NULL;
        result->c = letter;
    }
    return result;
}

char readTree(treenode *head, int hexi, int leni) {

    char letteri = '\0';
    if (leni == 0) {
        return head->c;
    }
    if (hexi % 2 == 1)
    {
        return readTree(head->right, hexi >> 1, leni - 1);
    }

    else {
        return readTree(head->left, hexi >> 1, leni - 1);        
    }
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
