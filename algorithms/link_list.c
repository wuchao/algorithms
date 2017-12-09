#define PF printf
#define N "\n"
#define D "%d"

#include<stdio.h>
#include<stdlib.h>

/**
 * 带头结点的单链表（代码未经过测试）
 *
 * 链表：
 * 带头结点/不带头结点（以后写链表都默认使用带头结点）
 * 单链表/双向链表/循环链表/双向循环链表
 */

// 变量和结构体的声明
typedef int dataType;

typedef struct node {
    // 链表结点的数据域
    dataType data;
    // 链表结点的下一个相邻结点
    struct node *next;
} LinkList, *PLinkList;

// 初始化头结点
PLinkList init_link_list() {
    PLinkList PL;

    PL = (PLinkList) malloc(sizeof(LinkList));
    if (PL) {
        PL->next = NULL;
    }

    return PL;
}

// 创建链表
PLinkList create_link_list(PLinkList PL) {
    if (PL) {
        // q 指向尾结点
        PLinkList q = PL->next;
        int l;
        scanf("请输入要创建的链表节点的长度： ", &l);

        // 在链表尾部插入新加元素
        for (int i = 0; i < l; ++i) {
            PLinkList p = (PLinkList) malloc(sizeof(LinkList));
            if (p) {
                scanf("请输入第 %d 个元素的值： ", i, &(p->data));
                p->next = q->next;
                q->next = p;
                q = p;
            }
        }
    }

    return PL;
}

//销毁 LinkList
void destroy_link_list(PLinkList *H) {
    PLinkList d, p;

    if (!(*H)) {
        PF("链表为空！" N);
        return;
    }

    p = *H;
    while (p) {
        d = p; // 当p为真时，将p释放
        p = p->next;
        free(d);
    }

    *H = NULL;

    return;
}

//获取 PLinkList 的长度
int count_link_list_length(PLinkList p) {
    int count = 0;//记录PLinkList结点总数（不计头结点）

    while (p) {
        count++;
        p = p->next;
    }

    return count;
}

/**
 * 查找指定位置的节点元素（头结点增加一个length属性？？？）
 * @param PL
 * @param location 头结点后第 location 个元素
 * @return
 */
PLinkList locate_link_list_element(PLinkList PL, int location) {
    PLinkList p = PL->next;
    int i = 0;

    if (!PL) {
        PF("PLinkList为空！" N);
        return NULL;
    }

    if (location < 1) {
        PF("插入位置不合理！" N);
        return NULL;
    }

    while (p && i < location - 1) {
        p = p->next;
        i++;
    }

    return p;
}

// 添加结点
void add_link_list_element(PLinkList PL, int location, dataType e) {
    int currentLength = length(PL);
    PLinkList p, addP;

    if (currentLength < 0) {
        PF("PLinkList为空！" N);
        return;
    }

    if ((p = locate_link_list_element(PL, location - 1)) == NULL) {//找出location位置前一个结点
        return;
    }

    addP = (PLinkList) malloc(sizeof(LinkList));
    if (!addP) {
        PF("申请空间失败！" N);
        return;
    }

    addP->data = e;
    addP->next = p->next;//p = p->next;//p->next是location位置上的结点
    p->next = addP;

    return;
}

// 删除结点
void remove_link_list_element(PLinkList PL, int location) {
    PLinkList p;

    if (!PL) {
        PF("PLinkList为空！" N);
        return;
    }

    p = locate_link_list_element(PL, location - 1); //定位location位置前一个结点
    if (p == NULL || p->next == NULL) { //要删除的结点不能为空
        PF("位置错误！" N);
        return;
    }

    PLinkList q = p->next;
    p->next = p->next->next;
    free(q);

    return;
}

// 查询结点，通过元素
PLinkList search_link_list_val(PLinkList PL, dataType e) {
    PLinkList p;

    if (!PL) {
        PF("PLinkList为空！" N);
        return NULL;
    }

    p = PL->next;
    while (p && p->data != e) {
        p = p->next;
    }

    if (!p || p->data != e) {
        PF("查找失败！" N);
        return NULL;
    }

    return p;
}

// 更新节点元素值
void update_link_list_element(PLinkList PL, int location, dataType e) {
    PLinkList p;

    if (!PL) {
        PF("PLinkList为空！" N);
        return;
    }

    p = locate_link_list_element(PL, location - 1);
    if (!p) {
        PF("位置错误！" N);
        return;
    }

    p->next->data = e;

    return;
}