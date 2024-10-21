#include<stdlib.h>
#include<stdio.h>
typedef struct vetPar_{
    int valor;
    int freq;
}vetPar;
typedef struct arvPar_{
    int valor;
    int parti;
    struct arvPar_ *esq;
    struct arvPar_ *dir; 
}arvPar;

arvPar *criaArvPar(vetPar vet[], int inf, int sup){
    if (sup<inf)
        return NULL;
    arvPar *raiz = malloc(sizeof(arvPar));   
    int ifreqmax=0;   
    for (int i=inf; i<=sup; i++){
        if (vet[i].freq > vet[ifreqmax].freq)
            ifreqmax = i;
        printf("%d ", vet[i].valor);
    }
    puts("");
    raiz->valor = vet[ifreqmax].valor;
    for (int i=ifreqmax; i<sup; i++)
        vet[i]=vet[i+1];
    sup--;

    for (int i=0; i<=sup; i++)
        printf("%d ", vet[i].valor);
    puts("");
    int mid = (inf+sup)>>1;
    raiz->parti = vet[mid].valor;
    raiz->esq = criaArvPar(vet, inf, mid);
    raiz->dir = criaArvPar(vet, mid+1, sup);
    return raiz;

}
void printTree(arvPar *raiz, int altura) {
     if (!raiz) 
         return;
    printTree(raiz->dir, altura + 1);

    for (int i = 0; i < altura; i++)
        printf("      ");  
    printf( "%d|%d\n", raiz->valor, raiz->parti);

    printTree(raiz->esq, altura + 1);
}
int main(){
    vetPar vetArv[15];
    //int vetValor[] = {32,33,34,36,38,40,55,60,61,65,68,72,74,91,97};
    //int vetFreq[] = {12,4,10,11,7,9,8,15,14,1,5,6,2,3,13};

    int vetValor[] = {33, 38, 42, 45, 48, 49, 50, 57, 60, 64, 73, 83, 84, 85, 95};
    int vetFreq[] = {11, 15, 8, 10, 7, 14, 6, 12, 5, 1, 13, 3, 4, 9, 2};

    //int vetValor[] = {33, 38, 42, 45, 48, 49, 50};
    //int vetFreq[] = {11, 15, 8, 10, 7, 14, 6, 12};
    for (int i=0; i<15; i++){
        vetArv[i].valor=vetValor[i];
        vetArv[i].freq=vetFreq[i];
    }

    arvPar *raiz = criaArvPar(vetArv, 0, 14);
    printTree(raiz, 0);
    return 0;
}