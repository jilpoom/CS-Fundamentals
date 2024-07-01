#include <stdio.h>

int div16(int x);

int main(void)
{
    printf("%d", div16(17));
}

/* 정수 X에 대해 X / 16를 반환하는 함수 */
/*
    `x >> 31`은 음수인 경우, 모든 비트를 1, 양수나 0인 경우 모든 비트를 0으로 만든다.
    `& 15`를 통해, 음수일 때만, bias 값을 15로 설정한다. 양수일 때는 0이다.
    `(x + bias) >> 4`로 16으로 나눈 값을 return한다.
*/
int div16(int x)
{
    int bias = (x >> 31) & 15;

    return (x + bias) >> 4;
}