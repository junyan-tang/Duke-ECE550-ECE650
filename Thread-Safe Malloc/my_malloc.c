#include <assert.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>

#include "my_malloc.h"

//initialize basic list structure
static node_t *head_lock = NULL;
__thread node_t *head_nolock = NULL;
static pthread_mutex_t sbrk_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;

//print free list
void print_freelist(node_t *head){
    node_t *curr = head;
    while(curr != NULL){
        printf("metadata address: %p, free size: %lu\n", curr, curr->size);
        curr = curr->next;
    }
}

//increase heap memory
void *sbrk_memory(size_t size){
    //sbrk is not thread-safe, add lock
    pthread_mutex_lock(&sbrk_lock);
    node_t *brk_block = sbrk(0);
    void *temp = sbrk(size + sizeof(node_t));
    pthread_mutex_unlock(&sbrk_lock);
    
    brk_block->size = size;
    brk_block->next = NULL;  
    return (void *)brk_block + sizeof(node_t);
}

//split free-memory block
void *split_block(node_t * head, node_t *curr, node_t *prev, size_t size){
    node_t *new_block = (node_t *)((void *)curr + sizeof(node_t) + size);
    new_block->size = curr->size - sizeof(node_t) - size;
    new_block->next = curr->next;
    curr->size = size;
    curr->next = NULL;
    if(prev == NULL){
        head = new_block;
    }
    else{
        prev->next = new_block;
    }
    return (void *)curr + sizeof(node_t);
}

//remove free-memory block
void *remove_block(node_t* head, node_t *curr, node_t *prev, size_t size){
    if(prev == NULL){
        head = curr->next;
    }
    else{
        prev->next = curr->next;
    }
    curr->next = NULL;
    return (void *)curr + sizeof(node_t);
}

//merge two free blocks
void merge_block(node_t *curr, node_t *prev){
    if((void *)prev + sizeof(node_t) + prev->size == (void *)curr){
        prev->size = prev->size + sizeof(node_t) + curr->size;
        prev->next = curr->next;
    }
}
void * bf_malloc(node_t *head, size_t size){
    if (size == 0){
        return NULL;
    }
    size_t min_suit = INT_MAX;
    node_t *curr = head;
    node_t *prev = NULL;
    node_t *op = NULL;
    node_t *op_prev = NULL;
    while(curr != NULL){
        if(curr->size > size && curr->size < min_suit){
            op = curr;
            op_prev = prev;
            min_suit = curr->size;
        }
        else if(curr->size == size){
            op = curr;
            op_prev = prev;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if(op == NULL && op_prev == NULL){
        return sbrk_memory(size);
    }
    else{
        if(op->size > (size + sizeof(node_t))){
            return split_block(head, op, op_prev, size);
        }
        else if(op->size >= size){
            return remove_block(head, op, op_prev, size);
        }
    }  
}

//free function
void __free(node_t *head, void *ptr){
    if(ptr == NULL){
        return;
    }
    node_t *free_block = (node_t *)(ptr - sizeof(node_t));
    
    if(head == NULL){
        head = free_block;
        return;
    }
    node_t *curr = head;
    node_t *prev = NULL;
    while(curr != NULL){
        assert(free_block != curr);
        if(curr < free_block){
            prev = curr;
            curr = curr->next;
        }
        else{
            break;
        }
    }
    //add block after last block
    if(curr == NULL){
        prev->next = free_block;
        merge_block(free_block, prev);
    }
    //add block before head block 
    else if(curr == head){
        free_block->next = curr;
        head = free_block;
        merge_block(curr, free_block);
    }
    //add block between head and tail block
    else{
        free_block->next = curr;
        prev->next = free_block;
        merge_block(curr, free_block);
        merge_block(free_block, prev);
    }       
}

//Thread Safe malloc: locking version
void *ts_malloc_lock(size_t size){
    pthread_mutex_lock(&list_lock); 
    void *ptr = bf_malloc(head_lock, size);
    pthread_mutex_unlock(&list_lock);  
    return ptr;
}

//Thread Safe free: locking version
void ts_free_lock(void *ptr){
    pthread_mutex_lock(&list_lock);
    __free(head_lock, ptr);
    pthread_mutex_unlock(&list_lock);
}

//Thread Safe malloc: non-locking version
void *ts_malloc_nolock(size_t size){
    return bf_malloc(head_nolock, size);
}

//Thread Safe free: non-locking version
void ts_free_nolock(void *ptr){
    __free(head_nolock, ptr);
}