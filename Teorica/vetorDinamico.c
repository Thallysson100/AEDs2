#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int n_realoca = 0;
typedef struct vetor_{
    size_t tam_alocado, tam;
    int *elm;
}vetor;
vetor *iniciaVet(){
    vetor *vet = malloc(sizeof(vetor));
    vet->tam_alocado = 3;
    vet->tam = 0;
    vet->elm = malloc(3 * sizeof(int));
    return vet;
}
void insereVet(vetor *vet, int valor){
    size_t tam = vet->tam, tam_alocado = vet->tam_alocado;
    if (tam >= tam_alocado){
        //multiplicação inteira por um fator de 1+79/128=1.6171875 (aproximação da razão aurea)       
        tam_alocado += ((tam_alocado<<6)+(tam_alocado<<4)-tam_alocado)>>7; 
        vet->elm = realloc(vet->elm, tam_alocado * sizeof(int));
        n_realoca++;
        vet->tam_alocado = tam_alocado;
        printf("%d %d\n", vet->tam_alocado, n_realoca);
    }    
    vet->elm[tam] = valor;
    vet->tam++;
}
int main(char *argv[]){
    vetor *vet = iniciaVet();
    clock_t begin = clock();
    for (int i=0; i<atoi(__argv[1]); i++){
        insereVet(vet, i);
        /*for (int j=0; j < vet->tam; j++)
            printf("%d ", vet->elm[j]);
        puts("");*/
    }
    clock_t end = clock();

    printf("%lf", (double) (end-begin)/CLOCKS_PER_SEC);
    free(vet->elm);
    free(vet);
}