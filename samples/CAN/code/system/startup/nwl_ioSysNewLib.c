/**
 * @file nwl_ioSysNewLib.c
 * Low level I/O bindings for the C library, implementation newlib. If the code is linked
 * against this library without the linker command line switch -specs=nosys.specs the
 * function from stdio (gets, puts, printf, etc.) refer to unresolved symbols. These are
 * the low level I/O functions, which bind the generic implementation of the C lib
 * functions to concrete, platform dependent I/O channels.\n
 *   This module offers a set of I/O functions, which suffice to make the character output
 * functions puts, printf, etc. work well through the serial interface of the
 * DEVKIT-MPC5748G, but which do not support streamed character input (gets) and likely
 * some more not yet identified C lib functions.\n
 *   One of the basic functions, implemented here is sbrk(), the lowest layer of the memory
 * management of the C lib. Therefore, malloc etc. are expected to work, too. This has
 * however not been tested yet.
 *   @remark
 * The connection of the serial input interface to the C library was not possible. The
 * way, how the C library functions request more chunks of data from the stream does not fit
 * to the character of a serial input, which can be temporarily exhausted but which will
 * have new data some time later. We couldn't find a way to satisfy the interface of the C
 * library (mainly through function read()) without unacceptable blocking states. As far as
 * input is concerned, you will have to build your application directly on the API of
 * module sio_serialIO.c.
 *   @remark
 * The operation of the functions offered here strongly depend on the availability of memory
 * space. The total memory space available to the function is defined in the linker file.
 * As a matter of experience, the printf function family requires about 6 kByte of RAM. If
 * the client code make use of malloc then an according additional amount of memory should
 * be reserved for the C lib. See comments here in the implementation and in the linker
 * file for more details.
 *
 * Copyright (C) 2017-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/* Module interface
 *   sbrk
 *   fstat
 *   isatty
 *   close
 *   lseek
 *   write
 *   read
 * Local functions
 */

/* The implementation is made for the Newlib C library. */
#ifdef USE_NEWLIB

/*
 * Include files
 */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "typ_types.h"
#include "mtx_mutex.h"
#include "sio_serialIO.h"
#include "rtos_ivorHandler.h"


/*
 * Defines
 */
 

/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */

/** Debug support for adjusting the memory allocation to your needs. The number of
    invokations of the low level memory allocation function \a sbrk are counted. */
unsigned long nwl_sbrk_noRequests = 0;
 
/** Debug support for adjusting the memory allocation to your needs. The total number of
    requested bytes of RAM in all invokations of the low level memmory allocation function
    \a sbrk is recorded. (This includes those requests, which could not be satisfied.) */
unsigned long nwl_sbrk_totalIncrement = 0;


/*
 * Function implementation
 */

#if 0 
/* Overloading the functions is possible but the implementation needs to have
   nested-call-counters. */
static mtx_mutex_t nwl_mutex_malloc = MTX_MUTEX_INITIALLY_RELEASED;
void __malloc_lock(void);
void __malloc_unlock(void);
void __malloc_lock(void)
{
    /// @todo An unconditional wait means a dead lock if a preempting context tries while
    // the preempted has
    mtx_acquireMutex(&nwl_mutex_malloc, /* wait */ true);
}
void __malloc_unlock(void)
{
    mtx_releaseMutex(&nwl_mutex_malloc);
}
#endif

/**
 * Implementation of function sbrk, a function which is required if printf is used, but
 * which is not implemented in the stdlib -- there's no low level memory allocation
 * implemented in the library.\n
 *   This function provides memory to \a printf and else as working areas of the text
 * formatting operations.\n
 *   A linker provided chunk of reserved memory is return to the requesting caller piece by
 * piece. In the first call the pointer to the beginning of the reserved memory is
 * returned. In the second call the pointer advanced by the value of \a increment from the
 * first call is returned and so on. No alignment adjustment is done as in malloc. Only the
 * first returned pointer is guaranteed to be properly aligned.
 *   @return
 * The pointer to next chunk of free memory, which can be used by the caller. The pointer
 * point to a chunk of \a increment Byte.
 *   @param increment
 * The number of requested Byte of memory.
 *   @remark
 * Refer to https://github.com/eblot/newlib/blob/master/newlib/libc/reent/sbrkr.c,
 * https://en.wikipedia.org/wiki/Sbrk and
 * https://www.gnu.org/software/libc/manual/html_node/Resizing-the-Data-Segment.html#Resizing-the-Data-Segment.
 */
void *sbrk(ptrdiff_t increment)
{
    /* This function shall be invoked from different cores. We protect it by a spin lock in
       order to safely update all static status variables. */
    /// @todo This is not sufficient. Try overloading __malloc_lock instead (which is still not suffient...).
    
    static mtx_mutex_t DATA_P1(mutex_) = MTX_MUTEX_INITIALLY_RELEASED;
    mtx_acquireMutex(&mutex_, /* wait */ true);

    /* Record the use of this function. The information retrieved from these variables may
       help adjusting the size of the linker reserved memory chunk. */
    ++ nwl_sbrk_noRequests;
    nwl_sbrk_totalIncrement += (unsigned long)increment;
    
    /* Shape access to the linker provided reserved memory for sbrk. */
    extern uint8_t ld_sbrkStart[0]
                 , ld_sbrkEnd[0];
                 
    /* Check alignment, should be no less than double alignment. Correct linker file if
       this assertion fires. */
    assert(((uintptr_t)ld_sbrkStart & (8-1)) == 0);
    
    static uint8_t *DATA_P1(pNextChunk_) = ld_sbrkStart;
    void *result;
    if(pNextChunk_ + increment <= ld_sbrkEnd)
    {
        result = (void*)pNextChunk_;
        pNextChunk_ += increment;
    }
    else
    {
        errno = ENOMEM;
        assert(false);
        result = (void*)-1;
    }
    
    /* Release the spin lock. */
    mtx_releaseMutex(&mutex_);
    
    return result;
    
} /* End of sbrk */



