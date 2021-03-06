#include "yp_list.c"

void print_node_value(yp_list_node* node) {
    int* p = NULL;
    if (node == NULL) {
        return;
    }
    p = (int*)node->value;
    if (node->next == NULL) {
        printf("%d", *p);
    } else {
        printf("%d->", *p);
    }
}


void print_list(yp_list* list) {
    printf("======================list info===============================\n");
    printf("list len:%d\t", list->len);
    printf("list head:%p\t", list->head);
    printf("list tail:%p\t", list->tail);
    printf("\n");
    list->visit = print_node_pointer;
    list_traverse(list);
    printf("\n");
    list->visit = print_node_value;
    list_traverse(list);
    printf("\n=====================================================\n");
    
}

void print_value(int* p) {
    if (p == NULL) {
        printf("empty value");
    } else {
        printf("node value is:%d", *p);
    }
    printf("\n");
}

void print_node(yp_list_node* node) {
    int* p = NULL;
    if (node == NULL) {
        printf("empty node");
    } else {
        p = (int*)node->value;
        printf("node value is:%d", *p);
    }
    printf("\n");
}


int main() {
    int* pval = NULL;
    yp_list_node* node = NULL;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    yp_list* list = list_create();
    for (int i = 0; i < 7; ++i) {
        list_push(list, &values[i]);
    }
    print_list(list);
    pval = (int*)list_pop(list);
    print_value(pval);
    print_list(list);
    node = list_ith_node(list, list->len);
    print_node(node);
    list_unshift(list, &values[8]);
    print_list(list);
    pval = (int*)list_shift(list);
    print_value(pval);
    print_list(list);
    list_reverse_r(list);
    print_list(list);
    list_reverse(list);
    print_list(list);
    list_empty(list);
    list_destroy(list);
    printf("end\n");

    return 0;
}