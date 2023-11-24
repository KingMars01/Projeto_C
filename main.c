#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define troca(A,B) {Item c = A; A = B; B = c;}

typedef struct Item {

    int chave_t;
    float elementos;

}Item;


void Insertion_Sort(Item *v, int n){

    int i,j;

    //e troquei esse for pois nao estava lendo o vetor inteiro
    for(i=0; i <= n; i++){
        for(j=i; j>= 0; j--){
            //apenas inverti o sinal de menor para maior
            if(v[j-1].chave_t < v[j].chave_t){
                troca(v[j-1],v[j]);
            }
        }
    }
}

//ver se esse metodo esta certo, torna-lo adaptável
void Buble_Sort(Item *v, int n){

    int i,j;

    for(i=0; i < n-1; i++){
        for(j=1; j >= n-i; j++){
            if(v[j].chave_t < v[j-1].chave_t)
                troca(v[j-1],v[j]);
        }
    }

}


void Shell_Sort(Item *v, int n){

    int i,j,h;
    Item aux;

    for (h = 1; h < n; h = 3*h+1);

    while(h > 0){
        h = (h-1)/3;
        for (i = h; i < n; i++){
            aux = v[i];
            j = i;
            //mudei aqui esse j >= h &&
            while(j >= h && v[j-h].chave_t < aux.chave_t){
                v[j] = v[j-h];
                j -= h;
                if(j < h)break;
            }
            v[j] = aux;
        }
    }

}


void Sort(Item *v, Item *c, int i, int f){

    if(i < f){
        int m = (i + f)/2;
        Sort(v,c,i,m);
        Sort(v,c,m+1,f);
        merge(v, c, i, m, f);

    }
}


void merge(Item *v, Item *c, int i, int m, int f){

    int z,iv = i, ic = m+1;
    for (z = i; z<= f; z++) c[z] = v[z];
    z = i;

    while(iv <= m && ic <= f)
    {
        if (c[iv].chave_t <= c[ic].chave_t)
        {
            v[z++] = c[iv++];
        }
        else
        {
            v[z++] = c[ic++];
        }
    while(iv <= m)
    {
        v[z++] = c[iv++];
    }
    while(ic <= f)
    {
        v[z++] = c[ic++];
    }
    }

}


void Merge_Sort(Item *v, int n){

    int *c = malloc(sizeof(int) * n);
    Sort(v,c,0,n-1);
    free(c);

}


int participacao_esquerda(int *v, int LI, int LS){

    int aux, pivo, e=LI, d=LS;
    pivo = v[e];
    while(e < d){
        while((v[e] <= pivo)&&(e < LS)){e++;}
        while((v[d] > pivo)&&(d > LI)){d--;}
        if(e < d){
            aux = v[e]=v[d]; v[d]=aux;
        }
    }
      aux = v[LI];v[LI] = v[d]; v[d]=aux;
      return d;
}


void quicksort_esquerda(int *v, int LI, int LS){

    if(LI < LS){
        int p;  //qualquer coisa criar i
        p = participacao_esquerda(v,LI,LS);
        quicksort_esquerda(v,LI,p-1);
        quicksort_esquerda(v,p+1,LS);
    }

}


int participacao_direita(int *v, int LI, int LS){

    int aux, pivo, e=LI, d=LS;
    pivo = v[d];
    while(e < d){
        while((v[e] > pivo)&&(e < LS)){e++;}
        while((v[d] <= pivo)&&(d > LI)){d--;}
        if(e < d){
            aux = v[e]=v[d]; v[d]=aux;
        }
    }
       aux = v[LS];v[LS] = v[e]; v[e] = aux;
       return e;
}


void quicksort_direita(int *v, int LI, int LS){

    if(LI < LS){
        int p;  //qualquer coisa criar i
        p = participacao_direita(v,LI,LS);
        quicksort_direita(v,LI,p-1);
        quicksort_direita(v,p+1,LS);
    }

}


