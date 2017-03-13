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

void print_node_pointer(yp_list_node* node) {
    if (node == NULL) {
        return;
    }
    if (node->next == NULL) {
        printf("%p", node);
    } else {
        printf("%p->", node);
    }
}

void print_list(yp_list* list) {
    list->visit = print_node_value;
    list_traverse(list);
    printf("\n");
    list->visit = print_node_pointer;
    list_traverse(list);
    printf("\n");
}


int main() {
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    yp_list* list = list_create();
    for (int i = 0; i < 7; ++i) {
        list_push(list, &values[i]);
    }
    print_list(list);
    return 0;
}