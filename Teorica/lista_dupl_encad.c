#include<stdlib.h>
#include<stdio.h>
//é lista circular, ou seja, o último aponta para ptlista
typedef struct no_{
    int chave;
    int valor;
    struct no_* ant;
    struct no_* prox;   
}no;
/*retorna o ponteiro da chave, caso não encontrar,
retorna o que seria o seu consecutivo*/ 
no *busca(no* ptlista, int chave){
    no *ultimo = ptlista->ant;
    if (chave <= ultimo->chave){
        no *pont = ptlista->prox;
        while(pont->chave < chave)
            pont = pont->prox;
        return pont;
    }
    return ptlista;
}
int insereEl(no *ptlista, no* elm){
    no *pont=busca(ptlista, elm->chave);
    if (pont==ptlista || pont->chave!=elm->chave){
        no *anterior = pont->ant;
        elm->ant = anterior;
        elm->prox = pont;
        anterior->prox = elm;
        pont->ant = elm;
        return 0;
    }
    return -1;
}
no* removeEl(no* ptlista, int chave){
    no* pont=busca(ptlista, chave);
    if (pont!=ptlista && pont->chave==chave){
        no *anterior = pont->ant;
        no *proximo = pont->prox;
        anterior->prox = proximo;
        proximo->ant = anterior;
        return pont;
    }
    return NULL;
}
int main(){
    int op, op2, chave=-1;
    no *ptlista = malloc(sizeof(no)); //é necessário pelo fato que                                   
    ptlista->ant=ptlista;             //ptlista inicia NULL
    ptlista->prox=ptlista;
    ptlista->chave=chave;
    
    no *elm, *aux;
    do{
        puts("1-inserir elemento");
        puts("2-remover elemento");
        scanf("%d", &op);
        if (op == 1){
            elm = malloc(sizeof(no));
            elm->chave = ++chave;
            insereEl(ptlista, elm);
        }else if (op ==2){
            puts("Digite a chave");
            scanf("%d", &op2);
            elm = removeEl(ptlista, op2);
            if ( elm == NULL)
                puts("Chave nao encontrada");
            else
                free(elm);
        }

        aux = ptlista->prox;
        puts("");
        while (aux != ptlista){
            printf("%d ", aux->chave);
            aux=aux->prox;
        }
        puts("");

    }while (op != 0);

    aux = ptlista->prox;
    while (aux != ptlista){ //libera a lista
        elm=aux;              
        aux=elm->prox;
        free(elm);  
    }
    return 0;
}