#include <stdio.h>
#include <math.h>

int main() {
    int di = 17, si = 5, z = 18;
    long long int sum = 0;
    for(int j = 2; j <=25; j++){
        sum += ((pow((double)(di-z), j) + 121) * 5) / j;
    }
    printf("%lld", sum);
    return 0;
}
