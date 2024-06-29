#include <stdio.h>

/*
    수의 비트 표현의 확장
    - Unsigned와 Signed를 비교할 때는, Unsigned 쪽으로 타입 캐스팅이 이루어진다.
    - 즉, 비교의 피연산자 중 하나가 부호 없는(Unsigned) 값이라면, 다른 피연산자는 암묵적으로 부호 없는 값으로 변환된다.
    - '*'가 표시된 결과값은 우리가 기대하는 결과값과 다르다는 것을 알 수 있다.

    - 부호 없는 숫자를 더 큰 데이터 타입으로 변환할 때는 Zero Extensions를 따른다.
    - 부호 있는 숫자(2의 보수 표현 숫자)를 더 큰 데이터 타입으로 변환할 때는 Sign Extension을 따른다.

    - 만약 더 작은 데이터에서 더 큰 Unsigned로 캐스팅하면, 데이터 크기가 먼저 일어난 후, 부호를 변경한다.
*/

typedef unsigned char *byte_pointer;

void test_promotion_rules(int x);
void test_extensions();
void show_bytes(byte_pointer start, int len);

int main(void)
{
    // C의 Unsigned, Signed 간의 형변환 규칙
    test_promotion_rules(0 == 0U); // 1
    test_promotion_rules(-1 < 0); // 1
    test_promotion_rules(-1 < 0U); // 0*
    test_promotion_rules(2147483647 > -2147483647-1); // 1
    test_promotion_rules(214783647U > -2147483647-1); // 0*
    test_promotion_rules(2147483647 > (int) 2147483648U); // 1*
    test_promotion_rules(-1 > -2); // 1
    test_promotion_rules((unsigned) -1 > -2); // 1

    // Unsigned, Signed의 데이터 크기별 차이
    test_extensions();
}

void test_promotion_rules(int x)
{
    printf("d = %d, u = %u\n", x);
}

void test_extensions()
{
    short sx = -12345; // -12345
    unsigned short usx = sx; // 53191;
    int x = sx; // -12345
    unsigned ux = usx; // 53191
    unsigned uy = sx; /* Mystery! */ 
    
    printf("sx = %d:\t", sx);
    show_bytes((byte_pointer) &sx, sizeof(short));
    printf("usx = %d:\t", usx);
    show_bytes((byte_pointer) &usx, sizeof(unsigned short));
    printf("x = %d:\t", x);
    show_bytes((byte_pointer) &x, sizeof(int)); // Sign Extension
    printf("ux = %u:\t", ux);
    show_bytes((byte_pointer) &ux, sizeof(unsigned)); // Zero Extension
    printf("uy = &u:\t", uy);
    show_bytes((byte_pointer) &uy, sizeof(unsigned));
}

void show_bytes(byte_pointer start, int len) 
{
    int i;
    
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}