#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "linkedlist.h"

/*
typedef struct Node_t
{
    long val; //value of the node
    //char padding[PAD];
    struct Node_t* next; //pointer to next node in the bucket
} Node;

typedef struct List_t
{
    Node *sentinel; // list of nodes in a bucket
} List;
*/

#define mark(A) ((unsigned long)(A) + 1)
#define marked(A) ({ ((unsigned long)(A)) % 2 != 0; })
#define unmark(A) ((unsigned long)(A)-1)

int insert_val(List *list, long val)
{
    // create the new node
    Node *i = (Node *)malloc(sizeof(Node));
    i->val = val;

    while (1)
    {
        Node **prev = &list->sentinel;
        Node *curr = *prev;

        while (1)
        {
            if (marked(curr))
            {
                break;
            }
            else if (curr != NULL && marked(curr->next))
            {
                Node *next = (Node *)unmark(curr->next);
                __sync_bool_compare_and_swap(prev, curr, next);
                curr = next;
            }
            else
            {
                if (curr == NULL || curr->val >= val)
                {
                    i->next = curr;
                    if (__sync_bool_compare_and_swap(prev, curr, i))
                    {
                        return 0;
                    }
                    curr = (*prev);
                }
                else
                {
                    prev = &curr->next;
                    curr = *prev;
                }
            }
        }
    }
    return 1;
}

int remove_val(List *list, long val)
{
    while (1)
    {
        Node **prev = &list->sentinel;
        Node *curr = *prev;

        while (1)
        {
            if (marked(curr))
            {
                break;
            }
            else if (curr != NULL && marked(curr->next))
            {
                Node *next = (Node *)unmark(curr->next);
                __sync_bool_compare_and_swap(prev, curr, next);
                curr = next;
            }
            else
            {
                if (curr == NULL || curr->val > val)
                {
                    return 1;
                }
                else if (curr->val == val)
                {
                    if (__sync_bool_compare_and_swap(&curr->next, curr->next, (Node *)mark(curr->next)))
                    {
                        return 0;
                    }
                }
                else
                {
                    prev = &curr->next;
                    curr = *prev;
                }
            }
        }
    }
    return 1;
}

int lookup_val(List *list, long val)
{
    while (1)
    {
        Node **prev = &list->sentinel;
        Node *curr = *prev;

        while (1)
        {
            if (marked(curr))
                break;
            else if (curr != NULL && marked(curr->next))
            {
                Node *next = (Node *)unmark(curr->next);
                __sync_bool_compare_and_swap(prev, curr, next);
                curr = next;
            }
            else
            {
                if (curr == NULL || curr->val > val)
                {
                    return 1;
                }
                else if (curr->val == val)
                {
                    return 0;
                }
                else
                {
                    prev = &curr->next;
                    curr = *prev;
                }
            }
        }
    }
}

List *alloc_list()
{
    List *list = (List *)malloc(sizeof(List));
    list->sentinel = (Node *)malloc(sizeof(Node));
    list->sentinel->val = LONG_MIN;
    list->sentinel->next = NULL;
    return list;
}

void free_list(List *list)
{
    Node *iter = list->sentinel->next;
    Node *tmp;

    while (1)
    {
        tmp = iter;

        if (iter == NULL)
            break;
        else if (marked(iter->next))
            iter = (Node *)unmark(iter->next);
        else
            iter = iter->next;

        free(tmp);
    }

    free(list->sentinel);
    free(list);
}

void print_list(List *list)
{
    Node *iter = list->sentinel->next;
    while (1)
    {
        if (iter == NULL)
            break;
        else if (marked(iter->next))
        {
            Node *next = (Node *)unmark(iter->next);
            iter = next;
        }
        else
        {
            printf(" - %ld ", iter->val);
            iter = iter->next;
        }
    }
    printf("\n");
}