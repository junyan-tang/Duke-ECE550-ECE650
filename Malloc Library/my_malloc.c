#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <limits.h>
#include "my_malloc.h"

static node_t *head = NULL;
unsigned long data_segment = 0;
unsigned long data_segment_free_space = 0;

//initialize free list
void init_memory(){
    head = sbrk(4096);
    head->size = 4096 - sizeof(node_t); 
    head->next = NULL;
    data_segment = 4096;
    data_segment_free_space = 4096;
}

//print free list
void print_freelist(){
    node_t *curr = head;
    while(curr != NULL){
        printf("metadata address: %p, free size: %lu\n", curr, curr->size);
        curr = curr->next;
    }
}

//increase heap memory
void *sbrk_memory(size_t size){
    node_t *brk_block = sbrk(0);
    void *temp = sbrk(size + sizeof(node_t));
    brk_block->size = size;
    brk_block->next = NULL;
    data_segment = data_segment + size + sizeof(node_t);
    return (void *)brk_block + sizeof(node_t);
}

//split free-memory block
void *split_block(node_t *curr, node_t *prev, size_t size){
    //allocate new block for memory
    node_t *new_block = (node_t *)((void *)curr + sizeof(node_t) + size);
    new_block->size = curr->size - sizeof(node_t) - size;
    new_block->next = curr->next;
    curr->size = size;
    curr->next = NULL;
    //add it to free list
    if(prev == NULL){
        head = new_block;
    }
    else{
        prev->next = new_block;
    }
    //update free space data
    data_segment_free_space = data_segment_free_space - curr->size - sizeof(node_t);
    return (void *)curr + sizeof(node_t);
}

//remove free-memory block
void *remove_block(node_t *curr, node_t *prev, size_t size){
    if(prev == NULL){
        head = curr->next;
    }
    else{
        prev->next = curr->next;
    }
    curr->next = NULL;
    data_segment_free_space = data_segment_free_space - curr->size - sizeof(node_t);
    return (void *)curr + sizeof(node_t);
}

//merge two free blocks
void merge_block(node_t *curr, node_t *prev){
    if((void *)prev + sizeof(node_t) + prev->size == (void *)curr){
        prev->size = prev->size + sizeof(node_t) + curr->size;
        prev->next = curr->next;
    }
}

//free function
void __free(void *ptr){
    //special case: ptr is NULL
    if(ptr == NULL){
        return;
    }
    //common case
    node_t *free_block = (node_t *)(ptr - sizeof(node_t));
    //update free space data
    data_segment_free_space = data_segment_free_space + free_block->size + sizeof(node_t);
    
    if(head == NULL){
        head = free_block;
        return;
    }
    
    //add this free block to appropriate position
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

//First Fit malloc
void *ff_malloc(size_t size){
    //special case: size is 0
    if(size == 0){
        return NULL;
    }
    //common case: size is larger than 0
    node_t *curr = head;
    node_t *prev = NULL;
    while(curr != NULL){
        //if there is enough space
        if(curr->size > (size + sizeof(node_t))){
            return split_block(curr, prev, size);
        }
        else if(curr->size >= size){
            return remove_block(curr, prev, size);
        }
        //move prev and curr pointer
        prev = curr;
        curr = curr->next;
    }
    //no more free space, increase extra memory
    return sbrk_memory(size);

}

//First Fit free
void ff_free(void *ptr){
    __free(ptr);
}

//Best Fit malloc
void *bf_malloc(size_t size){
    //special case: size is 0
    if (size == 0){
        return NULL;
    }

    //common case: size is larger than 0
    size_t min_suit = INT_MAX;
    node_t *curr = head;
    node_t *prev = NULL;
    node_t *op = NULL;
    node_t *op_prev = NULL;
    while(curr != NULL){
        //find the best fit position
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
        //sbrk new space
        return sbrk_memory(size);
    }
    else{
        if(op->size > (size + sizeof(node_t))){
            return split_block(op, op_prev, size);
        }
        else if(op->size >= size){
            return remove_block(op, op_prev, size);
        }
    }    
}

//Best Fit free
void  bf_free(void *ptr){
    __free(ptr);
}

unsigned long get_data_segment_size(){   
    return data_segment;
}

unsigned long get_data_segment_free_space_size(){
    return data_segment_free_space;
}