#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 10

/*直插排序_数组_递归*/
void straight_insert_sort_seq_list_recursion(int a[], int n) {
    int i;
    int t;

    //n - 1 > 0
    if (n > 1) {
        /*
            straight_insert_sort_seq_list_recursion()函数，使在对第n个元素进行排序前
            让前（n - 1）个元素先有序
        */
        straight_insert_sort_seq_list_recursion(a, n - 1);

        //对第n个元素进行直插排序
        t = a[n - 1];
        i = (n - 1) - 1;

        while (i >= 0 && a[i] > t) {
            a[i + 1] = a[i];
            i--;
        }

        a[i + 1] = t;
    }

    return;
}

int print_straight_insert_sort_seq_list_recursion() {
    int a[N];
    int i;

    srand(time(NULL));
    printf("（递归）直插排序待排序元素为：\n");
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
        printf("%d\t", a[i]);
    }
    printf("\n\n");

    straight_insert_sort_seq_list_recursion(a, N);
    printf("（递归）直插排序的结果为：\n");
    for (i = 0; i < N; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n\n");

    return 1;
}