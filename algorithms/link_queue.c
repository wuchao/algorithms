#include <stdio.h>
#include <malloc.h>

typedef char dataType;

typedef struct qnode {
    dataType data;
    struct qnode *next;
} Qnode;

typedef struct _LinkQueue {
    Qnode *front; // 指向队列第一个元素
    Qnode *rear; // 指向队列最后一个元素
} LinkQueue;

/*创建队列*/
LinkQueue *init_link_queue() {
    LinkQueue *Q = (LinkQueue *) malloc(sizeof(LinkQueue));
    if (Q != NULL) {
        Q->front = Q->rear = NULL;
    }

    return Q;
}

/*判断队列是否为空*/
int is_empty_link_queue(LinkQueue *Q) {
    if (Q != NULL && Q->front == NULL && Q->rear == NULL) {
        return 1;
    }
    return 0;
}

/*入队*/
int in_link_queue(LinkQueue *Q, dataType e) {
    Qnode *node = NULL;

    if (Q != NULL) {
        node = (Qnode *) malloc(sizeof(Qnode));
        if (node == NULL) {
            return 0;
        }
        node->data = e;
        node->next = NULL;

        if (is_empty_link_queue(Q)) {
            Q->front = Q->rear = node;
        } else {
            // 新加元素接在队列最后一个元素后面，同时 Q->rear 指向新加的元素
            Q->rear->next = node;
            Q->rear = node;
        }

        return 1;
    }

    return 0;
}

/**
 * 出队, 指针 e 保存出队元素值
 * @param Q
 * @param e
 * @return
 */
int out_link_queue(LinkQueue *Q, dataType *e) {
    Qnode *node = NULL;

    if (Q != NULL) {
        if (is_empty_link_queue(Q)) {
            return 0;
        } else {
            *e = node->data;
            node = Q->front;
            Q->front = node->next;
            free(node);

            /*最后一个元素出队后*/
            if (Q->front == NULL) {
                Q->rear = NULL;
            }

            return 1;
        }
    }

    return 0;
}

/*销毁队列*/
int destroy_link_queue(LinkQueue **Q) {
    LinkQueue *q = *Q;
    Qnode *node = q->front;

    if (is_empty_link_queue(q)) {
        free(q);
        *Q = NULL;
        return 1;
    }

    while (node != NULL) {
        q->front = node->next;
        free(node);
        node = q->front;
    }

    q->rear = NULL;
    free(q);
    *Q = NULL;

    return 1;
}

int print_link_queue(void) {
    LinkQueue *Queue = NULL;
    Qnode *p = NULL;
    char c;
    int n, i;

    Queue = init_link_queue();

    if (Queue != NULL) {
        printf("请输入Queue1的元素的个数：");
        scanf("%d", &n);

        printf("请输入%d个元素：\n", n);
        fflush(stdin);
        for (i = 0; i < n; i++) {
            c = getchar();
            in_link_queue(Queue, c);
        }
    }


    /*验证队列合并结果*/
    p = Queue->front;
    printf("\n两队列合并后的队列为：\n");
    while (p != NULL) {
        printf("%c\t", p->data);
        p = p->next;
    }

    /*前三个元素出队*/
    printf("\n前三个元素出队：\n");
    for (i = 0; i < 3; i++) {
        out_link_queue(Queue, &c);
        printf("第%d个元素%c出队：\n", i + 1, c);
    }

    p = Queue->front;
    printf("\n前三个元素出队后的队列为：\n");
    while (p != NULL) {
        printf("%c\t", p->data);
        p = p->next;
    }

    /*销毁队列*/
    destroy_link_queue(&Queue);

    printf("\n");
    return 0;
}