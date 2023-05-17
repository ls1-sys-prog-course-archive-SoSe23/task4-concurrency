#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "spinlock.h"

#define PAD 64

#ifdef __cplusplus
extern "C"
{
#endif

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

// insert val into the list and return 0 if successful
// return 1 otherwise, e.g., could not allocate memory
int insert_val(List* list, long val);

// remove val from the list, if it exist and return 0 if successful
// return 1 if item is not found
int remove_val(List* list, long val);

// check if val exists in list, return 0 if found, return 1 otherwise
int lookup_val(List* list, long val);

// allocate a list
List* alloc_list();

// free the list
void free_list(List* list);

// print all elements in the hashmap as follows:
// - val1 - val2 - val3 ...
void print_list(List* list);

#ifdef __cplusplus
}
#endif