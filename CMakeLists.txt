cmake_minimum_required(VERSION 3.22)

project(
        hello_world
        VERSION 0.1.0
        LANGUAGES CXX
)

option(SANITIZER "Enable sanitizer build" OFF)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

if (SANITIZER)
    message(STATUS "Building with sanitizer: ${SANITIZER}")
    if (SANITIZER STREQUAL "asan")
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    elseif (SANITIZER STREQUAL "ubsan")
        add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer)
        add_link_options(-fsanitize=undefined)
    elseif (SANITIZER STREQUAL "tsan")
        add_compile_options(-fsanitize=thread -fno-omit-frame-pointer)
        add_link_options(-fsanitize=thread)
    else()
        message(FATAL_ERROR "Unknown sanitizer: ${SANITIZER}")
    endif()
endif()

if (ENABLE_COVERAGE)
    message(STATUS "Building with coverage enabled")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

# ---- Main library ----
add_library(hello_world_lib src/addition.cpp)
target_include_directories(hello_world_lib PUBLIC src)

# ---- Main executable ----
add_executable(hello_world src/main.cpp)
target_link_libraries(hello_world PRIVATE hello_world_lib)

# ---- Dependencies ----
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---- Tests ----
add_subdirectory(tests)
