#ifndef _MERRY_SMEM_
#define _MERRY_SMEM_

// This is the shared memory that each process is going to use

#include <merry_mem.h>
#include <merry_types.h>
#include <merry_utils.h>

typedef struct MerrySMem MerrySMem;

// Our limit is 2MB here
// This will provide more than enough space for all the necessary shared mem allocations

// We won't have much to worry about here
// Fragmentation may be a problem though
struct MerrySMem
{
    // We don't even need to make checks with these because they will never overlap
    mbptr_t smem; // the memory we got from the OS
    mptr_t channel_begin;
    mptr_t imem_begin;
    mptr_t dmem_begin;
};

#define _MERRY_SMEM_MAX_LEN_ 2097152
#define _MERRY_SMEM_IMEM_BEGIN_ 1048576
#define _MERRY_SMEM_DMEM_BEGIN_ _MERRY_SMEM_IMEM_BEGIN_ + 524288

mret_t merry_init_smem(MerrySMem *smem);

void merry_destroy_smem(MerrySMem *smem);

// for the channel allocations
mptr_t merry_salloc(MerrySMem *smem, msize_t size);

/*
 * Here is how the 2MB has been divided:
 * The first 1MB is for the channels.
 * Then 512KB is for the imem
 * Then 512KB is for the dmem.
 * All of this provides space that we may never even use.
 */

#endif