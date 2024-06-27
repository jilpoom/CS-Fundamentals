#include <stdio.h>
#include <string.h>

float test_sum_elements(float a[], unsigned length);
int test_strlonger(char *s, char *t);

int main (void)
{
    float a[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    // test_sum_elements(a, 0); // ERROR
    printf("%d", test_strlonger("1234", "12345"));
}


/* WARNING: This is buggy code */
/* 
    length가 0 일 때,
    - unsigend 0 - 1은 4294967295가 되므로, i는 항상 참이되어 루프가 무한히 실행되어, 오류가 발생한다.
*/
float test_sum_elements(float a[], unsigned length)
{
    int i;
    float result = 0;
    
    for (i = 0; i <= length - 1; i++) {
        result += a[i];
    }

    return result;
}

/* WARNING: This is buggy code */
/*
    strlen의 타입인 t_size는 unsigend int로 정의되어 있다.
    즉, *s, *t로 "1234", "12345"가 주어졌을 때, 4 - 5는 unsigend int로 4294967295가 된다.
    그러므로 항상 *s가 *t보다 짧을 때는, 항상 참을 반환한다

    수정
    strlen(s) - strlen(t) > 0; 을 다음과 같이 변경
    - strlen(s) > strlen(t);
    - 위와 같이 하면 unsigned 숫자만으로 비교하게 된다.
*/
int test_strlonger(char *s, char *t)
{
    return strlen(s) - strlen(t) > 0;
}