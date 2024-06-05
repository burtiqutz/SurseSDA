#include <stdio.h>
#include <stdlib.h>


typedef struct _pair{
    int x, y;
}PAIR;

PAIR sol[100];
int n, m;
int visited[100][100];//max 100 elem
int moving;
void printSolution(int end){
    printf("Solution found:\n");
    for(int i = 0; i <= end; i++){
        printf("%d %d\n", sol[i].x, sol[i].y);
    }
}

int phi(int x1, int y1, int x2, int y2, int** a){
    if(a[x1][y1] < a[x2][y2] || (a[x1][y1] == a[x2][y2] && moving)){
        return 1;
    }
    return 0;
}

void backtrack(int k, int** a, int xOut, int yOut, int xPos, int yPos){
    int xNext = 0, yNext = 0;///current values
    if(k >= 100){
        return;
    }
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (int i = 0; i < 4; i++) {
        xNext = xPos + directions[i][0];
        yNext = yPos + directions[i][1];
        if(xNext < n && xNext >= 0 && yNext >= 0 && yNext < m){///out of bounds check so we dont segfault
            if(phi(xNext, yNext, xPos, yPos, a)){///valid path check;
                moving = 1;//the ball starts rolling
                sol[k].x = xNext;
                sol[k].y = yNext;
                 if (!visited[xNext][yNext]){
                    if(sol[k].x == xOut && sol[k].y == yOut){
                        printSolution(k);
                    } else{
                        visited[xNext][yNext] = 1;
                        backtrack(k + 1, a, xOut, yOut, xNext, yNext);
                        visited[xNext][yNext] = 0;
                    }
                }
            }
        }
    }
}

int main() {
    int xOut = 0, yOut = 0;
    int xPos = 0, yPos = 0;
    FILE* f = fopen("input.txt", "r");
    if (f == NULL){
        exit(-1);
    }

    fscanf(f, "%d %d", &n, &m);
    int** a = calloc(n, sizeof(int*));
    if(a == NULL){
        exit(-2);
    }

    for(int i = 0; i < n; i++){
        a[i] = calloc(m, sizeof(int));
        if(a == NULL){
            exit(-3);
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            fscanf(f, "%d", &a[i][j]);
        }
    }

    fscanf(f, "%d %d", &xPos, &yPos);
    ///determining start pos
    int min = 999;
    for(int i = 0; i < n;i++){
        for(int j = 0; j < m; j++){
            if(a[i][j] < min){
                min = a[i][j];
                xOut = i;
                yOut = j;
            }
        }
    }
    a[xOut][yOut]--;///scrie in cerinta ca e cu 1 mai mica
    sol[0].x = xPos;
    sol[0].y = yPos;
    visited[xPos][yPos] = 1;
    backtrack(1, a, xOut, yOut, xPos, yPos);

    return 0;
}
