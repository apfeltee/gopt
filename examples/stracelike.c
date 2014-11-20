
/*
* this file is part of 'gopt'. it is released into the public domain.
* please see the header of 'gopt.h' for more information.
*/

/*
* test:
* 
* $ ./a.exe -olog -I/usr/share/macros -v -d -o debug.txt ls -la strace -o info
* setting output filename to 'log'
* adding '/usr/share/macros' to search paths
* new verbosity level: 0
* enabling debug mode
* setting output filename to 'debug.txt'
* adding to args: 'ls'
* adding to args: '-la'
* adding to args: 'strace'
* adding to args: '-o'
* adding to args: 'info'
*
* seems to work fine
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
    bool stopparsing;
    struct gopt_t ci;
    struct gopt_result_t re;

    vblevel = 0;
    dbg_enabled = false;
    stopparsing = false;

    gopt_init(&ci, exprs, 1, argc, argv);
    while(gopt_next(&ci, &re, stopparsing) == true)
    {
        if(stopparsing == true)
        {
            addval:
            printf("adding to args: '%s'\n", re.value);
        }
        if((re.isoption == false) && (stopparsing == false))
        {
            stopparsing = true;
            /* have to use goto to pass the first value ... sorry :^) */
            goto addval;
        }
        else if((re.isoption == true) && (stopparsing == false))
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
                        printf("adding '%s' to search paths\n", re.value);
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
    }
    return 0;
}
