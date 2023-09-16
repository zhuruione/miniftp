#处理所有的指令操作
file(GLOB SOURCE_FILES *.c)
add_library(shell STATIC ${SOURCE_FILES})