#include "yp_bi_tree.h"
#include <stdio.h>

void print_bi_tree_node(yp_bi_tree_node* node) {
    char* p = (char*)node->value;
    printf("%c->", *p);
}


int main() {

    char a[] = {'a', 'b', 'c', 'd', 'e'};
    char* p[] = {a, a + 1, a + 2, NULL, a + 3, a + 4};
    yp_bi_tree* tree = bi_tree_create((void**)p, 6);
    tree->visit = print_bi_tree_node;
    bi_tree_pre_order_r(tree);
    printf("\n");
    bi_tree_in_order_r(tree);
    return 0;
}
