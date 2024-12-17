#include "arvores.h"
#include <stdlib.h>
//Aloca memória para um nó já inicializando seus ponteiros e seu valor
noArvore *criaNo(int valor){
    noArvore *no = malloc(sizeof(noArvore));
    no->esq = NULL;
    no->dir = NULL;
    no->valor = valor;
    return no;
}

//Libera toda a memória alocada para a arvore
void liberaArvore(noArvore *raiz){
    if (!raiz)
        return;
    if (raiz->esq)
        liberaArvore(raiz->esq);
    if (raiz->dir)
        liberaArvore(raiz->dir);
    free(raiz);
}

/*Retorna a altura de um nó, se o nó for nulo, retorna 0
Necessário para evitar acessos a ponteiros nulos*/
int alturaNo(noArvore *no){
    return (no) ? no->altura : 0;
}

//Calcula a altura de um nó em função da altura de seus filhos
int calculaAltura(noArvore *no){
    int alturaDir = alturaNo(no->dir);
    int alturaEsq = alturaNo(no->esq);
    //retorna a maior altura entre seus filhos mais um
    return (alturaDir >= alturaEsq) ? alturaDir+1 : alturaEsq+1;
}

//Retorna o fator de balanceamento de um nó
int calculaBalance(noArvore *no){
    int alturaDir = alturaNo(no->dir);
    int alturaEsq = alturaNo(no->esq);
    return alturaEsq-alturaDir;
}

//Rotaciona para esqueda a raíz de uma sub árvore, retorna a nova raíz
noArvore *RSE(noArvore *raiz){
    noArvore *direita = raiz->dir;
    raiz->dir = direita->esq;
    direita->esq = raiz;
    //recalcula as novas alturas dos nós envolvidos na rotação
    raiz->altura = calculaAltura(raiz);
    direita->altura = calculaAltura(direita);
    return direita;
}

//Rotaciona para direita a raíz de uma sub árvore, retorna a nova raíz
noArvore *RSD(noArvore *raiz){
    noArvore *esquerda = raiz->esq;
    raiz->esq = esquerda->dir;
    esquerda->dir = raiz;
    raiz->altura = calculaAltura(raiz);
    esquerda->altura = calculaAltura(esquerda);
    return esquerda;
}

/*Retorna o valor do nó mais a direita da raíz de uma sub árvore, já 
o removendo*/
int pegaMaisDireira(noArvore *raiz){
    int valor;
    if (raiz->dir->dir) 
        //vai descendo na árvore até encontrar o pai do nó mais a direita
        valor = pegaMaisDireira(raiz->dir);
    else{
        //caso encontre, o nó mais a direita é removido
        noArvore *temp = raiz->dir;
        raiz->dir = temp->esq;
        valor = temp->valor;
        free(temp);
    }
    //recalcula a altura dos nós em pós-ordem
    raiz->altura = calculaAltura(raiz); 
    return valor;
}

/*Rotaciona uma sub árvore de acordo com as regras de rotação na 
inserção na AVL. Retorna a nova raíz*/
noArvore *rotaciona_insere(noArvore *raiz, int fator_balance){
    //caso fator de balanceamento for positivo, é necessário rotacionar para direita
    if (fator_balance > 0){ 
        //testa se é necessário fazer uma rotação dupla caso for um joelho
        if (calculaBalance(raiz->esq) < 0)
            raiz->esq = RSE(raiz->esq);
        return RSD(raiz);
    }
    //caso contrário, testa se é um joelho e rotaciona para esquerda
    if (calculaBalance(raiz->dir) > 0)
        raiz->dir = RSD(raiz->dir);
    return RSE(raiz);
}

/*Rotaciona uma sub árvore de acordo com as regras de rotação na 
remoção na AVL. Retorna a nova raíz*/
noArvore *rotaciona_remove(noArvore *raiz){
    noArvore *esquerda = raiz->esq;
    noArvore *direita = raiz->dir;
    //caso o filho de esquerda tenha a maior altura 
    if (alturaNo(esquerda) > alturaNo(direita)){       
        //é realizada uma rotação dupla somente em caso obrigatório
        if (alturaNo(esquerda->esq) < alturaNo(esquerda->dir)) 
            raiz->esq = RSE(esquerda);
        return RSD(raiz);
    
    //faz o mesmo porém com filho da direita caso ele tenha a maior altura
    }else if (alturaNo(esquerda) < alturaNo(direita)){
        if (alturaNo(direita->esq) > alturaNo(direita->dir)) 
            raiz->dir = RSD(direita);
        return RSE(raiz);
    }
    /*caso os filhos possuem niveis iguais, é priorizado uma rotação simples
    (rotação no caminho esquerda esquerda ou direita direita)*/
    if (alturaNo(esquerda->esq) > alturaNo(esquerda->dir))
        return RSD(raiz);

    //é realizada uma rotação dupla somente em caso obrigatório
    if (alturaNo(direita->esq) > alturaNo(direita->dir))
        raiz->dir = RSD(direita); 
    return RSE(raiz);    
}