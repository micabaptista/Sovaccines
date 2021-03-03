cmake_minimum_required(VERSION 3.17)
project(Sovaccines C)

set(CMAKE_C_STANDARD 11)

include_directories(projeto1-headers)

add_executable(Sovaccines
    projeto1-headers/client.h
    projeto1-headers/main.h
    projeto1-headers/memory-private.h
    projeto1-headers/memory.h
    projeto1-headers/process.h
    projeto1-headers/proxy.h
    projeto1-headers/server.h
    projeto1-headers/synchronization.h
    ads.c)
