#include <stdlib.h>
#include <stdio.h>
typedef struct no{
    int chave;
    int valor;
    struct no *proximo;
}no;
no ptlista; //indice inicial

//pont é o ponteiro do nó achado, ant é o anterior
// pont = null caso não achar a chave, serve para listas ordenadas
void busca_enc(int chave, no **ant, no **pont){
    *ant = &ptlista;
    *pont = NULL;
    no *ptr = ptlista.proximo;
    while (ptr != NULL){
        if (ptr->chave < chave){ //se for menor, avança
            *ant = ptr;
            ptr = ptr->proximo;
        }else{ 
            if (ptr->chave == chave)
                *pont = ptr;
            ptr = NULL;
        }
    }
}
//retorna -1 caso achar uma chave igual
int insere_enc(no *elm){
    no *ant, *pont;
    busca_enc(elm->chave, &ant, &pont);
    if (pont == NULL){ 
        elm->proximo = ant->proximo;
        ant->proximo = elm;
        return 0;        
    }
    return -1;
}
//retorna null caso não encontrar a chave
no *remove_enc(int chave){
    no *ant, *pont;
    busca_enc(chave, &ant, &pont);
    if (pont != NULL){
        ant->proximo = pont->proximo;
        return pont;
    }
    return NULL;

}
int main(){
    int op, op2, chave=-1;
    no *elm, *aux;
    do{
        puts("1-inserir elemento");
        puts("2-remover elemento");
        scanf("%d", &op);
        if (op == 1){
            elm = malloc(sizeof(no));
            elm->chave = ++chave;
            insere_enc(elm);
        }else if (op ==2){
            puts("Digite a chave");
            scanf("%d", &op2);
            elm = remove_enc(op2);
            if ( elm == NULL)
                puts("Chave não encontrada");
            else
                free(elm);
        }

        aux = ptlista.proximo;
        puts("");
        while (aux != NULL){
            printf("%d ", aux->chave);
            aux=aux->proximo;
        }
        puts("");

    }while (op != 0);

    aux = ptlista.proximo;
    while (aux != NULL){ //libera a lista
        elm=aux;              
        aux=elm->proximo;
        free(elm);  
    }
    return 0;
}