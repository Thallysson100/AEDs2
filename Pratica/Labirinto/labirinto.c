#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "labirinto.h"
/*Na pilha duplamente encadeada, cada elemento 
representa um movimento realizado no labirinto*/

/*Função de inserção na pilha de movimentos. Recebe o ponteiro do topo,
a jogada inicial e o vetor de posição. Retorna o novo ponteiro do topo*/
mov *inserir_pilha(mov *topo, int nao_testar_jog, int *pos){
    mov *elm = malloc(sizeof(mov));
    //insere a posição de referência do novo movimento 
    elm->pos[0] = pos[0];
    elm->pos[1] = pos[1];
    elm->nao_testar_jog = nao_testar_jog;
    //inicializa a jogada atual com a jogada posterior de "nao_testar_jog"
    elm->jog_atu = (nao_testar_jog+1)%4;

    elm->ant = topo;     
    if (topo!=NULL)
        topo->prox=elm;   
    return elm;
}
/*Função que remove o topo da pilha. Retorna o novo valor do topo*/
mov *remover_pilha(mov *topo){
    mov *temp = topo;
    topo=topo->ant;
    free(temp); 
    return topo;
}

/*Função de encontrar o caminho, recebe o número de linhas e colunas do labirinto,
o ponteiro referente a ele e a posição da entrada*/
void encontrar_caminho(int lin, int col, char **labr, int *pos_ent){
    mov *topo = NULL, *aux, *fundo;
    int i, temp[2];
    /*matrix que representa quais casas estão sendo consideradas no momento
    como caminho da entrada até a saída, é necessário para evitar que
    o algoritmo entre neste mesmo caminho, o que resultaria em loop infinito*/
    bool **ja_passou = malloc(10*sizeof(bool*));
    for (int i=0; i<10; i++)
        ja_passou[i] = calloc(10, sizeof(bool));

    //a posição (0,0) é a casa superior direita
    int jogadas[4][2]={{0,1},  //jogada 0: mover para direita
                       {1,0},  //jogada 1: mover para cima
                       {0,-1}, //jogada 2: mover para esquerda
                       {-1,0}};//jogada 3: mover para baixo

    topo = inserir_pilha(topo, 0, pos_ent);
    fundo = topo; //armazena o fundo da pilha

    temp[0] = pos_ent[0];
    temp[1] = pos_ent[1];

    /*loop que processa todas os movimentos até encontrar a saída ou
    acabar os movimentos possíveis*/
    while(labr[temp[0]][temp[1]]!='S' && topo!=NULL){

        /*começando de "jog_atu", testa de forma circular todas as jogadas 
        exeto "nao_testar_jog" até encontrar uma válida*/
        for(i=topo->jog_atu; i!=topo->nao_testar_jog; i=(i+1)%4){
            temp[0] = topo->pos[0] + jogadas[i][0];
            temp[1] = topo->pos[1] + jogadas[i][1];

            /*caso a jogada for um movimento possível, ou seja, 
            caso a jogada resulta em uma casa dentro do labirinto que não seja
            uma parede e que não esteja dentro do caminho, o teste é interrompido*/
            if (temp[0]>=0 && temp[0]<lin && temp[1]>=0 && temp[1]<col &&
               labr[temp[0]][temp[1]]!='X' && !(ja_passou[temp[0]][temp[1]]))
                break;        
        }
        /*caso todas as jogadas foram testadas e não foi encontrada uma válida,
        é voltado um movimento e é testado as jogadas restantes do movimento anterior*/
        if (i==topo->nao_testar_jog){
            //desconsidera a posição atual como parte do caminho 
            ja_passou[topo->pos[0]][topo->pos[1]] = false;
            topo = remover_pilha(topo);
            
        //caso contrário, um novo movimento é realizado  
        }else{
            /*salva qual deve ser a jogada que o loop "for" deve começar
            para testar as jogadas restantes*/
            topo->jog_atu = (i+1)%4; 
            //considera a posição atual como parte do caminho 
            ja_passou[topo->pos[0]][topo->pos[1]] = true;

            /*se uma jogada válida é realizada, no próximo
            movimento não pode ser testado a posição do movimento anterior,
            por isso "nao_testa_jog" inicia com a inversa da jogada realizada*/
            topo = inserir_pilha(topo, (i+2)%4, temp);  
        }
        
    }
    //caso voltar todos os movimentos sem encontrar uma saída
    if (topo==NULL){
        puts("Labirinto sem saida!");
        return;
    }
    //o caminho da entrada até saída é a impressão das posições do fundo até o topo 
    topo->prox = NULL;
    while(fundo != NULL){
        aux=fundo;
        printf("%d,%d\n", fundo->pos[1], lin-1-fundo->pos[0]);
        fundo=fundo->prox;
        free(aux); //vai liberando os elementos da pilha      
    }
    //libera a matriz do caminho          
    for (int i=0; i<10; i++)
        free(ja_passou[i]);
    free(ja_passou);
}