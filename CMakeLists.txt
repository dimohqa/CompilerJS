cmake_minimum_required(VERSION 3.15)
project(CompilerJS)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompilerJS main.cpp Lexer/Lexer.cpp Lexer/Lexer.h Lexer/Token.h Lexer/Token.cpp EnumSwitch/TokenTypeSwitch.cpp EnumSwitch/TokenTypeSwitch.h Parser/Parser.cpp Parser/Parser.h Parser/AST/ExprAST.cpp Parser/AST/ExprAST.h Parser/AST/NumberExprAST.cpp Parser/AST/NumberExprAST.h Parser/AST/VariableExprAST.cpp Parser/AST/VariableExprAST.h Parser/AST/BinaryExprAST.cpp Parser/AST/BinaryExprAST.h Parser/AST/CallExprAST.cpp Parser/AST/CallExprAST.h Parser/AST/FunctionAST.cpp Parser/AST/FunctionAST.h Parser/AST/PrototypeAST.cpp Parser/AST/PrototypeAST.h Parser/AST/ArrayExprAST.cpp Parser/AST/ArrayExprAST.h Parser/__test__/parser.cpp Parser/AST/BodyAST.cpp Parser/AST/BodyAST.h Parser/AST/IfAST.cpp Parser/AST/IfAST.h Parser/AST/ReturnExprAST.cpp Parser/AST/ReturnExprAST.h Parser/AST/StringExprAST.cpp Parser/AST/StringExprAST.h Parser/AST/WhileAST.cpp Parser/AST/WhileAST.h Parser/AST/ConsoleLogExprAST.cpp Parser/AST/ConsoleLogExprAST.h Parser/AST/VariableArrayExprAST.cpp Parser/AST/VariableArrayExprAST.h Table/Table.cpp Table/Table.h Table/Identifier.cpp Table/Identifier.h)

add_executable(TestParser ./Parser/__test__/parser.cpp)

target_link_libraries(CompilerJS gtest gtest_main)

target_link_libraries(TestParser gtest gtest_main)

add_subdirectory(Google_tests)