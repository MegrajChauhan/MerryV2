#ifndef _MERRY_MMU_
#define _MERRY_MMU_

// Don't be fooled by the name.
// This is not a memory management unit.
// This is to create necessary structures that the different processes will use to communicate.
// This will keep track of channels that the processes will use to communicate
#include <merry_mem.h>
#include <merry_types.h>

typedef struct MerryChannel MerryChannel;
typedef struct MerryMMU MerryMMU;

#define _MERRY_CHANNEL_SIZE_ sizeof(MerryChannel)

struct MerryMMU
{
    mptr_t *pages;               // the pages we have mapped
    msize_t current_page_in_use; // the page currently in use
    msize_t page_count;          // the number of pages
    msize_t channel_count;       // the number of channels created
    mptr_t current_pos;          // the current position to use for another channel
};

struct MerryChannel
{
    msize_t request;
};

#endif