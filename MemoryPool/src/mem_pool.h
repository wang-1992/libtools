/*************************************************************************
    > File Name: mem_pool.h
    > Author: wangkunyao
    > Mail: wangkyao1992@163.com 
    > Created Time: Sat 12 Nov 2016 07:16:13 PM CST
 ************************************************************************/


#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdint.h>

void *mem_pool_init(uint32_t block_num, uint32_t block_size);
void *mem_pool_malloc(void *handle, uint32_t size);
void mem_pool_free(void *handle, uint8_t *ptr);

#endif
