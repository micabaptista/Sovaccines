cmake_minimum_required(VERSION 3.17)
project(Sovacinnes C)

set(CMAKE_C_STANDARD 99)

set (CMAKE_C_FLAGS "-pthread -lrt -I -g")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread -lrt")

add_executable(teste src/sovacinnes.c src/main.c src/client.c src/memory.c src/process.c src/proxy.c src/server.c src/synchronization.c)