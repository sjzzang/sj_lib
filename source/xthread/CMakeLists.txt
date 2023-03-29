cmake_minimum_required(VERSION 3.16)

project(xthread C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.h")

add_library(${PROJECT_NAME} ${srcs})

target_compile_options(${PROJECT_NAME} PUBLIC "-lpthread")

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${hdrs} DESTINATION include)