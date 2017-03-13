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


int main() {
    int* pval = NULL;
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    yp_list* list = list_create();
    for (int i = 0; i < 7; ++i) {
        list_push(list, &values[i]);
    }
    print_list(list);
    pval = (int*)list_pop(list);
    print_value(pval);
    print_list(list);
    return 0;
}