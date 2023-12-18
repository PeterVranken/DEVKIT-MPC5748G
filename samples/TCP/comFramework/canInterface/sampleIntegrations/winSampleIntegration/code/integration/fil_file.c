/**
 * @file fil_file.c
 * A collection of file and file name related operations.
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
/* Module interface
 *   fil_splitPath
 *   fil_changeExtension
 *   fil_copyDir
 *   fil_findApplication
 * Local functions
 *   removeTrailingSlash
 *   checkForInstallDir
 */

/*
 * Include files
 */

#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>

#include "types.h"
#include "smalloc.h"
#include "snprintf.h"
#include "oss_operatingSystemSimulation.h"
#include "main.h"
#include "fil_file.h"


/*
 * Defines
 */

/** The path separator character as a string constant. */
#ifdef __WINNT__
# define SL "\\"
#else
# define SL "/"
#endif

/** The path separator character as a character constant. */
#ifdef __WINNT__
# define cSL '\\'
#else
# define cSL '/'
#endif


/*
 * Local type definitions
 */


/*
 * Local prototypes
 */

static char *removeTrailingSlash(char * const path) ATTRIB_UNUSED;
static bool checkForInstallDir(const char *candidate) ATTRIB_UNUSED;


/*
 * Data definitions
 */


/*
 * Function implementation
 */

/**
 * Clean a path designation: Often, there's a trailing path sepeartor character. This
 * function removes it if present. The passed string is modified in place.
 *   @return
 * The modified string is returned. This is the same character pointer as passed in.
 *   @param path
 * The string pointer, which must not be a constant object like a string literal: If a
 * modification is needed then the function simply overwrites the last character with a
 * null character.
 */ 

static char *removeTrailingSlash(char * const path)
{
    assert(path != NULL);
    size_t strLen = strlen(path);
    if(strLen > 0)
    {
        char * const pLast = path + strLen - 1;
        if(*pLast == cSL)
            *pLast = '\0';
    }
    
    return path;    

} /* End of removeTrailingSlash */




/**
 * Local sub-function of fil_findApplication: A candidate for the installation directory is
 * checked if it really is the wanted directory.
 *   @return
 * \a true if \a candidate designates the application installation directory, \a false
 * otherwise.
 *   @param candidate
 * The supposed installation directory.
 */

static bool checkForInstallDir(const char *candidate)
{
#if 0
# define PRINTF(formatStr, ...)  printf("checkForInstallDir: " formatStr, __VA_ARGS__)
#else
# define PRINTF(formatStr, ...)
#endif

    char appName[strlen(candidate) + strlen(MAIN_APP_FILE_NAME) + sizeof(SL)];
    snprintf(appName, sizeof(appName), "%s" SL MAIN_APP_FILE_NAME, candidate);
    FILE *tmpExeFile = fopen(appName, "rb");
    if(tmpExeFile != NULL)
    {
        fclose(tmpExeFile);
        PRINTF("%s is the application directory\n", candidate);
        return true;
    }
    else
    {
        PRINTF("%s isn't the application directory\n", candidate);
        return false;
    }
#undef PRINTF
} /* End of checkForInstallDir */




/**
 * Split a file-path into path, file name and name extension.
 *   @return
 * The file name is returned as pointer to the part of input string filePath, which
 * contains the file name (including the extension). No copy of the string is made.
 *   @param pPath
 * If not NULL, then a malloc allocated string is placed in * \a pPath, which contains the
 * path (including the final separator char). The caller has to free the string after use.
 *   @param pPureFileName
 * If not NULL, then a malloc allocated string is placed in * \a pPureFileName, which
 * contains the file name without extension. The caller has to free the string after use.
 *   @param pExt
 * If not NULL, then a malloc allocated string is placed in * \a pExt, which contains the
 * file name extension (including the dot). The caller has to free the string after use.
 *   @param filePath
 * The complete file name including the path.
 *   @remark The implementation is based on
 * http://stackoverflow.com/questions/1575278/function-to-split-a-filepath-into-path-and-file,
 * visted on Feb 21, 2014
 */

