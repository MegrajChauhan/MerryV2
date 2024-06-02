#include "merry_sharedmem.h"

mret_t merry_init_smem(MerrySMem *smem)
{
    smem->smem = _MERRY_MEM_GET_PAGE_SHARED_(_MERRY_SMEM_MAX_LEN_, _MERRY_PROT_DEFAULT_);
    if (smem->smem == _MERRY_RET_GET_ERROR_)
        return RET_FAILURE;
    smem->channel_begin = (mptr_t)smem->smem;
    smem->imem_begin = (mptr_t)(smem->smem + _MERRY_SMEM_IMEM_BEGIN_);
    smem->dmem_begin = (mptr_t)(smem->smem + _MERRY_SMEM_DMEM_BEGIN_);
    return RET_SUCCESS;
}

void merry_destroy_smem(MerrySMem *smem)
{
    _MERRY_MEM_GIVE_PAGE_(smem->smem, _MERRY_SMEM_MAX_LEN_);
}

mptr_t merry_salloc(MerrySMem *smem, msize_t size)
{
    mptr_t b = (mptr_t)(smem->channel_begin);
    smem->channel_begin = (mptr_t)((mbptr_t)(smem->channel_begin) + size);
    return b;
}
