cmake_minimum_required(VERSION 3.10)
project(mypy)

find_package(LLVM REQUIRED CONFIG)
find_package(jsoncpp REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSONCPP_LIBRARIES})
include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# For jsb: specific the address
include_directories(/usr/include/llvm-13)
include_directories(/usr/include/llvm-c-13)
include_directories(/usr/include/jsoncpp)

execute_process(COMMAND llvm-config-13 --libs OUTPUT_VARIABLE LLVM_LINK_LIBRARIES)
string(STRIP "${LLVM_LINK_LIBRARIES}" LLVM_LINK_LIBRARIES)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ljsoncpp")

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
    main.cpp code_gen.cpp lex.l.cpp print_ast.cpp
    parser.y.cpp parser.y.hpp)

set_target_properties(mypy PROPERTIES LINK_LIBRARIES "${LLVM_LINK_LIBRARIES}")
target_link_libraries(${PROJECT_NAME} ${JSONCPP_LIBRARIES})