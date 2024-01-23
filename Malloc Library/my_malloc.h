#include <stdlib.h>
//free list data structure
typedef struct __node_t{
    size_t size;
    struct __node_t *next;
} node_t;

void __free(void *ptr);
void *sbrk_memory(size_t size);
void *split_block(node_t *curr, node_t *prev, size_t size);
void *remove_block(node_t *curr, node_t *prev, size_t size);
void merge_block(node_t *curr, node_t *prev);
void print_freelist();

//First Fit malloc/free
void *ff_malloc(size_t size);
void ff_free(void *ptr);

//Best Fit malloc/free
void *bf_malloc(size_t size);
void bf_free(void *ptr);

//library function
unsigned long get_data_segment_size();
unsigned long get_data_segment_free_space_size();
