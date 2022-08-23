#include <math.h>
#include "squaresolver.h"

int main()
{
    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    int roots = NAN;

    test();

    input(&a, &b, &c);
    roots = solve_quadr_eq(a, b, c, &x1, &x2);
    output(roots, x1, x2);

    return 0;
}