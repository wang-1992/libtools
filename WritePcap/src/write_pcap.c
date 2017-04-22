/*************************************************************************
    > File Name: write_pcap.c
    > Author: wangkunyao
    > Mail: wangkyao1992@163.com 
    > Created Time: Sat 22 Apr 2017 04:52:25 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>  

#include "write_pcap.h"

#define MAX_NAME_SIZE           100
#define MIN(_a, _b)             (((_a)>(_b))?(_b):(_a))

typedef struct pcap_file_header 
{
    uint32_t   magic;
    u_short    version_major;
    u_short    version_minor;
    uint32_t   thiszone;    
    uint32_t   sigfigs;   
    uint32_t   snaplen;   
    uint32_t   linktype;  
}pcap_file_header_t;

typedef struct
{
    char *p;
    uint32_t len;
    uint32_t max;
}buff_t;

typedef struct
{
    char file_name[MAX_NAME_SIZE];
    buff_t buff;
    FILE *fp;
}write_pcap_t;


static uint64_t get_file_size(const char *path)
{  
    uint64_t filesize = 0;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0)
    {
        return filesize;
    }
    else
    {
        filesize = statbuff.st_size;
    }
    return filesize;
}

static int write_file_header(FILE *fp)
{
    pcap_file_header_t file_header;
    memset(&file_header, 0, sizeof(pcap_file_header_t));

    file_header.magic = 0xa1b2c3d4;
    file_header.version_major = 2;
    file_header.version_minor = 4;
    file_header.thiszone = 0;
    file_header.sigfigs = 0;
    file_header.snaplen = 65535;
    file_header.linktype = 1;

    fwrite(&file_header, sizeof(pcap_file_header_t), 1, fp);
    fflush(fp);

    return 0;
}

int write_pcap_data(void *handle, uint8_t *data, uint32_t data_len, data_type_t type)
{
    write_pcap_t *write_pcap = handle;



    return 0;
}

void *write_pcap_malloc(char *file_name, uint32_t buff_size)
{
    write_pcap_t *write_pcap;
    uint64_t file_size;

    write_pcap = malloc(sizeof(write_pcap_t));
    if(write_pcap==NULL)
    {
        return NULL;
    }
    memset(write_pcap, 0, sizeof(write_pcap_t));
    strncpy(write_pcap->file_name, file_name, MIN(strlen(file_name), MAX_NAME_SIZE));
    write_pcap->buff.p = malloc(buff_size);
    if(write_pcap->buff.p==NULL)
    {
        free(write_pcap);
        return NULL;
    }
    write_pcap->buff.max = buff_size;
    file_size = get_file_size(file_name);
    if(file_size > 0)
    {
        write_pcap->fp = fopen(file_name, "ab+");
        if(write_pcap->fp==NULL)
        {
            perror("fopen");
            return NULL;
        }
    }
    else
    {
        write_pcap->fp = fopen(file_name, "wb+");
        if(write_pcap->fp==NULL)
        {
            perror("fopen");
            return NULL;
        }
        write_file_header(write_pcap->fp);
    }

    return NULL;
}
