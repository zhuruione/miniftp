
#include <fcntl.h>
#include "shell.h"
#include <limits.h>

extern char cwd[PATH_MAX];//当前目录
extern int fd = 0; //当前连接的描述符

int handleConnect(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "启动参数错误格式为:\nminiftp <远程设备地址>\n");
        exit(ERROR_SHELL);
    }
    fd = connectToServer(argv[1]);
}

int handleShell(char *instruct) {
    instruct[strlen(instruct) - 1] = '\0';
    char *commad;  //指令字符串
    char *argvs[MAX_ARGV_LEN] = {0}; //最多可以传入四个参数
    //解析指令字符串
    commad = strtok(instruct, " ");
    int argc = 0;
    for (; argc < MAX_ARGV_LEN; ++argc) {
        argvs[argc] = strtok(NULL, " ");
        if (!argvs[argc])
            break;
    }

    //处理命令
    void (*funsions[])(int argc, char **argvs) ={ls, cd, mv, rm};
    char *commands[] = {"ls", "cd", "mv", "rm"};

    for (int i = 0; i < MAX_ARGV_LEN; ++i) {
        if (!strcmp(commad, commands[i])) {
            funsions[i](argc, argvs); //执行函数
            break;
        }
    }


}



