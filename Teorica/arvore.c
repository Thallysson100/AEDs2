#include<stdio.h>
#include<stdlib.h>
typedef struct noArvore_{
    int valor;
    struct noArvore_ *esq;
    struct noArvore_ *dir;
}noArvore;

noArvore *insereA(noArvore *raiz, noArvore *n){
    if (raiz == NULL) return n;
    if (raiz->valor > n->valor)
        raiz->esq = insereA(raiz->esq, n);
    else
        raiz->dir = insereA(raiz->dir, n);
    return raiz;
}
noArvore *busca(noArvore *raiz, int k){
    if (raiz == NULL || raiz->valor == k)
        return raiz;
    if (raiz->valor > k)
        return busca(raiz->esq, k);
    else
        return busca(raiz->dir, k);
}
noArvore *buscaPai(noArvore *raiz, int k){
    if (raiz==NULL || raiz->esq->valor==k || raiz->dir->valor==k)
        return raiz;
    if (raiz->valor > k)
        return buscaPai(raiz->esq, k);
    else
        return buscaPai(raiz->dir, k);
}
noArvore *removeA(noArvore *raiz, noArvore *n){

}
int main(){
    return 0;
}