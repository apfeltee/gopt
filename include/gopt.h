
#ifndef __pdsoft_libgopt_header_defined__
#define __pdsoft_libgopt_header_defined__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>

struct gopt_t
{
    const char** options;
    size_t abegin;
    size_t argc;
    char** argv;
    size_t count;
    bool foundmultiopt;
    const char* multivalue;
};

struct gopt_result_t
{
    bool iserror;
    bool isoption;
    bool isknown;
    int name;
    const char* value;
};

void gopt_init(struct gopt_t* ci, const char* options[], int argcbegin, int argc, char** argv);

bool gopt_next(struct gopt_t* ci, struct gopt_result_t* re);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __pdsoft_libgopt_header_defined__ */
