#ifndef _MERRY_DMEM_
#define _MERRY_DMEM_

#include <merry_types.h>
#include <merry_utils.h>
#include <merry_membase.h>
#include <merry_error.h>
#include <string.h>
#include <stdatomic.h>
#include <stdlib.h>

typedef struct MerryDMem MerryDMem;

struct MerryDMem
{
    MerryMemPage *pages;
    msize_t page_count;
    merrot_t error;
};

MerryDMem *merry_data_mem_init(msize_t page_count);

void merry_destroy_data_mem(MerryDMem *mem);

mret_t merry_dmemory_add_new_page(MerryDMem *memory);

// After receiving the pages, the dmem will manage it so freeing it is the job of dmem
MerryDMem *merry_data_mem_init_provided(MerryMemPage *pages, msize_t count);

mret_t merry_dmemory_read_byte(MerryDMem *memory, maddress_t address, mqptr_t _store_in);
mret_t merry_dmemory_read_byte_atm(MerryDMem *memory, maddress_t address, mqptr_t _store_in);
mret_t merry_dmemory_write_byte(MerryDMem *memory, maddress_t address, mqword_t _to_write);
mret_t merry_dmemory_write_byte_atm(MerryDMem *memory, maddress_t address, mqword_t _to_write);

mret_t merry_dmemory_read_word(MerryDMem *memory, maddress_t address, mqptr_t _store_in);
mret_t merry_dmemory_read_word_atm(MerryDMem *memory, maddress_t address, mqptr_t _store_in);
mret_t merry_dmemory_write_word(MerryDMem *memory, maddress_t address, mqword_t _to_write);
mret_t merry_dmemory_write_word_atm(MerryDMem *memory, maddress_t address, mqword_t _to_write);

mret_t merry_dmemory_read_dword(MerryDMem *memory, maddress_t address, mqptr_t _store_in);
mret_t merry_dmemory_read_dword_atm(MerryDMem *memory, maddress_t address, mqptr_t _store_in);
mret_t merry_dmemory_write_dword(MerryDMem *memory, maddress_t address, mqword_t _to_write);
mret_t merry_dmemory_write_dword_atm(MerryDMem *memory, maddress_t address, mqword_t _to_write);

mret_t merry_dmemory_read_qword(MerryDMem *memory, maddress_t address, mqptr_t _store_in);
mret_t merry_dmemory_read_qword_atm(MerryDMem *memory, maddress_t address, mqptr_t _store_in);
mret_t merry_dmemory_write_qword(MerryDMem *memory, maddress_t address, mqword_t _to_write);
mret_t merry_dmemory_write_qword_atm(MerryDMem *memory, maddress_t address, mqword_t _to_write);

mbptr_t merry_dmemory_get_byte_address(MerryDMem *memory, maddress_t address);
mbptr_t merry_dmemory_get_byte_address_bounds(MerryDMem *memory, maddress_t address, msize_t bound);

mwptr_t merry_dmemory_get_word_address(MerryDMem *memory, maddress_t address);
mwptr_t merry_dmemory_get_word_address_bounds(MerryDMem *memory, maddress_t address, msize_t bound);

mdptr_t merry_dmemory_get_dword_address(MerryDMem *memory, maddress_t address);
mdptr_t merry_dmemory_get_dword_address_bounds(MerryDMem *memory, maddress_t address, msize_t bound);

mqptr_t merry_dmemory_get_qword_address(MerryDMem *memory, maddress_t address);
mqptr_t merry_dmemory_get_qword_address_bounds(MerryDMem *memory, maddress_t address, msize_t bound);

mstr_t merry_dmemory_get_bytes_maybe_over_multiple_pages(MerryDMem *memory, maddress_t address, msize_t length);

mret_t merry_dmemory_write_bytes_maybe_over_multiple_pages(MerryDMem *memory, maddress_t address, msize_t length, mbptr_t array);

#endif