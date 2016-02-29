#ifndef XMALLOC
#define XMALLOC

#include <stdio.h>

#define META_BLOCK_SIZE    sizeof(struct mem_block)

typedef struct mem_block *t_mem_block;

struct mem_block {
    size_t      size;
    t_mem_block next;
    int         free;
};

// Prototipi
t_mem_block find_block(t_mem_block *last, size_t size);
t_mem_block request_heap(t_mem_block last, size_t size);
void *xmalloc(size_t size);
void xfree(void *ptr);
t_mem_block get_ptr_block(void *ptr);

#endif