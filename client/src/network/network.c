
#include "network.h"

/**
 * 与服务器建立连接
 * @param remoteAddr 服务器地址ip或者域名
 * @return 若成功返回套接字文件描述符,失败返回0
 * @author zr
 */
int connectToServer(char *remoteAddr) {
    int client_socket;
    struct sockaddr_in server_address;
    struct hostent *server;

    // 创建套接字
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(ERROR_NET);
    }

    // 获取服务器的IP地址
    server = gethostbyname(remoteAddr);
    if (server == NULL) {
        fprintf(stderr, "Error: Host not found\n");
        exit(ERROR_NET);
    }

    // 设置服务器地址和端口
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    bcopy((char *) server->h_addr, (char *) &server_address.sin_addr.s_addr, server->h_length);

    // 连接到服务器
    if (connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("connect");
        exit(ERROR_NET);
    }

    return client_socket;
}


/**
 * 发送数据包
 * @param client_socket 客户端套接字
 * @param packet 数据包
 * @param flag 若为0,则说明packet中的数据段为message,若为1则说明使用的是buf
 * @return
 */
size_t sendPacket(int client_socket, struct DatePacket *packet, int flag) {
    if (flag) {
        //使用的是buf,这时需要注意数据长度是否大于最大传输单元
        size_t len = packet->message_length;
        size_t len_point=0;
        while (len >= MAX_MESSAGE_SIZE) {
            size_t LEN=MAX_MESSAGE_SIZE;
            //先发送结构体数据类型
            send(client_socket, (void *) packet, sizeof(size_t) , 0);
            //发送数据大小
            send(client_socket, (void *) &LEN, sizeof(size_t) , 0);
            //再发送数据部分
            send(client_socket, packet->buf+len_point, MAX_MESSAGE_SIZE, 0);
            len_point+=MAX_MESSAGE_SIZE;
            len-=MAX_MESSAGE_SIZE;
        }
        //发送剩下的部分
        if(len>0){
            //先发送结构体数据类型
            send(client_socket, (void *) packet, sizeof(size_t) , 0);
            //发送数据大小
            send(client_socket, (void *) &len, sizeof(size_t) , 0);
            send(client_socket, packet->buf, len, 0);
        }

    } else {
        //使用的是message,可以直接将结构体发送
        send(client_socket, (void *) packet,
             DATA_HEAD_LEN + (packet->message_length) * sizeof(char), 0);
    }
}


size_t receivePacket(int client_socket, struct DatePacket *packet) {
    char *buf = (char *) packet;
    size_t len = 0;
    //保证至少接收完这个结构体的信息部分
    while (len < DATA_HEAD_LEN) {
        len += recv(client_socket, buf + len, DATA_HEAD_LEN - len, 0);
    }
    len = 0;
    //保证接收完信息部分,且不会超出这个包的大小
    while (len < packet->message_length) {
        len += recv(client_socket, buf + len + DATA_HEAD_LEN, packet->message_length - len, 0);
        printf("");
    }
    return len;
}

void endPacket(int client_socket) {
    struct DatePacket endPacket = {
            .type=END,
            .message_length=0
    };
    sendPacket(client_socket, &endPacket, 0); //发送结束包
}
/**
 * 发送文件
 * @param client_socket socket描述符
 * @param fd 需要发送的文件描述符
 * @return
 */
size_t sendfile(int client_socket, int fd) {

}

/**
 * 接收文件
 * @param client_socket
 * @param fd
 * @return
 */
size_t receivefile(int client_socket, int fd) {

}
