[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/GUEdkqaQ)
# Concurrent Programming

This week you will implement a simple locking construct by relying only on primitive atomic operations. You will also implement a scalable, thread-safe concurrent data-structure. This will be achieved by following two different paths:
1. using locks
2. using a lock-free approach

## Deliverables

1. Implement the spinlock that is declared in `spinlock.h`. The file `spinlock.c` will be used to generate the library `libspinlock.so`.
2. Implement a lock-based linked list that is declared in `linkedlist.h`. The file `locklinkedlist.c` will be used to generate the library `liblocklinkedlist.so`.
3. Implement a lock free linked list also declared in `linkedlist.h`. The file `lockfreelinkedlist.c` will be used to generate the library `liblockfreelinkedlist.so`.
4. Implement an hashmap that is declared in `hashmap.h`.  The file `hashmap.c` will be used to generate the librares `liblockhashmap.so` and `liblockfreehashmap.so`.

**NB:** For task 1, only atomic primitives (e.g., compare-and-swap, atomic fetch-and-increment, etc.) are allowed. No synchronization library can be used (on Rust you can use `std::sync::atomic`).

**NB2:** Functions with an `int` return value should return 0 on success, and something else on failure.

**NB3:** The lock-based linked list task should use the spinlock library, i.e the functions declared in `spinlock.h`.

**NB4:** The hashmap task should use the linked list libraries, i.e the functions declared in `linkedlist.h`.

### Tip for Rust

You allocate datastructures via
[Box](https://doc.rust-lang.org/std/boxed/struct.Box.html) and cast those
to/from raw pointer when implementing the alloc/free functions required by the
`hashmap` and `spinlock` interface.

## Test Setup
There are four tests that needs to be passed to complete this task successfully.

### Mutual exclusion
`test_mutual_exclusion.py` expects `libspinlock.so` and checks whether the implementation of `spinlock` guarantees that no two critical sections can execute concurrently.

### Lock-based Linked List
`test_locklinkedlist.py` expects `liblocklinkedlist.so` and checks for the following:
1. the concurrent linked list is implemented correctly
2. the linked list scales with an increasing number of threads

### Lock free Linked List
`test_lockfreelinkedlist.py` expects `liblockfreelinkedlist.so` and checks for the following:
1. the concurrent linked list is implemented correctly
2. the linked list scales with an increasing number of threads

### Lock-based Hashmap
`test_lockhashmap.py` expects `liblockhashmap.so` and checks for the following:
1. the concurrent hashmap is implemented correctly
2. the hashmap scales with an increasing number of threads in high contention workloads.

### Lock free Hashmap
`test_lockfreehashmap.py` expects `liblockfreehashmap.so`
- If the previous tasks were implemented correctly this task should, in principle, also run without errors.


## Hints
- Both lock-based and lock-free hashmap tests rely on the `test_lockhashmap.c` and `test_lockfreehashmap.c` to execute a workload on the hashmap. You can check the usage of this code to test your own.
- The hashmap does not need to check if an element is already in the hashmap before inserting
- Inserts should be relatively fast (i.e. insert at the beginning of the bucket, not the end)

## Going further
1. If you want to further develop your concurrent programming skills you can check other synchronization techniques such as Read-Copy-Update (RCU) and figure out how can the hashmap use RCU.  
2. Another direction that is important for lock-free programming is memory reclamation. You can try to understand how to safely reclaim deleted nodes from the hashmap.

## References:
1. [MCS locks and qspinlocks](https://lwn.net/Articles/590243/)
2. [A Pragmatic Implementation of Non-Blocking Linked-Lists](https://www.cl.cam.ac.uk/research/srg/netos/papers/2001-caslists.pdf)
3. [Introduction to RCU](http://www2.rdrop.com/~paulmck/RCU/)
4. [Reclaiming Memory for Lock-Free Data Structures: There has to be a Better Way](https://arxiv.org/pdf/1712.01044.pdf)


 