const char *fil_splitPath( char ** const pPath
                         , char ** const pPureFileName
                         , char ** const pExt
                         , const char *filePath
                         )
{
    /* Loop to find the last occurance of the separator character. We consider the slashes
       and the drive separating colon such a character. Advance the fileName-pointer behind
       the separator character. fileName is the empty string if filePath ends on the path
       separator. */
    const char *fileName = filePath
             , *next;
    while((next=strpbrk(fileName, "\\/:")) != NULL)
        fileName = next+1;

    if(pPath != NULL)
    {
        const size_t sizeOfPath = fileName - filePath + 1;
        *pPath = smalloc(sizeOfPath, __FILE__, __LINE__);
        snprintf(*pPath, sizeOfPath, filePath);
    }

    /* Do the same as before inside the found file name but look for the dot as separator. */
    const char *extension = fileName;
    if(*extension != '\0')
    {
        while((next=strpbrk(extension+1, ".")) != NULL)
            extension = next;
    }

    if(*extension != '.'  &&  extension == fileName)
    {
        /* No dot found, everything is the file name without extension. */
        if(pPureFileName != NULL)
            *pPureFileName = stralloccpy(fileName);
        if(pExt != NULL)
            *pExt = stralloccpy("");
    }
    else
    {
        /* The extension begins with extension (including the dot). The file name ends at
           extension and might be empty. */
        if(pPureFileName != NULL)
        {
            const size_t sizeOfPureFileName = extension - fileName + 1;
            *pPureFileName = smalloc(sizeOfPureFileName, __FILE__, __LINE__);
            snprintf(*pPureFileName, sizeOfPureFileName, fileName);
        }
        if(pExt != NULL)
            *pExt = stralloccpy(extension);
    }

    return fileName;

} /* End of fil_splitPath */





/**
 * Compose a file name with changed extension from a given file name.
 *   @return
 * Get the new file name as malloc allocated string. The caller is in charge to free the
 * string after use.
 *   @param fileName
 * The file name to change. It may have a name extension but it doesn't need to.
 *   @param newExt
 * The extesnion used in the returned new file name. In the normal use case it'll begin
 * with the dot.
 */

char *fil_changeExtension(const char * const fileName, const char * const newExt)
{
    char *path, *pureFileName;
    fil_splitPath(&path, &pureFileName, /* pExt */ NULL, fileName);
    const size_t sizeOfNewFileName = strlen(path)+strlen(pureFileName)+strlen(newExt)+1;
    char newFileName[sizeOfNewFileName];
    snprintf(newFileName, sizeOfNewFileName, "%s%s%s", path, pureFileName, newExt);
    free(path);
    free(pureFileName);

    return stralloccpy(newFileName);

} /* End of fil_changeExtension */




/**
 * Compose a file name with changed name and extension from a given file name.
 *   @return
 * Get the new file name as malloc allocated string. The caller is in charge to free the
 * string after use.
 *   @param fileName
 * The file name to change. It may have a name and or extension but it doesn't need to.
 * Only the path of \a fileName is reused.
 *   @param newName
 * The pure file name (without extension) used in the returned new file name.
 *   @param newExt
 * The extesnion used in the returned new file name. In the normal use case it'll begin
 * with the dot.
 */

char *fil_changeFileName( const char * const fileName
                        , const char * const newName
                        , const char * const newExt
                        )
{
    char *path;
    fil_splitPath(&path, /* pPureFileName */ NULL, /* pExt */ NULL, fileName);
    const size_t sizeOfNewFileName = strlen(path)+strlen(newName)+strlen(newExt)+1;
    char newFileName[sizeOfNewFileName];
    snprintf(newFileName, sizeOfNewFileName, "%s%s%s", path, newName, newExt);
    free(path);

    return stralloccpy(newFileName);

} /* End of fil_changeExtension */




