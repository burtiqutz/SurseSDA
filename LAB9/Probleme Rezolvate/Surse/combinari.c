#include <stdio.h>
#include <stdlib.h>

/*      Problema cu aranjamente   */

int v[100], n, m, count;

void out()
{
    for(int i=1; i<=m; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void backt(int k)
{
    for(int i=v[k-1] + 1; i<=n; i++)
    {
        v[k]=i;
            if(k==m)
            {
                out();
                count++;
            }
            else{
                backt(k+1);
            }
    }
}

int main()
{
    printf("n>");
    scanf("%d", &n);
    printf("m>");
    scanf("%d", &m);

    backt(1);
    printf("%d solutions found", count);
    return 0;
}