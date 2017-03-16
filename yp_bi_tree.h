#ifndef YP_BI_TREE_H
#define YP_BI_TREE_H

typedef struct _yp_bi_tree_node {
    void* value;
    struct _yp_bi_tree_node* lchild;
    struct _yp_bi_tree_node* rchild;
} yp_bi_tree_node;

typedef struct _yp_bi_tree {
    yp_bi_tree_node* root;
    void(*free_value)(void* p);
    void(*visit)(yp_bi_tree_node* node);
} yp_bi_tree;

yp_bi_tree* bi_tree_create(void** p, int len);
void bi_tree_pre_order_r(yp_bi_tree* tree);
void bi_tree_in_order_r(yp_bi_tree* tree);
void bi_tree_post_order_r(yp_bi_tree* tree);
void bi_tree_level_visit(yp_bi_tree* tree);
void bi_tree_in_order(yp_bi_tree* tree);
void bi_tree_in_order2(yp_bi_tree* tree);

#endif