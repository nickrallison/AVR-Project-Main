#include <stdio.h>
#include <math.h>

void showbits( unsigned int x )
{
    int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
        putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

void main(void) {
    printf("a = %x\n", ((1 & 0b00000001) ^ (1 & 0b00000001)));

}
