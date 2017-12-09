#include <stdio.h>
#include <malloc.h>

typedef char dataType;

/*定义二叉树结点结构体*/
typedef struct node{
    dataType data;
    struct node *lchild;
    struct node *rchild;
} BinTree;

/*创建二叉树结点*/
BinTree* bintree_create() {
    BinTree *T;

    T = (BinTree *)malloc(sizeof(BinTree));

    if (T != NULL) {
        T->lchild = NULL;
        T->rchild = NULL;
    }

    return T;
}

/*按先序序列初始化二叉树*/
BinTree* bintree_init() {
    dataType c;
    BinTree *T = NULL;

    c = getchar();

    if(c != '#') {
        T = bintree_create();
        if (T != NULL) {
            T->data = c;
            T->lchild = bintree_init();
            T->rchild = bintree_init();
        }
    }

    return T;
}

int bintree_insert1(BinTree *p, int lr, dataType e) {
    BinTree *t = NULL;

    if (p != NULL) {
        t = bintree_create();

        if (t != NULL) {
            t->data = e;

            if (lr == 0) {
                t->lchild = p->lchild;
                p->lchild = t;
            }
            else {
                t->lchild = p->rchild;
                p->rchild = t;
            }
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

/*
函数名：bintree_insert
函数功能：二叉树的插入
参数：data为插入位置父节点的data属性的值，lr为插入到结点的左边还是右边，
	  0表示左边，1表示右边，e为要插入结点的data属性的值
*/
int bintree_insert2(BinTree *T, dataType data, int lr, dataType e) {
    LinkQueue *Q = NULL;
    BinTree *p = NULL;
    BinTree *pl = NULL;
    BinTree *pr = NULL;
    BinTree *t = NULL;

    if (T != NULL) {
        if (T->data == data) {
            t = bintree_create();
            bintree_insert1(T, lr, e);
            return 1;
        }

        Q = linkqueue_create();
        linkqueue_in(Q, T);

        while(!linkqueue_isempty(Q)) {
            linkqueue_out(Q, p);
            pl = p->lchild;
            pr = p->rchild;

            if (pl != NULL && pl->data == data) {
                t = bintree_create();
                bintree_insert1(pl, lr, e);
                return 1;
            }
            else if (pr != NULL && pr->data == data) {
                t = bintree_create();
                bintree_insert1(pr, lr, e);
                return 1;
            }

            linkqueue_in(Q, pl);
            linkqueue_in(Q, pr);

        }

        p = bintree_create();
        if (p != NULL) {
            p->data = data;
        }
    }

    return 0;
}

/*访问结点元素*/
void visit(BinTree *T) {
    printf("%c\t", T->data);
}

/*先序遍历*/
int bintree_preorder(BinTree *T) {
    if (T != NULL) {
        visit(T);
        bintree_preorder(T->lchild);
        bintree_preorder(T->rchild);
    }

    return 1;
}

/*中序遍历*/
int bintree_inorder(BinTree *T) {
    if (T != NULL) {
        bintree_inorder(T->lchild);
        visit(T);
        bintree_inorder(T->rchild);
    }

    return 1;
}

/*后序遍历*/
int bintree_postorder(BinTree *T) {
    if (T != NULL) {
        bintree_postorder(T->lchild);
        bintree_postorder(T->rchild);
        visit(T);
    }

    return 1;
}

/*销毁二叉树*/
void bintree_destroey(BinTree **T) {
    BinTree *p = *T;
    if (p) {
        bintree_destroey(&(p->lchild));
        bintree_destroey(&(p->rchild));
        free(p);
        T = NULL;
    }
    return;
}

/*主函数*/
int print_binary_tree(void) {
    BinTree *T = NULL;

    printf("请输入结点元素，以‘#’结束：\n");
    T = bintree_init();
    printf("\n");

    printf("先序遍历的结果为：\n");
    bintree_preorder(T);
    printf("\n");

    printf("中序遍历的结果为：\n");
    bintree_inorder(T);
    printf("\n");

    printf("后序遍历的结果为：\n");
    bintree_postorder(T);
    printf("\n");

    bintree_destroey(&T);

    return 1;
}