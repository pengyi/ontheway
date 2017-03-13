#ifndef YP_LIST_H
#define YP_LIST_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _yp_list_node {
    void* value;
    struct _yp_list_node* next;
} yp_list_node;

typedef struct _yp_list {
    yp_list_node* head;
    yp_list_node* tail;
    int len;
    int elemSize;
    void (*free_value)(void* value);
    void* (*copy_value)(void* value);
} yp_list;


yp_list* create(void* data, int elemSize, int num);
void list_empty(yp_list* list);
void list_destroy(yp_list* list);
yp_list_node* list_ith_node(yp_list* list, int i);
void* list_ith_value(yp_list* list, int i);
void* list_shift(yp_list* list);
int list_unshift(yp_list* list, void* val);
int list_push(yp_list* list, void* val);
void* list_pop(yp_list* list);
yp_list* reverseListRecursive(yp_list* list);
yp_list* reverseList(yp_list* list);


#endif
