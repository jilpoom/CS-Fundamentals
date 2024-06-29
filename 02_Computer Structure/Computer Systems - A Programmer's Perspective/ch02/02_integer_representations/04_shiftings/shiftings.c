#include <stdio.h>

/*
    - fun1 함수는 word의 하위 8비트를 논리적으로 시프트하여 부호 없는 값(Unsigned)을 반환
    - fun2 함수는 word의 하위 8비트를 산술적으로 시프트하여 부호 있는 값(Signed)을 반환
*/

typedef unsigned char *byte_pointer;

int fun1(unsigned word);
int fun2(unsigned word);
void show_bytes(byte_pointer start, int len);

int main(void)
{
    int f1v = fun1(1234);
    int f2v = fun2(1234);
    printf("%d\n", f1v);
    printf("%d", f2v);
}

int fun1(unsigned word)
{
    show_bytes((byte_pointer) &word, sizeof(unsigned));
    unsigned x = word << 24; // 최상위 비트만 유지
    show_bytes((byte_pointer) &x, sizeof(unsigned));
    int y = x >> 24; // 상위 8비트가 0으로 채워짐
    show_bytes((byte_pointer) &y, sizeof(int));
    return y;
}

int fun2(unsigned word)
{
    show_bytes((byte_pointer) &word, sizeof(unsigned));
    int x = word << 24;
    show_bytes((byte_pointer) &x, sizeof(unsigned));
    int y = x >> 24;
    show_bytes((byte_pointer) &y, sizeof(int));
    return y;
}


void show_bytes(byte_pointer start, int len) 
{
    int i;
    
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}