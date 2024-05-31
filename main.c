#include <stdio.h>
#include <stdlib.h>
#include <merry_stack.h>
#include <merry_thread.h>
#include <merry_console.h>
#include <merry_dmem.h>

mret_t test_stack()
{
    const msize_t len = 100;
    MerryStack *st = merry_init_stack(len, mtrue, 0, 10);
    if (st == NULL)
        return RET_FAILURE;
    for (int i = 0; i < len; ++i)
    {
        if (merry_stack_push(st, i) == RET_FAILURE)
        {
            merry_destroy_stack(st);
            return RET_FAILURE;
        }
    }
    for (int i = 0; i < len; ++i)
    {
        mqword_t val;
        if (merry_stack_pop(st, &val) == RET_FAILURE)
        {
            merry_destroy_stack(st);
            return RET_FAILURE;
        }
        if (val != len - i - 1)
        {
            merry_destroy_stack(st);
            return RET_FAILURE;
        }
        log("Popped %d\n", val);
    }
    merry_destroy_stack(st);
    return RET_SUCCESS;
}

int main()
{
    printf("Hello World!\n");
    if (test_stack() != RET_SUCCESS)
    {
        printf("Stack Test Failed\n");
        return 1;
    }
    printf("Stack Test Passed\n");
    return 0;
}

