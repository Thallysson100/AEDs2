#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui

//Estrura que representa um nó de uma árvore
typedef struct noArvore_{
    int valor;
    int altura;
    struct noArvore_ *esq;
    struct noArvore_ *dir;
}noArvore;

double arvore_binaria(char *diretorio);
double arvore_balanceada(char *diretorio);

//funções auxiliares

noArvore *criaNo(int valor);
void liberaArvore(noArvore *raiz);
int alturaNo(noArvore *no);
int calculaAltura(noArvore *no);
int calculaBalance(noArvore *no);
noArvore *RSE(noArvore *raiz);
noArvore *RSD(noArvore *raiz);
int pegaMaisDireira(noArvore *raiz);
noArvore *rotaciona_insere(noArvore *raiz, int fator_balance);
noArvore *rotaciona_remove(noArvore *raiz);

//funções de inserção e remoção na AVL

noArvore *insereNoAVL(noArvore *raiz, noArvore *no);
noArvore *removeRaizAVL(noArvore *raiz);
noArvore *removeNoAVL(noArvore *raiz, int valor);

//funções de inserção e remoção na BST

noArvore *insereNoBST(noArvore *raiz, noArvore *no);
noArvore *removeRaizBST(noArvore *raiz);
noArvore *removeNoBST(noArvore *raiz, int valor);


#endif // _H_ARVORES