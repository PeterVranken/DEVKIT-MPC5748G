/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * This software is owned or controlled by NXP and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 *
 * This file is derived from lwIP contribution example with the following copyright:
 *
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Directive 4.9, A function should be used in preference
 * to a function-like macro where they are interchangeable.
 * Function-like macros are used instead of inline functions in order to ensure
 * that the performance will not be decreased if the functions will not be
 * inlined by the compiler.
 *
 */

#ifndef LWIP_ARCH_CC_H
#define LWIP_ARCH_CC_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "lwipcfg.h"

#if defined(BYTE_ORDER)                 \
    || defined(LWIP_NO_STDDEF_H)        \
    || defined(LWIP_NO_STDINT_H)        \
    || defined(LWIP_PLATFORM_ASSERT)    \
    || defined(LWIP_PROVIDE_ERRNO)      \
    || defined(PACK_STRUCT_FIELD)       \
    || defined(PACK_STRUCT_STRUCT)      \
    || defined(PACK_STRUCT_Begin)       \
    || defined(PACK_STRUCT_END)         \
    || defined(LWIP_PLATFORM_DIAG)      \
    || defined(LWIP_RAND)
# error Conflicting configuration made at wrong code location
#endif

/** Define the byte order of the system.
 * Needed for conversion of network data to host byte order.
 * Allowed values: LITTLE_ENDIAN and BIG_ENDIAN
 */
#define BYTE_ORDER BIG_ENDIAN

/** Define this to 1 in arch/cc.h of your port if you do not want to
 * include stddef.h header to get size_t. You need to typedef size_t
 * by yourself in this case.
 */
#define LWIP_NO_STDDEF_H    0
 
/** Define this to 1 in arch/cc.h of your port if your compiler does not provide
 * the stdint.h header. You need to typedef the generic types listed in
 * lwip/arch.h yourself in this case (u8_t, u16_t...).
 */
#define LWIP_NO_STDINT_H    0

/** Platform specific assertion handling.<br>
 * Note the default implementation in lwip/arch.h pulls in printf, fflush and abort, which
 * may in turn pull in a lot of standard library code. In resource-constrained systems,
 * this should be defined to something less resource-consuming.
 */
#define LWIP_PLATFORM_ASSERT(x) assert(false)

/** LWIP_PROVIDE_ERRNO==1: Let lwIP provide ERRNO values and the 'errno' variable.
 * If this is disabled, cc.h must either define 'errno', include <errno.h>,
 * define LWIP_ERRNO_STDINCLUDE to get <errno.h> included or
 * define LWIP_ERRNO_INCLUDE to <errno.h> or equivalent.
 */
#define LWIP_PROVIDE_ERRNO  1

/** Packed structs support.
 * Wraps u32_t and u16_t members.<br>
 * For examples of packed struct declarations, see include/lwip/prot/ subfolder.<br>
 * A port to GCC/clang is included in lwIP, if you use these compilers there is nothing to do here.
 */
#define PACK_STRUCT_FIELD(x) x

/** Packed structs support.
 * Placed between end of declaration of a packed struct and trailing semicolon.<br>
 * For examples of packed struct declarations, see include/lwip/prot/ subfolder.<br>
 * A port to GCC/clang is included in lwIP, if you use these compilers there is nothing to
 * do here.
 */
#define PACK_STRUCT_STRUCT __attribute__((packed))

/** Packed structs support.
 * Placed BEFORE declaration of a packed struct.<br>
 * For examples of packed struct declarations, see include/lwip/prot/ subfolder.<br>
 * A port to GCC/clang is included in lwIP, if you use these compilers there is nothing to
 * do here.
 */
#define PACK_STRUCT_BEGIN

/** Packed structs support.
 * Placed AFTER declaration of a packed struct.<br>
 * For examples of packed struct declarations, see include/lwip/prot/ subfolder.<br>
 * A port to GCC/clang is included in lwIP, if you use these compilers there is nothing to
 * do here.
 */
#define PACK_STRUCT_END

#define LWIP_ERROR(message, expression, handler) do { if (!(expression)) {handler;} } while(0)

/** Platform specific diagnostic output.<br>
 * Note the default implementation pulls in printf, which may
 * in turn pull in a lot of standard library code. In resource-constrained
 * systems, this should be defined to something less resource-consuming.
 */
#define LWIP_PLATFORM_DIAG(x)   do {iprintf x;} while(0)

/** Define random number generator function of your system */
#define LWIP_RAND() ((u32_t)rand())

#define PPP_INCLUDE_SETTINGS_HEADER

#endif /* LWIP_ARCH_CC_H */
