#include <assert.h>
#include <cmath>
#include <stdio.h>
#include "squaresolver.h"
#include "color.h"

void run_tests( const char user_file[] )
{
    int error = 0, 
        curr_line = 0,
        roots_cor = 0; 
    double a = NAN, 
           b = NAN, 
           c = NAN, 
           x1_cor = NAN, 
           x2_cor = NAN;

    const char default_file[] = {STOCK_TEST_FILE};

    FILE *file = NULL;

    if (user_file == NULL)
        file = fopen(default_file, "r");
    else 
        file = fopen(user_file, "r");
    
    assert(file != NULL);

    while (file_input(file, &a, &b, &c, &x1_cor, &x2_cor, &roots_cor))
    {
        error += unit_test(a, b, c, x1_cor, x2_cor, roots_cor, curr_line + 1);
        curr_line++;
    }

    if (error == 0)
        printf(GREEN "All test completed successfully)\n" RESET);

    fclose(file);
}

int file_input( FILE *input_file, double *a, double *b, double *c, 
                double *x1_cor, double *x2_cor, int *roots_num_cor )
{
    assert(input_file != NULL);

    int error = fscanf(input_file, "%lf, %lf, %lf, %lf, %lf, %d", 
                       a, b, c, x1_cor, x2_cor, roots_num_cor);

    if (error > 0 && error != NUM_OF_FILE_ARGS)
    {
        printf("Error in number of red file args\n");
        printf("%i args have been red", error);
        return 0;
    }

    if (error == EOF)
        return 0;

    assert(!std::isnan(*a));
    assert(!std::isnan(*b));
    assert(!std::isnan(*c));
    assert(!std::isnan(*x1_cor));
    assert(!std::isnan(*x2_cor));
    assert(!std::isnan(*roots_num_cor));
        
    return 1;
}

int unit_test( double a, double b, double c, double x1_cor, double x2_cor, int roots_cor, int test_num )
{
    double x1 = 0, x2 = 0;
    int roots = 0;

    roots = solve_quadr_eq(a, b, c, &x1, &x2);

    if (roots != roots_cor)
    {
        printf(RED "FAIL\n");
        printf("Wrong number of roots : test number: %d\n", test_num);
        printf("Input data: a: %lf, b: %lf, c: %lf, correct num of roots: %d, num of roots: %d\n" RESET, 
                a, b, c, roots_cor, roots);

        return UNIT_TEST_ERROR;
    }

    if (roots_cor > NO_ROOTS && roots_cor < INF_ROOTS && 
      (!(is_equal(x1_cor, x1) && is_equal(x2_cor, x2)) && 
       !(is_equal(x1_cor, x2) && is_equal(x2_cor, x1))))
    {
        printf(RED "FAIL\n");
        printf("Wrong roots : test number: %d\n", test_num);
        printf("Input data:\n a: %lf, b: %lf, c: %lf,\n correct roots: (%lf, %lf), roots: (%lf, %lf)\n" RESET, 
                a, b, c, x1_cor, x2_cor, x1, x2);

        return UNIT_TEST_ERROR;
    }

    printf(GREEN "Success\n" RESET);

    return 0;
}
