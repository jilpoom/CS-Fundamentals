#include <stdio.h>
#include <limits.h>

/*
    Two's Complement Addition
    - signed int x, y를 덧셈할 경우, w를 비트수라고 할 때, 다음의 3가지 경우로 나눌 수 있다.
        - 2^{w - 1} <= x + y -> Negative Overflow 
        - -2^{w - 1} <= x + y < 2^{w - 1} - Normal
        - x + y < -2^{w - 1} - Positive Overflow
*/

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len);
int test_tadd_ok(int x, int y);
int buggy_test_tadd_ok(int x, int y);
int buggy_test_tsub_ok(int x, int y);

int main(void)
{
    printf("Normal: %d\n", test_tadd_ok(1, 1)); // Normal;
    printf("Negative Overflow: %d\n", test_tadd_ok(INT_MAX, 1)); // Negative Overflow;
    printf("Positive Overflow: %d\n", test_tadd_ok(INT_MIN, -1)); // Positive Overflow;
}  

/*
    int x, y를 더할 때, 오버플로우가 일어나는지 확인하는 함수
*/
int test_tadd_ok(int x, int y)
{
    show_bytes((byte_pointer) &x, sizeof(int));
    show_bytes((byte_pointer) &y, sizeof(int));
    
    int sum = x + y;
    printf("sum: %d\n", sum);
    
    if(x > 0 && y > 0 && sum < 0) { /* x, y가 양수일 때, sum이 음수라면 Negative Overflow*/
        return 0;
    }

    if(x < 0 && y < 0 && sum > 0) { /* x, y가 음수일 때, sum이 양수라면 Positive Overflow */
        return 0;
    }

    return 1; /* Normal */
}

/* WARNING: This is buggy code */
/*
    x 가 INT_MAX이고, y = 1 일 경우,
    sum은 Negative Overflow에 의해 INT_MIN이 된다.
    (INT_MIN - INT_MAX == 1) && (INT_MIN - 1 == INT_MAX) 를 만족하므로, 오버플로우가 되었음에도 불구하고 1을 반환하게 된다.
*/
int buggy_test_tadd_ok(int x, int y)
{
    int sum = x + y;

     return (sum - x == y) && (sum - y == x);
}

/* WARNING: This is buggy code */
/* 
    int x, y를 뺄 떄, 오버플로우가 일어나는지 확인하는 함수 
    x 가 INT_MIN이고, y = 1이라면, INT_MIN + (-1) == INT_MAX이므로 Positive Overflow를 발생시킨다.
    즉, x가 INT_MIN인 경우 y는 정의될 수 없다.(어떤 양수 값을 빼든, Positive Overflow가 발생한다.)
*/
int buggy_test_tsub_ok(int x, int y)
{
    /* 버그 해결 조건문
    if (x == INT_MIN) { // x가 최소값인 경우
        return (y <= 0); // y가 양수면 오버플로우가 발생하므로, y는 음수거나 0이어야 한다.
    }
    */

    return test_tadd_ok(x, -y);
}

void show_bytes(byte_pointer start, int len) 
{
    int i;
    
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}