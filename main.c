#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cvector.h"

struct node {
    struct node *next;
    int data;
};
struct llist {
    struct node *head;
};

int llist_init(struct llist *list) {
    assert(list);
    list->head = 0;
    return 0;
}
int llist_destroy(struct llist *list) {
    assert(list);
    struct node *curr = list->head;
    struct node *prev;
    while (curr) {
        prev = curr;
        curr = curr->next;        
        free(prev);
    }
    return 0;
}
int llist_push_front(struct llist *list, int data) {
    struct node *n = malloc(sizeof(*n));
    n->next = list->head;
    n->data = data;
    list->head = n;

    return 0;
}
int llist_push_back(struct llist *list, int data) {
    if (!list->head) {
        list->head = malloc(sizeof(*list->head));
        list->head->next = 0;
        list->head->data = data;
    } else {
        struct node *n = list->head;
        while (n->next) {
            n = n->next;
        }
        n->next = malloc(sizeof(*n->next));
        n = n->next;
        n->next = 0;
        n->data = data;
    }
    return 0;
}
void print_llist(struct llist *list) {
    assert(list);
    puts("Printing list...");
    struct node *n = list->head;
    while (n) {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n");
}

void print_cvector(struct cvector_int_t *vec) {
    assert(vec);
    puts("Printing vector...");
    const size_t size = cvector_int_size(vec);
    if (size) {
        const int *itr = cvector_int_front(vec);
        for (size_t i = 0; i < size; ++i, ++itr) {
            printf("%d ", *itr);
        }
    }
    printf("\n");
}

int main(int argc, char **argv) {
    struct cvector_int_t vec;
    struct llist list;
    if (cvector_int_init(&vec) != 0) {
        perror("cvector_int_init");
        exit(1);
    }
    if (llist_init(&list) != 0) {
        perror("llist_init");
        exit(1);
    }

    puts("Before inserts...");
    print_cvector(&vec);
    print_llist(&list);

    for (int i = 0; i < 20; ++i) {
        if (cvector_int_push(&vec, i) != 0) {
            perror("cvector_int_push");
            break;
        }
        if (llist_push_front(&list, i) != 0) {
            perror("llist_push_front");
            break;
        }
    }
    puts("After inserts...");
    print_cvector(&vec);
    print_llist(&list);
    
    for (int i = 0; i < 10; ++i) {
        cvector_int_pop_back(&vec);
    }
    puts("After popping 10 elements...");
    print_cvector(&vec);
    print_llist(&list);

    if (cvector_int_destroy(&vec) != 0) {
        perror("cvector_int_destroy");
        exit(1);
    }
    if (llist_destroy(&list) != 0) {
        perror("llist_destroy");
        exit(1);
    }
    return 0;
}
