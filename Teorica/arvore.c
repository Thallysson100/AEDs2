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
    if (raiz==NULL)
        return raiz;
    if (raiz->dir==NULL)
        raiz=raiz->esq;
    else if (raiz->esq==NULL)
        raiz=raiz->dir;
    else{
        temp=raiz->esq;
        if (temp->dir==NULL){
            temp->dir=raiz->dir;
            free(raiz);
            return temp;
        }else{
            while(temp->dir!=NULL)
                temp=temp->dir;
            noArvore *pai = buscaPai(raiz, temp->valor);
            pai->dir = temp->esq;
            raiz->valor = temp->valor;
        }        
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