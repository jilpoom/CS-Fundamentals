#include <stdio.h>

void inplace_swap(int *x, int *y);

int main(void) {
    int x = 1;
    int y = 2;
    printf("%d %d\n", x, y);

    inplace_swap(&x, &y);

    printf("%d %d", x, y);
}

// 포인터 변수 x와 y가 가리키는 위치에 저장된 값을 XOR(Exclusive-OR)을 사용하여 교환
// 일반적인 교환 기술과 성능 차이는 없다.
// 단지, 임시로 저장할 세 번째 위치가 필요하지 않을 뿐이다.
void inplace_swap(int *x, int *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}
