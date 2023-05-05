#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "locklinkedlist.h"

struct thread_args
{
    List* list;
    int thread_num;
};

/*
typedef struct Node_t;

typedef struct List_t;

int insert_val(List_t* list, long val);

int remove_val(List_t* list, long val);

int lookup_val(List_t* list, long val);

List_t* alloc_list();

void free_list(List_t* list);

void print_list(List_t* list);
*/

// The number of threads to use in the test
#define NUM_THREADS 10

// The number of nodes to add to the list
#define NUM_NODES 10000

// The function to be executed by each thread to insert their nodes into the list
void* thread_func_inserts(struct thread_args* args)
{
    List* list = args->list;
    int start_node = (args->thread_num)*NUM_NODES;
    int end_node = start_node+NUM_NODES;
    printf("start_node: %d\n; end_node: %d\n", start_node, end_node-1);
    
    for (int i = start_node; i < end_node; i++)
    {
        insert_val(list, i);
        //insert sleep here?
        sleep(0.01);
    }
    return NULL;
}

// The function to be executed by each thread to remove their nodes from the list
void* thread_func_removes(struct thread_args* args)
{
    List* list = args->list;
    int start_node = (args->thread_num)*NUM_NODES;
    int end_node = start_node+NUM_NODES;
    
    for (int i = start_node; i < end_node; i++)
    {
        remove_val(list, i);
    }

    return NULL;
}

int main()
{
    List* list = alloc_list();

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        struct thread_args* args = (struct thread_args*) malloc(sizeof(struct thread_args));
        args->list = list;
        args->thread_num = i;
        pthread_create(&threads[i], NULL, thread_func_inserts, (void*) args);
    }

    // Wait for the threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    print_list(list);

    //Check that all nodes were added to the list
    int all_nodes = NUM_NODES*NUM_THREADS;

    for (int i = 0; i < all_nodes; i++)
    {
        if(!lookup_val(list, i))
        {
            printf("Error: node %d was not added to the list\n", i);
            exit(1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        struct thread_args* args = (struct thread_args*) malloc(sizeof(struct thread_args));
        args->list = list;
        args->thread_num = i;
        pthread_create(&threads[i], NULL, thread_func_removes, (void*) args);
    }

    // Free the linked list
    free_list(list);

    printf("Test passed\n");
    return 0;
}