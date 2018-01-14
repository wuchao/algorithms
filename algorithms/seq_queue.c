/**
 * 循环队列：
 * 为了方便起见，约定：初始化建空队时，令
 *     front=rear=0,
 * 当队空时：front == rear
 * 当队满时：front == rear 亦成立
 * 因此只凭等式front=rear无法判断队空还是队满。  有两种方法处理上述问题：
 *   （1）另设一个标志位以区别队列是空还是满。
 *   （2）少用一个元素空间，约定以“队列头指针front在队尾指针rear的下一个位置上”作为队列“满”状态的标志。即：
 * 队空时： front == rear
 * 队满时： (rear+1) % maxsize == front
 */
#include <stdio.h>

#define MAX 100

typedef int dataType;

// 定义循环队列结构体
typedef struct {
    dataType data[MAX];
    int front, rear;
} SeqQueue, *PSeqQueue;

// 初始化队列
PSeqQueue init_seq_queue() {
    PSeqQueue PQ;
    PQ = (PSeqQueue) malloc(sizeof(SeqQueue));

    if (PQ) {
        PQ->front = PQ->rear = 0;
    }

    return PQ;
}

// 判断循环队列队空：front == rear
int is_empty_seq_queue(PSeqQueue PQ) {
    if (PQ->rear == PQ->front) {
        return 1;
    } else {
        return 0;
    }
}

// 判断循环队列队满：(rear+1) % maxsize == front
int is_full_seq_queue(PSeqQueue PQ) {
    if (((PQ->rear + 1) % MAX) == PQ->front) {
        return 1;
    } else {
        return 0;
    }
}

// 入队
void push_seq_queue(PSeqQueue PQ, dataType e) {
    if (is_full_seq_queue(PQ) == 1) {
        printf("队已满！\n");
        return;
    } else {
        PQ->rear = (PQ->rear + 1) % MAX;
        PQ->data[PQ->rear] = e;
        return;
    }
}

// 出队
void pop_seq_queue(PSeqQueue PQ, dataType *e) {
    if (is_empty_seq_queue(PQ) == 1) {
        printf("队列为空！\n");
        return;
    } else {
        *e = PQ->data[PQ->front];
        PQ->front = (PQ->front + 1) % MAX;
    }
}