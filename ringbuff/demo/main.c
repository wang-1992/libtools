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
#include <pthread.h>
#include <unistd.h>

#include "ringbuff.h"

typedef struct
{
    char *buf;
    int len;
}node_t;

static const uint32_t size = sizeof(node_t);
static void *rb_handle;

static void *write_fun(void *arg)
{
    pthread_detach(pthread_self());
    node_t node;
    int i = 0;
    while(1)
    {
        do{
            if(rb_canwrite(rb_handle))
            {
                break;
            }
            else
            {
                usleep(20);
            }
        }while(1);
        //usleep(1000);
        node.buf = malloc(100);
        node.len = snprintf(node.buf, 100, "data_%d", i);
        rb_writepeek(rb_handle, &node);
        rb_writein(rb_handle);
        i++;
    }
    return arg;
}
static void *read_fun(void *arg)
{
    pthread_detach(pthread_self());
    node_t *node;
    while(1)
    {
        node = rb_readoutVal(rb_handle);
        if(node!=NULL)
        {
            printf("data = %.*s\n", node->len, node->buf);
            free(node->buf);
            node->buf = NULL;
        }
        else
        {
            usleep(20);
        }
    }
    return arg;
}
int main()
{
    pthread_t pid[2];

    uint32_t num;

    num = 100;

    rb_handle = rb_create(size, num);

    int ret;

    ret = pthread_create(&pid[0], NULL, write_fun, NULL);
    if(ret!=0)
    {
        printf("pthread_create err\n");
        return 0;
    }
    ret = pthread_create(&pid[0], NULL, read_fun, NULL);
    if(ret!=0)
    {
        printf("pthread_create err\n");
        return 0;
    }

    while(1)
    {
        sleep(10);
    }

    return 0;
}
