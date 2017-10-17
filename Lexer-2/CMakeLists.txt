cmake_minimum_required(VERSION 3.8)
project(Lexer_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CDEFINE.h
        Error.h
        FA.cpp
        FA.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.h
        Util.h)

add_executable(Lexer_2 ${SOURCE_FILES})