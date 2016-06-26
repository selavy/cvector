#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cvector_int.h"
#include "cvector_char.h"
#include "cvector_long.h"

struct data_t {
    int a;
    int b;
    int c;
    int d;
};
void print_data(struct data_t *d) {
    printf("(%d %d %d %d)", d->a, d->b, d->c, d->d);
}

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

void print_char_vector(struct cvector_char_t *vec) {
    assert(vec);
    const size_t size = cvector_char_size(vec);
    if (size) {
        const char *itr = cvector_char_front(vec);
        for (size_t i = 0; i < size; ++i, ++itr) {
            printf("%c ", *itr);
        }
    }
    printf("\n");
}

void print_long_vector(struct cvector_long_t *vec) {
    assert(vec);
    const size_t size = cvector_long_size(vec);
    if (size) {
        const long *itr = cvector_long_front(vec);
        for (size_t i = 0; i < size; ++i, ++itr) {
            printf("%ld ", *itr);
        }
    }
    printf("\n");
}

void print_data_vector(struct cvector_data_t *vec) {
    assert(vec);
    const size_t size = cvector_long_size(vec);
    if (size) {
        const struct data_t *itr = cvector_long_front(vec);
        for (size_t i = 0; i < size; ++i, ++itr) {
            printf("%ld ", *itr);
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

    // CHAR VECTOR
    {
        struct cvector_char_t cvec;
        if (cvector_char_init(&cvec) != 0) {
            perror("cvector_char_init");
            exit(1);
        }
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (cvector_char_push(&cvec, c) != 0) {
                perror("cvector_char_push");
                break;
            }
        }
        printf("Printing char vector...");
        print_char_vector(&cvec);
        if (cvector_char_destroy(&cvec) != 0) {
            perror("cvector_char_destroy");
        }
    }

    // LONG VECTOR
    {
        struct cvector_long_t cvec;
        if (cvector_long_init(&cvec) != 0) {
            perror("cvector_long_init");
            exit(1);
        }
        for (long c = 0; c <= 25; ++c) {
            if (cvector_long_push(&cvec, c) != 0) {
                perror("cvector_long_push");
                break;
            }
        }
        printf("Printing long vector...");
        print_long_vector(&cvec);
        if (cvector_long_destroy(&cvec) != 0) {
            perror("cvector_long_destroy");
        }
    }
    
    return 0;
}
