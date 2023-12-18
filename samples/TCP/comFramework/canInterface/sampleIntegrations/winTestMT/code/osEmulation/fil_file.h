#ifndef FIL_FILE_INCLUDED
#define FIL_FILE_INCLUDED
/**
 * @file fil_file.h
 * Definition of global interface of module fil_file.c
 *
 * Copyright (C) 2014 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Include files
 */

#include "types.h"


/*
 * Defines
 */


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Split a file-path into path, file name and name extension. */
const char *fil_splitPath( char ** const pPath
                         , char ** const pPureFileName
                         , char ** const pExt
                         , const char *filePath
                         );

/** Compose a file name with changed extension from a given file name. */
char *fil_changeExtension(const char * const fileName, const char * const newExt);

/** Compose a file name with changed name and extension from a given file name. */
char *fil_changeFileName( const char * const fileName
                        , const char * const newName
                        , const char * const newExt
                        );

/** Copy a file. */
boolean_t fil_copyFile(const char * const targetFilePath, const char * const srcFile);

/** Copy a directory recursively. */
boolean_t fil_copyDir(const char * const targetDir, const char * const srcDir);

/** Determine the installation directory of this application. */
const char *fil_findApplication(const char * const appArg0);

#endif  /* FIL_FILE_INCLUDED */
