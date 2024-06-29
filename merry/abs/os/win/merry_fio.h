#ifndef _MERRY_FIO_
#define _MERRY_FIO_

#include <merry_types.h>
#include <windows.h>
#include <merry_utils.h>
#include <io.h>

#define _MERRY_OPEN_READ_ _O_RDONLY
#define _MERRY_OPEN_WRITE_ _O_WRONLY
#define _MERRY_OPEN_READ_WRITE_ _O_RDWR
#define _MERRY_OPEN_APPEND_ _O_APPEND
#define _MERRY_OPEN_TRUNC_ _O_TRUNC // truncate
#define _MERRY_CREATE_NEW_ _O_CREAT

// Permissions for when creating a new file
#define _MERRY_PERMIT_READ_ _S_IREAD
#define _MERRY_PERMIT_WRITE_ _S_IWRITE


#define _MERRY_MODE_READ_ 0
#define _MERRY_MODE_WRITE 1     // If doesn't exist, create one
#define _MERRY_MODE_APPEND_ 2   // if doesn't exist, create one
#define _MERRY_MODE_TRUNCATE_ 3 // if doesn't exist, create one
#define _MERRY_MODE_READ_WRITE_ 4

/*
 Read as binary and write binary are just simply read and write but there are no intermediate conversions done on the data.
*/

// _fd must not be changed
mret_t merry_open_new_file(mstr_t filepath, msize_t mode, mqptr_t _fd);

void merry_close_file(mqptr_t _fd);

msize_t merry_read_from_file(mqptr_t _fd, mbptr_t _store_in, msize_t number_of_bytes);

msize_t merry_write_to_file(mqptr_t _fd, mbptr_t src, msize_t num_of_bytes);

// Seek to _off from relative_pos(or as said in the docs, "whence")
mret_t merry_seek_in_file(mqptr_t _fd, msize_t _off, msize_t relative_pos);

#endif