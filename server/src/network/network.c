#include "network.h"

//处理相关请求
void handle_client(int client_socket) {
    char buffer[1024] = {0};
    ssize_t read_size;

    read_size = read(client_socket, buffer, sizeof(buffer));
    if (read_size < 0) {
        perror("read");
        close(client_socket);
        return;
    }

    printf("Received message from client: %s\n", buffer);

    const char *response = "Hello from server!";
    write(client_socket, response, strlen(response));

    close(client_socket);
}

/**
 * 开始监听
 * @return 若创建监听套接字,成功返回套接字描述符,否则返回0
 */
int listenToClient() {
    int server_socket, client_socket;
    struct sockaddr_in server_address;

    // 创建套接字
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        return 0;
    }

    // 设置服务器地址和端口
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // 绑定套接字
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("bind");
        return 0;
    }

    // 监听连接
    if (listen(server_socket, MAX_CONNECTIONS) < 0) {
        perror("listen");
        return 0;
    }
    return server_socket;
}

/**
 * 获取客户端套接字文件描述符
 * @param socketServer 监听套接字描述符
 * @return 返回建立连接的客户端的描述符
 */
int getClientSocket(int socketServer) {
    int client_socket;
    char ip_address[INET_ADDRSTRLEN];
    struct sockaddr_in client_address;
    socklen_t client_addr_len = sizeof(client_address);
    client_socket = accept(socketServer, (struct sockaddr *) &client_address, &client_addr_len);
    if (inet_ntop(AF_INET, &client_address.sin_addr, ip_address, INET_ADDRSTRLEN) == NULL) {
        perror("inet_ntop");
        return 1;
    }
    printf("IP 地址: %s连接成功", ip_address);
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

//接收数据包,使用完要记得释放struct DatePacket
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