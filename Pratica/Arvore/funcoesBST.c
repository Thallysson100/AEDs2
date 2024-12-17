#include "arvores.h"
#include <stdlib.h>
//Insere um nó na árvore de busca binária
noArvore *insereNoBST(noArvore *raiz, noArvore *no){
    /*desce na árvore até chegar em uma folha, 
    o novo nó será filho dessa folha*/
    if (!raiz){
        return no;
    }
    if (raiz->valor > no->valor)
        raiz->esq = insereNoBST(raiz->esq, no);
    else
        raiz->dir = insereNoBST(raiz->dir, no);
    //diferente da AVL, não é necessário realizar rotações na árvore binária de busca
    return raiz;
}

//Remove a raíz de uma sub árvore binária de busca
noArvore *removeRaizBST(noArvore *raiz){  
    if (!raiz) //teste para evitar acessos a ponteiros nulos
        return raiz;

    noArvore *temp=raiz;    
    if (!raiz->dir) //caso o filho a direita é nulo
        raiz=raiz->esq;
    else if (!raiz->esq) //caso o filho a esquerda é nulo
        raiz=raiz->dir;
    else{
        noArvore *pai = raiz->esq;
        temp=pai->dir;
        if (!temp){ //caso o filho a direita do filho a esquerda é nulo
            pai->dir=raiz->dir;
            free(raiz);
            return pai;
        }

        /*como não é necessário o recáculo das alturas na BST, 
        pode usar um método de loop ao invés de recurção para 
        encontrar o nó mais a direita da sub árvore*/  
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

//Remove um nó na árvore binária de busca com o valor expecificado 
noArvore *removeNoBST(noArvore *raiz, int valor){
    if (!raiz)
        return raiz;
    if (valor < raiz->valor)
        raiz->esq = removeNoBST(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = removeNoBST(raiz->dir, valor);
    else
        raiz = removeRaizBST(raiz);
    return raiz;
}
