#ifndef _MERRY_THPOOL_
#define _MERRY_THPOOL_

#include <merry_types.h>
#include <merry_utils.h>
#include <merry_thread.h>
#include <merry_time.h>
#include <stdlib.h>

typedef struct MerryThreadPool MerryThreadPool;
typedef struct MerryPoolThread MerryPoolThread;

struct MerryPoolThread
{
    MerryThread *thread;
    mbool_t is_busy;
    mbool_t should_stop;
    
};

struct MerryThreadPool
{
};

#endif