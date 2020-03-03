cmake_minimum_required(VERSION 3.15)
project(compilator)

set(CMAKE_CXX_STANDARD 14)

add_executable(compilator main.cpp Lexer.cpp Lexer.h Token.cpp Token.h EnumSwitch/TokenTypeSwitch.cpp EnumSwitch/TokenTypeSwitch.h)