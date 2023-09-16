
#include <fcntl.h>
#include "shell.h"


int handleConnect(int argc, char *argv[]) {
    printf("%s\n",argv[1]);
    int fd=connectToServer(argv[1]);
    while (1){
        char string[MAX_MESSAGE_SIZE];
        scanf("%s",string);
        struct DatePacket d={
                .type=COMMENT,
                .message_length=strlen(string),
                .buf=string
        };
        sendPacket(fd,&d,1);
    }

}

