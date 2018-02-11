#include <stdio.h>
#include <malloc.h>

#define SIZE 12

/*二叉排序树结点关键字结构体*/
typedef struct NodeData {
    int key;
} DataType;

/*定义二叉排序树结点结构体*/
typedef struct BinTreeNode {
    DataType elem;
    struct BinTreeNode *lchild;
    struct BinTreeNode *rchild;
} BinTree;

/**
 * 创建节点
 * @param elem
 * @return
 */
BinTree *create_bin_tree(DataType elem) {
    BinTree *T;
    T = (BinTree *) malloc(sizeof(BinTree));
    if (T) {
        T->elem = elem;
        T->lchild = NULL;
        T->rchild = NULL;
    }
    return T;
}

/**
 * 递归插入
 * @param T
 * @param elem
 * @return
 */
int insert_bin_tree(BinTree *T, DataType elem) {
    if (T == NULL) {
        T = create_bin_tree(elem);
    } else {
        if (T->elem.key == elem.key) {
            return 1;
        } else if (T->elem.key < elem.key) {
            insert_bin_tree(T->rchild, elem);
        } else {
            insert_bin_tree(T->lchild, elem);
        }
    }

    return 1;
}

/**
 * 非递归插入
 * @param T
 * @param key
 * @return
 */
int insert_bin_tree2(BinTree *T, DataType elem) {
    /* 当二叉排序树T中不存在关键字等于key的数据元素时 */
    /* 插入key并返回TRUE，否则返回FALSE */
    /* 调用查找函数SearchBST，非递归 */
    BinTree *p, *s;

    if (!search_bin_tree3(T, elem, NULL, p)) {
        s = create_bin_tree(elem);

        if (!p)
            T = s;             /* 插入s为根节点，此前树为空树 */
        else if (elem.key > p->elem.key)
            p->rchild = s;       /* 插入s为右孩子 */
        else
            p->lchild = s;       /* 插入s为左孩子 */
        return TRUE;
    }
    return FALSE;
}


int init_bin_tree(BinTree *T, DataType elems[], int size) {
    for (int v = 0; v < size; v++) {
        insert_bin_tree(T, elems[v]);
    }
    return 1;
}

/**
 * 按先序序列初始化二叉树
 * @param T
 * @param elems
 * @param size
 * @return
 */
BinTree *preorder_init_bin_tree() {
    DataType elem;
    BinTree *T = NULL;

    elem.key = getchar();

//    if (c != '#') {
//        T = create_bin_tree(elem);
//        if (T) {
//            T->lchild = preorder_bin_tree();
//            T->rchild = preorder_bin_tree();
//        }
//    }

    return T;
}

/**
 * 递归查找
 * @param T
 * @param elem
 * @return
 */
BinTree *search_bin_tree(BinTree *T, DataType elem) {
    if (!T) {
        return NULL;
    }

    if (elem.key == T->elem.key) {
        return T;
    } else {
        if (elem.key > T->elem.key) {
            return search_bin_tree(T->rchild, elem);
        } else {
            return search_bin_tree(T->lchild, elem);
        }
    }
}

/**
 * 访问节点元素
 * @param T
 * @param elem
 */
void visit(BinTree *T) {
    if (T) {
        printf("%c\t", T->elem.key);
    }
}

/**
 * 先序遍历二叉树
 * @param T
 * @return
 */
int preorder_travel_bin_tree(BinTree *T) {
    if (T != NULL) {
        visit(T);
        preorder_travel_bin_tree(T->lchild);
        preorder_travel_bin_tree(T->rchild);
    }
    return 1;
}

/**
 * 中序遍历二叉树
 * @param T
 * @return
 */
int inorder_travel_bin_tree(BinTree *T) {
    if (T != NULL) {
        inorder_travel_bin_tree(T->lchild);
        visit(T);
        inorder_travel_bin_tree(T->rchild);
    }
    return 1;
}

/**
 * 后序遍历二叉树
 * @param T
 * @return
 */
int postorder_travel_bin_tree(BinTree *T) {
    if (T != NULL) {
        postorder_travel_bin_tree(T->lchild);
        postorder_travel_bin_tree(T->rchild);
        visit(T);
    }
    return 1;
}

/**
 * 参考： http://blog.csdn.net/wangyunyun00/article/details/23708055
 * 递归查找
 * @param T
 * @param elem
 * @param f
 * @param p
 * @return
 */
