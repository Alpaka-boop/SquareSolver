#include <string.h>
#include <stdio.h>
#include <math.h>
#include "squaresolver.h"
#include "commandline.h"
#include "color.h"

enum MINUS_TYPE
{
    SINGLE_MINUS = 1,
    DOUBLE_MINUS
};

Flags flag_arr[] =
{
    {"-h", "--help",  HELP,    &help,      NULL,            " to get help\n"},
    {"-s", "--solve", SOLVE,   &solve,     NULL,            "to solve some square equations\n"},
    {"-u", "--unit",  UNIT,    &run_tests, STOCK_TEST_FILE, " to start unit tests\n"},
    {"-f", "--file",  OP_FILE, &run_tests, NULL,            " to start unit tests from your file " 
                                                         "(*file is required to be written here)\n"},
    {"-m", "--meow",  MEOW,    &meow,      NULL, " to print meow \n"},                                                     
};

void meow( const char * /* data */ )
{
    printf("MEOW\n");
}

void help( const char * /* data */ )
{
    printf("\n");

    for (int curr_struct = 0; 
         curr_struct < (int)(sizeof(flag_arr) / sizeof(flag_arr[0])); 
         ++curr_struct)
    {
        printf("============================================\n\n");
        printf("Write %s or %s %s\n", flag_arr[curr_struct].short_name,
                                         flag_arr[curr_struct].long_name,
                                         flag_arr[curr_struct].description);
    }
}

void solve( const char * /* data */ )
{
    double a = NAN, 
           b = NAN, 
           c = NAN, 
           x1 = NAN, 
           x2 = NAN;

    int roots = 0;

    input(&a, &b, &c);
    roots = solve_quadr_eq(a, b, c, &x1, &x2);
    output(roots, x1, x2);
}

void lookup_short_name( const char *argv[], int *curr_arg )
{
    const char *sh_name = argv[*curr_arg];
    int curr_struct = 0;

    while(curr_struct < (int)(sizeof(flag_arr) / sizeof(flag_arr[0]))
          && strcmp(flag_arr[curr_struct].short_name, sh_name))
    {
        curr_struct++;
    }

    if (curr_struct < (int)(sizeof(flag_arr) / sizeof(flag_arr[0]))
        && flag_arr[curr_struct].id == OP_FILE)
    {   
        (*curr_arg)++;

        const char *user_file = argv[*curr_arg];

        flag_arr[curr_struct].data = user_file;
    }

    if (curr_struct < (int)(sizeof(flag_arr) / sizeof(flag_arr[0])))
        flag_arr[curr_struct].handle_flag( flag_arr[curr_struct].data );
    else
        printf(YELLOW "There is no such flag: %s \nUse flag -h (or --help) to learn more\n" RESET, sh_name);
}

void lookup_long_name( const char *argv[], int *curr_arg )
{
    const char *l_name = argv[*curr_arg];
    int curr_struct = 0;

    while(curr_struct < (int)(sizeof(flag_arr) / sizeof(flag_arr[0]))
           && strcmp(flag_arr[curr_struct].long_name, l_name) != 0) 
    {
        curr_struct++;
    }

    if (curr_struct < (int)(sizeof(flag_arr) / sizeof(flag_arr[0]))
        && flag_arr[curr_struct].id == OP_FILE)
    {
        (*curr_arg)++;
        const char *user_file = argv[*curr_arg];

        flag_arr[curr_struct].data = user_file;
    }

    if(curr_struct < (int)(sizeof(flag_arr) / sizeof(flag_arr[0])))
        flag_arr[curr_struct].handle_flag( flag_arr[curr_struct].data );
    else
        printf(YELLOW "There is no such flag: %s \nUse flag -h (or --help) to learn more\n" RESET, l_name);
}

void parse_cmdline( int argc, const char *argv[] ) 
{
    int flag_num = 0;

    for (int curr_arg = 1; curr_arg < argc; ++curr_arg) 
    {
        if (curr_arg < argc && strstr(argv[curr_arg], "--")) 
        {
            flag_num++;
            lookup_long_name(argv, &curr_arg);
        }
        
        else if (strstr(argv[curr_arg], "-")) 
        {
            flag_num++;
            lookup_short_name(argv, &curr_arg);
        } 
    }

    if (!flag_num)
    {
        flag_arr[HELP].handle_flag(flag_arr[HELP].data);
        flag_arr[SOLVE].handle_flag(flag_arr[SOLVE].data);
    }
}
