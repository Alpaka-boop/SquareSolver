#ifndef SQUARESOLVER_INCLUDED
#define SQUARESOLVER_INCLUDED

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "squaresolver.h"


int solve_quadr_eq( double a, double b, double c, double *x1, double *x2 )
{
    assert(x1 != x2);
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(a != NAN);
    assert(b != NAN);
    assert(c != NAN);
     
    if (equal(a, 0)) 
    {
        int roots = solve_linear_eq(b, c, x1);

        *x2 = *x1;

        return roots;
    }
    else
    {
        if (equal(c, 0))
        {
            solve_linear_eq(a, 0, x1);
            solve_linear_eq(1, b, x2);

            return TWO_ROOTS;
        }
        else 
        {
            double d = b * b - 4 * a * c;

            if (d < 0) return NO_ROOTS;

            if (equal(d, 0))
            {
                *x1 = *x2 = (-b) / (2 * a);
                return ONE_ROOT;
            }

            double sqrt_d = sqrt(d);

            *x1 = (-b + sqrt_d) / (2 * a);
            *x2 = (-b - sqrt_d) / (2 * a);

            return TWO_ROOTS;
        }
    }
}

int solve_linear_eq( double a, double b, double *x )
{
    if (equal(a, 0) && !equal(b, 0))
    {
        *x = NAN;
        return NO_ROOTS;
    }
    if (equal(a, 0) && equal(b, 0))
        return UNLIM_NUM_ROOTS;

    *x = (-b) / a;

    if (equal(*x, 0))
        *x = 0;

    return ONE_ROOT;
}

int equal( double a, double b )
{
    return fabs(a - b) < EPS;
}

void input( double *a, double *b, double *c )
{
    printf("Enter a, b, c: "); 

    while (scanf("%lf %lf %lf", a, b, c) != NUM_OF_ARGS)
    {
        printf("\nNe pravilno poprobuy istcho ras\n");
        clear_buf();
    }
}

void clear_buf()
{
    char c = 0;

    do 
    {
        c = getchar();
    } while(c != '\n' || c != EOF);
}

void output( int roots, double x1, double x2 )
{
    switch (roots)
    {
    case NO_ROOTS:
        printf("No roots\n");
        break;
    case ONE_ROOT:
        printf("One root: %lf\n", x1);
        break;
    case TWO_ROOTS:
        printf("Two roots: %lf, %lf\n", x1, x2);
        break;
    case UNLIM_NUM_ROOTS:
        printf("Unlimited number of roots\n");
        break;
    default:
        printf("Unexpected error (number of roots: %d)", roots);
        break;
    }
}

void test()
{
    //        a   b  c x1_ref x2_ref roots_ref test_num
    unit_test(1,  5, 4,  -1,    -4,     2,      1);
    unit_test(1,  6, 9,  -3,    -3,     1,      2);
    unit_test(0,  2, -4,  2,     2,     1,      3);
    unit_test(1, -5, 4,   1,     4,     2,      4);
    unit_test(1, -8, 15,  5,     3,     2,      5);
}

int unit_test( double a, double b, double c, double x1_ref, double x2_ref, int roots_ref, int test_num )
{
    double x1 = 0, x2 = 0;
    int roots = 0;

    roots = solve_quadr_eq(a, b, c, &x1, &x2);

    if (roots != roots_ref)
    {
        printf("Wrong number of roots : test number: %d\n", test_num);
        printf("Input data: a: %lf, b: %lf, c: %lf, ref num roots: %d, num of roots: %d\n", a, b, c, roots_ref, roots);

        return 1;
    }

    if ((((x1_ref == x1 && x2_ref == x2) || (x1_ref == x2 && x2_ref == x1))) == 0)
    {
        printf("Wrong roots : test number: %d\n", test_num);
        printf("Input data: a: %lf, b: %lf, c: %lf, ref roots: (%lf, %lf), roots: (%lf, %lf)\n", a, b, c, x1_ref, x2_ref, x1, x2);

        return UNIT_TEST_ERROR;
    }

    return 0;
}

#endif