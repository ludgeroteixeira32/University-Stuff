#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

    int a = 1;
    int *b = &a;
    printf("1 %d\n" , *b);
    int *c;
    c = b;
    printf("1 %d\n" , *c);
}