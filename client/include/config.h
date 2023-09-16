#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H

#define PORT 2203
#define MAX_MESSAGE_SIZE 1024*10 //设置最大数据包为10K

#define GETOBJECT(linklist) (void *)((char *)linklist -(char *)sizeof (struct linklist))  //通过linklist的地址减去linklist的偏移量获取使用这个linklist的对象的地址

struct linklist {
    struct linklist *head;
    struct linklist *next;
} ;

#endif //CLIENT_CONFIG_H
