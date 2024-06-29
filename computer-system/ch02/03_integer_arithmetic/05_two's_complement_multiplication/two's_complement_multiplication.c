#include <stdio.h>
#include <limits.h>

/*
    Two's Complement Multiplication
    - 2의 보수(부호 있는 정수) 간의 곱셈은 다음을 만족한다.
    - x * y = (x * y) mod 2^{bits_count}
*/

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, int len);

int main(void)
{
    short x = 12345;
    short y = 12345;
    short mul = x * y;
    printf("(12345 * 12345) %% 65536 = %d\n", (12345 * 12345) % (USHRT_MAX + 1));
    printf("x * y = %d\n", mul);
    show_bytes((byte_pointer)&mul, sizeof(short));
}

void show_bytes(byte_pointer start, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}