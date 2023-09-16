

#ifndef SERVER_NETWORK_H
#define SERVER_NETWORK_H

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define DATA_HEAD_LEN 16
//数据包类型枚举
typedef enum DateType {
    COMMENT=1,    //内容
    INSTRUCT,    //指令
    END
} DateType;


//数据包结构体
struct DatePacket {
    DateType type;          //消息类型 4字节
    size_t message_length; // 消息长度 8字节   需要进行字节对齐  !!!他妈的真阴间啊
    union {
        char message[MAX_MESSAGE_SIZE]; // 消息内容
        char *buf;                      //消息内容指针
    };

};

int listenToClient();//开始监听
int getClientSocket(int socketServer);

void handle_client(int client_socket);//处理相关请求
size_t sendPacket(int client_socket, struct DatePacket *packet,int flag);    //发送数据包
size_t receivePacket(int client_socket, struct DatePacket *packet); //接收户数据包
void endPacket(int client_socket);

#endif //SERVER_NETWORK_H
