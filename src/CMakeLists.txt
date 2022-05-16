cmake_minimum_required(VERSION 3.10)
project(mypy)

find_package(LLVM REQUIRED CONFIG)
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# For jsb: specific the address
include_directories(/usr/include/llvm-13)
include_directories(/usr/include/llvm-c-13)

execute_process(COMMAND llvm-config-13 --libs OUTPUT_VARIABLE LLVM_LINK_LIBRARIES)
string(STRIP "${LLVM_LINK_LIBRARIES}" LLVM_LINK_LIBRARIES)

if(APPLE)
	include_directories(/usr/local/opt/llvm/include)
	string(APPEND CMAKE_CXX_FLAGS " -Wno-c++11-narrowing")
ENDIF(APPLE)


set(CMAKE_CXX_STANDARD 14)

# aux_source_directory(ast AST_SOURCE)
# aux_source_directory(generator GEN_SOURCE)
# aux_source_directory(vis VIS_SOURCE)

add_custom_command(
    OUTPUT lex.l.cpp
    COMMAND lex -o lex.l.cpp ${CMAKE_CURRENT_LIST_DIR}/lex.l
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/lex.l parser.y.cpp
)

add_custom_command(
    OUTPUT parser.y.hpp parser.y.cpp 
    COMMAND bison -d -o parser.y.cpp ${CMAKE_CURRENT_LIST_DIR}/parser.ypp
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/parser.ypp
)

# For jsb: "cannot find -lz", so must quote it
# llvm_map_components_to_libnames(LLVM_LINK_LIBRARIES core)

add_executable(
    mypy
    main.cpp ast.cpp code_gen.cpp lex.l.cpp
    parser.y.cpp parser.y.hpp)

set_target_properties(mypy PROPERTIES LINK_LIBRARIES "${LLVM_LINK_LIBRARIES}")