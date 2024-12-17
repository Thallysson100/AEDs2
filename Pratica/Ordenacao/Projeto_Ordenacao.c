#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<wchar.h>
#include<locale.h>
#include"ordenacao.h"
#define NUM_JOGADORES 1149 //números de jogadores que será lido no arquivo

int main(int argc, char *argv[]){
    setlocale(LC_CTYPE, ""); //no windows, ".utf-8"

    if (argc < 2){
        puts("Entre com um argumento para a função");
        puts("1 para o método de ordenação simples");
        puts("2 para o método de ordenação ótimo");
        puts("3 para o método de ordenação em tempo linear");
        return 0;
    }

    /*O vetor que será realizado a ordenação será um vetor de 
    ponteiro de struct, assim as operações de troca terão que 
    trocar apenas um ponteiro ao invés de um struct inteiro*/
    jogador **vet = malloc(NUM_JOGADORES * sizeof(jogador*));

    FILE *arq = fopen("jogadores.csv", "r");
    if (!arq){
        puts("Não foi possível abrir o arquivo");
        exit(0);
    }

    //lê o arquivo
    char nome[41], posicao[41], naturalidade[41], clube[41]; 
    fscanf(arq, "%*[^\n]"); //ignora a primeira linha
    for (int i=0; i<NUM_JOGADORES; i++){
        vet[i] = malloc(sizeof(jogador));
    
        fscanf(arq, " %40[^,],%40[^,],%40[^,],%40[^,],%d",
        nome, posicao, naturalidade, clube, &vet[i]->idade);
        
        //Converte as strings  do tipo `char` para `wchar_t` individualmente
        mbstowcs(vet[i]->nome, nome, 41);
        mbstowcs(vet[i]->posicao, posicao, 41);
        mbstowcs(vet[i]->naturalidade, naturalidade, 41);
        mbstowcs(vet[i]->clube, clube, 41); 
    }
    fclose(arq);

    //ordena a lista e coleta os dados do algoritmo de ordenação escolhido
    clock_t begin, end;
    float num_comparacao=0, num_troca=0, memoria_adicional=0;
    double tempo;
    char op = argv[1][0];
    switch (op){
        case '1':
            begin = clock();
            InsertionSort(vet, NUM_JOGADORES, &num_comparacao, &num_troca);
            end = clock();
            break;

        case '2':
            begin = clock();
            QuickSort(vet, 0, NUM_JOGADORES-1, &num_comparacao, &num_troca);
            end = clock();
            break;

        case '3':
            begin = clock();
            RadixSort(vet, NUM_JOGADORES, &num_comparacao, &num_troca, &memoria_adicional);
            end = clock();
            break;
    }  
    tempo = (float)(end-begin)/CLOCKS_PER_SEC;
   
    //Libera o vetor e imprime na tela a lista ordenada e os dados coletados 
    for (int i=0; i<NUM_JOGADORES; i++){
        wprintf(L"%ls,%ls,%ls,%ls,%d\n",vet[i]->nome, vet[i]->posicao, 
        vet[i]->naturalidade, vet[i]->clube, vet[i]->idade);
        free(vet[i]);
    }
    wprintf(L"%f\n%f\n%f\n%f\n", 
    tempo, num_comparacao, num_troca, memoria_adicional);
    free(vet);
     
    return 0;
}