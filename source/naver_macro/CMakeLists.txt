cmake_minimum_required(VERSION 3.16)

project(navermacro C CXX)

# set(CMAKE_CXX_STANDARD 11)91#9G5
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcurl")

find_package (CURL REQUIRED)

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.h")

IF (CURL_FOUND)
    add_library(${PROJECT_NAME} ${srcs})
    include_directories(
            ${CURL_INCLUDE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/../xthread
            ${CMAKE_CURRENT_SOURCE_DIR}/../util
    )
    target_link_libraries(navermacro ${CURL_LIBRARIES})
    install(TARGETS ${PROJECT_NAME} DESTINATION lib)
    install(FILES ${hdrs} DESTINATION include)
endif ()




