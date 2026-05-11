cmake_minimum_required(VERSION 4.3.1)

project(bfc)

# Set C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.h
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/headers/*.h
)

add_executable(bfc ${SOURCES} ${HEADERS})

target_include_directories(bfc PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
)