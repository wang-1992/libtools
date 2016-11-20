/*************************************************************************
    > File Name: main.c
    > Author: wangkunyao
    > Mail: wangkyao1992@163.com 
    > Created Time: Mon 21 Nov 2016 01:40:45 AM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "ringbuff.h"

int main()
{
    void *rb_handle;

    char *word = "abcdefghijklmnopqrstuvwxyz";

    int num = strlen(word);

    rb_handle = rb_create(1, num);

    int i;

    for(i = 0; i < num; i++)
    {
        rb_writeinVal(rb_handle, (void *)&word[i]);
    }

    char *p;
    for(i = 0; i < num; i++)
    {
        p = rb_readoutVal(rb_handle);

        printf(" p =%c\n", p[0]);
    }

    return 0;
}
