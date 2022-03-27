cmake_minimum_required(VERSION 3.20)
project(Projeto1_DA)

set(CMAKE_CXX_STANDARD 14)

set(Headers Carrinha.h Encomenda.h)
add_executable(Projeto1_DA main.cpp Encomenda.cpp Carrinha.cpp)
