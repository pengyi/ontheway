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
    printf("pre order:\n");
    bi_tree_pre_order_r(tree);printf("\n");
    bi_tree_pre_order(tree);printf("\n");
    bi_tree_pre_order2(tree);printf("\n");
    printf("in order:\n");
    bi_tree_in_order_r(tree);printf("\n");
    bi_tree_in_order(tree);printf("\n");
    bi_tree_in_order2(tree);printf("\n");
    printf("post order:\n");
    bi_tree_post_order_r(tree);printf("\n");
    bi_tree_post_order(tree);printf("\n");
    bi_tree_post_order2(tree);printf("\n");
    printf("level order:\n");
    bi_tree_level_visit(tree);
    printf("\n");
    return 0;
}
