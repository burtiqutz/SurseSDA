#include <stdio.h>
#define MAX 1000

int s,n, monede[MAX], combinatii[MAX + 1], min[MAX];
void read();
void DP1();
void DP2();
void write1();
void write2();
int main()
{
    read();
    DP2();
    write2();
	return 0;
}
void read()
{
    int i;
    scanf("%d",&n);
    scanf("%d",&s);
    for(i = 0; i < n; i++)
        scanf("%d",&monede[i]);
}
void DP1()///PB1
{
    combinatii[0] = 1;
    for(int i = 0; i < n; i++){///monede
        for(int j = 0; j <= s; j++){///combinatii
            if(j >= monede[i]){
                combinatii[j] += combinatii[j - monede[i]];
            }
        }
    }
}
void DP2(){///PB2
    for(int i = 0; i < MAX; i++){
        min[i] = 50000;///infinite
    }
    min[0] = 0;
    for(int i = 1; i <= s; i++){//parcurg sumele de la 1
        for(int j = 0; j < n; j++){//parcurg monezile
            if (monede[j] <= i && min[i -monede[j]] + 1 < min[i]){
                min[i] = min[i - monede[j]] + 1;
            }
        }
    }
}
void write1()///PB1
{
    printf("%d \n", combinatii[s]);
    for(int i = 0; i <= s; i++)
        printf("%d ", combinatii[i]);
}
void write2(){///PB2
    for(int i = 0; i <= s; i++){
        printf("%d ", min[i]);
    }
}