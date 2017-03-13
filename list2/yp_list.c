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

void* list_pop(yp_list* list) {
    void* p = NULL;
    yp_list_node* node = NULL, *q = NULL;
    if (list == NULL || list->tail == NULL) {
        return NULL;
    }
    q = list->tail;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        node = list->head;
        while (node->next != list->tail) {
            node = node->next;
        }
        list->tail = node;
        node->next = NULL;
    }
    list->len--;
    p = q->value;
    free(q);
    q = NULL;
    return p;
}

void* list_shift(yp_list* list) {
    yp_list_node* p = NULL;
    void* value = NULL;
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    p = list->head;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->head = list->head->next;
    }
    value = p->value;
    list->len--;
    free(p);
    p = NULL;
    return value;
}

yp_list* list_unshift(yp_list* list, void* p) {
    yp_list_node* node = NULL;
    if (list == NULL || p == NULL) {
        return NULL;
    }
    node = (yp_list_node*)malloc(sizeof(yp_list_node));
    if (!node) {
        return NULL;
    }
    node->value = p;
    node->next = NULL;
    if (list->head == NULL) {
        list->head = list->tail = node;
    } else {
        node->next = list->head;
        list->head = node;
    }
    list->len++;
    return list;
}

yp_list_node* list_ith_node(yp_list* list, int i) {
    yp_list_node* p = NULL;
    int count = 1;
    if (list == NULL || i < 1 || i > list->len) {
        return NULL;
    }
    p = list->head;
    while (p && count < i) {
        p = p->next;
        count++;
    }
    return p;
}

static yp_list_node* _list_reverse_r(yp_list_node* head) {
    yp_list_node* p = NULL, *q = NULL;
    if (head == NULL || head->next == NULL) {
        return head;
    }
    p = head->next;
    q = _list_reverse_r(p);
    p->next = head;
    head->next = NULL;
    return q;
}

yp_list* list_reverse_r(yp_list* list) {
    yp_list_node* p = NULL;
    if (list == NULL) {
        return NULL;
    }
    p = _list_reverse_r(list->head);
    list->tail = list->head;
    list->head = p;
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