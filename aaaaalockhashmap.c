#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hashmap.h"
#include "spinlock.h"

typedef struct Node_HM_t
{
    long m_val; //value of the node
    char padding[PAD];
    struct Node_HM_t* m_next; //pointer to next node in the bucket
} Node_HM;

typedef struct List_t
{
    cspinlock_t* lock;
    Node_HM* sentinel; //list of nodes in a bucket
} List;

typedef struct hm_t
{
  	int n_buckets;
    List** buckets; //list of buckets in the hashmap
} HM;

int insert_item(HM* hm, long val)
{
  // traverse the list to find the insertion point
  List* set = hm->buckets[val % hm->n_buckets];
  cspin_lock(set->lock);
  //  while(!__sync_bool_compare_and_swap(&set->lock,0,1));
  Node_HM* prev = set->sentinel;
  Node_HM* curr = prev->m_next;

  while (curr != NULL) {
    if (curr->m_val >= val)
    break;
    prev = curr;
    curr = prev->m_next;
  }

  if (!curr || (curr->m_val >= val)) {
    Node_HM* insert_point = (Node_HM*)(prev);

    // create the new node
    Node_HM* i = (Node_HM*)malloc(sizeof(Node_HM));
    i->m_val = val;
    i->m_next = (Node_HM*)(curr);
    insert_point->m_next = i;
    cspin_unlock(set->lock);
    //set->lock = 0;
    return 0;
  }
  cspin_unlock(set->lock);
  //set->lock = 0;
  return 1;
}

int remove_item(HM* hm, long val)
{
  List* set = hm->buckets[val % hm->n_buckets];
  //cspin_lock(set->lock);
  while(!__sync_bool_compare_and_swap(&set->lock,0,1));
  Node_HM* prev = set->sentinel;
  Node_HM* curr = prev->m_next;
  while (curr != NULL) {

    if (curr->m_val == val) {
      Node_HM* mod_point = (Node_HM*)(prev);
      mod_point->m_next = curr->m_next;
      cspin_unlock(set->lock);
      //set->lock = 0;
      free(curr);

      return 0;
    }
    else if (curr->m_val > val) {
      cspin_unlock(set->lock);
//      set->lock = 0;
      return 1;
    }
    prev = curr;
    curr = prev->m_next;
  }
  cspin_unlock(set->lock);
//  set->lock = 0;
  return 1;
}

int lookup_item(HM* hm, long val)
{
  List* set = hm->buckets[val % hm->n_buckets];
  cspin_lock(set->lock);
 // while(!__sync_bool_compare_and_swap(&set->lock,0,1));
  int found = 1;

  const Node_HM* curr = set->sentinel;
  curr = curr->m_next;

  while (curr != NULL) {
    if (curr->m_val >= val)
    break;
    curr = curr->m_next;
  }

  found = ((curr != NULL) && (curr->m_val == val));
  cspin_unlock(set->lock);
//  set->lock = 0;
  return !found;
}

HM* alloc_hashmap(size_t n_buckets){
  HM* hm = (HM*) malloc(n_buckets*sizeof(HM));
  hm->buckets = (List**) malloc(n_buckets*sizeof(List*));
  hm->n_buckets = n_buckets;
  for (int i = 0; i < n_buckets; i++) {
    hm->buckets[i] = (List*) malloc (sizeof(List));
    hm->buckets[i]->lock = cspin_alloc();
    hm->buckets[i]->sentinel = (Node_HM*) malloc(sizeof(Node_HM));
    hm->buckets[i]->sentinel->m_val = LONG_MIN;
    hm->buckets[i]->sentinel->m_next = NULL;
  }
  return hm;
}

void free_hashmap(HM* hm){
  for (size_t i = 0; i < hm->n_buckets; i++) {
    free(hm->buckets[i]->sentinel);
    free(hm->buckets[i]);
    free(hm->buckets[i]->lock);
  }
  free(hm->buckets);
  free(hm);
}


void print_hashmap(HM* hm){
  for (int i = 0; i < hm->n_buckets; i++) {
    printf("Bucket %d ", i);
    Node_HM* iter = hm->buckets[i]->sentinel->m_next;
    while(1){
      if (iter == NULL)
        break;
      printf(" - %ld ", iter->m_val);
      iter = iter->m_next;
    }
    printf("\n");
  }
}