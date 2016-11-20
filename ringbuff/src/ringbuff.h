/*************************************************************************
    > File Name: ringbuff.h
    > Author: wangkunyao
    > Mail: wangkyao1992@163.com 
    > Created Time: Mon 21 Nov 2016 01:38:17 AM CST
 ************************************************************************/
#ifndef _RINGBUFF_H_
#define _RINGBUFF_H_

#include <stdint.h>

void *rb_create(uint64_t elem_size, uint32_t elem_num);

int rb_canwrite(void *handle);
void rb_writepeek(void *handle, void *ptr);
void rb_writein(void *handle);
void rb_writeinVal(void *handle, void *ptr);

int rb_canread(void *handle);
void *rb_readpeek(void *handle);
void *rb_readout(void *handle);
void *rb_readoutVal(void *handle);

#endif
