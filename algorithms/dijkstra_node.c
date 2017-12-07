/**
 * 迪杰斯特拉算法（狄斯奎诺算法）解决的是从源点到其它所有顶点的最短路径问题
 */

#include <stdio.h>
#include <malloc.h>

#define MAX 20
#define MAX_FLOAT_NUM 1000 /*最大浮点数（假设最大浮点数是1000）*/

typedef int infoType; /*定义边表结点权值的数据的数据类型*/
typedef int vertexType; /*定义顶点结点上存储的数据的数据类型*/

//定义边表结点结构体
typedef struct edgenode {
    int adjvertex; //边表结点域
    infoType info; //边表结点权值，这里存放的是其父结点到该结点的距离
    struct edgenode *next; //指向下一个邻接点的指针域
} EdgeNode;

//定义顶点结点结构体
typedef struct vertexnode {
    vertexType boolval; /* 顶点结点域，这里存放的是该结点是否找到其距源顶点最短路径的标记，
						若找到最短路径，则该值为1，否则该值为0 */
    EdgeNode *firstedge; //边表头指针
} VertexNode;

typedef struct {
    VertexNode adjlist[MAX]; /*邻接表*/
    int vertexNum; /*顶点数*/
    int edgeNum; /*边数*/
} ALGraph; //adjacency list graph:邻接表

/**************************************************************
函数名称：CreateGraph
函数功能：创建邻接表
输入：顶点数vertexNum，边数edgeNum
输出：指向已创建好的邻接表的指针
**************************************************************/
ALGraph *CreateGraph(int vertexNum, int edgeNum) {
    int k;
    EdgeNode *p;

    //声明图的邻接表
    ALGraph *G;
    G = (ALGraph *) malloc(sizeof(ALGraph));

    if (!G) {
        G = NULL;
    } else {
        G->vertexNum = vertexNum;
        G->edgeNum = edgeNum;

        //建立顶点表
        for (k = 0; k < G->vertexNum; k++) {
            G->adjlist[k].boolval = 0; /*boolval值判断该结点到源结点的距离是否是最短距							离，是1表示已达最短距离，是0表示还没有达最短距离*/
            G->adjlist[k].firstedge = NULL;
        }

        //建立边表
        printf("请输入顶点、其邻接顶点和权值信息：\n");
        for (k = 0; k < G->edgeNum; k++) {
            int i, j;
            infoType info;

            //<i,j>表现的是边的关系，有多少对<i,j>就有多少边，所以for循环次数为G->edgeNum
            scanf("%d,%d,%d", &i, &j, &info);
            if (i != j) {
                p = (EdgeNode *) malloc(sizeof(EdgeNode));
                p->next = G->adjlist[i].firstedge;
                G->adjlist[i].firstedge = p;
                p->adjvertex = j;
                p->info = info;
            }
        }
    }

    return G;
}

