#include "merry_mmu.h"

// mret_t merry_init_mmu()
// {
//     // mmu.pages = (mqptr_t*)
//     mmu.current_page_in_use = 0;
//     mmu.current_pos = 0;
//     mmu.channel_count = 0;
//     mmu.pages[0] = _MERRY_MEM_GET_PAGE_SHARED_(_MERRY_MMU_PAGE_SIZE_, _MERRY_PROT_DEFAULT_);
//     if (mmu.pages[0] == _MERRY_RET_GET_ERROR_)
//         return RET_FAILURE;
//     mmu.page_count = 1;
//     return RET_SUCCESS;
// }

// void merry_destroy_mmu()
// {
//     for (msize_t i = 0; i < mmu.page_count; i++)
//     {
//         _MERRY_MEM_GIVE_PAGE_(mmu.pages[i], _MERRY_MMU_PAGE_SIZE_);
//     }
// }

// // Highly unlikely that we will ever use this function
// mret_t merry_mmu_get_new_page()
// {
//     mmu.pages[mmu.page_count] = _MERRY_MEM_GET_PAGE_SHARED_(_MERRY_MMU_PAGE_SIZE_, _MERRY_PROT_DEFAULT_);
//     if (mmu.pages[mmu.page_count] == _MERRY_RET_GET_ERROR_)
//         return RET_FAILURE;
//     mmu.current_page_in_use = mmu.page_count;
//     mmu.current_pos = 0;
//     mmu.page_count++;
//     return RET_SUCCESS;
// }

// MerryChannel *merry_allocate_new_channel()
// {
//     if (mmu.current_pos >= _MERRY_MMU_PAGE_SIZE_ || (mmu.current_pos + _MERRY_CHANNEL_SIZE_) > _MERRY_MMU_PAGE_SIZE_)
//     {
//         // We need another page
//         if (merry_mmu_get_new_page() == RET_FAILURE)
//             return RET_NULL;
//     }
//     MerryChannel *c = (MerryChannel *)(mmu.pages[mmu.current_page_in_use] + mmu.current_pos);
//     c->received_sig = 0;
//     c->request_sig = 0;
//     mmu.current_pos += _MERRY_CHANNEL_SIZE_;
//     mmu.channel_count++;
//     return c;
// }