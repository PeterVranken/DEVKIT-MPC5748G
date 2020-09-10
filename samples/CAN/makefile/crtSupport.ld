/*
 * GNU GCC Memory map for Freescale MPC5748G\n
 *   This file contains the sections, which are required to build the arrays of function
 * pointers used by the C run time to implement for example object construction and
 * destruction before entry and after exit from main or global on-entry and on-exit hooks.
 * Using the linker's capabilities rather than C source code to compile the arrays avoids
 * having a centralized C data structure somewhere in the C library; any module, be it
 * from the library or in the user code, can contribute to the arrays just like that, by
 * only putting their pointer variables into the accordingly named sections.\n
 *   The source of the code is hard to tell. The net is full of matches - anywhere and at
 * any point in time. See e.g.
 * https://stackoverflow.com/questions/420350/c-ctor-question-linux.
 *   This file needs to be inluded in the SECTIONS region of the linker control file.
 *
 * Copyright (C) 2017-2018 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

    .preinit_array :
    {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        
    } > memFlash

    .init_array :
    {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array ))
        PROVIDE_HIDDEN (__init_array_end = .);
        
    } > memFlash

    .ctors :
    {
        /* gcc uses crtbegin.o to find the start of the constructors, so we make sure it is
           first. Because this is a wildcard, it doesn't matter if the user does not
           actually link against crtbegin.o; the linker won't look for a file to match a
           wildcard. The wildcard also means that it doesn't matter which directory
           crtbegin.o is in. */
        KEEP (*crtbegin.o(.ctors))
        KEEP (*crtbegin?.o(.ctors))
        
        /* We don't want to include the .ctor section from the crtend.o file until after
           the sorted ctors. The .ctor section from the crtend file contains the end of
           ctors marker and it must be last */
        KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
        
        /* The sort command is applied to implement the priority of constructors: An
           appendix to the section name make them in conjunction with the linker SORT
           command appear in the array in a priority defined order. Note that the order of
           the array is reverse, the functions at the end of the array are called first. */
        KEEP (*(SORT(.ctors.*)))
        
        /* This will match only those modules which had been filtered two lines above with
           the EXCLUDE_FILE - thus the contribution of crtend. We are not changing this
           traditional code but it would be more transparent to have this file name
           explicitly stated here instead of the asterisk. */
        KEEP (*(.ctors))
        
    } > memFlash

    .dtors :
    {
        KEEP (*crtbegin.o(.dtors))
        KEEP (*crtbegin?.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*(.dtors))
        
    } > memFlash

    .fini_array :
    {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array ))
        PROVIDE_HIDDEN (__fini_array_end = .);

    } > memFlash

    /* Exception handling, see e.g.
       https://stackoverflow.com/questions/26300819/why-gcc-compiled-c-program-needs-eh-frame-section */
    .eh_frame_hdr : { *(.eh_frame_hdr) } > memFlash
    .eh_frame     : { KEEP (*(.eh_frame)) } > memFlash
