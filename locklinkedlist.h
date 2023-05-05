#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "spinlock.h"

typedef struct Node_t
{
    long val; //value of the node
    //char padding[PAD];
    struct Node_t* next; //pointer to next node in the bucket
} Node;

typedef struct List_t
{
    cspinlock_t* lock;
    Node* sentinel; //list of nodes in a bucket
} List;

int insert_val(List* list, long val);

int remove_val(List* list, long val);

int lookup_val(List* list, long val);

List* alloc_list();

void free_list(List* list);

void print_list(List* list);