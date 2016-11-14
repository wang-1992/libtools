/*************************************************************************
    > File Name: rmq.h
    > Author: wangkunyao
    > Mail: wangkyao1992@163.com 
    > Created Time: Sun 13 Nov 2016 10:05:38 PM CST
 ************************************************************************/

#ifndef _RMQ_H_
#define _RMQ_H_

#include <stdint.h>

#define RMP_MAX_NAME_SIZE           20

typedef struct
{
    uint32_t    qnum;
    uint32_t    qlen;
    uint32_t    qsize;
    uint32_t    producer;
    uint32_t    consumer;

    char        name[RMP_MAX_NAME_SIZE];
}rmq_param_t;


#endif
