#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len); 
void show_int(int x);
void show_float(float x);
void show_pointer(void *x);
void test_show_bytes(int val);
void test_show_pointer(int hex);

int main(void) 
{
    test_show_bytes(12345);
    test_show_pointer(0x87654321);
}

void test_show_bytes(int val) 
{
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

void test_show_pointer(int hex)
{
    byte_pointer valp = (byte_pointer) &hex;
    show_bytes(valp, 1);
    show_bytes(valp, 2);
    show_bytes(valp, 3);
}

void show_bytes(byte_pointer start, int len) 
{
    int i;
    
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) 
{
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) 
{
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) // void *: 어떤 타입의 주소라도 보관 가능하다.
{
    show_bytes((byte_pointer) &x, sizeof(void *));
}