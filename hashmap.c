#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hashmap.h"
/*
typedef struct HM_T
{
    int n_buckets;
    List **buckets; // list of buckets in the hashmap
} HM;*/

int insert_item(HM *hm, long val)
{
    List *set = hm->buckets[val % hm->n_buckets];
    return insert_val(set, val);
}

int remove_item(HM *hm, long val)
{
    List *set = hm->buckets[val % hm->n_buckets];
    return remove_val(set, val);
}

int lookup_item(HM *hm, long val)
{
    List *set = hm->buckets[val % hm->n_buckets];
    return lookup_val(set, val);
}

HM* alloc_hashmap(size_t n_buckets)
{
    HM *hm = (HM *)malloc(n_buckets * sizeof(HM));
    hm->buckets = (List **)malloc(n_buckets * sizeof(List *));
    hm->n_buckets = n_buckets;
    for (size_t i = 0; i < n_buckets; i++)
    {
        hm->buckets[i] = alloc_list();
    }
    return hm;
}

void free_hashmap(HM *hm)
{
    for (size_t i = 0; i < hm->n_buckets; i++)
    {
        free_list(hm->buckets[i]);
    }
    free(hm->buckets);
    free(hm);
}

void print_hashmap(HM *hm)
{
    for (int i = 0; i < hm->n_buckets; i++)
    {
        printf("Bucket %d ", i);
        print_list(hm->buckets[i]);
    }
}