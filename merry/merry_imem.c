#include "merry_imem.h"

mret_t merry_inst_mem_init(MerryIMem *imem, mptr_t *ptr, msize_t page_count)
{
    imem->pages = (mqptr_t)ptr;
    imem->page_count = page_count;
    return imem;
}

mret_t merry_imem_read_inst(MerryIMem *imem, maddress_t address, mqptr_t store_in)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= imem->page_count))
    {
        // this implies the request is for a page that doesn't exist
        imem->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *store_in = imem->pages[addr.page][addr.offset];
    return RET_SUCCESS;
}

mret_t merry_imemory_add_new_page(MerryIMem *memory)
{
    memory->page_count++;
    return RET_SUCCESS;
}

mret_t merry_imem_write_inst(MerryIMem *imem, maddress_t address, mqword_t _to_write)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= imem->page_count))
    {
        // this implies the request is for a page that doesn't exist
        imem->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    imem->pages[addr.page][addr.offset] = _to_write;
    return RET_SUCCESS;
}