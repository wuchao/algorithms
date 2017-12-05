#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

/**
 * bubble_sort函数每次都以a[i]和与其相邻的a[i + 1]作比较得出一个最大值，
				再以这个最大值继续和后面的元素作比较，所以经过一轮循环使
				得参与该论比较的元素中的最大值被移动到了最后一位（index:n - 1 - i）。

    冒泡排序的定义是：
				不停地比较相邻记录的关键字，如果不满足排序要求，就交换相
				邻记录，直到所有的记录都已经排好序为止。
 * @param a
 * @param n
 * @return
 */
int bubble_sort(int a[], int n) {
    int i, j, t;
    // 每一个元素循环执行完第二层循环后，它就与其他所有的元素都有序了，到最后一个元素，
    // 它没有其他元素可以比较了，因为它已经和其他元素都有序了
    for (i = 0; i < n - 1; i++) {
        // n - 1 - i 表示剩余待排序元素个数
        for (j = 0; j < n - 1 - i; j++) {
            // 排在前面的元素大于排在后面的元素时，两元素对换位置
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }

        printf("本轮循环找出的最值为：%d\n", a[n - 1 - i]);
    }
    return 0;
}

int print(int a[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\t", a[i]);
    }
    return 0;
}

int print_bubble_sort(void) {
    int i;
    int a[N];

    srand(time(0));
    printf("待排序的元素为\n");
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
        printf("%d\t", a[i]);
    }
    printf("\n");

    bubble_sort(a, N);

    printf("\n");
    printf("冒泡排序的结果为\n");
    print(a, N);
    printf("\n");

    return 0;

}