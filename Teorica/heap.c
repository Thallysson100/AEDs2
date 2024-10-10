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
        i = (i-1)>>1; //i = pai do i
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
    int esq, dir, min = 0, i = 0, flag;
    
    do{
        flag = 0;
        esq = (i<<1)+1; //filho a esquerda de i
        dir = (i<<1)+2; //flho a direita de i
        if (arv[esq] < arv[i])
            min = esq;
        if (arv[dir] < arv[min])
            min = dir;
        if (min != i){
            swap(&arv[i], &arv[min]);
            i = min;
            flag = 1;
        }
    }while (flag);

}
int main(){
    heap arv;
    for (int i=0; i<tam; i++)
        arv[i] = -1;
    



    return 0;
}