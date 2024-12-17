#include "arvores.h"
#include <stdlib.h>

//Insere um nó na árvore AVL já rotacionando caso necessário
noArvore *insereNoAVL(noArvore *raiz, noArvore *no){
    /*desce na árvore até chegar em uma folha, 
    o novo nó será filho dessa folha*/
    if (!raiz){
        no->altura = calculaAltura(no);
        return no;
    }
    if (raiz->valor > no->valor)
        raiz->esq = insereNoAVL(raiz->esq, no);
    else
        raiz->dir = insereNoAVL(raiz->dir, no);

    /*testa se é necessário realizar uma rotação e atualiza o nível do nó
    em pós ordem, assim esse procedimento é realizado somente no caminho 
    da inserção*/
    int fator_balance = calculaBalance(raiz);
    if (abs(fator_balance)>1)
        raiz = rotaciona_insere(raiz, fator_balance);
    raiz->altura = calculaAltura(raiz);
    return raiz;
}

//Remove a raíz de uma sub árvore AVL
noArvore *removeRaizAVL(noArvore *raiz){
    if (!raiz) //teste para evitar o acesso a um ponteiro nulo
        return raiz;

    //trata as 3 exeções para a remoção da raíz
    noArvore *temp=raiz;
    if (!raiz->dir) //caso o filho a direita é nulo
        raiz=raiz->esq;
    else if (!raiz->esq) //caso o filho a esquerda é nulo
        raiz=raiz->dir;
    else if (!raiz->esq->dir){ //caso o filho a direita do filho a esquerda é nulo
        raiz->esq->dir = raiz->dir;
        raiz = raiz->esq;
        raiz->altura = calculaAltura(raiz);

    }else{ 
        //no caso normal, o novo valor da raiz é o maior valor menor que o antigo 
        raiz->valor = pegaMaisDireira(raiz->esq);
        raiz->altura = calculaAltura(raiz);
        return raiz;
    }
    free(temp);
    return raiz; 
}

//Remove um nó na AVL com o valor expecificado já rotacionando caso necessário
noArvore *removeNoAVL(noArvore *raiz, int valor){
    if (!raiz)
        return raiz;
    if (valor < raiz->valor)
        raiz->esq = removeNoAVL(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = removeNoAVL(raiz->dir, valor);
    else
        raiz = removeRaizAVL(raiz);
        
    /*testa se é necessário realizar uma rotação e atualiza o nível do nó
    em pós ordem, assim esse procedimento é realizado somente no caminho 
    da remoção*/
    if (raiz){
        if (abs(calculaBalance(raiz))>1)
            raiz = rotaciona_remove(raiz);
        raiz->altura = calculaAltura(raiz);
    }
    return raiz;   
}