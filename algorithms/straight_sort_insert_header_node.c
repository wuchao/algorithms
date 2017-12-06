#include <stdio.h>
#include <malloc.h>

/**
 * 带头结点链式存储的直插排序
 */

typedef struct node {
    int data;
    struct node *next;
} LinkList;

LinkList *createList() {
    int n, i;
    LinkList *linkList = (LinkList *) malloc(sizeof(LinkList));;
    LinkList *pre = NULL;

    if (linkList != NULL) {
        linkList->next = NULL;
        //指针引用的变量一定要有内存空间，所以不能在定义时写成这样：LinkList *pre = linkList;
        pre = linkList;
        printf("请输入链表结点的个数：");
        scanf("%d", &n);
        printf("\n");

        for (i = 0; i < n; i++) {
            LinkList *listNode = NULL;
            int e;
            printf("第%d个结点元素：", i + 1);
            scanf("%d", &e);
            listNode = (LinkList *) malloc(sizeof(LinkList));
            listNode->data = e;
            listNode->next = NULL;
            pre->next = listNode;
            pre = listNode;
        }
    }

    return linkList;
}

int destroyList(LinkList **pplinkList) {

    LinkList *p = NULL, *q = NULL;

    if (!(*pplinkList)) {
        return 0;
    }

    p = *pplinkList;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }

    // 释放完空间，将实参所指向的指针的i置空
    *pplinkList = NULL;
    return 1;
}

int straight_insert_sort_header_node(LinkList *linkList) {

    LinkList *p = NULL, *q = NULL, *r = NULL;

    if (!linkList) {
        return 0;
    }

    p = linkList->next;
    linkList->next = NULL;

    // r=p->next; p=r;
    while (p) {
        r = p->next;
        q = linkList;

        while ((q->next != NULL) && (q->next->data < p->data)) {
            q = q->next;
        }

        // 把p插到q结点后面
        p->next = q->next;
        q->next = p;

        p = r;
    }

    return 1;
}

int print_straight_insert_sort_header_node() {

    LinkList *linkList = NULL, *p = NULL, *q = NULL;

    linkList = createList();

    if (linkList == NULL) {
        printf("链表为空\n");
    }

    straight_insert_sort_header_node(linkList);

    p = linkList->next;

    printf("直插排序结果为：\n");

    while (p) {
        q = p;
        p = p->next;
        printf("%d\t", q->data);
    }

    destroyList(&linkList);

    return 1;
}