#主要负责整合操作
file(GLOB SOURCE_FILES *.c)
add_library(work STATIC ${SOURCE_FILES})
target_link_libraries(work PRIVATE file network shell)