int participacao_meio(int *v, int LI, int LS) {
    int aux, pivo, meio;
    meio = (LI + LS) / 2;
    pivo = v[meio];

    // Troca o pivô para a posição LI para facilitar a implementação
    aux = v[meio];
    v[meio] = v[LI];
    v[LI] = aux;

    int e = LI + 1;
    int d = LS;

    while (e <= d) {
        while (e <= LS && v[e] <= pivo) {e++;}
        while (d > LI && v[d] > pivo) {d--;}
        if (e < d) {
            aux = v[e];
            v[e] = v[d];
            v[d] = aux;
        }
    }

    // Reposiciona o pivô na posição correta
    aux = v[LI];
    v[LI] = v[d];
    v[d] = aux;

    return d;
}

void quicksort_meio(int *v, int LI, int LS) {
    if (LI < LS) {
        int p = participacao_meio(v, LI, LS);
        quicksort_meio(v, LI, p - 1);
        quicksort_meio(v, p + 1, LS);
    }
}


void countingSort(Item *v, int n) {
    int max = v[0].chave_t;
    for (int i = 1; i < n; i++) {
        if (v[i].chave_t > max) {
            max = v[i].chave_t;
        }
    }

    // Criar array para contar a frequência de cada elemento
    int *count = (int *)malloc((max + 1) * sizeof(int));
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Contar a frequência de cada elemento
    for (int i = 0; i < n; i++) {
        count[v[i].chave_t]++;
    }

    // Reconstruir o array ordenado
    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            v[index].chave_t = i;
            count[i]--;
            index++;
        }
    }

    free(count);
}


void imprimirArray(Item vetor[4]) {
    for (int i = 0; i < 4; i++) {

        printf("Chave: %d\n", vetor[i].chave_t);
        printf("Numero Float: %.2f\n", vetor[i].elementos);
        printf("--------------------------------\n");
    }
}


int main()
{
    double tempogasto;
    clock_t inicio,fim;
    double media =0;
    Item vetor[4];


    printf("Digite a chave e o numero do vetor (tamanho 4)\n\n");
    for (int i = 0;i < 4;i++){
        printf("Chave: ");
        scanf("%d",&vetor[i].chave_t);
        printf("Numero float: ");
        scanf("%f",&vetor[i].elementos);
        printf("\n");
        system("cls");
    }
    printf("\n\n");


        printf("\n===========================================================");
        printf("\n\t  Ordenacao de vetores\n");


            printf("\nVetor nao ordenado:\n\n");
            imprimirArray(vetor);
            inicio = clock();
            Insertion_Sort(vetor,4);
            fim = clock();
            tempogasto = ((double) (fim-inicio))/CLOCKS_PER_SEC;
            media += tempogasto;
            printf("\n\nVetor ordenado com Insertion_Sort:\n\n");
            printf("Tempo gasto para ordenar o vetor:%f\n\n",tempogasto);
            imprimirArray(vetor);

            /*
            printf("\n\n");
            inicio = clock();
            Buble_Sort(vetor,4);
            fim = clock();
            tempogasto = ((double) (fim-inicio))/CLOCKS_PER_SEC;
            media += tempogasto;
            printf("Vetor ordenado com Buble_Sort:\n\n");
            printf("Tempo gasto para ordenar o vetor:%f\n\n",tempogasto);
            imprimirArray(vetor);


            printf("\nVetor nao ordenado:\n\n");
            imprimirArray(vetor);
            printf("\n\n");
            Shell_Sort(vetor,4);
            printf("Vetor ordenado com Shell_Sort:\n\n");
            imprimirArray(vetor);


            printf("\nVetor nao ordenado:\n\n");
            imprimirArray(vetor);
            printf("\n\n");
            Merge_Sort(vetor,4);
            printf("Vetor ordenado com Shell_Sort:\n\n");
            imprimirArray(vetor);


            printf("\nVetor nao ordenado:\n\n");
            imprimirArray(vetor);
            printf("\n\n");
            quicksort_esquerda(vetor, 0, 3); // na funcao la em cima recebe um vetor tipo int e nao Item
            printf("Vetor ordenado com Quick Sort (pivo esquerda):\n\n");
            imprimirArray(vetor);


            printf("\nVetor nao ordenado:\n\n");
            imprimirArray(vetor);
            printf("\n\n");
            // Chama o Counting Sort
            countingSort(vetor, 4);
            printf("Vetor ordenado com Counting Sort:\n\n");
            imprimirArray(vetor);
                                    */


    return 0;
}
