#include<stdio.h>
#include<stdlib.h>
typedef struct noArvore_{
    int valor;
    struct noArvore_ *esq;
    struct noArvore_ *dir;
}noArvore;

noArvore *insereNo(noArvore *raiz, noArvore *n){
    if (raiz == NULL) return n;
    if (raiz->valor > n->valor)
        raiz->esq = insereNo(raiz->esq, n);
    else
        raiz->dir = insereNo(raiz->dir, n);
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
    if (raiz==NULL || (raiz->esq!=NULL && raiz->esq->valor==k)
        || (raiz->dir!=NULL && raiz->dir->valor==k))
        return raiz;
    if (raiz->valor > k)
        if (raiz->esq!=NULL)
            return buscaPai(raiz->esq, k);
    else
        if (raiz->dir!=NULL)
            return buscaPai(raiz->dir, k);
}
noArvore *removeRaiz(noArvore *raiz){
    noArvore *temp=raiz;
    if (raiz==NULL)
        return raiz;
    if (raiz->dir==NULL)
        raiz=raiz->esq;
    else if (raiz->esq==NULL)
        raiz=raiz->dir;
    else{
        temp = raiz->esq;          //vai para esquerda, depois para
        while (temp->dir != NULL)  //mais direita possível
            temp = temp->dir;     
        raiz->valor = temp->valor;
        noArvore *pai = buscaPai(raiz, temp->valor);
        pai->dir=temp->esq;
    }
    free(temp);
    return raiz;   
}

noArvore * removeNo(noArvore * raiz, int valor) {
    noArvore * n = busca(raiz, valor); //checa se o noh existe
        if (n) {
            noArvore * pai = buscaPai(raiz, n->valor); //descobre quem eh o noh pai
            if (pai) { //caso tenha noh pai
                if (pai->dir == n) //noh a ser removido eh filho a direita
                    pai->dir = removeRaiz(n);
                else //noh a ser removido eh filho a esquerda
                    pai->esq = removeRaiz(n);

            } else { //nao possui pai, logo, eh o proprio noh raiz
                raiz = removeRaiz(n);
                }
        }
    return raiz;
}
void imprimeArv(noArvore *raiz){
    if (raiz==NULL) return; 
    printf("%d ", raiz->valor);   
    if (raiz->esq!=NULL) imprimeArv(raiz->esq); 
    
    if (raiz->dir!=NULL) imprimeArv(raiz->dir);
}
int main(){
    int valores[]={5,8,9,3,7,2,6,0,4,1};
    noArvore *raiz=NULL, *no;
    for (int i=0; i<10; i++){
        no = malloc(sizeof(noArvore));
        no->valor=valores[i];
        no->esq=NULL;
        no->dir=NULL;
        raiz = insereNo(raiz, no);
        imprimeArv(raiz);
        puts("");
    }
    int n;
    noArvore *temp;
    while(1){
        puts("remove:");
        scanf(" %d", &n);
        removeNo(raiz, n);
        // temp=buscaPai(raiz, n);
        // printf("%d", temp->valor);
        // puts("");
        imprimeArv(raiz);
        puts("");
    }
    return 0;
}