#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hashmap.h"
#include "spinlock.h"

/*
typedef struct Node_t
{
    long val; //value of the node
    char padding[PAD];
    struct Node_t* next; //pointer to next node in the bucket
} Node;

typedef struct List_t
{
    cspinlock_t* lock;
    Node* sentinel; //list of nodes in a bucket
} List;*/

int insert_val(List* list, long val)
{
    cspin_lock(list->lock);
    //  while(!__sync_bool_compare_and_swap(&set->lock,0,1));
    Node* prev = list->sentinel;
    Node* curr = prev->next;

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = (Node*)(curr);
    prev->next = new_node;
    cspin_unlock(list->lock);
    return 0;
}

int remove_val(List* list, long val)
{
    cspin_lock(list->lock);
    //while(!__sync_bool_compare_and_swap(&set->lock,0,1));
    Node* prev = list->sentinel;
    Node* curr = prev->next;

    while (curr != NULL)
    { 
        if (curr->val == val)
        {
            Node* mod_node = (Node*)(prev);
            mod_node->next = curr->next;
            cspin_unlock(list->lock);
            //set->lock = 0;
            free(curr);
            return 0;
        }
        prev = curr;
        curr = prev->next;
    }
    cspin_unlock(list->lock);
    //set->lock = 0;
    //Value not found
    return 1;
}

int lookup_val(List* list, long val)
{
    cspin_lock(list->lock);
    //while(!__sync_bool_compare_and_swap(&set->lock,0,1));
    int found = 1;

    Node* curr = list->sentinel->next;

    while (curr != NULL)
    {
        if (curr->val == val)
            break;
        curr = curr->next;
    }

    found = ((curr != NULL) && (curr->val == val));
    cspin_unlock(list->lock);
    //set->lock = 0;
    return !found;
}

List* alloc_list()
{
    List* new_list = (List*)malloc(sizeof(List));
    new_list->lock = (cspinlock_t*)cspin_alloc();
    new_list->sentinel = (Node*)malloc(sizeof(Node));
    new_list->sentinel->next = NULL;
    return new_list;
}

void free_list(List* list)
{
    cspin_lock(list->lock);
    Node* prev = list->sentinel;
    Node* curr = prev->next;

    while (curr->next != NULL)
    {
        free(prev);
        prev = curr;
        curr = prev->next;
    }

    free(prev);
    free(curr);

    //We dont need to free the just free it. Unless another thread is waitting for the lock, probably wont happen.
    free(list->lock);
    free(list);
}

void print_list(List* list)
{
    Node* iter = list->sentinel->next;
    while(1)
    {
        if(iter == NULL)
            break;
        printf(" - %ld ", iter->val);
        iter = iter->next;
    }
    printf("\n");
}