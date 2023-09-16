//
// Created by zr on 9/16/23.
//
#include "shell.h"
#include <limits.h>

extern char cwd[PATH_MAX];//当前目录
extern int fd; //当前连接的描述符

void ls_fun(char *command) {
    FILE *p_fd; //使用ls的指令的管道描述符
    char buffer[128];
    p_fd = popen(command, "r");
    if (p_fd == NULL) {
        perror("popen");
        exit(ERROR_SHELL);
    }
    printf("本地主机:");
    // 从命令的输出中读取数据
    while (fgets(buffer, sizeof(buffer), p_fd) != NULL) {
        printf("%s", buffer);
    }
    // 关闭管道
    if (pclose(p_fd) == -1) {
        perror("pclose");
        exit(ERROR_SHELL);
    }
}

void ls(int argc, char **argvs) {
    char *command;
    if(argc>2){
        fprintf(stderr,"参数数量错误");
        return;
    }
    if (argc == 0) {//没有参数的话,就列举出当前所有主机当前目录所有文件
        command = "ls -lh";
        ls_fun(command);
    } else {//第一个参数用于选择主机  -r(remote)表示远程主机,-c(current)表示本地主机
        if (!strcmp("-r", argvs[0])) {
            //访问远程主机当前文件夹所有文件
            char command_tem[100];
            if (argvs[1]) {
                sprintf(command_tem, "ls -lh %s", argvs[1]);
                command = (char *) &command_tem;
            } else
                command = "ls -lh";
            struct DatePacket sendDatePacket = {
                    .message_length=strlen(command),
                    .type=INSTRUCT,
                    .buf=command
            };
            sendPacket(fd, &sendDatePacket, 1);
            struct DatePacket receiveDatePacket = {0};
            receivePacket(fd, &receiveDatePacket);
            printf("远程主机:\n");
            while (receiveDatePacket.type != END) {
                printf("%s", receiveDatePacket.message);
                memset(&receiveDatePacket,0, sizeof(struct DatePacket));
                receivePacket(fd, &receiveDatePacket);
            }

        }
    }
}

void cd(int argc, char **argvs) {

}

void mv(int argc, char **argvs) {

}

void rm(int argc, char **argvs) {

}