#include <stdio.h>
#include <stdlib.h>

int merge(int *a,int low,int mid,int high){
    int i=low,k=low,j=mid+1;
    int *aux= (int*)malloc((high+1)*sizeof (int));
    if(aux==NULL){
        exit(1);
    }

    while(i<=mid && j<=high){
        if(a[i] <= a[j]){
            aux[k++]=a[i];
            i++;
        } else{
            aux[k++]=a[j];
            j++;
        }
    }
    while (i <= mid){
        aux[k++]=a[i++];
    }
    while (j <= high){
        aux[k++]=a[j++];
    }
    for(int kk=low; kk<=high; kk++)
        a[kk]=aux[kk];
    free(aux);
}

void mergeSort(int* a, int low, int high){
    if(low < high){
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid+1, high);
        merge(a, low, mid, high);
    }
}

void printArr(int* a, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int x[100], visited[1000];


void bt(int *a, int k, int size, int sum){///b
    if(k > size)
        return;

    for(int i = 0; i < size; i++){
        ///parcurg tot spatiul de solutii
        x[k] = a[i];///aleg o solutie partiala
        if(visited[x[k]] == 0 && x[k] > x[k-1]){
            if(sum - x[k] == 0) {
                printArr(x, k+1);
            } else if (sum-x[k] > 0){
                visited[x[k]] = 1;///consider
                bt(a, k+1, size, sum-x[k]);
                visited[x[k]] = 0;///backtrack
            }
        }
    }
}

int binarySearch(int*a,int searched, int low, int high){///aux for c
    if(low > high){
        return -1;
    }
    int mid = (low + high) / 2;
    if(a[mid] == searched){
        return mid;
    }
    if(a[mid] > searched){
        ///search in left side
        return binarySearch(a, searched, low, mid - 1);
    } else{
        return binarySearch(a, searched, mid+1, high);
    }
}

void findSums(int*a, int s, int size){/// C
    int* used = calloc(size, sizeof(int));
    for(int i = 0; i < size; i++){
        if(s - a[i] > 0){
            int index = binarySearch(a, (s - a[i]), 0, size);
            if(index != -1 && used[i] == 0 && used[index] == 0 && a[i] != a[index]){
                used[i] = 1;
                used[index] = 1;
                printf("(%d %d)\n", a[i], s-a[i]);
            }
        }
    }

}

int dp[100];
void subseq(int*a, int n){///aux for D
    dp[0] = a[0];
    for(int i = 1; i < n; i++){
        dp[i] = a[i] + dp[i-1];
    }
}

int main() {
    int a[] = {4, 1, 3, 2};
    int n = sizeof (a) / sizeof (int);
    mergeSort(a, 0, n - 1);
    printArr(a, n);



    int sortedArr[] = {4, 6, 8, 10, 12, 14, 16, 18, 20};
    int s = 24;
    bt(sortedArr,0,9,24);
    findSums(sortedArr, s, 9);

    ///d
    subseq(sortedArr, 9);///generating dp arr
    int k = 0, i = 0, j = 0;
    scanf("%d", &k);
    for(int l = 0; l < k; l++){
        scanf("%d%d", &i, &j);
        printf("pentru %d si %d suma este %d", i, j, (dp[j] - dp[i-1]));
    }
    return 0;
}
