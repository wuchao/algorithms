//
// Created by wu on 17-11-30.
//
#include <stdio.h>

void syntax() {
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

    //
    char *str = "Hello";
    printf("size of str : %d \n", sizeof(str));

    int intary[3];
    printf("size of int array : %d \n", sizeof(intary));
    int *intpointer = intary;
    printf("size of int pointer %d \n", sizeof(intpointer));
    printf("zhizhen de zhizhen %d \n", sizeof(&intpointer));
    printf("zhizhen de zhizhen %d \n", sizeof((&intpointer)[10]));


    return;
}
