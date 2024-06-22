#include <stdio.h>

void get_least_significant_byte(int x);
void reverse_except_LSB(int x);
void set_one_LSB(int x);

int main(void)
{  
    int x = 0x87654321;

    printf("LSB\n");
    get_least_significant_byte(x);
    
    printf("Reverse Except LSB\n");
    reverse_except_LSB(x);

    printf("Set One LSB\n");
    set_one_LSB(x);
    
}

void get_least_significant_byte(int x)
{
    printf("%08x\n", x);
    printf("%08x\n", x & 0xFF);
    printf("\n");
}

void reverse_except_LSB(int x)
{
    printf("%08x\n", x);
    printf("%08x\n", (x & 0xFF));
    printf("%08x\n", ~(x | 0xFF));
    printf("%08x\n", ((x & 0xFF) | ~(x | 0xFF)));
    printf("\n");
}

void set_one_LSB(int x)
{
    printf("%08x\n", x);
    printf("%08x\n", (x | 0xFF));
    printf("\n");
}