#include<stdlib.h>
#include<stdio.h>
#define tam 100
typedef int heap[tam];
int tam_atu=0;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int pai(int indice){
    return (indice-1)>>1;
}
 
int insereHeap(heap arv, int tam_atu, int valor, int pos){
    if (tam_atu >= tam)
        return -1;

    tam_atu++;
    int i = tam_atu-1;
    arv[i] = valor;
    /*sobe na arvore trocando todos os pai maiores que seus filhos
    ate achar um certo ou chegar na raiz*/
    while (i!=0 && arv[pai(i)] > arv[i]){
        swap(&arv[pai(i)], &arv[i]);
        i = pai(i);
    }
    return 0;
}

int main(){
    heap arv;
    for (int i=0; i<tam; i++)
        arv[i] = -1;
    



    return 0;
}