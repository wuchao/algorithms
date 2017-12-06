#include <stdio.h>
#include "syntax.c"
#include "algorithms/bubble_sort .c"
#include "utils/GetWeek.c"
#include "algorithms/straight_insert_sort.c"
#include "algorithms/straight_sort_insert_header_node.c"

int main() {
    printf("Hello, World!\n\n");

    systnx();

    //bubble sort
    print_bubble_sort();

    print_straight_insert_sort();

    print_straight_insert_sort_header_node();

    return 0;
}