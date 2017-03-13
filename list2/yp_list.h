#ifndef YP_LIST_H
#define YP_LIST_H

typedef struct _yp_list_node {
    void* value;
    struct _yp_list_node* next;
} yp_list_node;

typedef struct _yp_list {
    yp_list_node* head;
    yp_list_node* tail;
    int len;
    void (*free_value)(void* p);
    void* (*copy_value)(void* p);
    int (*compare_value)(void* p1, void* p2);
    void(*visit)(yp_list_node* node);
} yp_list;

yp_list* list_create();
yp_list* list_push(yp_list* list, void* p);
yp_list* list_unshift(yp_list* list, void* p);
void* list_pop(yp_list* list);
void* list_shift(yp_list* list);
yp_list_node* list_ith_node(yp_list* list, int i);
void list_traverse(yp_list* list);

#endif