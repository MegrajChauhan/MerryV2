#ifndef _MERRY_REQUEST_
#define _MERRY_REQUEST_

#include <merry_thread.h>

typedef struct MerryOSRequest MerryOSRequest;
/*
 Each service that the OS provides has a Number and this request struct holds that number.
 When a core posts a request, it will have to stop execution totally and wait for it's request to be fulfilled.
 This is just not efficient as valuable time and resources are wasted. Unless we have a decoder and a way to implement Out of order execution without messing up,
 inefficiency is the key.
*/

struct MerryOSRequest
{
    msize_t request_number; // this is like the interrupt number
    MerryCond *_wait_lock;  // the requesting core's condition variable
    msize_t id;             // the core's id
};

enum
{
    // these error value ranges will change with time
    /*From 0 - 50 is for the error that the internal modules generate.*/
    /*51 - 150 for any program generated errors*/
    // any remaining for actual requests
    _REQ,
};

#endif