#include <stdio.h>

/*
    Unsigned Addition
    - 산술 연산에서 오버플로우란 전체 정수 결과가 데이터 타입의 워드 크기 제한 내에 맞지 않을 때 발생한다.
    - unsigend int x, y가 있을 때, x + y 가 x보다 크거나 같다면, 오버플로우가 일어났다고 볼 수 있다.

*/

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len);
int uadd_ok(unsigned x, unsigned y);

int main(void)
{
    unsigned x = 123;
    unsigned y = 123;
    
    printf("%d\n", uadd_ok(x, y));
    
    x = -1; /* UINT_MAX */ 
    y = 1;
    printf("%d", uadd_ok(x, y));
}


/* 오버플로우가 일어났는지 확인하는 함수 */
int uadd_ok(unsigned x, unsigned y)
{
    show_bytes((byte_pointer) &x, sizeof(x));
    show_bytes((byte_pointer) &y, sizeof(x));

    return x + y >= x; 
}

void show_bytes(byte_pointer start, int len) 
{
    int i;
    
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}
