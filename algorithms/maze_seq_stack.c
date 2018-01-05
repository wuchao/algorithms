#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define STACK_INIT_SIZE 200
#define STACK_INCREMENT 10

#define MAZE_WIDTH 20
#define MAZE_HIGH 20

#define ERROR 0
#define TRUE 1
#define FALSE 0

#define OVERFLOW 0
#define OK 1

typedef int Status;

typedef struct {
    int x;
    int y;
} PosType;

typedef struct {
    int ord;        //通道块在路径上的“序号”
    PosType seat;    //通道块在迷宫中的“坐标位置”
    int di;           //从此通道块走向下一通道块的“方向”
} SElemType;

typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
} SeqStack;

int mg[MAZE_WIDTH][MAZE_HIGH];

//随机生成迷宫的函数
//为了能够让尽量能通过，将能通过的块和不能通过的块数量比大致为2:1 (0表示可以通过, 1表示不可以通过)
void random_init_maze() {
    int i, j, k;
    srand(time(NULL));
    mg[1][0] = mg[1][1] = mg[MAZE_HIGH - 2][MAZE_WIDTH - 1] = 0;    //将入口、出口设置为“0”即可通过

    for (j = 0; j < MAZE_WIDTH; j++) {
        mg[0][j] = mg[MAZE_HIGH - 1][j] = 1;        /*设置迷宫外围“不可走”（第一行和最后一行无处口），保证只有一个出口和入口*/
    }

    for (i = 2; i < MAZE_HIGH - 2; i++) {
        mg[i][0] = mg[i - 1][MAZE_HIGH - 1] = 1;        /*设置迷宫外围“不可走”（第一列第二行有出口，最后一列倒数第二行有出口），保证只有一个出口和入口*/
    }

    for (i = 1; i < MAZE_HIGH - 1; i++) {
        for (j = 1; j < MAZE_WIDTH - 1; j++) {
            k = rand() % 3;            //随机生成0、1、2三个数，使通过的块和不能通过的块比大致为2:1
            if (k) {
                mg[i][j] = 0;    //k不等于0，不能被整除，设该处能通过
            } else {
                if ((i == 1 && j == 1) ||
                    (i == MAZE_HIGH - 2 && j == MAZE_WIDTH - 2))    /*因为距入口或出口一步的路是必经之路，故设该通道块为“0”加大迷宫能通行的概率*/
                    mg[i][j] = 0;
                else
                    mg[i][j] = 1;
            }
        }
    }
}

//当前块可否通过
Status pass(PosType e) {
    if (mg[e.x][e.y] == 0) { // 0时可以通过
        return OK;           // 如果当前位置是可以通过，返回1
    }
    return OVERFLOW;         // 其它情况返回0
}

//留下通过的足迹
Status foot_print(PosType e) {
    mg[e.x][e.y] = 7;
    return OK;
}

//构造一个空栈
Status init_seq_stack(SeqStack *s) {
    s->base = (SElemType *) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s->base) {
        return OVERFLOW;
    }
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
    return OK;
}

//出栈
Status pop(SeqStack *s, SElemType *e) {
    if (s->top == s->base) {
        return ERROR;
    }
    *e = *(--s->top);
    return OK;
}

//入栈
Status push(SeqStack *s, SElemType e) {
    if (s->top - s->base >= s->stacksize) {
        s->base = (SElemType *) realloc(s->base, (s->stacksize + STACK_INCREMENT) * sizeof(SElemType));
        if (!s->base) {
            exit(OVERFLOW);
        }
        s->top = s->base + s->stacksize;
        s->stacksize += STACK_INCREMENT;
    }
    *(s->top++) = e;
    return OK;
}

//是否空栈
Status is_empty_seq_stack(SeqStack *s) {
    if (s->top == s->base) {
        return OK;
    }
    return OVERFLOW;
}

//留下不能通过的足迹
Status mark_print(PosType e) {
    mg[e.x][e.y] = 3;
    return OK;
}

//下一步
PosType next_pos(PosType *e, int dir) {
    PosType E;
    switch (dir) {
        case 1:                 //向右
            E.x = e->x;
            E.y = e->y + 1;
            break;
        case 2:                 //向下
            E.x = e->x + 1;
            E.y = e->y;
            break;
        case 3:                 //向左
            E.x = e->x;
            E.y = e->y - 1;
            break;
        case 4:                 //向上
            E.x = e->x - 1;
            E.y = e->y;
            break;
    }
    return E;
}


// 若迷宫maze中从入口 start到出口 end的通道，则求得一条存放在栈中
// （从栈底到栈顶），并返回TRUE；否则返回FALSE
// 迷宫函数
Status maze_path(int mg, PosType start, PosType end, SeqStack *s) {
    PosType curpos;     // 当前位置
    SElemType e;
    int curstep;        // 所走步数

    init_seq_stack(s);
    curpos = start;    // 设定"当前位置"为"入口位置"
    curstep = 1;        // 探索第一步

    do {
        if (pass(curpos)) {    // 当前位置可通过，即是未曾走到过的通道块
            foot_print(curpos);    // 留下足迹
            e.di = 1;
            e.ord = curstep;
            e.seat = curpos;
            push(s, e);    // 加入路径
            if ((curpos.x == end.x) && (curpos.y == end.y)) {
                printf("\n\n0∩_∩0 能到达终点!\n路径如下：\n");
                return TRUE;
            }
            curpos = next_pos(&curpos, 1);    // 下一位置是当前位置的下方位置
            curstep++;     // 探索下一步
        } else {    // 当前位置不能通过
            if (!is_empty_seq_stack(s)) {
                pop(s, &e);
                while ((e.di == 4) && (!is_empty_seq_stack(s))) {
                    mark_print(e.seat);
                    pop(s, &e);
                }
                if (e.di < 4) {
                    e.di++;
                    push(s, e);    // 留下不能通过的标记，并退回一步
                    curpos = next_pos(&(e.seat), e.di);    /* 当前位置设为新方向的相邻块*/
                }//if
            }//if
        }//else
    } while (!is_empty_seq_stack(s));

    printf("\n\n此迷宫不能走通！\n");
    return FALSE;
}

//打印迷宫
void print_maze() {
    int i, j;
    printf("运行路径:\n\n");
    for (i = 0; i < MAZE_HIGH; i++) {
        for (j = 0; j < MAZE_WIDTH; j++) {
            if (mg[i][j] == 0) {
                printf(" ");               //可以走的路径
            } else if (mg[i][j] == 1) {
                printf("■");                //迷宫的“墙”
            } else if (mg[i][j] == 3) {
                printf("#");                //不通的路
            } else if (mg[i][j] == 7) {
                printf("○");                //已通过的路径
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_maze_path_stack(SeqStack *s) {
    while (s->top != s->base) {
        PosType pos = (*(s->base++)).seat;
        printf("(%d, %d) ", pos.x, pos.y);
    }
    printf("\n\n");
}

void print_maze_seq_stack() {
    SeqStack S;
    PosType start, end;
    start.x = 1;
    start.y = 0;                   //起点坐标
    end.x = MAZE_HIGH - 2;
    end.y = MAZE_WIDTH - 1;        //终点坐标

    random_init_maze();
    maze_path(mg[20][20], start, end, &S);
    print_maze();
    print_maze_path_stack(&S);
}