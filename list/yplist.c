#include "yplist.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

yp_list* create(void* data, int elemSize, int num) {
    int i = 0;
    void* p = NULL;
    yp_list_node* node = NULL;
    yp_list* list = (yp_list*)malloc(sizeof(yp_list));
    if (!list) {
        return NULL;
    }
    list->head = list->tail = NULL;
    list->len = 0;
    list->elemSize = elemSize;
    if (data == NULL || num < 1) {
        return list;
    }
    for(;i < num; i++) {
        node = (yp_list_node*)malloc(sizeof(yp_list_node));
        if (!node) {
            return NULL;
        }
        p = malloc(elemSize);
        if (!p) {
            return NULL;
        }
        memcpy(p, data + i * elemSize, elemSize);
        node->value = p;
        node->next = NULL;
        if (i == 0) {
            list->head = list->tail = node;
        } else {
            list->tail->next = node;
            list->tail = node;
        }
    }
    list->len  = num;
    return list;
    }


void list_empty(yp_list* list) {
    yp_list_node* node = NULL, *p = NULL;
    if (list == NULL) {
        return;
    }
    p = list->head;
    while(p) {
        node = p;
        p = p->next;
        free(node->value);
        node->value = NULL;
        free(node);
        node = NULL;
    }
    list->head = list->tail = NULL;
    list->len = 0;
    return;
}




void list_destroy(yp_list* list) {
    if (list == NULL) {
        return;
    }
    list_empty(list);
    free(list);
    list = NULL;
    return;
}


yp_list_node* list_ith_node(yp_list* list, int i) {
    yp_list_node* p = NULL;
    int j = 1;
    if (list == NULL || i < 1 || i > list->len) {
        return NULL;
    }
    p = list->head;
    while (j < i) {
        p = p->next;
        j++;
    }
    return p;
}

yp_list* list_make_cycle(yp_list* list, int i) {
    yp_list_node* p = NULL;
    p = list_ith_node(list, i);
    if (p == NULL) {
        return list;
    }
    list->tail->next = p;
    return list;
}

void* list_ith_value(yp_list* list, int i) {
    yp_list_node* p = NULL;
    p = list_ith_node(list, i);
    if (p == NULL) {
        return NULL;
    }
    return p->value;
}

void* list_shift(yp_list* list) {
    yp_list_node* p = NULL;
    void* value = NULL;
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    p = list->head;
    if (list->len == 1) {
        list->head = list->tail = NULL;
    } else {
        list->head = p->next;
    }
    list->len--;
    value = p->value;
    free(p);
    return value;
}

int list_unshift(yp_list* list, void* val) {
    void* p = NULL;
    yp_list_node* node = NULL;
    if (list == NULL) {
        return -1;
    }
    p = malloc(list->elemSize);
    if (!p) {
        return -1;
    }
    memcpy(p, val, list->elemSize);
    node = (yp_list_node*)malloc(sizeof(yp_list_node));
    node->value = p;
    node->next  = NULL;
    if (list->len == 0) {
        list->head = list->tail = node;
    } else {
        node->next = list->head;
        list->head = node;
    }
    list->len++;
    return 0;
}

