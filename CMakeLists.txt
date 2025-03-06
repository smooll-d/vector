cmake_minimum_required(VERSION 3.30)

project(vector
        DESCRIPTION "Custom std::vector implementation"
        LANGUAGES CXX
)

option(VECTOR_SANITIZE "Build vector with -fsanitize=address flags" FALSE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_BUILD_TYPE RelWithDebugInfo)

file(GLOB_RECURSE exe_src FOLLOW_SYMLINKS LIST_DIRECTORIES TRUE CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*")

add_executable(${CMAKE_PROJECT_NAME} ${exe_src})

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
)

if (VECTOR_SANITIZE)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -fsanitize=address)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -fsanitize=address)
endif()
