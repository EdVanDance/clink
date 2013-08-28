/* Copyright (c) 2012 Martin Ridgers
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <io.h>
#include <conio.h>
#include <process.h>
#include <limits.h>

#include "hooks.h"

// here be dragons (for purposes of utf-8 and changing stdout handles)
//
int                         hooked_fwrite(const void*, int, int, void*);
void                        hooked_fprintf(const void*, const char*, ...);
int                         hooked_putc(int, void*);
size_t                      hooked_mbrtowc(wchar_t*, const char*, size_t, mbstate_t*);
size_t                      hooked_mbrlen(const char*, size_t, mbstate_t*);
int                         hooked_stat(const char*, struct hooked_stat*);
int                         hooked_fstat(int, struct hooked_stat*);
int                         hooked_wcwidth(wchar_t wc);

#define wcwidth(x)          (((x) > 0x7f) ? hooked_wcwidth(x) : 1)
#define fwrite              hooked_fwrite
#define fprintf             hooked_fprintf
#define putc                hooked_putc
#define mbrtowc             hooked_mbrtowc
#define mbrlen              hooked_mbrlen
#define stat                hooked_stat
#define fstat               hooked_fstat

#undef MB_CUR_MAX
#define MB_CUR_MAX  3       // utf-8 takes 3 bytes to encode 16 bits.

// msvc vs posix|readline|gnu
//
#if defined(_MSC_VER)
#   define strncasecmp      strnicmp
#   define strcasecmp       _stricmp
#   define strchr           strchr
#   define getpid           _getpid
#   define snprintf         _snprintf

#   define __STDC__         0
#   define __MSDOS__
/*
#   define __MINGW32__
#   define __WIN32__
*/

#   pragma warning(disable : 4018)  // signed/unsigned mismatch
#   pragma warning(disable : 4090)  // different 'const' qualifiers
#   pragma warning(disable : 4101)  // unreferenced local variable
#   pragma warning(disable : 4244)  // conversion from 'X' to 'Y', possible loss of data
#   pragma warning(disable : 4267)  // conversion from 'X' to 'Y', possible loss of data
#endif // _MSC_VER

#define RL_LIBRARY_VERSION  "6.2"

// What follows was generated by autotools...
//
#define RETSIGTYPE void
#define VOID_SIGHANDLER 1
#define PROTOTYPES 1
#define HAVE_ISASCII 1
#define HAVE_ISWCTYPE 1
#define HAVE_ISWLOWER 1
#define HAVE_ISWUPPER 1
#define HAVE_ISXDIGIT 1
#define HAVE_MBRLEN 1
#define HAVE_MBRTOWC 1
#define HAVE_MBSRTOWCS 1
#define HAVE_MEMMOVE 1
//#define HAVE_PUTENV 1
#define HAVE_SETLOCALE 1
#define HAVE_STRCASECMP 1
#define HAVE_STRCOLL 1
#define STRCOLL_BROKEN 1
#define HAVE_STRPBRK 1
#define HAVE_TOWLOWER 1
#define HAVE_TOWUPPER 1
#define HAVE_VSNPRINTF 1
#define HAVE_WCRTOMB 1
#define HAVE_WCSCOLL 1
#define HAVE_WCTYPE 1
#define HAVE_WCWIDTH 1
#define STDC_HEADERS 1
#define HAVE_DIRENT_H 1
#define HAVE_FCNTL_H 1
#define HAVE_LIMITS_H 1
#define HAVE_LOCALE_H 1
#define HAVE_MEMORY_H 1
#define HAVE_STDARG_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_WCHAR_H 1
#define HAVE_WCTYPE_H 1
#define HAVE_MBSTATE_T 1
#define HAVE_WCHAR_T 1
#define HAVE_WCTYPE_T 1
#define HAVE_WINT_T 1
#define VOID_SIGHANDLER 1
#define MUST_REINSTALL_SIGHANDLERS 1
#if !defined (HAVE_TERMIOS_H) || !defined (HAVE_TCGETATTR) || defined (ultrix)
#  define TERMIOS_MISSING
#endif

#if defined (__STDC__) && defined (HAVE_STDARG_H)
#  define PREFER_STDARG
#  define USE_VARARGS
#else
#  if defined (HAVE_VARARGS_H)
#    define PREFER_VARARGS
#    define USE_VARARGS
#  endif
#endif

#endif // CONFIG_H