/**
 * Stub function for fstat, a function which is required if printf is used, but which is
 * not implemented in the stdlib -- there's no file system in the library and no low level
 * binding of the standard streams to some I/O.\n
 *   All function arguments are ignored.
 *   @return 
 * The stub always returns the error code of the C stdlib.
 *   @remark
 * Refer to https://github.com/eblot/newlib/blob/master/newlib/libc/reent/fstatr.c
 */
int fstat(int fildes ATTRIB_UNUSED, struct stat *buf ATTRIB_UNUSED)
{
    return -1;
    
} /* End of fstat */
    
    

/**
 * Stub function for isatty, a function which is required by the linker (but not invoked at
 * runtime) if printf is used, but which is not implemented in the stdlib -- there's no
 * file system in the library and no low level binding of the standard streams to some
 * I/O.\n
 *   All function arguments are ignored.\n
 *   An assertion will fire on unexpected invocation.
 *   @return 
 * The stub always returns true.
 *   @remark
 * Refer to https://github.com/eblot/newlib/blob/master/newlib/libc/reent/isattyr.c
 */
int isatty(int fildes ATTRIB_UNUSED)
{
    assert(false);
    return 1;
    
} /* End of isatty */

    
    
/**
 * Stub function for close, a function which is required by the linker (but not invoked at
 * runtime) if printf is used, but which is not implemented in the stdlib -- there's no
 * file system in the library and no low level binding of the standard streams to some
 * I/O.\n
 *   All function arguments are ignored.\n
 *   An assertion will fire on unexpected invocation.
 *   @return 
 * The stub always returns zero, not indicating a problem.
 *   @remark
 * Refer to https://github.com/eblot/newlib/blob/master/newlib/libc/reent/closer.c
 */
int close(int fildes ATTRIB_UNUSED)
{
    assert(false);
    return 0;
    
} /* End of close */
    
    
    
/**
 * Stub function for lseek, a function which is required by the linker (but not invoked at
 * runtime) if printf is used, but which is not implemented in the stdlib -- there's no
 * file system in the library and no low level binding of the standard streams to some
 * I/O.\n
 *   All function arguments are ignored.\n
 *   An assertion will fire on unexpected invocation.
 *   @return 
 * The stub always returns the error code of the C stdlib.
 *   @remark
 * Refer to https://github.com/eblot/newlib/blob/master/newlib/libc/reent/lseekr.c
 */
off_t lseek(int fildes ATTRIB_UNUSED, off_t offset ATTRIB_UNUSED, int whence ATTRIB_UNUSED)
{
    assert(false);
    return -1;
    
} /* End of lseek */



/**
 * Implementation of function write, a function which is required if printf is used, but
 * which is not implemented in the stdlib -- there's no file system in the library and no
 * low level binding of the standard streams to some I/O.\n
 *   This function connects the stream outout of the C library, which goes through stdout
 * or stderr to our own implementation of a serial I/O channel.
 *   @return 
 * The actual number of written characters. Normally the same as \a noBytes, but can be
 * less if the serial send buffer is temporarily full. The difference \a noBytes - returned
 * value is the count of lost characters, these characters will not appear in the serial
 * output.
 *   @param file
 * The file stream ID from the stdlib. We only support \a stdout and \a stderr, the two
 * always open output streams. Both are redirected into our serial output. No characters
 * are written for other stream IDs.
 *   @param msg
 * The character string to be written. Although formally a pointer to void \a msg is
 * understood as pointer to bytes. \a msg is not a C string, zero bytes will be sent as
 * any other bytes.
 *   @param noBytes
 * The number of bytes to be sent.
 *   @remark
 * Other streams than stdout and stderr (i.e. files from the stdlib) would also work but
 * they are not supported by this interface as it is useless and would require open and
 * close functionality.
 *   @remark
 * Refer to https://github.com/eblot/newlib/blob/master/newlib/libc/reent/writer.c
 */
signed int write(int file, const void *msg, size_t noBytes)
{
    if(noBytes == 0  ||  msg == NULL  ||  (file != stdout->_file  &&  file != stderr->_file))
        return 0;
    else
    {
        /// @todo Do we need EOL conversion?
        /* We check the core status register to find out if can use the OS variant of the
           write function or if we need to do the more expensive system call. */
        if((rtos_getCoreStatusRegister() & 0x00004000u) == 0)
            return (signed int)sio_osWriteSerial((const char*)msg, (unsigned int)noBytes);
        else
            return (signed int)sio_writeSerial((const char*)msg, (unsigned int)noBytes);
    }
} /* End of write */


/**
 * Stub function for read, a function which is required by the linker (but not invoked at
 * runtime) if printf is used, but which is not implemented in the stdlib -- there's no
 * file system in the library and no low level binding of the standard streams to some
 * I/O.\n
 *   Note, this function would be invoked when the stdin stream would be use, e.g. by
 * calling \a scanf or \a getchar. It was not possible to make this function fit to the
 * behavior of our serial input stream and stdin must therefore never be used. An assertion
 * will fire on unexpected invocation.\n
 *   All function arguments are ignored.
 *   @return
 * The stub always returns the error code of the C stdlib.
 *   @remark
 * Refer to https://github.com/eblot/newlib/blob/master/newlib/libc/reent/readr.c
 */
ssize_t read(int fildes ATTRIB_UNUSED, void *buf ATTRIB_UNUSED, size_t nbytes ATTRIB_UNUSED)
{
    assert(false);
    return -1;

} /* End of read */

#endif /* USE_NEWLIB */
