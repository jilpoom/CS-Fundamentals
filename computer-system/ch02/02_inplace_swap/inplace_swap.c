#include <stdio.h>

void inplace_swap(int *x, int *y);
void reverse_array(int a[], int cnt);
void print_array(int a[], int cnt);

int main(void) {
    int x = 1;
    int y = 2;
    int a[] = {1, 2, 3, 4, 5, 6};

    printf("%d %d\n", x, y);
    print_array(a, 6);

    inplace_swap(&x, &y);
    reverse_array(a, 6);

    printf("%d %d\n", x, y);
    print_array(a, 6);
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

void reverse_array(int a[], int cnt)
{
    int first, last;

    for(first = 0, last = cnt - 1; first < last; first++, last--)
    {
        inplace_swap(&a[first], &a[last]);
    }
}

void print_array(int a[], int cnt)
{
    int i;

    for(i = 0; i < cnt; i++) 
    {
        printf(" %d", a[i]);
    }
    printf("\n");
}