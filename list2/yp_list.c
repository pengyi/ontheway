#include "yp_list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

yp_list* list_create(void* p, int len) {
    yp_list_node* node = NULL;
    yp_list* list = NULL;
    list = (yp_list*)malloc(sizeof(yp_list));
    if (!list) {
        return NULL;
    }
    list->head = list->tail = NULL;
    list->len  = 0;
    if (p == NULL || len == 0) {
        return list;
    }
    for (int i = 0; i < len; ++i) {
        node = (yp_list_node*)malloc(sizeof(yp_list_node));
        if (!node) {
            return NULL;
        }
        node->value = p + i;
        node->next  = NULL;
        if (i == 0) {
            list->head = list->tail = node;
        } else {
            list->tail->next = node;
            list->tail = node;
        }
        list->len++;
    }
    return list;
}

void list_traverse(yp_list* list, void(*visit)(yp_list_node* node)) {
    yp_list_node* node = NULL;
    int count = 0;
    if (list == NULL) {
        return;
    }
    node  = list->head;
    count = 0;
    while (node && count < list->len) {
        if (visit) {
            visit(node);
        }
    }

}