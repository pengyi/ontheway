#include "yp_list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


static void print_node_pointer(yp_list_node* node) {
    if (node == NULL) {
        return;
    }
    if (node->next == NULL) {
        printf("%p", node);
    } else {
        printf("%p->", node);
    }
}

yp_list* list_create() {
    yp_list_node* node = NULL;
    yp_list* list = (yp_list*)malloc(sizeof(yp_list));
    if (!list) {
        return NULL;
    }
    list->head = list->tail = NULL;
    list->len  = 0;
    list->copy_value    = NULL;
    list->free_value    = NULL;
    list->compare_value = NULL;
    list->visit         = print_node_pointer;
    return list;
}

yp_list* list_push(yp_list* list, void* p) {
    yp_list_node* node = NULL;
    if (list == NULL || p == NULL) {
        return list;
    }
    node = (yp_list_node*)malloc(sizeof(yp_list_node));
    if (!node) {
        return NULL;
    }
    node->value = p;
    node->next  = NULL;
    if (list->head == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->len++;
    return list;
}




void list_traverse(yp_list* list) {
    yp_list_node* node = NULL;
    int count = 0;
    if (list == NULL) {
        return;
    }
    node  = list->head;
    //使用count使得可以遍历存在环的情况
    while (node && count++ <= list->len) {
        if (list->visit) {
            list->visit(node);
        }
        node = node->next;
    }
}