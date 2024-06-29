#include <stdio.h>

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, int len);

/*
2의 보수를 통한 음수 변환은 다음의 규칙을 따른다.
    1. 숫자가 양수이면, 2진수를 10진수로 단순히 변환합니다.
    2. 숫자가 음수이면, 2의 보수 규칙을 사용하여 변환합니다:
        - 모든 비트를 반전시킵니다.
        - 반전된 2진수 숫자에 1을 더합니다.
        - 결과를 10진수로 변환하고 음수 기호를 추가합니다.
*/
int main(void)
{
    short x = 12345;
    short mx = -x;
    short tx = ~x + 1; // 부호 있는 비트의 역 + 1은 해당 비트의 음수와 같다.
    
    show_bytes((byte_pointer) &x, sizeof(short)); // [00110000 00111001]
    show_bytes((byte_pointer) &mx, sizeof(short)); // [11001111 11000111] 
    show_bytes((byte_pointer) &tx, sizeof(short)); // [11001111 11000111] 
}

void show_bytes(byte_pointer start, int len) 
{
    int i;
    
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}