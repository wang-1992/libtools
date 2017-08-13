#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdarg.h>

#define MAX_PATH_SIZE               1024
int tools_mkdirs(char *path)
{
    int i,len;
    char str[MAX_PATH_SIZE + 1] = {0};
    strncpy(str, path, MAX_PATH_SIZE);

    len=strlen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] == '/')
        {
            str[i] = '\0';
            if (access(str,0)!=0)
            {
                mkdir(str, 0777);
            }
            str[i]='/';
        }
    }
    return 0;
}

int make_path_by_time(char *buf, int buf_size, time_t *ti)
{
    int ret;
    struct tm *ptoday;
    struct tm today;

    memset(&today, 0, sizeof(today));
    ptoday = localtime(ti);

    ret = snprintf(buf, buf_size, "/%04d/%02d/%02d/%04d_%02d_%02d_%02d_%02d.log",
            ptoday->tm_year+1900,ptoday->tm_mon+1,ptoday->tm_mday,
            ptoday->tm_year+1900,ptoday->tm_mon+1,ptoday->tm_mday,
            ptoday->tm_hour,ptoday->tm_min);
    return ret;
}

typedef struct
{
    FILE *fp;
#define MAX_PRE_PATH_SIZE       100
    //文件路径的前缀
    char pre_path[MAX_PRE_PATH_SIZE + 1];
    int pre_path_len;
    //真实的文件路径
    char path[MAX_PATH_SIZE + 1];
}write_log_handle_t;

static int write_log_start(void *handle, uint32_t jiffie)
{
    write_log_handle_t *write_log_handle = (write_log_handle_t *)handle;
    time_t tm;
    tm = (time_t)jiffie;
    make_path_by_time(write_log_handle->path + write_log_handle->pre_path_len, MAX_PATH_SIZE - write_log_handle->pre_path_len, &tm);
    tools_mkdirs(write_log_handle->path);
    printf("path = %s\n", write_log_handle->path);
    write_log_handle->fp = fopen(write_log_handle->path, "wb+");
    return 0;
}

static int write_log_end(void *handle)
{
    write_log_handle_t *write_log_handle = (write_log_handle_t *)handle;
    if (write_log_handle->fp)
    {
        fclose(write_log_handle->fp);
        write_log_handle->fp = NULL;
    }
    return 0;
}

void *write_log_init(char *pre_path)
{
    write_log_handle_t *handle = malloc(sizeof(write_log_handle_t));
    memset(handle, 0, sizeof(write_log_handle_t));
    handle->fp = NULL;
    strncpy(handle->pre_path, pre_path, MAX_PRE_PATH_SIZE);
    handle->pre_path_len = strlen(handle->pre_path);
    strncpy(handle->path, handle->pre_path, handle->pre_path_len);
    return handle;
}

int write_log(void *handle, const char *format, ...)
{
    va_list vp;
    write_log_handle_t *write_log_handle = (write_log_handle_t *)handle;

    if (write_log_handle->fp == NULL)
    {
        return -1;
    }

    va_start(vp, format);
    vfprintf(write_log_handle->fp, format, vp);
    va_end(vp);
    return 0;
}


int main()
{
    uint32_t jiffie = 1502518683;
    void *handel;
    handel = write_log_init("./112234/");

    write_log_start(handel, jiffie);
    write_log(handel, "asdasdsadsd:%u.........%s\n", jiffie, "hello1");
    write_log(handel, "asdasdsadsd:%u.........%s\n", jiffie, "hello2");
    write_log(handel, "asdasdsadsd:%u.........%s\n", jiffie, "hello3");
    write_log(handel, "asdasdsadsd:%u.........%s\n", jiffie, "hello4");
    write_log_end(handel);

    return 0;
}
