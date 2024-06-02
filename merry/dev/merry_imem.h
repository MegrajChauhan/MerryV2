#ifndef _MERRY_IMEM_
#define _MERRY_IMEM_

#include <merry_types.h>
#include <merry_utils.h>
#include <merry_membase.h>
#include <merry_error.h>
#include <string.h>
#include <stdlib.h>

typedef struct MerryIMem MerryIMem;

struct MerryIMem
{
    mqptr_t *pages;
    msize_t page_count;
    merrot_t error;
};

mret_t merry_inst_mem_init(MerryIMem *imem, mptr_t *ptr, msize_t page_count);

mret_t merry_imemory_add_new_page(MerryIMem *memory);

// Since this is the instruction memory, we don't need things like read_byte, read_word, read_dword etc All we need is one function to read one 8-byte instruction
mret_t merry_imem_read_inst(MerryIMem *imem, maddress_t address, mqptr_t store_in);

mret_t merry_imem_write_inst(MerryIMem *imem, maddress_t address, mqword_t to_write);

#endif