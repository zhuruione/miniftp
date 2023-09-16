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
    INSTRUCT,    //指令
    END             //结束标志
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
void endPacket(int client_socket); //发送结束标志

size_t sendfile(int client_socket,int fd); //发送文件
size_t receivefile(int client_socket,int fd);//接收文件
#endif //CLIENT_NETWORK_H
