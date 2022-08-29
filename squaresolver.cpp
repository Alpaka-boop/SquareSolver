#include <assert.h>
#include <cmath>
#include "squaresolver.h"
#include "color.h"

int handle_zero_c( double a, double b, double *x1, double *x2 ) 
{
    int num_of_the_roots = 0;

    num_of_the_roots++;
    *x1 = 0;
    num_of_the_roots += solve_linear_eq(a, b, x2);

    if (num_of_the_roots == 0)
        return num_of_the_roots;
    if (num_of_the_roots > 2)
        return INF_ROOTS;
    return is_equal(*x1, *x2) ? ONE_ROOT : TWO_ROOTS;
}

int diskriminant( double a, double b, double c, double *x1, double *x2 )
{
    double d = b * b - 4 * a * c;

    if (d < 0) return NO_ROOTS;

    if (is_equal(d, 0))
    {
        *x1 = *x2 = (-b) / (2 * a);
        return ONE_ROOT;
    }

    double sqrt_d = sqrt(d);

    *x1 = (-b + sqrt_d) / (2 * a);
    *x2 = (-b - sqrt_d) / (2 * a);

    return TWO_ROOTS;
}

int solve_quadr_eq( double a, double b, double c, double *x1, double *x2 )
{
    assert(x1 != x2);
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c)); 
     
    if (is_equal(a, 0)) 
    {
        int roots = solve_linear_eq(b, c, x1);

        *x2 = *x1;

        return roots;
    }
    else
    {
        if (is_equal(c, 0))
            return handle_zero_c(a, b, x1, x2);
        return diskriminant(a, b, c, x1, x2);
    }
}

int solve_linear_eq( double a, double b, double *x )
{
    if (is_equal(a, 0) && !is_equal(b, 0))
    {
        *x = NAN;
        return NO_ROOTS;
    }
    if (is_equal(a, 0) && is_equal(b, 0))
        return INF_ROOTS;

    *x = (-b) / a;

    if (is_equal(*x, 0))
        *x = 0;

    return ONE_ROOT;
}

int is_equal( double a, double b )
{
    return fabs(a - b) < EPS;
}

void input( double *a, double *b, double *c )
{   
    printf(RED "Hello, " GREEN "my " YELLOW "dear " BLUE "friend!!! " VIOLET);
    printf("Do " TURQOUISE "you " RED "want " GREEN "to " YELLOW "solve " BLUE 
            "some " VIOLET "square " TURQOUISE "equations?!\n" RESET);
    printf("Enter a, b, c: "); 

    while (scanf("%lf %lf %lf", a, b, c) != NUM_OF_ARGS)
    {
        printf("\nIncorrect entered data, make another try\n");
        clear_buf();
        printf("Enter a, b, c:");
    }
}

void clear_buf()
{
    int c = 0;

    do 
    {
        c = getchar();
    } while(c != '\n' && c != EOF);
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
        case INF_ROOTS:
            printf("Unlimited number of roots\n");
            break;
        default:
            printf("Unexpected number of roots: %d", roots);
    }
}
