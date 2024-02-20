#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//Data structure of free list
typedef struct __node_t{
     size_t size;
    struct __node_t *next;
} node_t;

//helper function
void *sbrk_memory(size_t size);
void *split_block(node_t *head, node_t *curr, node_t *prev, size_t size);
void *remove_block(node_t *head, node_t *curr, node_t *prev, size_t size);
void merge_block(node_t *curr, node_t *prev);
void *bf_malloc(node_t *head, size_t size);
void __free(node_t *head, void *ptr);

//Thread Safe malloc/free: locking version
void *ts_malloc_lock(size_t size);
void ts_free_lock(void *ptr);

//Thread Safe malloc/free: non-locking version
void *ts_malloc_nolock(size_t size);
void ts_free_nolock(void *ptr);