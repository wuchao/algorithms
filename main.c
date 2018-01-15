#include <stdio.h>
#include "syntax/syntax.c"
#include "algorithms/bubble_sort .c"
#include "algorithms/straight_insert_sort_seq_list.c"
#include "algorithms/straight_insert_sort_link_list_header.c"
#include "algorithms/shell_sort.c"
#include "algorithms/dijkstra_node.c"
#include "algorithms/seq_list.c"
#include "algorithms/maze_seq_stack.c"
#include "algorithms/bin_seq_tree.c"

int main() {
    printf("Hello, World!\n\n");

//    syntax();

    // 冒泡排序
//    print_bubble_sort();

    // 直插排序
//    print_straight_insert_sort_seq_list();

    // 带头结点链式存储的直插排序
//    print_straight_insert_sort_link_list_header();

    // 希尔排序
//    print_shell_sort();

    // dijkstra 算法
//    print_dijkstra_node();

    // 顺序表
//    print_seq_list();

    // 顺序表栈实现的迷宫
//    print_maze_seq_stack();

    // 二叉排序树
    print_bin_tree();

    return 0;
}