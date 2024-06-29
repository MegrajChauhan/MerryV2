/*
 * The omnipotent being of the Merry VM
 * MIT License
 *
 * Copyright (c) 2024 MegrajChauhan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef _MERRY_OS_
#define _MERRY_OS_

// This module is the backbone of the VM and controls everything

#include <merry_config.h>
#include <merry_types.h>
#include <merry_utils.h>
#include <merry_nreader.h>
#include <merry_dynl.h>
#include <merry_fio.h>
#include <merry_dmemory.h>
#include <merry_memory.h>
#include <merry_request_hdlr.h>
#include <merry_core.h>
#include <merry_console.h>
#include <merry_process.h>
#include <stdatomic.h>

typedef struct Merry Merry;

struct Merry
{
  MerryReader *reader;
  MerryCore **cores;          // the vcores
  MerryThread **core_threads; // the vcore's threads
  MerryMemory *inst_mem;      // the instruction memory that every vcore shares
  MerryDMemory *data_mem;     // the data memory that every vcore shares
  MerryMutex *_lock;          // the Manager's lock
  MerryCond *_cond;           // the Manager's cond
  msize_t core_count;         // the number of vcores
  msize_t active_core_count;  // the number of vcores currently active
  mbool_t stop;               // tell the manager to stop the VM and exit
  msize_t ret;
};

#define _MERRY_REQUEST_QUEUE_LEN_ 10 // for now
#define _MERRY_THPOOL_LEN_ 10        // for now

#define _MERRY_REQUEST_INTERNAL_ERROR_(request_id) (request_id >= 0 && request_id <= 50)
#define _MERRY_REQUEST_PROGRAM_ERROR_(request_id) (request_id >= 51 && request_id <= 150)
#define _MERRY_REQUEST_VALID_(req_id) (req_id >= 151)

#define merry_mem_error(msg) fprintf(stderr, "Memory Error: %s.\n", msg)
#define merry_internal_module_error(msg) fprintf(stderr, "Internal Error; %s.\n", msg)
#define merry_general_error(type, msg) fprintf(stderr, "%s: %s.\n", type, msg)

#define merry_error(msg, ...) err_log("Error: %s\n", msg, __VA_ARGS__)

/*
 The Manager assigns core ids to every core it manages which then helps in identifying the cores.
*/

// this only initializes an instance of Merry while leaving inst_mem, data_mem uninitialized which is valid as we need to know the input and how many
// pages to start with

static Merry os;

#define merry_manager_mem_read_inst(inst_mem, address, store_in) merry_memory_read(inst_mem, address, store_in)

mret_t merry_os_init(mcstr_t _inp_file, char **options, msize_t count);
_THRET_T_ merry_os_start_vm(mptr_t some_arg);

mret_t merry_os_add_core();
mret_t merry_os_boot_core(msize_t core_id, maddress_t start_addr);

// destroy the OS
void merry_os_destroy();

// print the suitable error message and exit the VM
void merry_os_handle_error(merrot_t error);

void merry_os_handle_internal_module_error(merrot_t error_num);

void merry_os_new_proc_init();

#define _os_exec_(reqname) mret_t merry_os_execute_request_##reqname(Merry *os, MerryOSRequest *request)

// r, r+, w, w+, a, a+
// #define _openmode_(bits) (bits == 1) ? "r+" : (bits == 2) ? "w"  \
//                                           : (bits == 3)   ? "w+" \
//                                           : (bits == 4)   ? "a"  \
//                                           : (bits == 5)   ? "a+" \
//                                           : (bits == 6)   ? "rb"\
//                                           : (bits == 7)   ? "wb"\
//                                                           : "r"

// handle the halt request
_os_exec_(halt);
_os_exec_(new_core);
_os_exec_(dynl);
_os_exec_(dynul);
_os_exec_(dyncall);
_os_exec_(fopen);
_os_exec_(fclose);
_os_exec_(fread);
_os_exec_(fwrite);
_os_exec_(feof);
_os_exec_(fseek);
_os_exec_(ftell);
_os_exec_(rewind);
_os_exec_(mem);
_os_exec_(newprocess);

#endif