/**
 * Copy a file.
 *   @return
 * A Boolean success message is returned. If the function returns true then the error code
 * and message can be retrieved with the according function from the stdlib (errno,
 * strerror).
 *   @param targetFilePath
 * The target file name including the path. The path needs to be an existing directory and
 * the file should not yet exist: otherwise it is silently overwritten.
 *   @param srcFile
 * The name of the source file to be copied including the path.
 */

bool fil_copyFile(const char * const targetFilePath, const char * const srcFile)
{
#if 0
# define PRINTF(formatStr, ...)  printf("fil_copyFile: " formatStr, __VA_ARGS__)
#else
# define PRINTF(formatStr, ...)
#endif


    bool success = true;
    FILE *hSrcFile = NULL
       , *hTargetFile = NULL;

    hSrcFile = fopen(srcFile, "rb");
    if(hSrcFile == NULL)
    {
       PRINTF("Can't open file %s for read access\n", srcFile);
       success = false;
    }

    if(success)
    {
        hTargetFile = fopen(targetFilePath, "wb");
        if(hTargetFile == NULL)
        {
           PRINTF("Can't open file %s for write access\n", targetFilePath);
           success = false;
        }
    }

    /* Data copying is done character-wise by alternating read and write. This is most
       simple but not optimal with respect to performance. The implementation could be
       changed to block oriented data copying using fread/fwrite if the amount of copied
       data rises significantly and delay time become noticeable. */
    signed int ch;
    while(success &&  (ch=fgetc(hSrcFile)) != EOF)
    {
        if(fputc(ch, hTargetFile) == EOF)
        {
            success = false;
            PRINTF("Error in write to output file %s", targetFilePath);
        }
    }
    if(success &&  ferror(hSrcFile) != 0)
    {
        success = false;
        PRINTF("Error in read from input file %s", srcFile);
    }

    if(hSrcFile != NULL)
    {
        if(fclose(hSrcFile) != 0)
            success = false;
    }
    if(hTargetFile != NULL)
    {
        if(fclose(hTargetFile) != 0)
            success = false;
    }

    if(success)
    {
        PRINTF("File %s successfully copied to %s\n", srcFile, targetFilePath);
    }
    else
    {
        PRINTF("Failed to copy file %s to %s\n", srcFile, targetFilePath);
    }
    
    return success;

#undef PRINTF
} /* End of fil_copyFile */





/**
 * Copy a directory and its contents.
 *   @return
 * A Boolean success message is returned. If the function returns true then the error code
 * and message can be retrieved with the according function from the stdlib (errno,
 * strerror).
 *   @param targetDir
 * The target directory name not including the final slash. This is an existing directory
 * and a recursive copy of \a srcDir will be found inside this directory if the function
 * succeeds.
 *   @param srcDir
 * The source file or directory to be copied. May be a single file or a directory of those.
 */

bool fil_copyDir(const char * const targetDir, const char * const srcDir)
{
#if 0
# define PRINTF(formatStr, ...)  printf("fil_copyDir: " formatStr, __VA_ARGS__)
#else
# define PRINTF(formatStr, ...)
#endif

    /* Compose the full path and name of the target file. */
    const char * const srcPureDirName = fil_splitPath(NULL, NULL, NULL, srcDir);
    char targetPath[strlen(targetDir) + strlen(srcPureDirName) + sizeof(SL)];
    snprintf(targetPath, sizeof(targetPath), "%s" SL "%s", targetDir, srcPureDirName);

    /* Check if srcDir designates a single file or a directory. */
    DIR *hDir = opendir(srcDir);
    PRINTF("%s is %s\n", srcDir, hDir == NULL? "either a file or not existent": "a directory");

    /* If it is a directory: Create such a directory as empty directory at the target
       location and copy all contained files by using this function recursively.
         Otherwise just copy the file. */
    if(hDir != NULL)
    {
        bool success = true;

        /* Create empty directory at target location. */
        if(mkdir( targetPath
#ifdef __unix__
                , /* mode: full access to anybody */ S_IRWXO | S_IRWXG | S_IRWXU
#endif
                ) != 0
          )
        {
            PRINTF("Can't create new directory %s\n", targetPath);
        }
        else
        {
            PRINTF("Succesfully created directory %s\n", targetPath);

            /* Look for all files in srcDir (be it true files or sub-directories) and copy
               each by a recursive call of the same function. */
            struct dirent *pDirEntry;
            while((pDirEntry=readdir(hDir)) != NULL)
            {
                /* Skip special directory entries . and .. */
                if(strcmp(pDirEntry->d_name, ".") == 0
                   ||  strcmp(pDirEntry->d_name, "..") == 0
                  )
                {
                    continue;
                }

                /* Compose source path for file inside of directory under progress. */
                char srcFileName[strlen(srcDir) + strlen(pDirEntry->d_name) + sizeof(SL)];
                snprintf( srcFileName
                        , sizeof(srcFileName)
                        , "%s" SL "%s"
                        , srcDir
                        , pDirEntry->d_name
                        );
                if(!fil_copyDir(targetPath, srcFileName))
                    success = false;
            }
        }

        closedir(hDir);
        return success;
    }
    else
    {
        /* Copy the ordinary file. */
        return fil_copyFile(targetPath, srcDir);
    }
#undef PRINTF
} /* End of fil_copyDir */




