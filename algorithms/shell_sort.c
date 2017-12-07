/*
	希尔排序的思想：

	希尔排序是以直接插入排序为基础拓展的，直接插入排序比较的是相邻的元素，
	而希尔排序比较的是间隔gap距离的元素。

	希尔排序开始时gap的值较大，子序列中的元素较少，排序速度比较快；
	随着排序进展gap的值逐渐减小，子序列中的元素增多，不过
	由于前面排序工作的基础，大多数元素已经基本有序，所以排
	序速度依然是比较快的
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define T "\t"
#define GapLength 3
#define FSDT "%d"    /*FSDT:dataType类型的格式说明符(format specifier of dataType)*/

typedef int dataType;

//函数声明
void shell_sort(dataType H[], int aryLength, int gap);

/****************************************
函数名称：shell_sort
函数功能：希尔排序
函数参数：要排序的元素的数组H[]，数组的长度aryLength
返回值：void
****************************************/
void shell_sort(dataType H[], int aryLength, int gap) {

    int i, j;

    dataType tmp;

    for (i = gap; i < aryLength; i++) {
        tmp = H[i];
        j = i - gap;

        while (j >= 0 && H[j] > tmp) {
            H[j + gap] = H[j];
            j = j - gap;
        }

        H[j + gap] = tmp;
    }

    return;
}


int print_shell_sort() {
    dataType *H;    /*指向带排序序列数组首地址的地址*/
    int i, j, SIZE;        /*用户输入的带排序序列的长度*/
    int gaps[GapLength] = {5, 3, 1};    /*gaps数组存放步长*/
    //int S[14] = {39, 80, 76, 41, 13, 29, 50, 78, 30, 11, 100, 7, 41, 86};	/*数据结构数中的带排序序列*/

    printf("请输入大小SIZE：\n");
    scanf(FSDT, &SIZE);
    H = (dataType *) malloc(sizeof(dataType) * SIZE);

    srand(time(NULL));
    printf("带排序序列：\n");
    for (i = 0; i < SIZE; i++) {
        H[i] = rand() % 101;        /*随机赋SIZE个介于0至100整数范围内的待排序的值  （*运算与[]运算是等价的）*/
        printf(FSDT T, H[i]);
    }
    printf("\n");

    //循环调用希尔排序
    for (i = 0; i < GapLength; i++) {
        shell_sort(H, SIZE, gaps[i]);
        printf("步长为" FSDT "排序结果为：\n", gaps[i]);
        for (j = 0; j < SIZE; j++) {
            printf(FSDT T, H[j]);
        }
        printf("\n");
    }
    printf("\n\n");

    return 0;
}