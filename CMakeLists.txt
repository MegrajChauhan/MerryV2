# 
# MIT License
# 
# Copyright (c) 2024 MegrajChauhan
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE. 

# This is a novice's attempt at making use of CMake
# Feel free to make changes to suit your needs
cmake_minimum_required(VERSION 3.28.2)
project(mvm C ASM)

enable_language(ASM)

# set(CMAKE_VERBOSE_MAKEFILE ON)

# Check for the system's bus length
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "Merry requires a 64-bit operating system to run.")
endif()

if(MSVC)
    message(FATAL_ERROR "Please use gcc or clang.")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "debug")
    add_compile_options(-Wextra -Wall -g)
else()
    add_compile_options(-Wextra -Wall -O3)
endif()


# Setting up build directory
# Ensure all output directories are set correctly
set(OutputDir "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OutputDir}/${CMAKE_BUILD_TYPE}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OutputDir}/${CMAKE_BUILD_TYPE}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OutputDir}/${CMAKE_BUILD_TYPE}/libs)


# Include directories
# Check for platform and set platform-specific include directories
if(WIN32)
    set(PlatFormIncludeDirs
        merry/abs/hard/win
        merry/abs/os/win
    )
elseif(LINUX)
    set(PlatFormIncludeDirs
        merry/abs/hard/linux
        merry/abs/os/linux
    )
endif()

# Set common include directories and include platform-specific directories
set(IncludeDirs
    utils
    merry/core
    merry/defs
    merry/dev
    merry/os
    merry/tools
    ${PlatFormIncludeDirs}
)

include_directories(${IncludeDirs})

# The libraries to add
# set(LIBS_TO_ADD
# )

set(LIBS_NAME
)

# list(LENGTH LIBS_TO_ADD LIBS_TO_ADD_LENGTH)
# math(EXPR LIBS_TO_ADD_LENGTH "${LIBS_TO_ADD_LENGTH} - 1")

# foreach(i RANGE ${LIBS_TO_ADD_LENGTH})
#     list(GET LIBS_TO_ADD ${i} LIB_SRC)
#     list(GET LIBS_NAME ${i} LIB_NAME)
#     add_library(${LIB_NAME} ${LIB_SRC})
# endforeach()

# Add subdirectories
add_subdirectory(merry)

# Add executable
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ${LIBS_NAME} ${ADDITIONAL_FILESM} ${ADDITIONAL_FILESA})

