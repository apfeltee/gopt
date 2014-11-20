
/*
* this file is part of 'gopt'. it is released into the public domain.
* please see the header of 'gopt.h' for more information.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gopt.h"

void gopt_init(struct gopt_t* ci, const char** options, int argcbegin, int argc, char** argv)
{
    ci->options = options;
    ci->abegin = argcbegin;
    ci->argc = argc;
    ci->argv = argv;
    ci->count = ci->abegin;
    ci->foundmultiopt = false;
}

bool gopt_findopt(struct gopt_t* ci, struct gopt_result_t* re, const char* carg)
{
    size_t oj;
    const char* optstr;
    for(oj=0; ci->options[oj] != NULL; oj++)
    {
        optstr = ci->options[oj];
        /* check that the names (the value after the dash) is the same ... */
        if(optstr[1] == carg[1])
        {
            /* if so, we found a known option. neat! */
            re->isoption = true;
            re->isknown = true;
            re->name = carg[1];
            /*
            * if the option string ends with a question mark, a value is
            * expected.
            */
            if(optstr[2] == '?')
            {
                /*
                * if the option ends after the name (i.e., only "-h"), then
                * the next value in argv is the option value.
                */
                if(carg[2] == 0)
                {
                    /* next value in argv is thus the argument, so check argc ... */
                    if((ci->count + 1) == ci->argc)
                    {
                        /* no args left */
                        re->iserror = true;
                        re->needed_value = true;
                    }
                    else
                    {
                        re->value = ci->argv[ci->count + 1];
                        ci->count++;
                    }
                }
                else
                {
                    /* retrieve the option value by discarding the dash and the name */
                    re->value = (carg + 2);
                }
            }
            ci->count++;
            return true;
        }
    }
    return false;
}

bool gopt_next(struct gopt_t* ci, struct gopt_result_t* re, bool stopparsing)
{
    const char* carg;

    /* restore default values */
    re->iserror = false;
    re->isoption = false;
    re->isknown = false;
    re->name = -1;
    re->value = NULL;

    for(; (ci->count) < (ci->argc); ci->count++)
    {
        carg = ci->argv[ci->count];
        if(stopparsing)
        {
            re->iserror = false;
            re->isoption = false;
            re->isknown = false;
            re->name = -1;
            re->value = carg;
            ci->count++;
            return true;
        }
        /*
        * check if $carg could be an option, but discard single and double dashes
        */
        if((carg[0] == '-') && (carg[1] != '-') && (carg[1] != 0))
        {
            if(gopt_findopt(ci, re, carg))
            {
                return true;
            }
            /* if we still haven't returned at this point it's likely a bogus option */
            re->isoption = true;
            re->isknown = false;
            re->iserror = true;
            re->value = carg;
            re->name = carg[1];
            ci->count++;
            return true;
        }
        else
        {
            /* position values are yielded as-is */
            re->isoption = false;
            re->iserror = false;
            re->value = carg;
            ci->count++;
            return true;
        }
    }
    return false;
}
