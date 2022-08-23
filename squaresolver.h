
#ifndef SQUARESOLVER_INCLUDED_H
#define SQUARESOLVER_INCLUDED_H

#define EPS 0.00000000000000001
#define NUM_OF_ARGS 3
#define UNIT_TEST_ERROR 1

enum NUM_OF_ROOTS 
{
    NO_ROOTS, 
    ONE_ROOT, 
    TWO_ROOTS, 
    UNLIM_NUM_ROOTS
};

int solve_quadr_eq( double a, double b, double c, double *x1, double *x2 );
int solve_linear_eq( double a, double b, double *x );
int equal( double a, double b );
void input( double *a, double *b, double *c );
void output( int roots, double x1, double x2 );
void clear_buf();

void test();
int unit_test( double a, double b, double c, double x1_ref, double x2_ref, int roots_ref, int test_num );

#endif