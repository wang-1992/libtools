/*************************************************************************
    > File Name: ringbuff.c
    > Author: wangkunyao
    > Mail: wangkyao1992@163.com 
    > Created Time: Mon 21 Nov 2016 12:40:47 AM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define RB_NODE_SIZE        (sizeof(rb_node_t))
#define RB_HANDLE_SIZE      (sizeof(rb_handle_t))

#define ALIGN_64(s)         (((s) + 63 ) & ~63)

typedef struct
{
    void *buf;
}rb_node_t;

typedef struct
{
    uint32_t    w_point;
    uint32_t    r_point;
    uint32_t    elem_num; 
    uint64_t    elem_size;
    rb_node_t   *rb_node;
}rb_handle_t;

int rb_canread(void *handle)
{
    rb_handle_t *rb_handle = handle;
    return (rb_handle->r_point==rb_handle->w_point)?(0):(1);
}

void *rb_readpeek(void *handle)
{
    rb_handle_t *rb_handle = handle;
    return rb_handle->rb_node[rb_handle->r_point].buf;
}

void *rb_readout(void *handle)
{
    rb_handle_t *rb_handle = handle;
    rb_handle->r_point = (rb_handle->r_point + 1) % rb_handle->elem_num;
    return NULL;
}

void *rb_readoutVal(void *handle)
{
    void *ptr = NULL;
    (rb_canread(handle)!=0)?(ptr = rb_readpeek(handle), rb_readout(handle)):(ptr = NULL);
    return ptr;
}

int rb_canwrite(void *handle)
{
    rb_handle_t *rb_handle = handle;
    return ((rb_handle->w_point + 1) % rb_handle->elem_num==rb_handle->r_point)?(0):(1);
}

void rb_writepeek(void *handle, void *ptr)
{
    rb_handle_t *rb_handle = handle;
    memcpy(rb_handle->rb_node[rb_handle->w_point].buf, ptr, rb_handle->elem_size);
}

void rb_writein(void *handle)
{
    rb_handle_t *rb_handle = handle;
    rb_handle->w_point = (rb_handle->w_point + 1) % rb_handle->elem_num;
}

void rb_writeinVal(void *handle, void *ptr)
{
    (rb_canwrite(handle))?(rb_writepeek(handle, ptr), rb_writein(handle)):(1);
}

void *rb_create(uint64_t elem_size, uint32_t elem_num)
{
    rb_handle_t *rb_handle;
    uint8_t     *buf;
    uint64_t    need_size;
    uint32_t    block_index;
    uint64_t    offset;

    rb_handle = malloc(RB_HANDLE_SIZE);
    if(rb_handle==NULL)
    {
        return NULL;
    }

    memset(rb_handle, 0, RB_HANDLE_SIZE);

    rb_handle->elem_num     = elem_num + 1;
    rb_handle->elem_size    = elem_size;
    rb_handle->r_point      = 0;
    rb_handle->w_point      = 0;

    need_size       = (elem_num + 1) * (RB_NODE_SIZE + rb_handle->elem_size);
    buf = malloc(need_size);
    if(buf==NULL)
    {
        return NULL;
    }

    rb_handle->rb_node = (rb_node_t *)buf;
    offset = RB_NODE_SIZE * (elem_num + 1);
    for(block_index = 0; block_index <= elem_num; block_index++)
    {
        rb_handle->rb_node[block_index].buf = buf + offset;
        offset+=rb_handle->elem_size;
    }

    return rb_handle;
}

