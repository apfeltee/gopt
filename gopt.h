
/*
* This file (gopt.h), as well as its implementation (gopt.c) are hereby released
* into the public domain. Do whatever you wish with it.
*
* <unlicense.org>
* This is free and unencumbered software released into the public domain.
*
* Anyone is free to copy, modify, publish, use, compile, sell, or
* distribute this software, either in source code form or as a compiled
* binary, for any purpose, commercial or non-commercial, and by any
* means.
*
* In jurisdictions that recognize copyright laws, the author or authors
* of this software dedicate any and all copyright interest in the
* software to the public domain. We make this dedication for the benefit
* of the public at large and to the detriment of our heirs and
* successors. We intend this dedication to be an overt act of
* relinquishment in perpetuity of all present and future rights to this
* software under copyright law.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* For more information, please refer to <http://unlicense.org/>
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stdbool.h>

struct gopt_t
{
    /*
    * pointer to the NULL-terminated list of patterns (see gopt_init)
    */
    const char** options;

    /*
    * where $count should begin (see gopt_init)
    */
    size_t abegin;

    /*
    * arg count (see gopt_init)
    */
    size_t argc;

    /*
    * arg vector (see gopt_init)
    */
    char** argv;

    /*
    * internal counter; incremented in gopt_next
    */
    size_t count;

    /*
    * whether a multi-option was found (i.e., "-vd", where "-v" and "-d")
    * not yet used
    */
    bool foundmultiopt;

    /*
    * value of multi option
    * not yet used
    */
    const char* multivalue;
};

struct gopt_result_t
{
    /*
    * whether there was an error of some kind.
    * false if $stopparsing in gopt_next is true.
    */
    bool iserror;

    /*
    * whether it is an option, regardless of whether it is known or not.
    * i.e., it starts with a dash (no MSDOS-style option support here, sorry).
    * false if $stopparsing in gopt_next is true.
    */
    bool isoption;

    /*
    * whether the option is known (i.e., it matched a pattern given to gopt_init)
    * false if $stopparsing in gopt_next is true.
    */
    bool isknown;

    /*
    * set to true when an option expected a value, but none was passed.
    * implies $iserror.
    */
    bool needed_value;

    /*
    * the short name of the option. set to -1 if $isoption == false.
    * also -1 if $stopparse in gopt_next is true.
    */
    char name;

    /*
    * value of the option.
    * that is, for KNOWN options declared as, say, "-o?", whereas "-ofoo.txt" would
    * result in $value having the value "foo.txt" (same for {"-o", "foo.txt", NULL}, to
    * explain it with some C arrays).
    *
    * if stopparsing in gopt_next is true, this is the raw, unfiltered value from $argv.
    */
    const char* value;
};

void gopt_init(
    /* pointer to a gopt_t instance (can be stack-allocated) */
    struct gopt_t* ci,

    /* NULL-terminated list of option patterns */
    const char** options,

    /* where argc begins. typically, this should be 1. */
    int argcbegin,

    /* argc from your main() function (should be self-explanatory ...) */
    int argc,

    /* same as argc, except argv, of course. */
    char** argv
);

bool gopt_next(
    /* pointer to a gopt_t instance (same as for gopt_init) */
    struct gopt_t* ci,

    /* pointer to a gopt_result_t instance (can also be stack-allocated) */
    struct gopt_result_t* re,

    /*
    * whether to stop parsing or not.
    * if your program never expects variadic values (sort-of like strace, valgrind, gdb, etc...),
    * then just pass 'false' here. otherwise, define a boolean variable that tracks
    * whether a returned gopt_result_t is an option; if it is not an option, set that
    * boolean variable to true.
    *
    * for an example of the voodoo above, see 'stracelike.c' in the examples directory.
    */
    bool stopparsing
);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */
