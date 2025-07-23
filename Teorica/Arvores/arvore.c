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
        return buscaPai(raiz->esq, k);
    else
        return buscaPai(raiz->dir, k);
}
noArvore *removeRaiz(noArvore *raiz){
    noArvore *temp=raiz;
    if (!raiz)
        return raiz;
    if (!raiz->dir)
        raiz=raiz->esq;
    else if (!raiz->esq)
        raiz=raiz->dir;
    else{
        noArvore *pai = raiz->esq;
        temp=pai->dir;
        if (!temp){
            pai->dir=raiz->dir;
            free(raiz);
            return pai;
        }

        while(temp->dir){
            pai=pai->dir;
            temp=temp->dir;
        }
        pai->dir = temp->esq;
        raiz->valor = temp->valor;                
    }
    free(temp);
    return raiz;   
}

noArvore *removeNo(noArvore *raiz, int valor){
    if (!raiz)
        return raiz;
    if (valor < raiz->valor)
        raiz->esq = removeNo(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = removeNo(raiz->dir, valor);
    else
        raiz = removeRaiz(raiz);
    return raiz;
}
void printTree(noArvore *root, int level) {
    if (root == NULL) {
        return;
    }

    // Primeiro, imprimir o lado direito da árvore
    printTree(root->dir, level + 1);

    // Imprimir o valor do nó com recuo
    for (int i = 0; i < level; i++) {
        printf("    "); // Ajuste o número de espaços conforme necessário
    }
    printf("%d\n", root->valor);

    // Finalmente, imprimir o lado esquerdo da árvore
    printTree(root->esq, level + 1);
}

int main(){
    int valores[]={5,8,3,9,7,1,0,2,4,6};
    noArvore *raiz=NULL, *no;
    for (int i=0; i<sizeof(valores)/sizeof(int); i++){
        no = malloc(sizeof(noArvore));
        no->valor=valores[i];
        no->esq=NULL;
        no->dir=NULL;
        raiz = insereNo(raiz, no);
        printTree(raiz, 0);
        puts("---------------------------------------");
    }
    int n;
    noArvore *temp;
    while(1){
        puts("remove:");
        scanf(" %d", &n);
        raiz = removeNo(raiz, n);

        puts("-----------------");
        printTree(raiz, 0);
        puts("");
    }
    return 0;
}