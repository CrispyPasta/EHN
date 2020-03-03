cmake_minimum_required(VERSION 3.15)
project(client C)

set(CMAKE_C_STANDARD 99)
include_directories(/usr/include/openssl/)
link_libraries(ssl)
link_libraries(crypto)

add_executable(client main.c)