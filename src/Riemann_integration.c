//The next program uses a function pointer to invoke one of two functions (sin or cos) indirectly from another function (compute_sum, computing an approximation of the function's Riemann integration). The program operates by having function main call function compute_sum twice, passing it a pointer to the library function sin the first time, and a pointer to function cos the second time. Function compute_sum in turn invokes one of the two functions indirectly by dereferencing its function pointer argument funcp multiple times, adding together the values that the invoked function returns and returning the resulting sum. The two sums are written to the standard output by main. 

// add -lm as compiler flag
#include <math.h>
#include <stdio.h>


// Function taking a function pointer as an argument

double compute_sum(double (*funcp)(double), double lo, double hi) {

    double sum = 0.0;


    // Add values returned by the pointed-to function '*funcp'

    int i;

    for(i = 0;  i <= 100;  i++) {

        // Use the function pointer 'funcp' to invoke the function

        double x = i / 100.0 * (hi - lo) + lo;

        double y = funcp(x);

        sum += y;

    }

    return sum / 101.0;

}


double square(double x) {

     return x * x;

}


int main(void) {

    double  sum;


    // Use standard library function 'sin()' as the pointed-to function

    sum = compute_sum(sin, 0.0, 1.0);

    printf("sum(sin): %g\n", sum);


    // Use standard library function 'cos()' as the pointed-to function

    sum = compute_sum(cos, 0.0, 1.0);

    printf("sum(cos): %g\n", sum);


    // Use user-defined function 'square()' as the pointed-to function

    sum = compute_sum(square, 0.0, 1.0);

    printf("sum(square): %g\n", sum);


    return 0;

}
