//
// Created by nickr on 2022-02-14.
//

#ifndef AVR_PROJECT_MAIN_HEX2CHAR_H
#define AVR_PROJECT_MAIN_HEX2CHAR_H

typedef struct treenode {
    char c;
    struct treenode *left;
    struct treenode *right;
} treenode;

treenode *createNode(char letter);

char readTree(treenode *head, int hex, int len);

void createTree(treenode *head);

void error();

#endif AVR_PROJECT_MAIN_HEX2CHAR_H


