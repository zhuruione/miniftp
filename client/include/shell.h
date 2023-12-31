#ifndef CLIENT_SHELL_H
#define CLIENT_SHELL_H

#include "file.h"
#include "network.h"
#include "config.h"


//shell.c
int handleConnect(int argc, char *argv[]);  //处理命令行参数,并建立连接
int handleShell(char *instruct);//处理每条指令



//shell_funsions.c
void ls(int argc,char **argvs); //浏览当前文件夹所有文件
void cd(int argc,char **argvs); //进入特定文件夹
void mv(int argc,char **argvs); //移动文件或文件夹
void rm(int argc,char **argvs);//删除文件
#endif //CLIENT_SHELL_H
