#include "work.h"
#include <pthread.h>

void *client_handle(void *attr);//客户端处理线程

void startListen() {
    //服务器套接字文件描述符
    int serverSocket;
    //开始监听端口
    if (!(serverSocket = listenToClient())) {
        exit(ERROR_NET);
    }
    while (1) {
        int clientSocket = getClientSocket(serverSocket);
        pthread_t t_id = 0;

        //建立连接,并等待其他客户端连接,此客户端的所有操作都移交给client_handle函数处理
        pthread_create(&t_id, NULL, client_handle, &clientSocket);
    }
}

void *client_handle(void *attr) {
    int clinetSocket = *(int *) attr;
    while (1){
        struct DatePacket d={0};
        receivePacket(clinetSocket,&d);
        if(d.type==INSTRUCT){
            printf("类型:指令  长度:%d   内容:%s\n",d.message_length,d.message);
        } else{
            for (int i = 0; i < d.message_length; ++i) {
                printf("%c",d.message[i]);
            }
            printf("\n");
            printf("长度:%d\n",d.message_length);
            fflush(stdout);
        }
    }

}