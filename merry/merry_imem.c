#include "merry_imem.h"

MerryIMem *merry_inst_mem_init(msize_t page_count)
{
    MerryIMem *imem = (MerryIMem *)malloc(sizeof(MerryIMem));
    if (imem == NULL)
        return NULL;
    imem->pages = (MerryMemPage *)malloc(sizeof(MerryMemPage) * page_count);
    for (msize_t i = 0; i < page_count; i++)
    {
        imem->pages[i].is_full = mfalse;
        imem->pages[i].offset = 0;
    }
    imem->page_count = page_count;
    return imem;
}

void merry_destroy_inst_mem(MerryIMem *mem)
{
    if (mem == NULL)
        return;
    free(mem->pages);
    free(mem);
}

MerryIMem *merry_inst_mem_init_provided(MerryMemPage *pages, msize_t count)
{
    MerryIMem *imem = (MerryIMem *)malloc(sizeof(MerryIMem));
    if (imem == NULL)
        return NULL;
    imem->pages = pages;
    imem->page_count = count;
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
    *store_in = imem->pages[addr.page].page.qword[addr.offset];
    return RET_SUCCESS;
}

mret_t merry_imemory_add_new_page(MerryIMem *memory)
{
    MerryMemPage *temp = memory->pages;
    if ((memory->pages = (MerryMemPage *)realloc(memory->pages, sizeof(MerryMemPage) * (memory->page_count + 1))) == NULL)
    {
        memory->pages = temp;
        return RET_FAILURE;
    }
    memory->pages[memory->page_count].is_full = mfalse;
    memory->pages[memory->page_count].offset = 0;
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
    imem->pages[addr.page].page.qword[addr.offset] = _to_write;
    return RET_SUCCESS;
}