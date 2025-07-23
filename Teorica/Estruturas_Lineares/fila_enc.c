#include<stdio.h>
#include<stdlib.h>
typedef struct no_{
    int chave;
    int valor;
    struct no_ *prox;
}no;
void insereFila(no **inicio, no **fim, no *elm){
    if (*fim != NULL)
        (*fim)->prox = elm;
    else
        *inicio = elm;
    *fim = elm;    
}
int *removeFila(no **inicio, no **fim){
    no *retorno = NULL;
    if (*inicio != NULL){
        retorno = *inicio;
        *inicio = (*inicio)->prox;
        if (*inicio==NULL)
            *fim==NULL;
    }
    return retorno;
}