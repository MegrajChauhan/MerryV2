#ifndef _MERRY_MMU_
#define _MERRY_MMU_

// Don't be fooled by the name.
// This is not a memory management unit.
// This is to create necessary structures that the different processes will use to communicate.
// This will keep track of channels that the processes will use to communicate
#include <merry_mem.h>
#include <merry_types.h>

// typedef struct MerryChannel MerryChannel;
// typedef struct MerryMMU MerryMMU;

// #define _MERRY_CHANNEL_SIZE_ sizeof(MerryChannel)
// #define _MERRY_MMU_PAGE_SIZE_ 1048576

// // The amount of channels we can create with the following already far exceeds what the Host OS and the hardware is capable of
// // The VM will be forcefully terminated before even doing any harm

// struct MerryMMU
// {
//     // I doubt we will ever need that much memory
//     mbptr_t pages[5];             // the pages we have mapped
//     msize_t current_page_in_use; // the page currently in use
//     msize_t page_count;          // the number of pages
//     msize_t channel_count;       // the number of channels created
//     msize_t current_pos;         // the current position to use for another channel
// };

// struct MerryChannel
// {
//     msize_t received_sig; // the received signal(The master OS will use this to send messages)
//     msize_t request_sig;  // the request signal(The slave OS will send messages through here)
// };

// static MerryMMU mmu;

// // Get initialize it with 1 page
// mret_t merry_init_mmu();

// void merry_destroy_mmu();

// MerryChannel *merry_allocate_new_channel();

// We don't need to free any channels

#endif