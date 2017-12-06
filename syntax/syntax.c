//
// Created by wu on 17-11-30.
//
#include <stdio.h>

void systnx() {
    char c;
    int i;
    long l;
    float f;
    double d;

    printf("Size of char : %d bytes\n", sizeof(c));
    printf("Size of int : %d bytes\n", sizeof(i));
    printf("Size of long : %d bytes\n", sizeof(l));
    printf("Size of float : %d bytes\n", sizeof(f));
    printf("Size of double : %d bytes\n", sizeof(d));


    printf("------------------------------------------------------------------\n");


    int num = 5;
    int *p = &num;

    printf("value of variable num : %d\n", num);
    printf("value of &num %u\n", &num);
    printf("value of variable p : %u\n", p);
    printf("value of *p : %d\n", *p);

    return;
}
