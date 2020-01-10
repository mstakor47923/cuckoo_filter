
cmake_minimum_required(VERSION 3.1)

project(Cuckoo_Filter)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

set (CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(cuckoo_filter ${SOURCES})

target_compile_features(cuckoo_filter PRIVATE cxx_range_for)