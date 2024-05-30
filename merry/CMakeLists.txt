cmake_minimum_required(VERSION 3.28.2)

add_subdirectory(abs)

# The libraries to add from here
set(LIBS_TO_ADDM
    merry_errno.c
    merry_stack.c
)

set(LIBS_NAMEM
    merrno
    mstack
)

list(LENGTH LIBS_TO_ADDM LIBS_TO_ADDM_LENGTH)
math(EXPR LIBS_TO_ADDM_LENGTH "${LIBS_TO_ADDM_LENGTH} - 1")

foreach(i RANGE ${LIBS_TO_ADDM_LENGTH})
    list(GET LIBS_TO_ADDM ${i} LIB_SRC)
    list(GET LIBS_NAMEM ${i} LIB_NAME)
    add_library(${LIB_NAME} ${LIB_SRC})
endforeach()

# Add the include directories to the project
include_directories(${IncludeDirs})

set(ADDITIONAL_FILESM ${LIBS_NAMEM} PARENT_SCOPE)
set(ADDITIONAL_FILESA ${ADDITIONAL_FILESA} PARENT_SCOPE)