/**************************************************************
函数名称：dijkstra（迪杰斯特拉/迪斯奎诺）
函数功能：实现迪杰斯特拉算法，找出每个顶点到源定点u的最短距离
输入：邻接表指针G，源顶点u，记录每个顶点到源顶点的最短距离的数组d[]，到源顶点的最短路径上的前方顶点编号p[]
输出：记录每个顶点到源顶点的最短距离的数组d[]，到源顶点的最短路径上的前方顶点编号p[]
**************************************************************/
void dijkstra(ALGraph *G, int u, int d[], int p[]) {
    int i, j, t;
    EdgeNode *pnode;

    //初始化参数
    for (i = 0; i < G->vertexNum; i++) {
        //G->adjlist[i].boolval = 0;
        d[i] = MAX_FLOAT_NUM;
        p[i] = -1;
    }

    //更新源顶点直接子结点到源结点的最短距离
    if (!(pnode = G->adjlist[u].firstedge)) {
        return;
    }

    while (pnode) {
        d[pnode->adjvertex] = pnode->info;
        p[pnode->adjvertex] = u;
        pnode = pnode->next;
    }

    G->adjlist[u].boolval = 1;
    d[u] = 0;

    //更新所有除源结点外的结点到源结点的最短距离
    for (i = 1; i < G->vertexNum; i++) {
        int min = MAX_FLOAT_NUM;
        t = u;

        //在所有结点中找出一个距离源结点距离最小的一个结点
        for (j = 0; j < G->vertexNum; j++) {
            if (G->adjlist[j].boolval != 1 && min > d[j]) {
                t = j;
                min = d[j];
            }
        }

        if (t == u) { //顶点到达不了源顶点（距离为MAX_FLOAT_NUM）或者顶点已经找到了到源顶点的最短路径（boolval值为1）
            break;
        }

        G->adjlist[t].boolval = 1;

        /*
            找到一个距离源结点距离最小的结点时，将该结点看成是一个源结点，更新
            它的所有直接子结点到源结点u的最短距离d[i]，然后再去找一个距离源结点
            距离最小的结点，如此反复的更新所有结点到源结点的最短距离。
        */
        pnode = G->adjlist[t].firstedge;

        while (pnode) {
            if ((G->adjlist[pnode->adjvertex].boolval != 1) && (d[pnode->adjvertex] > (d[t] + pnode->info))) {
                d[pnode->adjvertex] = d[t] + pnode->info;
                p[pnode->adjvertex] = t;
            }
            pnode = pnode->next;
        }
    }
}

/**
 *
示例：

请输入顶点个数和边个数：
8,15

请输入顶点、其邻接顶点和权值信息：
0,1,1
0,2,4
0,3,4
1,2,2
1,4,9
2,4,6
2,5,3
2,6,4
2,3,3
3,6,7
4,7,1
5,4,2
5,7,5
6,5,1
6,7,3
请输入源结点：
0

各点到源顶点0的距离：
顶点0距离源顶点0的距离: 0
所走最短路径为：	0

顶点1距离源顶点0的距离: 1
所走最短路径为：	0	1

顶点2距离源顶点0的距离: 3
所走最短路径为：	0	1	2

顶点3距离源顶点0的距离: 4
所走最短路径为：	0	3

顶点4距离源顶点0的距离: 8
所走最短路径为：	0	1	2	5	4

顶点5距离源顶点0的距离: 6
所走最短路径为：	0	1	2	5

顶点6距离源顶点0的距离: 7
所走最短路径为：	0	1	2	6

顶点7距离源顶点0的距离: 9
所走最短路径为：	0	1	2	5	4	7

 *
 */
int print_dijkstra_node() {
    ALGraph *G;
    int vertexNum, edgeNum; //图的邻接表的顶点数和边数
    int u; //源顶点编号
    int *d = NULL; //动态数组，各顶点到源顶点的最短路径
    int *p = NULL; //动态数组，存放到源顶点的最短路径上的前方顶点编号
    int i, j, k, t;
    int *tmp;

    printf("请输入顶点个数和边个数：\n");
    scanf("%d,%d", &vertexNum, &edgeNum);
    printf("\n");

    G = CreateGraph(vertexNum, edgeNum);
    if (!G) {
        printf("G为空！\n");
        return 0;
    }

    d = (int *) malloc(sizeof(int) * vertexNum);
    p = (int *) malloc(sizeof(int) * vertexNum);

    printf("请输入源结点：\n");
    scanf("%d", &u);
    printf("\n");

    //调用迪杰斯特拉算法函数
    dijkstra(G, u, d, p);

    tmp = (int *) malloc(sizeof(int) * (vertexNum + 1));

    printf("各点到源顶点%d的距离：\n", u);
    for (i = 0; i < vertexNum; i++) {
        printf("顶点%d距离源顶点%d的距离: %d\t", i, u, d[i]);
        printf("\n");

        printf("所走最短路径为：\t");
        j = 0;
        tmp[j++] = i;
        t = p[i];
        while (t != -1) {
            tmp[j++] = t;
            t = p[t];
        }

        for (k = --j; k >= 0; k--) {
            printf("%d\t", tmp[k]);
        }

        printf("\n\n");
    }

    printf("\n");
    free(G);
    return 0;
}