/*************************************************************************
    > File Name: mem_pool.c
    > Author: wangkunyao
    > Mail: wangkyao1992@163.com 
    > Created Time: Sat 12 Nov 2016 07:00:30 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct __pool_list__
{
    uint8_t                 *buf;
    struct __pool_list__    *next;
}pool_list_t;

typedef struct
{
    uint64_t    block_num;
    uint64_t    block_size;

    uint8_t     *head;
    uint8_t     *tail;
    
    pool_list_t *free;
    pool_list_t *busy;
}mem_pool_t;

void *mem_pool_malloc(void *handle, uint32_t size)
{
    mem_pool_t *mem_pool = handle;
    if(mem_pool->free==NULL)
    {
        return NULL;   
    }

    if(size > mem_pool->block_size)
    {
        return NULL;
    }

    pool_list_t *tmp    = mem_pool->free;
    mem_pool->free      = tmp->next; 

    tmp->next           = mem_pool->busy;
    mem_pool->busy      = tmp;

    return tmp->buf;
}

void mem_pool_free(void *handle, uint8_t *ptr)
{
    mem_pool_t *mem_pool = handle;
    pool_list_t *tmp    = mem_pool->free;

    if(mem_pool->busy==NULL)
    {
        return;   
    }
    tmp = mem_pool->busy;
    mem_pool->busy = tmp->next;

    tmp->buf = ptr;
    tmp->next = mem_pool->free;
    mem_pool->free = tmp;
}

void *mem_pool_init(uint32_t block_num, uint32_t block_size)
{
    mem_pool_t  *mem_pool;
    uint64_t    total_size;
    uint8_t     *buf;
    uint32_t    i;

    mem_pool = malloc(sizeof(mem_pool_t));
    if(mem_pool==NULL)
    {
        return NULL;
    }
    
    mem_pool->block_num     = block_num;
    mem_pool->block_size    = block_size;

    mem_pool->free = malloc(block_num * (sizeof(pool_list_t)));

    total_size = mem_pool->block_num * mem_pool->block_size;

    buf = malloc(total_size);
    if(buf==NULL)
    {
        return NULL;
    }
    
    for(i = 0; i < mem_pool->block_num - 1; i++)
    {
        mem_pool->free[i].buf   = buf + (i * mem_pool->block_size);
        mem_pool->free[i].next  = &mem_pool->free[i + 1];
    }

    mem_pool->free[i].next  = NULL;
    mem_pool->free[i].buf   = buf + (i * mem_pool->block_size);

    mem_pool->busy = NULL;

    return mem_pool;
}
