cmake_minimum_required(VERSION 3.15)
project(try1 C)

set(CMAKE_C_STANDARD 99)
include_directories(/usr/include/openssl/)
link_libraries(ssl)
link_libraries(crypto)

add_executable(try1 main.c)