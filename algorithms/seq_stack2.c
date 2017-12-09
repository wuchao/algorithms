/*
	栈：后进先出
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 1000

typedef int stackdt;  //stackdt:stack dataType
typedef struct {
    stackdt *base;
    stackdt *top; //当栈为空时,base和top相等,当入栈时,top指向入栈后元素位置的下一位地址
    int length;
} SeqStack, *PSeqStack;


//初始化栈
PSeqStack init_seq_stack() {
    PSeqStack PS = (PSeqStack) malloc(sizeof(SeqStack));

    if (PS) {
        PS->base = stackdt[MAXSIZE];
        if (PS->base) {
            PS->top = PS->base;
            PS->length = MAXSIZE;
        }
    }

    return PS;
}

//判断栈是否为空
int is_empty_seq_stack(PSeqStack PS) {
    if (PS && PS->top == PS->base) {
        return 1;
    } else {
        return 0;
    }
}

//判断栈是否已满
int is_full_seq_stack(PSeqStack PS) {
    if (PS && PS->top - PS->base == PS->length) {
        return 1;
    } else {
        return 0;
    }
}

//入栈
void push_seq_stack(PSeqStack PS, stackdt e) {
    if (is_full_seq_stack(PS) == 1) {
        printf("栈已满！\n");
        return;
    } else {
        *(PS->top++) = e;
        printf("入栈成功！\t入栈元素是：%d\t", e);
        return;
    }
}

//出栈
void pop_seq_stack(PSeqStack PS, stackdt *e) {
    if (is_empty_seq_stack(PS) == 1) {
        printf("栈已空！\n");
        return;
    } else {
        *e = *(--PS->top);
        printf("出栈成功！\t出栈元素是：%d\t", *e);
        return;
    }
}

//获取栈顶元素
void get_top_seq_stack(PSeqStack PS, stackdt *e) {
    if (is_empty_seq_stack(PS) == 1) {
        printf("栈为空！\n");
        return;
    } else {
        PSeqStack p = PS->top;
        *e = *(--p);
        return;
    }
}

//修改栈元素的值
void update_seq_stack(PSeqStack PS, int i, int e) {
    if (is_empty_seq_stack(PS) == 1) {
        printf("栈为空！\n");
        return;
    }

    if (i - 1 < 0 || i - 1 >= PS->length) {
        printf("修改的元素的位置错误！\n");
        return;
    } else {
        PS->base[i - 1] = e;
        return;
    }
}

//销毁栈
void destroy_seq_stack(PSeqStack *PS) {
    if (*PS) {
        free(PS);
    }

    *PS = NULL;

    return;
}

int print_seq_stack() {
    PSeqStack PS;
    stackdt stacke;
    int i, n;

    PS = init_seq_stack();
    if (!PS) {
        printf("栈为空！\n");
        return 0;
    }

    printf("请输入栈元素的个数（小于100个）：\n");
    scanf("%d", &n);
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        push_seq_stack(PS, rand() % 101);
    }
    printf("\n\n");

    //入栈
    push_seq_stack(PS, 99);

    //出栈
    pop_seq_stack(PS, &stacke);

    //获取栈顶元素
    get_top_seq_stack(PS, &stacke);
    printf("栈顶元素是：%d\n", stacke);

    //释放栈内存空间
    destroy_seq_stack(PS);

    return 0;
}