#include <stdio.h>
#include <stdlib.h>
#include <merry_stack.h>
#include <merry_thread.h>
#include <merry_console.h>
#include <merry_dmem.h>
#include <merry_imem.h>
#include <merry_time.h>

mret_t test_dmem()
{
    MerryDMem *dmem = merry_data_mem_init(2);
    if (dmem == RET_NULL)
        return RET_FAILURE;
    if (merry_dmemory_write_byte(dmem, 900000, 123) == RET_FAILURE)
        goto failed;
    if (merry_dmemory_write_qword(dmem, 1700778, 0xABCDEF012345BABA) == RET_FAILURE)
        goto failed;
    mqword_t read;
    if (merry_dmemory_read_byte(dmem, 900000, &read) == RET_FAILURE)
        goto failed;
    printf("Read byte: %llu\n", read);
    if (merry_dmemory_read_word(dmem, 900000, &read) == RET_FAILURE)
        goto failed;
    printf("Read word: %llu\n", read);
    if (merry_dmemory_read_word(dmem, 899999, &read) == RET_FAILURE)
        goto failed;
    printf("Read word: %lX\n", read);
    if (merry_dmemory_read_qword(dmem, 1700778, &read) == RET_FAILURE)
        goto failed;
    printf("Read qword: %lX\n", read);
    if (merry_dmemory_read_byte(dmem, 1700778, &read) == RET_FAILURE)
        goto failed;
    printf("Read byte: %lX\n", read);
    if (merry_dmemory_read_dword(dmem, 1700778, &read) == RET_FAILURE)
        goto failed;
    printf("Read dword: %lX\n", read);
    merry_destroy_data_mem(dmem);
    return RET_SUCCESS;
failed:
    merry_destroy_data_mem(dmem);
    return RET_FAILURE;
}

mret_t test_imem()
{
    MerryIMem *imem = merry_inst_mem_init(2);
    if (imem == RET_NULL)
        return RET_FAILURE;
    if (merry_imemory_add_new_page(imem) == RET_FAILURE)
        goto failed;
    if (merry_imem_write_inst(imem, 1000, 0xABCDEF012345BABA) == RET_FAILURE)
        goto failed;
    mqword_t read;
    if (merry_imem_read_inst(imem, 0, &read) == RET_FAILURE)
        goto failed;
    printf("Read inst: %lX\n", read);
    if (merry_imem_read_inst(imem, 1000, &read) == RET_FAILURE)
        goto failed;
    printf("Read inst: %lX\n", read);
    merry_destroy_inst_mem(imem);
    return RET_SUCCESS;
failed:
    merry_destroy_inst_mem(imem);
    return RET_FAILURE;
}

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
    MerryTime t;
    merry_get_time(&t);
    if (test_stack() != RET_SUCCESS)
    {
        printf("Stack Test Failed\n");
        return 1;
    }
    printf("Stack Test Passed\n");
    if (test_dmem() != RET_SUCCESS)
    {
        printf("Data memory test Failed\n");
        return 1;
    }
    printf("Data Memory Test Passed\n");
    if (test_imem() != RET_SUCCESS)
    {
        printf("Instruction memory test Failed\n");
        return 1;
    }
    printf("Instruction Memory Test Passed\n");
    merry_sleep(1);
    t = merry_get_time_difference_from(&t);
    printf("Time taken: %d and %d\n", t.seconds, t.microseconds);
    return 0;
}
