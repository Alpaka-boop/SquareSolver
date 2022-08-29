#ifndef COMMANDLINE_H
#define COMMANDLINE_H

enum FLAGS_NAMES
{
    HELP,
    SOLVE,
    UNIT,
    OP_FILE,
    MEOW
};

struct Flags
{
    const char *short_name;
    const char *long_name;

    FLAGS_NAMES id;

    void (*handle_flag)( const char* data );

    const char *data;
    const char *description;
};

///------------------------------------------
///@brief This function prints help info 
///@note This function prints short name of flag, long name of flag and description from structure Flags
///------------------------------------------
void help( const char * data );

///------------------------------------------
///@brief This function starts decision of a square equation 
///@note This function prints short name of flag, long name of flag and description from structure Flags
///------------------------------------------
void solve( const char * data );

///------------------------------------------
///@note This function look up short name of the flag in the struct and starts function for such flag  
///------------------------------------------
void lookup_short_name( const char *argv[], int *curr_arg );

///------------------------------------------
///@note This function look up long name of the flag in the struct and starts function for such flag  
///------------------------------------------
void lookup_long_name( const char *argv[], int *curr_arg );

///------------------------------------------
///@brief This function parse the command line
///@brief This function parse the command line
///------------------------------------------
void parse_cmdline( int argc, const char *argv[] );

///------------------------------------------
///@note This function prints meow
///------------------------------------------
void meow( const char * /* data */ );

#endif
