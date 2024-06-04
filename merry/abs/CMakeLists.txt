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

cmake_minimum_required(VERSION 3.28.2)

# The libraries to add from here
set(LIBS_TO_ADDA
    merry_thread.c
    merry_time.c
    merry_process.c
    merry_dynl.c
    merry_fio.c
    arithmetic.S
)

set(LIBS_NAMEA
    mthread
    mtime
    mprocess
    mdynl
    mfio
    marithmetic
)

list(LENGTH LIBS_TO_ADDA LIBS_TO_ADDA_LENGTH)
math(EXPR LIBS_TO_ADDA_LENGTH "${LIBS_TO_ADDA_LENGTH} - 1")

foreach(i RANGE ${LIBS_TO_ADDA_LENGTH})
    list(GET LIBS_TO_ADDA ${i} LIB_SRC)
    list(GET LIBS_NAMEA ${i} LIB_NAME)
    add_library(${LIB_NAME} ${LIB_SRC})
endforeach()

set_target_properties(marithmetic PROPERTIES LINKER_LANGUAGE ASM)

# Export variables to parent scope
set(ADDITIONAL_FILESA ${LIBS_NAMEA} PARENT_SCOPE)
