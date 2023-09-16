
#ifndef SERVER_WORK_H
#define SERVER_WORK_H
#include "config.h"
#include "network.h"
#include "file.h"
struct ClientObject{
    struct linklist *l;     //使用链表连接所有的客户端对象
    int clientSocket; //客户端套接字
    pthread_t thread_id; //处理当前连接客户端的线程
};

void startListen();
#endif //SERVER_WORK_H
