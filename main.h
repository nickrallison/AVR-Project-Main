//
// Created by nickr on 2022-02-14.
//

#ifndef AVR_PROJECT_MAIN_MAIN_H
#define AVR_PROJECT_MAIN_MAIN_H


void initAVR();

unsigned int detTimerThreshold(unsigned int freq, unsigned int desiredFreq);

#define FUNDFREQ 4000000.0
#define FREQDIV 1024.0
#define FREQ 3906.3
#define COUNTSEC FREQDIV/FUNDFREQ
#define LONGESTTIME COUNTSEC*65535

void ButtonSwap();

#endif //AVR_PROJECT_MAIN_MAIN_H

#ifndef LONGPRESS
#define LONGPRESS 1

#endif

#ifndef AVR_PROJECT_MAIN_2_COUNT2BINARY_H
#define AVR_PROJECT_MAIN_2_COUNT2BINARY_H

int Count2Binary(int count, int press);

#endif //AVR_PROJECT_MAIN_2_COUNT2BINARY_H

#ifndef LONGPAUSE
#define LONGPAUSE 3.0

#endif

#ifndef AVR_PROJECT_MAIN_3_BIN2HEX_LEN_H
#define AVR_PROJECT_MAIN_3_BIN2HEX_LEN_H

void Bin2Hex(int *hex, int *counter, int longpress);

#endif //AVR_PROJECT_MAIN_3_BIN2HEX_LEN_H

#ifndef AVR_PROJECT_MAIN_4_HEX2CHAR_H
#define AVR_PROJECT_MAIN_4_HEX2CHAR_H

typedef struct treenode {
    char c;
    struct treenode *left;
    struct treenode *right;
} treenode;

treenode *createNode(char letter);

char readTree(treenode *head, int hex, int len);

void createTree(treenode *head);

void error();

#endif //AVR_PROJECT_MAIN_4_HEX2CHAR_H



