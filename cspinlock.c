#include <stdlib.h>
#include "cspinlock.h"

typedef struct cspinlock{
  //define your locking structure here
  volatile int _lock;
} cspinlock_t;

int cspin_lock(cspinlock_t* slock){
  while(! __sync_bool_compare_and_swap(&slock->_lock, 0, 1));
  return 0;
}

int cspin_unlock(cspinlock_t *slock){
  slock->_lock = 0;
  return 0;
}

cspinlock_t* cspin_alloc(){
  return (cspinlock_t*) calloc(1, sizeof(cspinlock_t));
}

void cspin_free(cspinlock_t* slock) {
  free(slock);
}
