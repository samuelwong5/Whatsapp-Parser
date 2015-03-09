#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Simple double-linked list implementation. */
struct list
{
    struct list_elem *head;   /* Head of the list. */
    int max_len_name;         /* For list_print formatting. */
};

struct list_elem
{
    struct list_elem *next;   /* Next list_elem. */
    struct list_elem *prev;   /* Prev list_elem. */
    char *id;                 /* Name of the message sender. */
    int count;                /* Current count of messages from sender. */
};

struct list * list_init(void);
void list_add(struct list *, char *);
void list_free(struct list *);
void list_print(struct list *);
struct list_elem * list_elem_init(char *);
void list_sort(struct list *l);
#endif