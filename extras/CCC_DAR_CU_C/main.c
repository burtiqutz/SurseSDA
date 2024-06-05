#include <stdio.h>

void solve_test(int test_number, FILE* fin, FILE* fout){

    int visited[100][100] = {};
    char matrix[100][100] = {};
    int n = 0, m = 0;

    int tree_x = 0, tree_y = 0;
    fscanf(fin, "%d %d", &m, &n);
    char buf[100];
    for(int i = 0; i < n; i++){
        fscanf(fin, "%s", &buf);
        for(int j = 0; j < m; j++){

        }
    }

}

int main() {

    int tests;
    FILE* f = fopen("level3_1.txt", "r");
    FILE* g = fopen("111OUTPUT.txt", "w");
    fscanf(f, "%d", &tests);
    for (int i = 0; i < tests; i++)
    {
        solve_test(i, f, g);
    }
    return 0;
}
