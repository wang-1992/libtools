/*************************************************************************
    > File Name: rmq.c
    > Author: wangkunyao
    > Mail: wangkyao1992@163.com 
    > Created Time: Sun 13 Nov 2016 09:07:32 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "rmq.h"
#include "ring_buffer.h"

#define RMQ_HANDLE_SIZE         (sizeof(rmq_handle_t))
#define RMQ_RING_SIZE           (sizeof(rmq_ring_t))
#define RMQ_MIN(a, b)           ((a > b)?(b):(a))

typedef struct __rmq_ring_t__
{
    uint8_t *ring;
}rmq_ring_t;

typedef struct __rmq_handle_t__
{
    rmq_ring_t  *ring_free;
    rmq_ring_t  *ring_use;
    char        name[RMP_MAX_NAME_SIZE + 1];
    uint32_t    qnum;
    uint32_t    producer_num;
    uint32_t    consumer_num;
}rmq_handle_t;

static int _rmq_ring_init(rmq_handle_t *rmq_handle, int qid, uint32_t qlen, uint64_t qsize, int gate)
{
    return  0;
}

void *rmq_malloc(rmq_param_t *param)
{
    int             len;
    uint32_t        i;

    uint32_t        gate;

    rmq_handle_t    *rmq_handle;

    if(param==NULL)
    {
        return NULL;
    }

    rmq_handle = malloc(RMQ_HANDLE_SIZE);
    if(rmq_handle==NULL)
    {
        return NULL;
    }
    len = RMQ_MIN(RMP_MAX_NAME_SIZE, strlen(param->name));
    strncpy(rmq_handle->name, param->name, len);

    rmq_handle->qnum            = param->qnum;
    rmq_handle->producer_num    = param->producer;
    rmq_handle->consumer_num    = param->consumer;

    rmq_handle->ring_free       = malloc(param->qnum * RMQ_RING_SIZE);
    rmq_handle->ring_use        = malloc(param->qnum * RMQ_RING_SIZE);

    gate                        = (param->qlen * 30) / 100;

    for(i = 0; i < param->qnum; i++)
    {
        _rmq_ring_init(rmq_handle, i, param->qlen, param->qsize, gate);
    }
    return rmq_handle;
}
