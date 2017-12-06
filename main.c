#include <stdio.h>
#include "syntax/syntax.c"
#include "algorithms/bubble_sort .c"
#include "algorithms/straight_insert_sort.c"
#include "algorithms/straight_sort_insert_header_node.c"

int main() {
    printf("Hello, World!\n\n");

    systnx();

    // 冒泡排序
    print_bubble_sort();

    // 直插排序
    print_straight_insert_sort();

    // 带头结点链式存储的直插排序
    print_straight_insert_sort_header_node();

    return 0;
}