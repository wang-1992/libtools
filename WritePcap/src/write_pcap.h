/*************************************************************************
    > File Name: write_pcap.h
    > Author: wangkunyao
    > Mail: wangkyao1992@163.com 
    > Created Time: Sat 22 Apr 2017 05:36:39 PM CST
 ************************************************************************/

#ifndef _WRITE_PCAP_H_
#define _WRITE_PCAP_H_

#include <stdint.h>

typedef enum
{
    data_type_ip = 1,
    data_type_l1mac,
}data_type_t;

void *write_pcap_malloc(char *file_name, uint32_t buff_size);

#endif
