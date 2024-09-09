#include <stdio.h>
#include <stdlib.h>
//retorna -1 se a fila estiver cheia
//f=inicio e r=retaguarda
int insere(int elm, int *v, int *r, int *f, int tam){
    int retorno = -1;
    int aux = (*r+1)%tam;
    if (aux != *f){
        *r=aux;
        v[*r]= elm;
        if (*f = -1)
            *f=0;
        return *r; 
    }
    return -1;
}
//retorna null se não conseguir remover da lista
int* removeL(int *v, int *r, int *f, int tam){
    int *retorno = NULL;
    if (*f != -1){
        retorno = malloc(sizeof(int));
        *retorno = v[*f];
        if (*f==*r){
            *f=-1;
            *r=-1;
        }
        else 
            *f=(*f+1)%tam;
    }
    return retorno;
}
int main(){
    int tam=10, v[tam], r=-1, f=-1, op, elm, a;
    int *Elremovido;
    do{
        puts("1 para inserir");
        puts("2 para remover");
        puts("0 para sair");
        scanf("%d", &op);
        if (op == 1){
            puts("Digite o elemento");
            scanf("%d", &elm);
            insere(elm, v, &r, &f, tam);
        }
        else{
            Elremovido = removeL(v, &r, &f, tam);
            if (Elremovido!=NULL){
                printf("\n%d\n", *Elremovido);
                free(Elremovido);
            }
        }
        for(int i=0; i<tam; i++)
            printf("%d ", v[i]);       
        puts("");
       
    }while (op!=0);

    return 0;
}
