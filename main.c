// left is equivalent to dot, right is equivvalent to dash
//
// TODO
// Compile partial library functions
// Clean function, maybe change from using hex, just use a string??
//      Does that help memory or only speed?
// Review Mallocs and mem
// Dealloc At end
// Test

#include <stdio.h>
#include <stdlib.h>

typedef struct treenode {
    char c;
    struct treenode *left;
    struct treenode *right;
} treenode;

treenode *createNode(char letter);

char readTree(treenode *head, int hex, int len);

void createTree(treenode *head);

void error();

void main(void) {
    treenode* head = createNode('\0');
    createTree(head);
    char letter = readTree(head, 0xc, 3);
    printf("letter = %c\n", letter);
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

char readTree(treenode *head, int hex, int len) {
    char letter;
    if (len == 0)
        return head->c;
    if (hex % 2 == 1)

    {
        if (head->right == NULL)
            error();
        letter = readTree(head->right, hex >> 1, len - 1);
    }

    else
    {
        if (head->left == NULL)
            error();
        letter = readTree(head->left, hex >> 1, len - 1);
    }
    return letter;
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

void error() {
    printf("Len Overflow\n");
}