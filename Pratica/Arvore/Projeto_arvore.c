#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"
double arvore_binaria(char *diretorio) {
    int valor;
    double tempo = 0;
    char acao;
    noArvore *raiz = NULL;
    FILE *arq = fopen(diretorio, "rt");
    if (!arq)
        puts("Nao foi possivel abrir o arquivo, verifique se ele esta no diretorio correto");
    
    clock_t begin, end;
    while (fscanf(arq, " %c %d", &acao, &valor) != EOF){
        begin = clock();

        if (acao == 'I')
            raiz = insereNoBST(raiz, criaNo(valor));
        else
            raiz = removeNoBST(raiz, valor);
            
        end = clock();
        // calcula o tempo decorrido encontrando a diferença (end - begin) e
        // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
        tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    }   
    fclose(arq);    
    liberaArvore(raiz); //caso sobrar algum nó
    return (tempo);
}

double arvore_balanceada(char *diretorio) {
    int valor;
    double tempo = 0;
    char acao;
    noArvore *raiz = NULL;
    FILE *arq = fopen(diretorio, "rt");

    clock_t begin, end;
    while (fscanf(arq, " %c %d", &acao, &valor) != EOF){
        begin = clock();

        if (acao == 'I')
            raiz = insereNoAVL(raiz, criaNo(valor));
        else
            raiz = removeNoAVL(raiz, valor);
            
        end = clock();
        // calcula o tempo decorrido encontrando a diferença (end - begin) e
        // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
        tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    }
    fclose(arq);
    liberaArvore(raiz); 
    return (tempo);
}


int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }
    char diretorio[20] = "./instancias/";
    strcat(diretorio, argv[1]);

    double tempo_n_balanceada = arvore_binaria(diretorio);
    double tempo_balanceada = arvore_balanceada(diretorio);
    
    printf("%f\n%f\n", tempo_n_balanceada, tempo_balanceada);

    return (1);
}