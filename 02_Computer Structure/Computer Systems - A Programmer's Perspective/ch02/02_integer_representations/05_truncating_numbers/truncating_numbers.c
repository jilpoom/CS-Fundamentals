#include <stdio.h>

/*
    Truncating Numbers
    - 32비트 int를 16비트 short로 캐스팅하는 경우, 하위 16비트만 유지되고 상위 16비트는 버려진다.
    - Signed 에서 상위 비트를 버리면, 가장 상위의 비트가 1 이라면 음수, 아니라면 양수 혹은 0을 나타낸다.
    - Unsigned 에서 상위 비트를 버리는 것은 해당 Unsigned를 2^k로 나눈 나머지를 구하는 것과 같다.

*/
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len);
void test_truncate();

int main(void)
{
    int x = 53191;
    short sx = (short) x; /* -12345 */ 
    int y = sx; /* -12345 */
    
    show_bytes((byte_pointer) &x, sizeof(int)); 
    show_bytes((byte_pointer) &y, sizeof(int));
}

void show_bytes(byte_pointer start, int len) 
{
    int i;
    
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}
