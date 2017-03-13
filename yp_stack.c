#include "yp_stack.h"
#include<stdlib.h>

yp_stack* stack_create() {
    yp_list* list = NULL;
    yp_stack* stack = malloc(sizeof(yp_stack));
    if (!stack) {
        return NULL;
    }
    list = list_create();
    if (list == NULL) {
        free(stack);
        return NULL;
    }
    stack->list = list;
    return stack;
}

yp_stack* stack_push(yp_stack* stack, void* p) {
    if (stack == NULL || stack->list == NULL) {
        return NULL;
    }
    list_push(stack->list, p);
    return stack;
}

void* stack_pop(yp_stack* stack) {
    if (stack == NULL || stack->list == NULL) {
        return NULL;
    }
    return list_pop(stack->list);
}

int stack_is_empty(yp_stack* stack) {
    if (stack == NULL || stack->list == NULL) {
        return 1;
    }
    if (stack->list->len == 0) {
        return 1;
    } else {
        return 0;
    }
}

void stack_destroy(yp_stack* stack) {
    if (stack == NULL) {
        return;
    }
    list_destroy(stack->list);
}