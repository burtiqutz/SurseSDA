#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    double a = 9.36, b = 15.66, x = 11.84, z = 3.73;
    double sum = 0;
    for(double i = 1.0; i <= 10.0; i++){
        double pow1 = pow(i, z);
        double termen1 = 16.94 - b;
        double pow2 = pow(termen1, i);
        double termen2 = x / a;
        double paranteza = pow2 - termen2;
        double termenMare = pow1 * paranteza;
        sum += termenMare;
    }
    printf("%lf", sum);
    return 0;
}
