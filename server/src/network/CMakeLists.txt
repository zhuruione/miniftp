#主要负责网络传输
file(GLOB SOURCE_FILES *.c)
add_library(network STATIC ${SOURCE_FILES})