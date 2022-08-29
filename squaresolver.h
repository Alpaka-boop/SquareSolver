#ifndef SQUARESOLVER_H
#define SQUARESOLVER_H

#include <stdio.h>

#define EPS 1e-6           ///< const for inaccuracy
#define NUM_OF_ARGS 3      ///< number of coefficients which have to be red by input function 
#define NUM_OF_FILE_ARGS 6 ///< number of args reading from file 
#define UNIT_TEST_ERROR 1  ///< const for an error return in unit test
#define MAX_FILENAME 300   ///< maximum length of the input file name

#define STOCK_TEST_FILE "Tests.txt"

enum NUM_OF_ROOTS          /// namespace for number of roots constants
{
    NO_ROOTS,              ///< const for absence of roots
    ONE_ROOT,              ///< const for one root
    TWO_ROOTS,             ///< const for two roots
    INF_ROOTS              ///< const for unlimited number of roots
};

//!------------------------------------------
//!@brief This function solves a square equation (a * x^2 + b * x + c = 0)
//!@note TODO if equation is a * x + b = 0 type function solves linear equation 
//!@note TODO if equation does not have roots (discriminant < 0) function returns no roots
//!@param [in] a coefficient before x^2
//!@param [in] b coefficient before x
//!@param [in] c free term 
//!@param [out] x1 first root
//!@param [out] x2 second root
//!@return number of roots (0, 1, 2, infinite number of roots)
//!------------------------------------------
int solve_quadr_eq( double a, double b, double c, double *x1, double *x2 );

///------------------------------------------
///@brief This function solves a linear equation (a * x + b = 0)
///@note If equation does not have root function returns no roots 
///@param [in] a coefficient before x 
///@param [in] b free coefficient 
///@param [out] x root of the equation 
///@return is there root
///------------------------------------------
int solve_linear_eq( double a, double b, double *x );

///------------------------------------------
///@brief This function compare two numbers 
///@note This function checks is diffirence between two numbers less then error (EPS)
///@param [in] a first number
///@param [in] b second number
///@return logic test if |a - b| < error
///------------------------------------------
int is_equal( double a, double b );

///------------------------------------------
///@brief This function read coefficients in square equation (a * x^2 + b * x + c = 0)
///@note if any coefficient have not red function has another try
///@param [out] a coefficient before x^2
///@param [out] b coefficient before x
///@param [out] c free term
///------------------------------------------
void input( double *a, double *b, double *c );

///------------------------------------------
///@brief This function prints roots andd thir number
///@note This function prints different text depending on the number of roots
///@param [in] roots - number of roots
///@param [in] x1 - first root (if it exists)
///@param [in] x2 - second root (if it exists)
///------------------------------------------
void output( int roots, double x1, double x2 );

///------------------------------------------
///@brief This function clears buffer
///@note This function takes symbols from buffer till it finds '\n' or EOF symbol
///------------------------------------------
void clear_buf();

///------------------------------------------
///@brief This function starts some unit_tests 
///@note This function reads name of file from the command line then it starts some unit tests based on the data from this file 
///@param [in] argc - number of comand line arguments
///@param [in] argv - array of command line arguments pointers
///------------------------------------------
void run_tests( const char user_file[] );

///------------------------------------------
///@brief This function compares result of solve_quadr_eq function with handmade programer results and compares number of roots 
///@note This function starts solve_quadr_eq with the coefficient of the equation, which have been solven by author, prints if there is an error and the type of this error
///@param [in] a coefficient before x^2
///@param [in] b coefficient before x
///@param [in] c free coefficient
///@param [in] x1_cor first correct root 
///@param [in] x2_cor second correct root 
///@param [in] roots_cor correct number of roots 
///@param [in] test_num number of the unit test
///@return 1 in case all is ok 0 in case something is wrong
///------------------------------------------
int unit_test( double a, double b, double c, double x1_cor, double x2_cor, int roots_cor, int test_num );

///------------------------------------------
///@brief This function reads file name from the command line 
///@note pointer goes through arguments and if an argument contains ".txt" line such arguement is considered to be name of the file then this name is being written to the array which returns
///@param [in] argc - number of comand line arguments
///@param [in] argv - array of command line arguments pointers
///@param [out] fn - array where the file name written 
///------------------------------------------
void read_filename( char *file_name, int argc, char **argv );

///------------------------------------------
///@brief This function reads input data for unit tests
///@param [in] input_file - pointer on the file 
///@param [in] a - coeffincent before x^2 
///@param [in] b - coefficient before x
///@param [in] c - free coeffincent 
///@param [in] x1_cor - first correct root
///@param [in] x2_cor - second correct root
///@param [in] roots_num_cor - correct number of roots
///@return error code
///------------------------------------------
int file_input( FILE *input_file, double *a, double *b, double *c, double *x1_cor,
                double *x2_cor, int *roots_num_cor );

int handle_zero_c( double a, double b, double *x1, double *x2 );

int diskriminant( double a, double b, double c, double *x1, double *x2 );

#endif
