#include <stdio.h>
typedef char BYTE;

int main(void)
{
    BYTE x = 0x66; // 0110 0110
    BYTE y = 0x39; // 0011 1001
    
    printf("x & y: 0x%x\n", x & y); // 0010 0000: 0x20
    printf("x | y: 0x%x\n", x | y); // 0111 1111: 0x7f
    printf("~x: 0x%x\n", ~x); // 0xffffff99
    printf("~y: 0x%x\n", ~y); // 0xffffffc6
    printf("~x | ~y: 0x%x\n", ~x | ~y);  // 0xffffffdf
    printf("x & !y: 0x%x\n", x & !y); // 0x0
    printf("x && y: 0x%x\n", x && y); // 0x1
    printf("x || y: 0x%x\n", x || y); // 0x1
    printf("!x || !y: 0x%x\n", !x || !y); // 0x0
    printf("x && ~y: 0x%x\n", x && ~y); // 0x1
}