#include "list.h"

struct list *
list_init(void)
{
    struct list *l = (struct list *) malloc(sizeof(struct list));
    l->head = NULL;
    l->max_len_name = 0;
    return l;
}

void
list_add(struct list *l, char *name)
{
    int slen;
    struct list_elem *curr;
    if (l->head == NULL) {
        curr = list_elem_init(name);
        l->head = curr;
        l->max_len_name = strlen(name);        
    } else {
        slen = strlen(name);
        curr = l->head;
        while (curr != NULL) {
            if (strncmp(curr->id, name, slen) != 0) {
                if (curr->next == NULL) {
                    struct list_elem *new_elem = list_elem_init(name);
                    curr->next = new_elem;
                    new_elem->prev = curr;
                    if (slen > l->max_len_name)
                        l->max_len_name = slen;
                    break;
                } else {
                    curr = curr->next;
                }
            } else {
                curr->count++;
                free(name);
                break;
            } 
        }
    }
}

void
list_free(struct list *l)
{
    struct list_elem *curr = l->head;
    struct list_elem *next;
    while (curr != NULL && curr->prev != NULL) { curr = curr->prev; }
    while (curr != NULL) {
        next = curr->next;
        free(curr->id);
        free(curr);
        curr = next;
    }
    free(l);
}

void
list_print(struct list *l)
{
    int maxlen = l->max_len_name;
    struct list_elem *curr = l->head;
    if (l->head == NULL) { printf("No messages found.\n"); } 
    while (curr->prev != NULL) { curr = curr->prev; }
    while (curr != NULL) {
        printf("%-*s : %d\n", maxlen, curr->id, curr->count);
        curr = curr->next;
    }
}

/* Insertion sort implementation for list. */
void
list_sort(struct list *l)
{  
    if (l->head == NULL) { return; }
    if (l->head->next == NULL) { return; }
    struct list_elem *curr = l->head;
    struct list_elem *next;
    struct list_elem *ptr;
    while (curr != NULL) {
        next = curr->next;
        ptr = curr->prev;
        while (ptr != NULL) {
            if (curr->count < ptr->count) {
                /* [a] - [ptr] - ... - [c] - [curr] - [next] */
                if (curr->prev != NULL)
                    curr->prev->next = next;
                /* [c] -> [next] */
                if (next != NULL)
                    next->prev = curr->prev;
                /* [c] <- [next] */ 
                curr->prev = ptr->prev;
                /* [a] <- [curr] */
                curr->next = ptr;
                /* [curr] -> ptr */
                if (ptr->prev != NULL)
                    ptr->prev->next = curr;
                /* [a] -> [curr] */
                ptr->prev = curr;
                /* [curr] <- [ptr] */
                break;
            } else {
                ptr = ptr->prev;
            }
        }
        curr = next;        
    }
}

struct list_elem *
list_elem_init(char *name)
{
    struct list_elem *new_elem = (struct list_elem *) malloc(sizeof(struct list_elem));
    new_elem->id = name;
    new_elem->count = 1;
    new_elem->next = NULL;
    new_elem->prev = NULL;
    return new_elem;
}