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

add_subdirectory(abs)

# The libraries to add from here
set(LIBS_TO_ADDM
    merry_errno.c
    merry_stack.c
    merry_request_queue.c
    merry_request_hdlr.c
    merry_dmemory.c
    merry_memory.c
    merry_nreader.c
    merry_core.c
    merry_os.c
    merry.c
)

set(LIBS_NAMEM
    merrno
    mstack
    mreqqueue
    mreqhdlr
    mdmem
    mimem
    mnreader
    mcore
    mos
    mclo
)

list(LENGTH LIBS_TO_ADDM LIBS_TO_ADDM_LENGTH)
math(EXPR LIBS_TO_ADDM_LENGTH "${LIBS_TO_ADDM_LENGTH} - 1")

foreach(i RANGE ${LIBS_TO_ADDM_LENGTH})
    list(GET LIBS_TO_ADDM ${i} LIB_SRC)
    list(GET LIBS_NAMEM ${i} LIB_NAME)
    add_library(${LIB_NAME} ${LIB_SRC})
endforeach()

# Specify some targets
target_link_libraries(mos PUBLIC mimem mdmem mcore mnreader mreqhdlr)
target_link_libraries(mcore PUBLIC mimem mdmem mreqhdlr marithmetic mstack)
target_link_libraries(mreqhdlr PUBLIC mreqqueue)

set(ADDITIONAL_FILESM ${LIBS_NAMEM} PARENT_SCOPE)
set(ADDITIONAL_FILESA ${ADDITIONAL_FILESA} PARENT_SCOPE)