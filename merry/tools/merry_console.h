#ifndef _MERRY_CONSOLE_
#define _MERRY_CONSOLE_

#include <stdio.h>

#define err_log(msg, ...) fprintf(stderr, msg, __VA_ARGS__)
#define inerr_log(msg) err_log(msg, NULL)

#define log(msg, ...) fprintf(stdout, msg, __VA_ARGS__)
#define inlog(msg) log(msg, NULL)

#endif