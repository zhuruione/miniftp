#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "shell.h"
int main(int argc, char *argv[]) {
    char cwd[PATH_MAX];//当前目录
    char instruct[PATH_MAX];//指令
    handleConnect(argc,argv); //处理传入参数
    while (1){
        getcwd(cwd,sizeof (cwd));
        printf("miniftp@%s>",argv[1]);
        fgets(instruct,PATH_MAX,stdin);
        handleShell(instruct);
    }
}
