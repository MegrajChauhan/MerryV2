#ifndef _MERRY_MEMBASE_
#define _MERRY_MEMBASE_

// #include <merry_mem.h>
#include <merry_types.h>
#include <stdlib.h>

// Configurations for memory
#define _MERRY_MEMORY_ADDRESSES_PER_PAGE_ 1048576 // the number of addresses per page[Equal to 1MB]
#define _MERRY_MEMORY_QS_PER_PAGE_ 131072
#define _MERRY_MEMORY_GET_PAGE_OFFSET_(address) (address & 0xFFFFF) // get the offset from the address
#define _MERRY_MEMORY_GET_PAGE_(address) (address >> 20)            // get the page number from the address

// we currently have no limit set to how many pages Merry can have at max but lets leave it to the OS
#define _MERRY_MEMORY_GENERATE_ADDRESS_(page, offset) ((page << 20) & offset) // generate an address

// the memory follows the same endianness as the host system
#define _MERRY_MEMORY_BYTE_ORDER_ _MERRY_BYTE_ORDER_
#define _MERRY_MEMORY_IS_ACCESS_ERROR_(offset) ((offset + 7) >= _MERRY_MEMORY_ADDRESSES_PER_PAGE_)
#define _MERRY_STACKMEM_BYTE_LEN_ _MERRY_MEMORY_ADDRESSES_PER_PAGE_
#define _MERRY_STACKMEM_SIZE_ 131072 // this is the number of qwords and not the bytes[equals 1MB]

#define _MERRY_MAX_ADDRESS_ 131071

// #define _MERRY_MEM_PGALLOC_MAP_PAGE_ _MERRY_MEM_GET_PAGE_(_MERRY_MEMORY_ADDRESSES_PER_PAGE_, _MERRY_PROT_DEFAULT_, _MERRY_FLAG_DEFAULT_)
// #define _MERRY_MEM_PGALLOC_UNMAP_PAGE_(address) _MERRY_MEM_GIVE_PAGE_(address, _MERRY_MEMORY_ADDRESSES_PER_PAGE_)

#define _MERRY_MEM_DEDUCE_ADDRESS_(addr)                                                                        \
    {                                                                                                           \
        .page = addr / _MERRY_MEMORY_ADDRESSES_PER_PAGE_, .offset = address % _MERRY_MEMORY_ADDRESSES_PER_PAGE_ \
    }

typedef struct MerryMemPage MerryMemPage;
typedef struct MerryAddress MerryAddress;

struct MerryMemPage
{
    union
    {
        mbyte_t byte[_MERRY_MEMORY_ADDRESSES_PER_PAGE_];
        mqword_t qword[_MERRY_MEMORY_ADDRESSES_PER_PAGE_ / 8];
    } page;
    mbool_t is_full; // is the page full?
    msize_t offset;  // if not full, what is the current offset[Index]?
    // add more flags as necessary
};

struct MerryAddress
{
    msize_t page;
    msize_t offset;
};

MerryMemPage *merry_get_new_page();

void merry_destroy_page(MerryMemPage *page);

#endif
