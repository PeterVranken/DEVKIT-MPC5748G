/**
 * @file sup_startup.S
 * Assembler implementation of a function double f2d(float f). The function can be used
 * when calling functions with double arguments in code, which has been compiled not using
 * switch -fshort-double; our code is compiled with this switch and will therefore not by
 * itself provide the called function with a double argument.\n
 *   The intended use case is the call of the library function printf with format character
 * %f or similar. printf had been compiled using true 64 Bit double and will expect such a
 * number in the variable argument list. Wrapping the application provided pseudo-double
 * value into the call of this function will provide such a number. Example:
 *
 *   double pi = 3.14; // Yields a 32 Bit float in our machine code, due to -fshort-double.
 *   printf("pi = %f\n", pi);       // Fails to print the correct value. 
 *   printf("pi = %f\n", f2d(pi));  // Prints the correct value. 
 *
 *   @remark
 * This function is just a work around for the missing library being compiled with
 * -fshort-double.
 *   @remark
 * The implementation is valid only if the called subroutine __extendsfdf2 in the C library
 * has not been compiled with setting -fshort-double -- this is the case in our environment
 * and wherever it wouldn't were this function obsolete anyway.
 *
 * Copyright (C) 2017 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   f2d
 * Local functions
 */

/*
 * Include files
 */


/*
 * Defines
 */


/*
 * External function declarations
 */

/** Function from the C library to convert a float into a double. */
.extern __extendsfdf2


/*
 * Data declarations
 */


/*
 * Function implementation
 */


/**
 *   @func f2d
 * Convert a float value into a real 64 Bit double value.
 *   @return
 * Get the value of \a f as 64 Bit double in register pair r3/r4.
 *   @param f
 * The float value is expected as 32 Bit input in r3.
 */
    .section    .text.f2d, "ax", @progbits
    .global     f2d
    .type       f2d, @function
f2d:
#ifdef __VLE__

    e_stwu      sp, -16(sp)     /* Create stack frame */
    mflr        r0              /* Save return address in local stack space */
    se_stw      r0, 20(sp)
    
    /* Call the required function in the library. The effect results from a basic error: We
       don't have a suiting library, which has been compiled with the same settings as our
       own code. We use short double, all data which would be double in C is actually
       computed and stores as float. Since we don't have a library using this switch, many
       library function still expect or return true 64 Bit values although they will always
       interface with 32 Bit pseudo double values from our code compilation. Normally this
       leads to bad results, here it is the wanted effect: we get a real 64 Bit value
       back in r3/r4. */
    e_bl        __extendsfdf2

    se_lwz      r0, 20(sp)      /* Load return address back into linkr register */
    mtlr        r0
    e_la        sp, 16(sp)      /* Delete stack frame */
    se_blr                  /* Return */
    
#else /* Book E */

    stwu        sp, -16(sp)     /* Create stack frame */
    mflr        r0              /* Save return address in local stack space */
    stw         r0, 20(sp)
    
    /* Call the required function in the library. The effect results from a basic error: We
       don't have a suiting library, which has been compiled with the same settings as our
       own code. We use short double, all data which would be double in C is actually
       computed and stores as float. Since we don't have a library using this switch, many
       library function still expect or return true 64 Bit values although they will always
       interface with 32 Bit pseudo double values from our code compilation. Normally this
       leads to bad results, here it is the wanted effect: we get a real 64 Bit value
       back in r3/r4. */
    bl          __extendsfdf2

    lwz         r0, 20(sp)      /* Load return address back into linkr register */
    mtlr        r0
    la          sp, 16(sp)      /* Delete stack frame */
    blr                     /* Return */

#endif

/* End of f2d */