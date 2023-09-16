#主要负责文件操作
file(GLOB SOURCE_FILES *.c)
add_library(file STATIC ${SOURCE_FILES})