int search_bin_tree2(BinTree *T, DataType elem, BinTree *f, BinTree *p) {
    /* 递归查找二叉排序树T中是否存在key */
    /* 指针f指向T的双亲，其初始调用值为NULL */
    /* 若查找成功，则指针p指向该数据元素节点，并返回TRUE */
    /* 否则指针p指向查找路径上访问的最后一个节点并返回FALSE */
    if (!T) {
        p = f;     //这是f唯一被用到的位置。
        return FALSE;
    } else {
        if (elem.key == T->elem.key) {
            p = T;
            return TRUE;
        } else if (elem.key > T->elem.key)
            return search_bin_tree2(T->rchild, elem, T, p);        /* 在右子树继续查找 */
        else
            return search_bin_tree2(T->lchild, elem, T, p);        /* 在左子树继续查找 */
    }
}

/**
 * 非递归查找
 * @param T
 * @param elem
 * @param f
 * @param p
 * @return
 */
int search_bin_tree3(BinTree *T, DataType elem, BinTree *f, BinTree *p) {
    /*非递归*/
    BinTree *s;
    if (!T) {
        p = f;
        return FALSE;
    } else {
        while (T) {
            if (elem.key == T->elem.key) {
                s = T;
                return TRUE;
            }
            if (elem.key > T->elem.key) {
                s = T;
                T = T->rchild;
            } else {
                s = T;
                T = T->lchild;
            }
        }
        p = s;
        return FALSE;
    }
}


BinTree *find_min_bin_tree(BinTree *T) {
    if (T != NULL) {
        while (T->lchild != NULL) {
            T = T->lchild;
        }
    }
    return T;
}


BinTree *find_max_bin_tree(BinTree *T) {
    if (T != NULL) {
        while (T->rchild != NULL) {
            T = T->rchild;
        }
    }
    return T;
}

/**
 * 删除节点（《linux c 编程一站式学习》中案例）
 * 参考： http://blog.csdn.net/jnu_simba/article/details/8888014
 *
 * @param T
 * @param key
 * @return
 */
BinTree *delete_bin_tree(BinTree **T, DataType elem) {
    BinTree *p, *t = *T;
    if (!t) {
        return NULL;
    }
    if (t->elem.key > elem.key) { /* delete from left subtree */
        t->lchild = delete_bin_tree(t->lchild, elem);
    } else if (t->elem.key < elem.key) { /* delete from right subtree */
        t->rchild = delete_bin_tree(t->rchild, elem);
    } else {   /* if (t->elem.key == elem.key) */
        if (t->lchild == NULL && t->rchild == NULL) {
            /* if t is a leaf node */
            free(t);
            *T = NULL;
        } else if (t->lchild) {  /* if t has left subtree */
            /* replace t with the rightmost node in left subtree */
            p = find_max_bin_tree(t->lchild);
            /* 将左子树下最靠右的节点（直接前驱）值赋予想要删除的节点 */
            t->elem = p->elem;
            t->lchild = delete_bin_tree(t->lchild, t->elem); /*删除原直接前驱（叶子）节点*/
        } else { /* if t has right subtree */
            /* replace t with the leftmost node in right subtree */
            p = find_min_bin_tree(t->rchild);
            /* 将右子树下最靠左的节点（直接后继）值赋予想要删除的节点 */
            t->elem = p->elem;
            t->rchild = delete_bin_tree(t->rchild, t->elem); /*删除原直接后继（叶子）节点*/
        }
    }
    return t;
}

/**
 * 删除节点（data structure and algorithm analysis in c》中案例）
 * @param X
 * @param T
 * @return
 */
BinTree *delete_bin_seq_tree2(BinTree *T, DataType elem) {
    BinTree *tmp;
    if (T == NULL) {
        printf("Tree is empty!\n");
        return NULL;
    }

    if (elem.key < T->elem.key) { //go left
        T->lchild = delete_bin_seq_tree2(T->lchild, elem);
    } else if (elem.key > T->elem.key) {// go right
        T->rchild = delete_bin_seq_tree2(T->rchild, elem);
    }
        /* found elem to be deleted*/
    else if (T->lchild && T->rchild) { //have two children
        // replace with smallest in right subtree
        tmp = find_min_bin_tree(T->rchild);
        T->elem.key = tmp->elem.key;
        T->rchild = delete_bin_seq_tree2(T->rchild, T->elem);
    } else { //one or zero children
        tmp = T;
        if (T->lchild == NULL)
            T = T->rchild;
        else if (T->rchild == NULL)
            T = T->lchild;
        free(tmp);
    }

    return T;
}

void print_bin_tree_shape(BinTree *T, int n) {
    if (!T)return;
    print(T->rchild, n + 2);
    for (int i = 0; i < n; ++i) {
        printf(" ");
    }
    printf(T->elem.key);
    print(T->lchild, n + 2);
}

int print_bin_tree(void) {
    DataType elem;
    BinTree *T = NULL;
    DataType elems[SIZE] = {34, 18, 76, 52, 13, 67, 82, 25, 58, 91, 73, 20};

    init_bin_tree(T, elems, SIZE);

    print_bin_tree_shape(T, SIZE);

    return 1;
}