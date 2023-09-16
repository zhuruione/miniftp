#ifndef CLIENT_NETWORK_H
#define CLIENT_NETWORK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include "config.h"

#define DATA_HEAD_LEN 16

typedef enum DateType{
    COMMENT=1,    //内容
    INSTRUCT    //指令
}DateType;
struct DatePacket {
    DateType type;
    size_t message_length; // 消息长度
    union {
        char message[MAX_MESSAGE_SIZE]; // 消息内容
        char *buf;                      //消息内容指针
    };

};

size_t sendPacket(int client_socket, struct DatePacket *packet,int flag);    //发送数据包
size_t receivePacket(int client_socket, struct DatePacket *packet); //接收户数据包
int connectToServer(char *remoteAddr); //建立连接
#endif //CLIENT_NETWORK_H
