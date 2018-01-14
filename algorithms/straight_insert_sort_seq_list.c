#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 10

/*直插排序*/
void straight_insert_sort_seq_list(int a[], int n) {

    int i, j, t;

    for (i = 1; i < n; i++) {

        t = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > t) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = t;
    }

    return;
}

int print_straight_insert_sort_seq_list() {
    int a[N];
    int i;

    srand(time(NULL));
    printf("\n\n直插排序待排序元素为：\n");
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
        printf("%d\t", a[i]);
    }
    printf("\n\n");

    straight_insert_sort_seq_list(a, N);
    printf("直插排序的结果为：\n");
    for (i = 0; i < N; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n\n");

    return 1;
}

