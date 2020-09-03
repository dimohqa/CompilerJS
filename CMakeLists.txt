cmake_minimum_required(VERSION 3.15)
project(compilator)

set(CMAKE_CXX_STANDARD 14)

add_executable(compilator main.cpp Lexer/Lexer.cpp Lexer/Lexer.h Lexer/Token.h Lexer/Token.cpp EnumSwitch/TokenTypeSwitch.cpp EnumSwitch/TokenTypeSwitch.h Parser/Expression.cpp Parser/Expression.h Parser/VariableExpression.cpp Parser/VariableExpression.h Parser/NumberExpression.cpp Parser/NumberExpression.h Parser/CallExpression.cpp Parser/CallExpression.h Parser/Parser.cpp Parser/Parser.h)

target_link_libraries(compilator gtest gtest_main)

add_subdirectory(Google_tests)