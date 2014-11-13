cmake_minimum_required(VERSION 2.6)
project(smic)

set(SOURCES main.cpp)
set(SUB_DIRS linear_assignement forward_backward model_to_real)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include("CMakeLists.shared")

subdirs(${SUB_DIRS})

include_directories(linear_assignement/include)
include_directories(forward_backward/include)
include_directories(model_to_real/include)

add_executable(${PROJECT_NAME} ${SOURCES} ${SHARED_SOURCES})
target_link_libraries(${PROJECT_NAME} ${SHARED_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SUB_DIRS})
