#define PF printf
#define SF printf
#define N "\n"
#define D "%d"
#define MAX_SEQ_LIST_SIZE 100

#include<stdio.h>
#include<stdlib.h>

/*类型声明*/
typedef int dataType;

typedef struct _SeqList {
    dataType data[MAX_SEQ_LIST_SIZE];
    int length; // 当前表长度
} SeqList, *PSeqList;

// 初始化 SeqList
PSeqList init_seq_list(void) {
    PSeqList PS;

    if ((PS = (PSeqList) malloc(sizeof(SeqList))) != NULL) {
        // 当前表长度置为0
        PS->length = 0;
    }

    return PS;
}
/*
	注意：
	初始化表先动态分配内存，再将表长置为0
	void * malloc(unsigned size) 分配size大小的内存单位，并返回所分配内存单元的地址，该地址是void类型
	指针的强制转化
*/

// 销毁 SeqList
void destroy_seq_list(PSeqList *PPS) {
    if (*PPS != NULL) {
        free(*PPS);
        *PPS = NULL;
    } else {
        PF("参数指针为空！" N);
        return;
    }
}

// 向顺序列表的指定位置插入一个元素
void insert_seq_list(PSeqList PS, int location, dataType e) {
    int i;

    if (PS->length >= MAX_SEQ_LIST_SIZE) {
        PF("空间已满！" N);
        return;
    }

    if (location < 0 || location >= MAX_SEQ_LIST_SIZE) {
        PF("插入的位置不正确！" N);
        return;
    }

    PS->length++;
    // 从 PS->length - 1 开始，每位前面的元素值赋值给下一位
    // i > location 表示 location 上的元素值赋值给 location + 1 位上的元素
    // 从 PS->length 到 location + 1
    for (i = PS->length - 1; i > location; i--) {//i能取到的值都要往后移一位
        PS->data[i] = PS->data[i - 1];
    }

    PS->data[location] = e;

    return;
}

// 删除顺序表中指定位置上的元素
void remove_seq_list(PSeqList PS, int location) {
    int i;

    if (!PS) {
        PF("参数指针为空！" N);
        return;
    }

    if (location < 0 || location >= MAX_SEQ_LIST_SIZE) {
        PF("location错误！" N);
        return;
    }

    // 从 i 开始，每位元素的下一个元素值赋值给该元素
    // 从 location 到 PS->length - 2
    for (i = location; i < PS->length - 1; i++) {
        PS->data[i] = PS->data[i + 1];
    }

    PS->length--;

    return;
}

// 在顺序表中找出所有的查找元素
void global_search_seq_list(PSeqList PS, dataType e) {
    int i, count = 0;

    if (!PS) {
        PF("参数指针为空！" N);
        return;
    }

    for (i = 0; i < PS->length; i++) {
        if (PS->data[i] == e) {
            count++;
            PF("查找的元素出现在顺序列表中的第 %d 个位置：" N, i + 1);
        }
    }

    if (count > 0) {
        PF(N);
        return;
    } else {
        PF("顺序列表中没有此元素！" N);
        return;
    }
}

// 在顺序表中查找出第一个要查找的元素，并保存其位置
int find_seq_list_element(PSeqList PS, dataType e) {
    if (!PS) {
        PF("参数指针为空！" N);
        return;
    }

    for (int i = 0; i < PS->length; i++) {
        if (PS->data[i] == e) {
            return i;
        }
    }

    PF("顺序列表中没有此元素！" N);

    return -1;
}

// 在顺序表的指定位置替换一个元素
void update_seq_list_element(PSeqList PS, int location, dataType e) {
    if (!PS) {
        PF("参数指针为空！" N);
        return;
    }

    if (location < 0 || location >= MAX_SEQ_LIST_SIZE) {
        PF("位置错误！" N);
        return;
    }

    PS->data[location] = e;

    return;
}

// 获取顺序列表的长度
int count_seq_list_length(PSeqList PS) {
    if (PS != NULL) {
        return PS->length;
    } else {
        PF("参数指针为空！" N);
        return 0;
    }
}

void print_seq_list() {
    PSeqList PS = init_seq_list();
    if (PS == NULL) {
        PF("初始化失败！" N);
        return;
    }

    insert_seq_list(PS, 1, 1);
    insert_seq_list(PS, 2, 2);
    insert_seq_list(PS, 3, 3);
    insert_seq_list(PS, 4, 1);
    insert_seq_list(PS, 5, 2);
    insert_seq_list(PS, 6, 3);

    PF(D N, PS->length);
    PF(D N, PS->data[0]);
    PF(D N, PS->data[1]);
    PF(D N, PS->data[2]);
    PF(D N, PS->data[3]);
    PF(D N, PS->data[4]);
    PF(D N, PS->data[5]);

    global_search_seq_list(PS, 1);

    remove_seq_list(PS, 2);

    PF(D N, PS->data[1]);
    PF(D N N,PS->data[5]);

    update_seq_list_element(PS, 7, 5);

    PF(D N N, PS->data[7]);

    //销毁顺序表
    destroy_seq_list(PS);
}