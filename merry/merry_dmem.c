#include "merry_dmem.h"

mret_t merry_data_mem_init(MerryDMem *dmem, msize_t page_count, mptr_t *ptr)
{
    dmem->pages = (mbptr_t)ptr;
    dmem->page_count = page_count;
    return RET_SUCCESS;
}

mret_t merry_dmemory_add_new_page(MerryDMem *memory)
{
    memory->page_count++;
    return RET_SUCCESS;
}

mret_t merry_dmemory_read_byte(MerryDMem *memory, maddress_t address, mqptr_t _store_in)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *_store_in = memory->pages[addr.page][addr.offset];
    return RET_SUCCESS;
}

mret_t merry_dmemory_read_byte_atm(MerryDMem *memory, maddress_t address, mqptr_t _store_in)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *_store_in = atomic_load(&memory->pages[addr.page][addr.offset]);
    return RET_SUCCESS;
}

mret_t merry_dmemory_write_byte(MerryDMem *memory, maddress_t address, mqword_t _to_write)
{
    // pretty much the same as read
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    memory->pages[addr.page][addr.offset] = _to_write;
    return RET_SUCCESS;
}

mret_t merry_dmemory_write_byte_atm(MerryDMem *memory, maddress_t address, mqword_t _to_write)
{
    // pretty much the same as read
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    atomic_store(&memory->pages[addr.page][addr.offset], _to_write & 0xFF);
    return RET_SUCCESS;
}

