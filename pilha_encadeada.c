#include<stdio.h>
#include<stdlib.h>
typedef struct no_{
    int valor;
    struct no_ *ant;
}no;
void insere_pilha(no **topo, no *elm){
    elm->ant = *topo;
    *topo = elm;
}
void remove_pilha(no **topo){
    if (*topo!=NULL){
        no *aux = *topo;
        *topo = (*topo)->ant;
        free(aux);
    }
}
int main(){
    int op, valor=0;
    no *topo = NULL, *elm, *aux;
    do{
        puts("1-inserir elemento");
        puts("2-remover elemento");
        scanf("%d", &op);
        if (op == 1){
            elm = malloc(sizeof(no));
            elm->valor = ++valor;
            insere_pilha(&topo, elm);
        }else if (op ==2){
            remove_pilha(&topo);
        }
       
        puts("");
        aux=topo;
        while (aux != NULL){
            printf("%d ", aux->valor);
            aux=aux->ant;
        }
        puts("");

    }while (op != 0);
    aux=topo;
    while (aux != NULL){ //libera a lista
        elm=aux;              
        aux=elm->ant;
        free(elm);  
    }
    return 0;
}