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
    int a = 0x00;
    a += pow(2,4);
    a  = a>>0;
    showbits(a);
    printf("a = %x", a);
}
