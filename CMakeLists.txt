cmake_minimum_required(VERSION 3.15)
project(CompilerJS)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompilerJS main.cpp Lexer/Lexer.cpp Lexer/Lexer.h Lexer/Token.h Lexer/Token.cpp EnumSwitch/TokenTypeSwitch.cpp EnumSwitch/TokenTypeSwitch.h Parser/Parser.cpp Parser/Parser.h AST/ExprAST.cpp AST/ExprAST.h AST/NumberExprAST.cpp AST/NumberExprAST.h AST/VariableExprAST.cpp AST/VariableExprAST.h AST/BinaryExprAST.cpp AST/BinaryExprAST.h AST/CallExprAST.cpp AST/CallExprAST.h AST/FunctionAST.cpp AST/FunctionAST.h AST/PrototypeAST.cpp AST/PrototypeAST.h)

target_link_libraries(CompilerJS gtest gtest_main)

add_subdirectory(Google_tests)