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
 * 递归插入
 * @param T
 * @param elem
 * @return
 */
int insert_bin_tree(BinTree *T, DataType elem) {
    if (T == NULL) {
        T = (BinTree *) malloc(sizeof(BinTree));
        if (T) {
            T->elem.key = elem.key;
            T->lchild = NULL;
            T->rchild = NULL;
        }
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
int insert_bin_tree2(BiTree *T, int key) {
    /* 当二叉排序树T中不存在关键字等于key的数据元素时 */
    /* 插入key并返回TRUE，否则返回FALSE */
    /* 调用查找函数SearchBST，非递归 */
    BinTree *p, s;

    if (!search_bin_tree3(*T, key, NULL, &p)) {
        s = (BinTree *) malloc(sizeof(BinTree));
        s.elem.key = key;
        s->lchild = s->rchild = NULL;

        if (!p)
            T = s;             /* 插入s为根节点，此前树为空树 */
        else if (key > p->elem.key)
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
 * 参考： http://blog.csdn.net/wangyunyun00/article/details/23708055
 * 递归查找
 * @param T
 * @param key
 * @param f
 * @param p
 * @return
 */
int search_bin_tree2(BinTree *T, int key, BinTree *f, BinTree *p) {
    /* 递归查找二叉排序树T中是否存在key */
    /* 指针f指向T的双亲，其初始调用值为NULL */
    /* 若查找成功，则指针p指向该数据元素节点，并返回TRUE */
    /* 否则指针p指向查找路径上访问的最后一个节点并返回FALSE */
    if (!T) {
        p = f;     //这是f唯一被用到的位置。
        return FALSE;
    } else {
        if (key == T->elem.key) {
            p = T;
            return TRUE;
        } else if (key > T->elem.key)
            return search_bin_tree2(T->rchild, key, T, p);        /* 在右子树继续查找 */
        else
            return search_bin_tree2(T->lchild, key, T, p);        /* 在左子树继续查找 */
    }
}

/**
 * 非递归查找
 * @param T
 * @param key
 * @param f
 * @param p
 * @return
 */
int search_bin_tree3(BinTree *T, int key, BinTree *f, BinTree *p) {
    /*非递归*/
    BinTree *s;
    if (!T) {
        p = f;
        return FALSE;
    } else {
        while (T) {
            if (key == T->elem.key) {
                s = T;
                return TRUE;
            }
            if (key > T->elem.key) {
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

/*T是被删结点的左孩子*/
BinTree *get_max_left_node(BinTree *T) {
    if (T->rchild) {
        return get_max_left_node(T->rchild);
    } else {
        return T;
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
 * @param t
 * @param key
 * @return
 */
BinTree *delete_bin_tree(BinTree *t, DataType key) {
    BinTree *p;
    if (!t) {
        return NULL;
    }
    if (t->item > key) { /* delete from left subtree */
        t->left = delete_bin_tree(t->left, key);
    } else if (t->item < key) { /* delete from right subtree */
        t->right = delete_bin_tree(t->right, key);
    } else {   /* if (t->item == key) */
        if (t->left == NULL && t->right == NULL) {
            /* if t is a leaf node */
            free(t);
            t = NULL;
        } else if (t->left) {  /* if t has left subtree */
            /* replace t with the rightmost node in left subtree */
            p = find_max_bin_tree(t->left);
            /* 将左子树下最靠右的节点（直接前驱）值赋予想要删除的节点 */
            t->item = p->item;
            t->left = delete_bin_tree(t->left, t->item); /*删除原直接前驱（叶子）节点*/
        } else { /* if t has right subtree */
            /* replace t with the leftmost node in right subtree */
            p = find_min_bin_tree(t->right);
            /* 将右子树下最靠左的节点（直接后继）值赋予想要删除的节点 */
            t->item = p->item;
            t->right = delete_bin_tree(t->right, t->item); /*删除原直接后继（叶子）节点*/
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
BinTree *delete_bin_seq_tree2(DataType X, BinTree *T) {
    BinTree *tmp;
    if (T == NULL) {
        printf("Tree is empty!\n");
        return NULL;
    }

    if (X < T->elem.key) { //go left
        T->left = delete(X, T->left);
    } else if (X > T->key) {// go right
        T->right = delete(X, T->right);
    }
        /* found elem to be deleted*/
    else if (T->left && T->right) { //have two children
        // replace with smallest in right subtree
        tmp = find_min_bin_tree(T->right);
        T->key = tmp->key;
        T->right = delete(T->key, T->right);
    } else { //one or zero children
        tmp = T;
        if (T->left == NULL)
            T = T->right;
        else if (T->right == NULL)
            T = T->left;
        free(tmp);
    }

    return T;
}

BinTree *search_bin_tree(BinTree *T, DataType elem) {
    if (!T) {
        printf("\n查找失败！！！\n");
        return NULL;
    }
    if (elem.key == T->elem.key) {
        printf("\n查找成功！！！\n");
        return T;
    } else if (elem.key > T->elem.key) {
        return search_bin_tree(T->rchild, elem);
    } else {
        return search_bin_tree(T->lchild, elem);
    }
}

int print_bin_tree(void) {
    DataType elem;
    BinTree *T = NULL;
    DataType elems[SIZE] = {34, 18, 76, 52, 13, 67, 82, 25, 58, 91, 73, 20};
    int delstatus = 0;

    printf("请输入欲查找的关键字：\n");
    scanf("%d", &(elem.key));
    init_bin_tree(&T, elems, SIZE);

    search_bin_tree(T, elem);
    printf("\n删除关键字为：%d的结点\n", elem.key);
    delstatus = delete_bin_tree(&T, elem);
    if (delstatus == 1) {
        printf("删除成功！！！\n");
    } else {
        printf("删除失败！！！\n");
    }
    search_bin_tree(T, elem);

    return 1;
}