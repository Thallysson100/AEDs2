#include<stdlib.h>
#include<stdio.h>
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
        //multiplicação inteira por um fator de 1+79/128 = 1.6171875 (aproximação da razão aurea)       
        tam_alocado += ((tam_alocado<<6)+(tam_alocado<<4)-tam_alocado)>>7; 
        vet->elm = realloc(vet->elm, tam_alocado * sizeof(int));
        vet->tam_alocado = tam_alocado;
    }    
    vet->elm[tam] = valor;
    vet->tam++;
}
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void insereHeap(vetor *heap, int valor){

    insereVet(heap, valor); //insere o novo elemento no final do vetor

    /*sobe na arvore trocando todos os pai maiores que seus filhos
    ate achar um certo ou chegar na raiz*/
    int i = heap->tam-1, pai = (i-1)>>1, *pontVetor = heap->elm;
    while (i!=0 && pontVetor[pai] > pontVetor[i]){
        swap(pontVetor + pai, pontVetor + i);
        i = (i-1)>>1; //i = pai do i
        pai = (i-1)>>1; //atualiza o valor do pai
    }
}
int removeHeap(vetor *heap){
    size_t tam = heap->tam;
    if (tam <= 0)
        return -1;
    heap->tam--;
    if (tam == 1) //caso a heap possuir apenas um elemento
        return heap->elm[0];
    tam--;   
    int *pontVet=heap->elm, flag=1, valEsq, valDir, valMin, aux, flag2;
    pontVet[0] = pontVet[tam];//troca a raiz pelo último elemento  
    
    //desce na arvore trocando os filhos menores pelos pais 
    size_t i=0, esq=1, dir=2, min = 0;
    /*Jeito normal:
    while (flag && esq<tam && dir<tam){
        flag = 0;
        if (pontVet[esq] < pontVet[i])
            min = esq;
        if (pontVet[dir] < pontVet[min])
            min = dir;
        if (min != i){
            swap(pontVet + i, pontVet + min);
            i = min;
            flag = 1;
        }
        esq = (i<<1)+1; //filho a esquerda de i
        dir = (i<<1)+2; //flho a direita de i
    }   
    Jeito sem duas condições:*/
    while (flag && esq<tam && dir<tam){
        flag = 0;
        valMin = pontVet[i];
        valEsq = pontVet[esq];
        valDir = pontVet[dir];
        //encontra o índice do menor número sem usar condição
        aux = (valMin+valEsq-abs(valMin-valEsq))>>1;
        flag2 = !(valMin-aux); //1 quando igual, 0 caso contrário
        min = (min&-flag2) + (esq&(flag2-1));

        valMin = pontVet[min];

        aux = (valMin+valDir-abs(valMin-valDir))>>1;
        flag2 = !(valMin-aux);
        min = (min&-flag2) + (dir&(flag2-1));
        if (min != i){
            swap(pontVet + i, pontVet + min);
            i = min;
            flag = 1;
        }
        esq = (i<<1)+1; //filho a esquerda de i
        dir = (i<<1)+2; //flho a direita de i
    }
    return pontVet[0];
}
void printHeap(vetor *heap, size_t i, int nivel){
    if (i >= heap->tam)
        return;
    printHeap(heap, (i<<1)+2, nivel+1); //direita
    for (int i=0; i<nivel; i++)
        printf("    ");
    printf("%d\n", heap->elm[i]);
    printHeap(heap, (i<<1)+1, nivel+1); //esquerda
}
int main(){
    vetor *heap = iniciaVet();
    for (int i=9; i>=0; i--){
        insereHeap(heap, i);
        printHeap(heap, 0, 0);
        puts("--------------");
    }
    char op;
    do{
        puts("Digite s para sair ou qualquer coisa para remover");
        scanf(" %c", &op);
        removeHeap(heap);
        for (int i=0; i<heap->tam; i++)
            printf("%d ", heap->elm[i]);
        puts("\n----------------");    
        printHeap(heap, 0, 0);
        puts("---------------");
          
    }while(op!='s');
    free(heap->elm);
    free(heap);

    return 0;
}