cmake_minimum_required(VERSION 3.0)

project(diarybase)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wall ${CMAKE_CXX_FLAGS}")

include_directories(src)
set(SOURCE
    src/fs_util.cc
    src/base.cc
    src/diarybase.cc
    )

add_library(diarybase STATIC ${SOURCE})