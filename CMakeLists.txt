cmake_minimum_required(VERSION 3.20)
project(Projeto1_DA)

set(CMAKE_CXX_STANDARD 14)

set(Headers include/Van.h include/Order.h)
add_executable(Projeto1_DA main.cpp src/Order.cpp src/Van.cpp include/App.h src/App.cpp)
