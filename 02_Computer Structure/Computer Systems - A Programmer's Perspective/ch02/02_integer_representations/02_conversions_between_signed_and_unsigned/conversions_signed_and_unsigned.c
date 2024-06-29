#include <stdio.h>

/*
    C언어에서는 타입 형변환을 허용한다.
    - signed 값을 unsigned 값으로 캐스팅할 때는, 비트 수준의 관점에 기반한다.
    - 타입이 캐스팅 될 때는, 기본 비트 표현은 동일하게 유지된다.
    
    1. U 2 T (Unsigned To Two's complement)
      - Unsigned 값에서 Signed 값으로의 변환은 전체 비트의 절반 (2^n-1)의 값을 양수로, 0을 제외한 나머지를 음수로 인식하여 캐스팅 된다.
    
    2. T 2 U (Two's complement To Unsigned)
      - Signed 값에서 Unsigned 값으로의 변환은 0보다 작은 값 (0 < x < -2^n-1)을 Unsigned의 중간값(2^n-1) 이상으로 인식하고 캐스팅 된다.
*/

void test_t2u(int x);

int main(void)
{
    short int v = -12345; 
    unsigned short uv = (unsigned short) v;
    
    unsigned u = 4294967295u; /* UMAX_32 */
    int tu = (int) u;


    printf("v = %d, uv = %u\n", v, uv);
    printf("u = %u, tu = %d\n", u, tu);

    printf("Test T To U\n");
    test_t2u(-8);
    test_t2u(-3);
    test_t2u(-2);
    test_t2u(-1);
    test_t2u(0);
    test_t2u(5);
}

void test_t2u(int x)
{
    printf("u = %u, v = %d\n", (unsigned int) x, x);
}