#include "yp_bi_tree.h"
#include <stdlib.h>
#include "yp_list.h"

static yp_bi_tree_node* _create_node(void* p) {
    yp_bi_tree_node* node = malloc(sizeof(yp_bi_tree_node));
    if (!node) {
        return NULL;
    }
    node->value = p;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

yp_bi_tree* bi_tree_create(void** p, int len) {
    yp_bi_tree* tree = NULL;
    yp_list* list = NULL, *i_list = NULL;
    yp_bi_tree_node* node = NULL, *lnode = NULL, *rnode = NULL;
    int* index = NULL;
    int i = 0, l = 0, r = 0;
    tree = (yp_bi_tree*)malloc(sizeof(yp_bi_tree));
    if (!tree || p == NULL){
        return NULL;
    }
    index = (int*)malloc(sizeof(int) * len);
    for (i = 0; i < len; ++i) {
        *(index + i) = i;
    }
    tree->root = NULL;
    tree->free_value = NULL;
    list  = list_create();
    i_list = list_create();
    if (list == NULL || i_list == NULL) {
        return NULL;
    }
    if (*(p + 0) == NULL) {
        return NULL;
    }
    node = _create_node(*(p + 0));
    tree->root = node;
    list_push(list, (void*)node);
    list_push(i_list, (void*)(index + 0));
    while (list->len != 0) {
        node = (yp_bi_tree_node*)list_shift(list);
        i    = (*(int*)list_shift(i_list));
        l    = 2 * i + 1;
        r    = 2 * i + 2;
        if (l < len && *(p + l) != NULL) {
            lnode = _create_node(*(p + l));
            list_push(list, (void*)lnode);
            list_push(i_list,(int*)(index + l));
            node->lchild = lnode;
        }
        if (r < len && *(p + r) != NULL) {
            rnode = _create_node(*(p + r));
            list_push(list, (void*)rnode);
            list_push(i_list,(int*)(index + r));
            node->rchild = rnode;
        }
    }
    return tree;
}

static void _bi_tree_pre_order_r(yp_bi_tree* tree, yp_bi_tree_node* root) {
    if (root == NULL) {
        return;
    }
    if (tree->visit) {
        tree->visit(root);
    }
    _bi_tree_pre_order_r(tree, root->lchild);
    _bi_tree_pre_order_r(tree, root->rchild);
}

void bi_tree_pre_order_r(yp_bi_tree* tree) {
    if (tree == NULL) {
        return;
    }
    _bi_tree_pre_order_r(tree, tree->root);
}

static void _bi_tree_in_order_r(yp_bi_tree* tree, yp_bi_tree_node* root) {
    if (root == NULL) {
        return;
    }
    _bi_tree_in_order_r(tree, root->lchild);
    if (tree->visit) {
        tree->visit(root);
    }
    _bi_tree_in_order_r(tree, root->rchild);
}

void bi_tree_in_order_r(yp_bi_tree* tree) {
    if (tree == NULL) {
        return;
    }
    _bi_tree_in_order_r(tree, tree->root);
}