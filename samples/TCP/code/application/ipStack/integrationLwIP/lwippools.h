/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#error The multiple include lock is wrong. This file is included intendly several times
#ifndef LWIP_LWIPPOOLS_H
#define LWIP_LWIPPOOLS_H

/* Configuration of lwIP's memory allocation:
 *   There are two modules, mem and memp, for heap and memory pool related allocation,
 * respectively. lwIP, in particular pbuf_alloc(), uses memp for pbufs and other objects of
 * fixed, known size and mem for object with runtime-known sizes, in particular pbufs,
 * which don't use a REF but embed the contained data.
 *   lwIP has a set of memory pools with sizes that fit for its objects with known fixed
 * size. The size of these pools is application dependent and subject to user configuration
 * in lwipopts.h. Look for macros named MEMP_NUM_<kindOfObj>, e.g., #MEMP_NUM_SYS_TIMEOUT.
 *   These memory pools are defined in memp_std.h. They are instantiated as static objects
 * named memp_<nameOfPool>, e.g., memp_SYS_TIMEOUT. References to all of them are bundled
 * in an array of memp_pools, see memp.c, l.81.
 *   The implementation of pools has configuration macro #MEMP_MEM_MALLOC. If set to 1 then
 * the calls of memp don't use pooling but the heap implementation mem is called instead.
 * It further depends on the configuration of mem what actually happens.
 *   The heap implementation mem has two principal configuration macros, #MEM_USE_POOLS and
 * #MEM_LIBC_MALLOC. One of the two may be set to 1. If both of them are set to 0 then the
 * heap implementation made in mem.c, ll.831ff, is used. The implementation follows the
 * explanations given in the lwIP manual, section 6.2. If #MEM_USE_POOLS is set to 1 then
 * the set of standard pools (see above) is extended by an arbitrary number of user defined
 * pools sizes and mem will call the memp API functions to fulfill the request. No heap
 * operation is performed. If #MEM_LIBC_MALLOC is set to 1 then mem just calls functions
 * malloc() and free() from the C library.
 *   Note, a cyclic configuration -- memp delegates to mem (#MEMP_MEM_MALLOC == 1) and mem
 * calls memp (#MEM_USE_POOLS == 1) -- is invalid and should be caught by compile-time
 * checks (TBC).
 *   Setting #MEM_USE_POOLS to 1 requires setting #MEMP_USE_CUSTOM_POOLS (see below) to 1,
 * too. It is not clear, whether setting #MEMP_USE_CUSTOM_POOLS==1 and #MEM_USE_POOLS==0
 * would be valid. Anonymous user defined pools would be created but how to use, how to
 * address to them?
 *   This header, lwippools.h, is read if #MEMP_USE_CUSTOM_POOLS is set to 1. It specifies
 * the pools in object size and number of objects, which are required for the application.
 * The specified pools need to satisfy all calls of mem, which are going to be made by lwIP
 * and application.
 *   Note, header lwippools.h is read several times during compilation of memp.c. Prior to
 * inclusion, the macros #LWIP_MALLOC_MEMPOOL, #LWIP_MALLOC_MEMPOOL_START and
 * #LWIP_MALLOC_MEMPOOL_END are defined in different ways in order to produce different
 * pool related code sequences, e.g., enumerated values for each pool, array initializer
 * expressions, object definitions, etc.
 *   Application required pools can be instantiated individually, too. The macros
 * #LWIP_MEMPOOL_DECLARE, #LWIP_MEMPOOL_INIT, #LWIP_MEMPOOL_ALLOC and #LWIP_MEMPOOL_FREE
 * hide the calls of memp, for handling these pools. The difference to the other pools is
 * that these pools are unrelated, individual static objects, which can be addressed by
 * name only. They are not enumerated in memp_pools and can't be used with memp_malloc() or
 * memp_free(), which base on this enumeration. The mentioned macros hide the calls of the
 * pool name based API in memp. 
 *   Note, using macros LWIP_MEMPOOL_xxx allows re-using the memory pool implementation of
 * lwIP without any interference with the lwIP stack. They can be used for any arbitrary
 * application purpose and, particularly, without any constraints on the configuration of
 * #MEMP_USE_CUSTOM_POOLS or #MEM_USE_POOLS.
 */ 

/* OPTIONAL: Pools to replace heap allocation
 * Optional: Pools can be used instead of the heap for mem_malloc. If
 * so, these should be defined here, in increasing order according to 
 * the pool element size.
 *
 * LWIP_MALLOC_MEMPOOL(number_elements, element_size)
 */
#if MEM_USE_POOLS
LWIP_MALLOC_MEMPOOL_START
LWIP_MALLOC_MEMPOOL(100, 256)
LWIP_MALLOC_MEMPOOL(50, 512)
LWIP_MALLOC_MEMPOOL(20, 1024)
LWIP_MALLOC_MEMPOOL(20, 1536)
LWIP_MALLOC_MEMPOOL_END
#endif /* MEM_USE_POOLS */

/* Optional: Your custom pools can go here if you would like to use
 * lwIP's memory pools for anything else.
 */

#endif /* LWIP_LWIPPOOLS_H */
