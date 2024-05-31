#include "merry_membase.h"

MerryMemPage *merry_get_new_page()
{
    MerryMemPage *pg = (MerryMemPage *)malloc(sizeof(MerryMemPage));
    if (pg == NULL)
        return RET_NULL;
    pg->is_full = mfalse;
    pg->offset = 0;
    return pg;
}

void merry_destroy_page(MerryMemPage *page)
{
    free(page);
}