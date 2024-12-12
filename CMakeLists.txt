cmake_minimum_required(VERSION 3.29)
project(trans)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/lexeme)
include_directories(src/lexical_analyzer)
include_directories(src/trie)

add_executable(trans
    src/lexeme/lexeme.cpp
    src/lexeme/lexeme.h
    src/lexical_analyzer/lexical_analyzer.cpp
    src/lexical_analyzer/lexical_analyzer.h
    src/trie/Trie.cpp
    src/trie/Trie.h
    main.cpp
        src/syntax_analyzer/syntax_analyzer.cpp
        src/syntax_analyzer/syntax_analyzer.h
        src/tid.cpp
        src/tid.h
)
