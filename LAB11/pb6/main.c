#include <stdio.h>

int main() {
    int n = 4;
    int m = 4;
    int dp[m] = {};
    int a[4][4] = {
            {1, 4, 2, 3},
            {2, 9, 8, 7},
            {3, 6, 3, 8},
            {1, 2, 3 , 3}
    };

    for(int j = 0; j < m; j++){
        int count = 0;
        int max = 0;
        for(int i = 0; i < n; i++){
            //parcurg pe coloane
            if (a[i][j] > max){
                max = a[i][j];
                count++;
            }
        }
        dp[j] = count;
    }
    for(int i = 0; i < m; i++){
        printf("%d ", dp[i]);
    }

    return 0;
}
