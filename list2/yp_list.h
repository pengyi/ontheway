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
} yp_list;

yp_list* list_create(void* p, int len);
void list_traverse(yp_list* list, void(*visit)(yp_list_node* node));

#endif