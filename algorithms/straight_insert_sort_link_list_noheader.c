#include <stdio.h>
#include <malloc.h>

/**
 * 不带头结点链式存储的直插排序
 */

//定义链式列表元素结构体
typedef struct node {
    int data;
    struct node *next;
} LinkList;

int straight_insert_sort_link_list_noheader(LinkList *linkList) {

    LinkList *p = NULL, *q = NULL, *r = NULL;

    if (!linkList) {
        return 0;
    }

    p = linkList->next;
    q = linkList;
    linkList->next = NULL;

    /*
        无头节点比有头结点多了以下这个if判断语句
        if判断语句里面执行的代码就是将一个无头结点的链表的第一个元素和第二个元素调换位置，
        这个操作也是一个无头节点链表的逆置的关键操作
    */
//    if (p && q->data > p->data) {
//        p->next = q->next;
//        q->next = p;
//    }
//
//    while (p) {
//        r = p->next;
//        q = linkList;
//
//        while ((q != NULL) && (q->data < p->data)) {
//            q = q->next;
//        }
//
//        p->next = q->next;
//        q->next = p;
//
//        p = r;
//    }

    return 1;
}