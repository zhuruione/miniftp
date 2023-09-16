#include <stdio.h>
#include "work.h"

int main() {
    chdir("/home");//设置工作目录
    startListen();
    return 0;
}
