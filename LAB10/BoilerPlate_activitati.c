#include <stdio.h>
#include <string.h>
typedef struct{
	int s, f; //timpii de start si final 
	char nume[100]; //denumire
}activitate;
activitate activitati[100];
int n;
void select_activitati(int x[], int* nr_activitati){
	//se selecteaza activitatile conform strategiei greedy
	//x[i] contine numere 0:n-1
	//x[i] = k, inseamna ca am selectat activitatea k
	//nr_activitati se modifica
	x[0] = 0;
	*nr_activitati = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(activitati[i].f > activitati[j].f){
//                int t1 = activitati[i].s;
//                activitati[i].s = activitati[j].s;
//                activitati[j].s = t1;
//                t1 = activitati[i].f;
//                activitati[i].f = activitati[j].f;
//                activitati[j].f = t1;
//                char temp[100];
//                memcpy(temp, activitati[i].nume, 99);
//                memcpy(activitati[i].nume, activitati[j].nume, 99);
//                memcpy(activitati[j].nume, temp, 99);
                activitate temp = activitati[i];
                activitati[i] = activitati[j];
                activitati[j] = temp;
            }
        }
    }
    int lastEnd = 0;
    int k = 0;
    for(int i = 0; i < n; i++){
        if(activitati[i].s >= lastEnd){
            x[k++] = i;
            (*nr_activitati)++;
            lastEnd = activitati[i].f;
        }
    }

}

void afisare(int x[], int nr){
	printf("Am selectat %d activitati\n", nr);
	for (int i = 0; i < nr; i++){
		printf("(%2d) %2d : %2d %s", x[i], activitati[x[i]].s, activitati[x[i]].f, activitati[x[i]].nume);
	}
}

int main(){
	FILE* f = fopen("date_activitati.txt", "r");

	fscanf(f,"%d", &n);
	for (int i = 0; i < n; i++){
		fscanf(f,"%d%d", &activitati[i].s, &activitati[i].f);
		fgets(activitati[i].nume, 100, f);
	}
	fclose(f);

	int x[100]={};
	int nr_activitati = 0;
	select_activitati(x, &nr_activitati);
	afisare(x, nr_activitati);
	return 0;
}
