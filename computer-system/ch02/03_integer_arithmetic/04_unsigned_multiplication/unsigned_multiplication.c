#include <stdio.h>
#include <limits.h>

/*
    Unsigend Multiplication
    - Unsigned x, y의 곱은 다음을 만족한다.
      - x * y = (x * y) mod 2^{bits_count}
*/

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, int len);

int main(void)
{
    unsigned short x = 12345;
    unsigned short y = 12345;
    unsigned short mul = x * y;
    printf("x * y = %d\n", mul); // 27825: (12345 * 12345) mod 2^{16}
    printf("(12345 * 12345) / 65536 = %d\n", (12345 * 12345) % (USHRT_MAX + 1));
    show_bytes((byte_pointer)&mul, sizeof(unsigned short));
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