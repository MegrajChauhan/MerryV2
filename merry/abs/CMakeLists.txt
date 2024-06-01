cmake_minimum_required(VERSION 3.28.2)

# The libraries to add from here
set(LIBS_TO_ADDA
    merry_thread.c
    merry_time.c
    merry_process.c
)

set(LIBS_NAMEA
    mthread
    mtime
    mprocess
)

list(LENGTH LIBS_TO_ADDA LIBS_TO_ADDA_LENGTH)
math(EXPR LIBS_TO_ADDA_LENGTH "${LIBS_TO_ADDA_LENGTH} - 1")

foreach(i RANGE ${LIBS_TO_ADDA_LENGTH})
    list(GET LIBS_TO_ADDA ${i} LIB_SRC)
    list(GET LIBS_NAMEA ${i} LIB_NAME)
    add_library(${LIB_NAME} ${LIB_SRC})
endforeach()

# Export variables to parent scope
set(ADDITIONAL_FILESA ${LIBS_NAMEA} PARENT_SCOPE)
