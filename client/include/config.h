#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#define PORT 2200
#define MAX_MESSAGE_SIZE 1024*10 //设置最大数据包为10K
#define MAX_ARGV_LEN 5  //最大参数长度

#define ERROR_NET 101       //网络错误
#define ERROR_SHELL 102       //shell错误
#define ERROR_FILE 103       //文件操作错误


#define GETOBJECT(linklist) (void *)((char *)linklist -(char *)sizeof (struct linklist))  //通过linklist的地址减去linklist的偏移量获取使用这个linklist的对象的地址

struct linklist {
    struct linklist *head;
    struct linklist *next;
} ;

#endif //CLIENT_CONFIG_H
