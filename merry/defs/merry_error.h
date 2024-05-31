#ifndef _MERRY_ERRORS_
#define _MERRY_ERRORS_

// this includes all of the internal errors that may be produced

/*The call depth will be set according to how much the stack can handle*/
enum
{
    MERRY_ERROR_NONE,
    _PANIC_REQBUFFEROVERFLOW = 1,
    MERRY_MEM_ACCESS_ERROR = 51,   // accessing the memory in a wrong way
    MERRY_MEM_INVALID_ACCESS,      // indicating memory access for memory addresses that either do not exist or are invalid
    MERRY_DIV_BY_ZERO,             // dividing by zero
    MERRY_STACK_OVERFLOW,          // stack is overflowing
    MERRY_STACK_UNDERFLOW,         // the stack has less than expected number of values
    MERRY_CALL_DEPTH_REACHED,      // reached the limit of function calls
    MERRY_INVALID_RETURN,          // invalid return instruction
    MERRY_INVALID_VARIABLE_ACCESS, // accessing variable in the wrong way on the stack
    MERRY_DYNL_FAILED,             // failed to load library
    MERRY_DYNCALL_FAILED,          // failed to make a function call
    MERRY_FILEHANDLE_NULL,         // performing operations on a NULL file
    MERRY_INTERNAL_ERROR,          // this error occured such that the requester is unable to deduce the cause
};

#endif