int list_push(yp_list* list, void* val) {
    void* p = NULL;
    yp_list_node* node = NULL;
    if (list == NULL) {
        return -1;
    }
    p = malloc(list->elemSize);
    if (!p) {
        return -1;
    }
    memcpy(p, val, list->elemSize);
    node = (yp_list_node*)malloc(sizeof(yp_list_node));
    if (!node) {
        free(p);
        return -1;
    }
    node->value = p;
    node->next = NULL;
    if (list->tail == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    list->len++;
    return 0;
}

void* list_pop(yp_list* list) {
    yp_list_node *p = NULL, *node = NULL;
    void* value = NULL;
    if (list == NULL || list->tail == NULL) {
        return NULL;
    }
    if (list->head == list->tail) {
        node = list->head;
        list->head = list->tail = NULL;
    } else {
        p = list->head;
        while (p->next != list->tail) {
            p = p->next;
        }
        node = list->tail;
        list->tail = p;
        list->tail->next = NULL;
    }
    list->len--;
    value = node->value;
    free(node);
    return value;
}

static yp_list_node* _reverseList(yp_list_node* head) {
    yp_list_node* p = NULL, *t = NULL;
    if (head == NULL || head->next == NULL) {
        return head;
    }
    t = head->next;
    p = _reverseList(t);
    t->next = head;
    head->next = NULL;
    return p;
}

yp_list* reverseListRecursive(yp_list* list) {
    yp_list_node* head = NULL, *tail= NULL;
    if (list == NULL) {
        return NULL;
    }
    tail = list->head;
    head = _reverseList(list->head);
    list->head = head;
    list->tail = tail;
    return list;
}

yp_list* reverseList(yp_list* list) {
    yp_list_node* pre = NULL, *cur= NULL, *post = NULL;
    if (list == NULL) {
        return NULL;
    }
    cur = list->head;
    if (cur == NULL) {
        return list;
    }
    post = cur->next;
    while (post != NULL) {
        cur->next = pre;
        pre  = cur;
        cur  = post;
        post = post->next;
    }
    cur->next = pre;
    list->tail = list->head;
    list->head = cur;
    return list;
}

//使用不带头结点的单链表
yp_list_node* list_last_k(yp_list* list, int k) {
    yp_list_node* p = NULL, *q = NULL;
    if (list == NULL) {
        return NULL;
    }
    if (k <= 0) {
        return NULL;
    }
    if (list->head == NULL) {
        return NULL;
    }
    p = q = list->head;
    while(--k && q) {
        q = q->next;
    }
    if (k > 0 || q == NULL) {
        return NULL;
    }

    while(q->next) {
        p = p->next;
        q = q->next;
    }
    return p;
}


yp_list_node* list_has_cycle(yp_list* list) {
    int find = 0;
    int lena = 0, lenb=0, diff = 0;
    yp_list_node* slow = NULL, *fast = NULL, *pa = NULL, *pb = NULL;
    if (list == NULL) {
        return NULL;
    }
    if (list->head == NULL) {
        return NULL;
    }
    slow = fast = list->head;
    while(slow != NULL && fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            find = 1;
            break;
        }
    }
    if (find == 0) {
        return NULL;
    }
    //break the cycle
    pa = list->head;
    slow = pb = fast->next;
    fast->next = NULL;

    while(pa) {
        lena++;
        pa = pa->next;
    }
    while(pb) {
        lenb++;
        pb = pb->next;
    }

    pa = list->head;
    pb = slow;
    diff =  lena > lenb ? lena - lenb : lenb - lena;

    if (lena > lenb) {
        while (diff--) {
            pa = pa->next;
        }
    } else {
        while (diff--) {
             pb = pb->next;
        }
     }

    while(pa != pb) {
        pa = pa->next;
        pb = pb->next;
    }
    return pa;
}


    
yp_list_node* list_has_cycle2(yp_list* list) {
    yp_list_node* slow = NULL, *fast = NULL;
    yp_list_node* pa = NULL, *pb = NULL;
    int find = 0;
    if (list == NULL) {
        return NULL;
    }
    slow = fast = list->head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            find = 1;
            break;
        }
    }
    if (find == 0) {
        return NULL;
    }
    pa = list->head;
    pb = fast->next;
    fast->next = NULL;
    slow = pa;
    fast = pb;
    while (pa != pb) {
        pa = pa == NULL ? fast : pa->next;
        pb = pb == NULL ? slow : pb->next;
    }
    return pa;
}



//=============test code===============
void printIntList(yp_list* list) {
    int count = 0;
    int* pval = NULL;
    yp_list_node* node = NULL;
    if (list == NULL) {
        return;
    }
    printf("list length is: %d \n", list->len);
    printf("list head is: %p \n", list->head);
    printf("list tail is: %p \n", list->tail);
    printf("list value is:");
    node = list->head;
    count = list->len + 1;
    while(node != NULL && count--) {
        pval = (int*)(node->value);
        if (node->next != NULL) {
            printf("%d->", *pval);
        } else {
            printf("%d",  *pval);
        }
        node = node->next;
    }
    printf("\n");
    printf("list node is:");
    node = list->head;
    count = list->len + 1;
    while(node != NULL && count--) {
        pval = (int*)(node->value);
        if (node->next != NULL) {
            printf("(%p)->", node);
        } else {
            printf("(%p)",  node);
        }
        node = node->next;
    }
    printf("\n");
    printf("\n");
}


int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ret = 0;
    int* value = NULL;
    yp_list_node* node = NULL;
    yp_list* list = create(a, sizeof(int), 7);
    printIntList(list);

    reverseListRecursive(list);
    printIntList(list);

    reverseList(list);
    printIntList(list);

    ret = list_push(list, &a[7]); 
    if (ret < 0) {
        printf("fail to push\n");
    }
    printIntList(list);

    value = (int*)list_pop(list);
    printf("pop value is: %d\n", *value);
    free(value);
    printIntList(list);

    list_unshift(list, &a[8]);
    printIntList(list);

    value = (int*)list_shift(list);
    free(value);
    printf("shift value is: %d\n", *value);
    printIntList(list);

    value = (int*)list_ith_value(list, 1);
    printf("1th value is: %d\n", *value);

    value = (int*)list_ith_value(list, list->len);
    printf("last value is: %d\n", *value);

    node = list_last_k(list, 6);
    if (node != NULL) {
        printf("last 6 value is: %d\n", (*(int*)node->value));
    } else {
        printf("invalid param\n");
    }
    node =  list_has_cycle(list);
    printf("list has cycle:%p\n", node);
    list_make_cycle(list, 3);
    printIntList(list);

    node =  list_has_cycle(list);
    printf("list has cycle:%p\n", node);

    node =  list_has_cycle2(list);
    printf("list has cycle:%p\n", node);


}
