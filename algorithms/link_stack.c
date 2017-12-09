#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int stackdt;

//定义链栈结点结构体
typedef struct _StackNode {
    stackdt data;
    struct _StackNode *next;
} StackNode, *PStackNode;

//定义链栈栈顶结构体
typedef struct node {
    PStackNode top;
} LinkStack, PLinkStack;

//初始化链栈
PLinkStack init_link_stack() {
    PLinkStack PS;
    PS = (PLinkStack) malloc(sizeof(LinkStack));

    if (PS) {
        PS->top = NULL;
    }

    return PS;
}

//判断链栈是否为空
int is_empty_link_stack(PLinkStack PS) {
    if (PS) {
        if (PS->top == NULL) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

//入栈
void push_link_stack(PLinkStack PS, stackdt e) {
    if (!PS) {
        printf("链栈为空\n");
        return;
    }

    PStackNode p;
    p = (PStackNode) malloc(sizeof(StackNode));

    if (!p) {
        printf("链栈结点申请内存空间失败！\n");
        return;
    }

    p->data = e;

    p->next = PS->top;
    PS->top = p;

    printf("入栈成功！\n");
    return;
}

//出栈
void pop_link_stack(PLinkStack PS, stackdt *e) {
    if (!PS) {
        printf("链栈为空\n");
        return;
    }

    PStackNode p;

    if (is_empty_link_stack(PS) == 1) {
        printf("栈空，出栈失败！\n");
        return;
    }

    p = PS->top;
    *e = p->data;
    PS->top = p->next;

    free(p);

    printf("出栈成功！ \n");
    return;
}

//获取栈顶元素
void get_top_link_stack(PLinkStack PS, stackdt *e) {
    if (!PS) {
        printf("栈空\n");
        return;
    }

    if (is_empty_link_stack(PS) == 1) {
        printf("栈为空！\n");
        return;
    }

    *e = PS->top->data;

    return;
}

//销毁栈
void destroy_link_stack(PLinkStack *PS) {
    PStackNode p, q;

    if (*PS != NULL) {
        p = (*PS)->top;

        while (p) {
            q = p;
            p = p->next;
            free(q);
        }

        free(*PS);
    }

    *PS = NULL;

    return;
}