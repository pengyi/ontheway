#ifndef YP_STACK_H
#define YP_STACK_H

#include "yp_list.h"

typedef struct _yp_stack {
    yp_list* list;
} yp_stack;

yp_stack* stack_create();
yp_stack* stack_push(yp_stack* stack, void* p);
void* stack_pop(yp_stack* stack);
int stack_is_empty(yp_stack* stack);
void stack_destroy(yp_stack* stack);
void* stack_top(yp_stack* stack);


#endif