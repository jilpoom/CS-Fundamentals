#include <stdio.h>

/*
    2의 보수의 부정(Two's Complement Negation)
    - x + y = 0을 만족하는 y를 x의 역원이라고 한다.
    - unsigned int x를 부정(-)하면 다음의 식이 성립힌다.
        - -x = ~x + 1
    - 여기서 중요한 것은, unsigend int x에 `-`연산자룰 붙여, -x로 나타내면, 암묵적으로 `int` 타입 캐스팅이 일어난다.
*/
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len);
void test_sub_operator(unsigned short x);

int main(void)
{
    unsigned short x = 1;
    unsigned short nx = -x; // unsigend 수의 `-`는 ~x + 1로 계산된다. 
    
    show_bytes((byte_pointer) &x, sizeof(unsigned short)); // 01 00 == 0000 0000 0000 0001 : 1
    show_bytes((byte_pointer) &nx, sizeof(unsigned short)); // ff ff == 1111 1111 1111 1111 : 65535
    test_sub_operator(x);
}

void test_sub_operator(unsigned short x)
{
    unsigned short ux = x; 
    unsigned short nx = -x; // 사실상 타입 캐스팅이 이루어 진 것. -x 자체는 `int` 타입이다.

    printf("-x: %d nx: %d, ux: %d ~x + 1: %d\n", -x, nx, ux, ~x + 1);
}

void show_bytes(byte_pointer start, int len) 
{
    int i;
    
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

