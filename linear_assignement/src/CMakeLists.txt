cmake_minimum_required(VERSION 3.0)

set(LIB_NAME linear_assignement)

set(SRC linear_assignement_solver.cpp)

set(C_FLAGS -std=c++11)

include_directories(${PROJECT_SOURCE_DIR}/${LIB_NAME}/include)

# Compiler flags
add_definitions(${C_FLAGS})

add_library(${LIB_NAME} ${SRC})
