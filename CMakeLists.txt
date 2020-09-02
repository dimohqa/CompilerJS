cmake_minimum_required(VERSION 3.15)
project(compilator)

set(CMAKE_CXX_STANDARD 14)

add_executable(compilator main.cpp Lexer/Lexer.cpp Lexer/Lexer.h Lexer/Token.h EnumSwitch/TokenTypeSwitch.cpp EnumSwitch/TokenTypeSwitch.h Lexer/Token.cpp)

target_link_libraries(compilator gtest gtest_main)

add_subdirectory(Google_tests)