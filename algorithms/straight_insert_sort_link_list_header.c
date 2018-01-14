#include <stdio.h>
#include <malloc.h>

/**
 * 带头结点链式存储的直插排序
 */

typedef struct node {
    int data;
    struct node *next;
} LinkList;

LinkList *init_straight_insert_sort_link_list_header() {
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

int destroy_straight_insert_sort_link_list_header(LinkList **pplinkList) {

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

int straight_insert_sort_link_list_header(LinkList *linkList) {

    LinkList *p = NULL, *q = NULL, *r = NULL, *u = NULL;

    if (!linkList) {
        return 0;
    }

    // 指向原链表（除头结点）
    p = linkList->next;
    // 原链表置空
    linkList->next = NULL;

    // 循环p链表，将p链表上的节点按照节点data域递增顺序排列到q节点上
    while (p) {
        // 指向新链表（除头结点）
        r = p->next;
        q = linkList->next;

        while ((q != NULL) && (q->data <= p->data)) {
            u = q;
            q = q->next;
        }

        // 把p插到q结点前面，即u后面
        p->next = u->next;
        u->next = p;

        p = r;
    }

    return 1;
}

int print_straight_insert_sort_link_list_header() {

    LinkList *linkList = NULL, *p = NULL, *q = NULL;

    linkList = init_straight_insert_sort_link_list_header();

    if (linkList == NULL) {
        printf("链表为空\n");
    }

    straight_insert_sort_link_list_header(linkList);

    p = linkList->next;

    printf("直插排序结果为：\n");

    while (p) {
        q = p;
        p = p->next;
        printf("%d\t", q->data);
    }

    destroy_straight_insert_sort_link_list_header(&linkList);

    return 1;
}