#if 0
/**
 * This function tries to find out, where the application linNet is installed. It uses
 * several prioritzed rules to do so:\n
 *   If the application related environment variable XXX_HOME is set it is expected to
 * point to the installation directory.\n
 *   If not, it uses the first program argument to find its own executable. This is not a
 * safe mechanism as the shell might pass the full or a relative path.\n
 *   In a last step it relates the first program argument to the current working
 * directory and looks for the executable.
 *   @return
 * The malloc allocated string that holds the name of the directory, which contains the
 * executable of this application or NULL if the executable could not be localized.\n
 *   It depends if this is relative or absolute path.
 *   @param appArg0
 * The first argument from the command line.
 */

const char *fil_findApplication(const char * const appArg0)
{
#if 0
# define PRINTF(...)  printf("fil_findApplication: " __VA_ARGS__)
#else
# define PRINTF(...)
#endif

    /* The first rule is fine but the others don't really help: Most likely is that the
       executable is found via the shell's search path mechanism and then the other rules
       don't match. Anyway, they don't harm neither ... */

    /* The user should have set an environment variable that points to the installation
       directory. */
    const char * const home = getenv(MAIN_ENV_VAR_HOME);
    if(home != NULL  && checkForInstallDir(home))
    {
        PRINTF( "Installation dir %s found via enviroment variable " MAIN_ENV_VAR_HOME "\n"
              , home
              );
        return removeTrailingSlash(stralloccpy(home));
    }
    else
    {
        PRINTF("Environment variable " MAIN_ENV_VAR_HOME " not set or wrong\n");
    }

    /* Try to separate a path from the first program argument. This could point to the
       installation directory. */
    char *path;
    fil_splitPath(&path, /* pPureFileName */ NULL, /* pExt */ NULL, appArg0);
    assert(path != NULL);
    removeTrailingSlash(path);
    if(checkForInstallDir(path))
    {
        PRINTF("First program argument designates installation dir %s\n", path);
        return path;
    }
    else
    {
        PRINTF("First program argument doesn't designate installation dir\n");
    }
    
    /* Try to relate the first program argument to the current working directory. */
    char * const cwd = getcwd(/* buffer */ NULL, /* size */ 0)
       , path2[strlen(cwd) + strlen(path) + sizeof(SL)];
    snprintf(path2, sizeof(path2), "%s" SL "%s", cwd, path);
    free(cwd);
    free(path);
    path = NULL;
    if(checkForInstallDir(path2))
    {
        PRINTF("CWD and first program argument designate installation dir %s\n", path2);
        return stralloccpy(path2);
    }
    else
    {
        PRINTF("CWD and first program argument don't designate installation dir."
               " Return NULL\n"
              );
    }

    return NULL;

#undef PRINTF
} /* End of fil_findApplication */
#endif



