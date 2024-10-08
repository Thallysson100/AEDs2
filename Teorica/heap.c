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
int filhoEsq(int indice){
    return indice<<1+1;
}
int filhoDir(int indice){
    return indice<<1+2;
}
int insereHeap(heap arv, int tam_atu, int valor){
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
int removeHeap(heap arv, int tam_atu, int valor){
    if (tam_atu <= 0)
        return -1;
    if (tam_atu == 1){
        tam_atu--;
        return arv[0];
    }
        
    tam_atu--;
    arv[0] = arv[tam_atu];
    int esq, dir, min = 0, i = 0;
    
    do{
        esq = filhoEsq(i);
        dir = filhoDir(i);
        if (arv[esq] < arv[i])
            min = esq;
        if (arv[dir] < arv[min])
            min = dir;
        if (min != i){
            swap(&arv[i], &arv[min]);
            i = min;
        }
    }while (i != min);

}
int main(){
    heap arv;
    for (int i=0; i<tam; i++)
        arv[i] = -1;
    



    return 0;
}