
/*
* this file is part of 'gopt'. it is released into the public domain.
* please see the header of 'gopt.h' for more information.
*/

#include <stdio.h>
#include "gopt.h"

static const char* exprs[] =
{
    "-h",
    "-v",
    "-d",
    "-I?",
    "-o?",
    NULL,
};

int main(int argc, char* argv[])
{
    size_t vblevel;
    bool dbg_enabled;

    struct gopt_t ci;
    struct gopt_result_t re;

    vblevel = 0;
    dbg_enabled = false;

    gopt_init(&ci, exprs, 1, argc, argv);
    while(gopt_next(&ci, &re, false) == true)
    {
        if(re.isoption)
        {
            if(re.isknown && (re.iserror == false))
            {
                switch(re.name)
                {
                    case 'h':
                        printf("help goes here\n");
                        break;
                    case 'v':
                        printf("new verbosity level: %d\n", vblevel++);
                        break;
                    case 'd':
                        if(dbg_enabled == false)
                        {
                            printf("enabling debug mode\n");
                            dbg_enabled = true;
                        }
                        break;
                    case 'I':
                        printf("adding '%s' to #include paths\n", re.value);
                        break;
                    case 'o':
                        printf("setting output filename to '%s'\n", re.value);
                        break;
                }
            }
            else
            {
                if(re.needed_value)
                {
                    printf("**error* option '-%c' expects a value\n", re.name);
                }
                else
                {
                    printf("*error* unknown option '%s'\n", re.value);
                }
            }
        }
        else
        {
            printf("adding '%s' to input files\n", re.value);
        }
    }
    return 0;
}