mret_t merry_dmemory_read_word(MerryDMem *memory, maddress_t address, mqptr_t _store_in)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    // The byte that the address points to is the lower byte while the next byte is the
    if (surelyF((addr.offset + 1) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *_store_in = *((mwptr_t)(memory->pages[addr.page] + addr.offset));
    return RET_SUCCESS;
}

mret_t merry_dmemory_read_word_atm(MerryDMem *memory, maddress_t address, mqptr_t _store_in)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    // The byte that the address points to is the lower byte while the next byte is the
    if (surelyF((addr.offset + 1) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *_store_in = (mqword_t)atomic_load(((mwptr_t)(memory->pages[addr.page] + addr.offset)));
    return RET_SUCCESS;
}

mret_t merry_dmemory_write_word(MerryDMem *memory, maddress_t address, mqword_t _to_write)
{
    // pretty much the same as read
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    if (surelyF((addr.offset + 1) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *((mwptr_t)(memory->pages[addr.page] + addr.offset)) = _to_write & 0xFFFF;
    return RET_SUCCESS;
}

mret_t merry_dmemory_write_word_atm(MerryDMem *memory, maddress_t address, mqword_t _to_write)
{
    // pretty much the same as read
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    if (surelyF((addr.offset + 1) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    atomic_store((mwptr_t)(memory->pages[addr.page] + addr.offset), _to_write & 0xFFFF);
    return RET_SUCCESS;
}

mret_t merry_dmemory_read_dword(MerryDMem *memory, maddress_t address, mqptr_t _store_in)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    // The byte that the address points to is the lower byte while the next byte is the
    if (surelyF((addr.offset + 3) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *_store_in = *((mdptr_t)(memory->pages[addr.page] + addr.offset));
    return RET_SUCCESS;
}

mret_t merry_dmemory_read_dword_atm(MerryDMem *memory, maddress_t address, mqptr_t _store_in)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    // The byte that the address points to is the lower byte while the next byte is the
    if (surelyF((addr.offset + 3) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *_store_in = (mqword_t)atomic_load((mdptr_t)(memory->pages[addr.page] + addr.offset));
    return RET_SUCCESS;
}

mret_t merry_dmemory_write_dword(MerryDMem *memory, maddress_t address, mqword_t _to_write)
{
    // pretty much the same as read
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    if (surelyF((addr.offset + 3) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *((mdptr_t)(memory->pages[addr.page] + addr.offset)) = _to_write & 0xFFFFFFFF;
    return RET_SUCCESS;
}

mret_t merry_dmemory_write_dword_atm(MerryDMem *memory, maddress_t address, mqword_t _to_write)
{
    // pretty much the same as read
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    if (surelyF((addr.offset + 3) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    atomic_store((mdptr_t)(memory->pages[addr.page] + addr.offset), _to_write & 0xFFFFFFFF);
    return RET_SUCCESS;
}

mret_t merry_dmemory_read_qword(MerryDMem *memory, maddress_t address, mqptr_t _store_in)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    // The byte that the address points to is the lower byte while the next byte is the
    if (surelyF((addr.offset + 7) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *_store_in = *((mqptr_t)(memory->pages[addr.page] + addr.offset));
    return RET_SUCCESS;
}

mret_t merry_dmemory_read_qword_atm(MerryDMem *memory, maddress_t address, mqptr_t _store_in)
{
    // get the actual address and the page
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    // The byte that the address points to is the lower byte while the next byte is the
    if (surelyF((addr.offset + 7) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *_store_in = atomic_load((mqptr_t)(memory->pages[addr.page] + addr.offset));
    return RET_SUCCESS;
}

mret_t merry_dmemory_write_qword(MerryDMem *memory, maddress_t address, mqword_t _to_write)
{
    // pretty much the same as read
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    if (surelyF((addr.offset + 7) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    *((mqptr_t)(memory->pages[addr.page] + addr.offset)) = _to_write;
    return RET_SUCCESS;
}

mret_t merry_dmemory_write_qword_atm(MerryDMem *memory, maddress_t address, mqword_t _to_write)
{
    // pretty much the same as read
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    if (surelyF((addr.offset + 7) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    atomic_store((mqptr_t)(memory->pages[addr.page] + addr.offset), _to_write);
    return RET_SUCCESS;
}

mbptr_t merry_dmemory_get_byte_address(MerryDMem *memory, maddress_t address)
{
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    // this just basically returns an actual address to the address that the manager can use
    return &memory->pages[addr.page][addr.offset];
}

mbptr_t merry_dmemory_get_byte_address_bounds(MerryDMem *memory, maddress_t address, msize_t bound)
{
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    if (surelyF((addr.offset + bound) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    // this just basically returns an actual address to the address that the manager can use
    return &memory->pages[addr.page][addr.offset];
}

mwptr_t merry_dmemory_get_word_address(MerryDMem *memory, maddress_t address)
{
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    // this just basically returns an actual address to the address that the manager can use
    return (mwptr_t)(memory->pages[addr.page] + addr.offset);
}

// here bound is bound*2 bytes
mwptr_t merry_dmemory_get_word_address_bounds(MerryDMem *memory, maddress_t address, msize_t bound)
{
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    if (surelyF((addr.offset + bound * 2) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    // this just basically returns an actual address to the address that the manager can use
    return (mwptr_t)(memory->pages[addr.page] + addr.offset);
}

mdptr_t merry_dmemory_get_dword_address(MerryDMem *memory, maddress_t address)
{
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    // this just basically returns an actual address to the address that the manager can use
    return (mdptr_t)(memory->pages[addr.page] + addr.offset);
}

// here bound is bound*4 bytes
mdptr_t merry_dmemory_get_dword_address_bounds(MerryDMem *memory, maddress_t address, msize_t bound)
{
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    if (surelyF((addr.offset + bound * 4) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    // this just basically returns an actual address to the address that the manager can use
    return (mdptr_t)(memory->pages[addr.page] + addr.offset);
}

mqptr_t merry_dmemory_get_qword_address(MerryDMem *memory, maddress_t address)
{
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    // this just basically returns an actual address to the address that the manager can use
    return (mqptr_t)(memory->pages[addr.page] + addr.offset);
}

// here bound is bound*8 bytes
mqptr_t merry_dmemory_get_qword_address_bounds(MerryDMem *memory, maddress_t address, msize_t bound)
{
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    if (surelyF((addr.offset + bound * 8) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    // this just basically returns an actual address to the address that the manager can use
    return (mqptr_t)(memory->pages[addr.page] + addr.offset);
}

mstr_t merry_dmemory_get_bytes_maybe_over_multiple_pages(MerryDMem *memory, maddress_t address, msize_t length)
{
    mstr_t array = (mstr_t)malloc(length + 1);
    mstr_t curr = array;
    if (array == NULL)
        return RET_NULL;
    array[length] = '\0';
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        // this implies the request is for a page that doesn't exist
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_NULL;
    }
    msize_t dist_from_end = _MERRY_MEMORY_ADDRESSES_PER_PAGE_ - addr.offset;
    if (dist_from_end > length)
    {
        // the entire array is in this page only
        // simply copy the memory
        memcpy(array, memory->pages[addr.page] + addr.offset, length);
        return array; // we are entrusting the stdlib to not fail as this should not fail
    }
    else
    {
        // the array is in multiple pages
        // first copy whatever part is in this page
        curr += dist_from_end;
        memcpy(array, memory->pages[addr.page] + addr.offset, dist_from_end);
        length -= dist_from_end;
        // now until we copy everything, keep doing it
        register msize_t no_of_pages = length / _MERRY_MEMORY_ADDRESSES_PER_PAGE_;
        register msize_t remaining = length % _MERRY_MEMORY_ADDRESSES_PER_PAGE_;
        if ((addr.page + no_of_pages + (remaining > 0 ? 1 : 0)) >= memory->page_count)
        {
            memory->error = MERRY_MEM_INVALID_ACCESS;
            free(array);
            return RET_NULL;
        }
        addr.page++;
        for (msize_t i = 0; i < no_of_pages; i++, addr.page++)
        {
            memcpy(curr, memory->pages[addr.page], _MERRY_MEMORY_ADDRESSES_PER_PAGE_);
            curr += _MERRY_MEMORY_ADDRESSES_PER_PAGE_;
        }
        if (remaining > 0)
        {
            // addr.page will be correctly pointed
            memcpy(curr, memory->pages[addr.page], remaining);
        }
    }
    return array;
}

mret_t merry_dmemory_write_bytes_maybe_over_multiple_pages(MerryDMem *memory, maddress_t address, msize_t length, mbptr_t array)
{
    // Exact opposite of the above
    if (array == NULL)
        return RET_SUCCESS;
    mbptr_t curr = array;
    register MerryAddress addr = _MERRY_MEM_DEDUCE_ADDRESS_(address);
    if (surelyF(addr.page >= memory->page_count))
    {
        memory->error = MERRY_MEM_INVALID_ACCESS;
        return RET_FAILURE;
    }
    msize_t dist_from_end = _MERRY_MEMORY_ADDRESSES_PER_PAGE_ - addr.offset;
    if (dist_from_end > length)
    {
        memcpy(memory->pages[addr.page] + addr.offset, array, length);
        return RET_SUCCESS; // we are entrusting the stdlib to not fail as this should not fail
    }
    else
    {
        curr += dist_from_end;
        memcpy(memory->pages[addr.page] + addr.offset, array, dist_from_end);
        length -= dist_from_end;
        // now until we copy everything, keep doing it
        register msize_t no_of_pages = length / _MERRY_MEMORY_ADDRESSES_PER_PAGE_;
        register msize_t remaining = length % _MERRY_MEMORY_ADDRESSES_PER_PAGE_;
        if ((addr.page + no_of_pages + (remaining > 0 ? 1 : 0)) >= memory->page_count)
        {
            memory->error = MERRY_MEM_INVALID_ACCESS;
            return RET_FAILURE;
        }
        addr.page++;
        for (msize_t i = 0; i < no_of_pages; i++, addr.page++)
        {
            memcpy(memory->pages[addr.page], curr, _MERRY_MEMORY_ADDRESSES_PER_PAGE_);
            curr += _MERRY_MEMORY_ADDRESSES_PER_PAGE_;
        }
        if (remaining > 0)
        {
            // addr.page will be correctly pointed
            memcpy(memory->pages[addr.page], curr, remaining);
        }
    }
    return RET_SUCCESS;
}
