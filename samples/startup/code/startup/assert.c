/**
 * @file assert.c
 * The C standard macro assert is in case of GCC for PowerPC implemented by an external
 * function. This leaves it open, how the target platform should behave when an assertion
 * fires. This module implement the wanted behavior for this project.
 */
/* Module interface
 *   __assert_func
 * Local functions
 */

/* The entire contents of this file are not required in PRODUCTION compilation. */
#ifdef DEBUG

/* The implementation is made for the Newlib C library. */
#ifdef USE_NEWLIB

/*
 * Include files
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


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
 
/** A Boolean flag, which indicates, whether an assertion has fired since reset. */
volatile bool assert_assertionFired = false;

/** If an assertion has fired: The name of the causing source file. Otherwise NULL. */
volatile const char *assert_fileName = NULL;

/** If an assertion has fired: The name of the causing function. Otherwise NULL. */
volatile const char *assert_funcName = NULL;

/** If an assertion has fired: The causing source line in the source file. Otherwise NULL. */
volatile signed int assert_line = -1;
 
/** If an assertion has fired: The failing condition. Otherwise NULL. */
volatile const char *assert_expression = NULL;


/*
 * Function implementation
 */

/**
 * This is the function, which is invoked by the assert macro if the condition is false. We
 * write the information about the location of the problem into global variables, where
 * they can be inspected with the debugger, disable all external interrupts and go into an
 * infinite loop.
 *   @todo Find a way to make the debugger break rather that waiting for the user to break.
 */
void _EXFUN(__assert_func, (const char *fileName, int line, const char *funcName, const char *expression))
{
    assert_assertionFired = true;
    assert_fileName = fileName;
    assert_line = line;
    assert_funcName = funcName;
    assert_expression = expression;
    
    /* This function must not return. Disable interrupts and thus scheduler: Other
       execution threads should not be continued, neither. */
    asm volatile ( /* AssemblerTemplate */
                   "wrteei  0\n"
                 : /* OutputOperands */
                 : /* InputOperands */
                 : /* Clobbers */
                 );
    while(true)
        ;
    
} /* End of __assert_func */

#endif /* USE_NEWLIB */
#endif /* DEBUG */