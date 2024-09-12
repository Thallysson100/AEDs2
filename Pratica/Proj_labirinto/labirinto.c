#include<stdio.h>
#include<stdlib.h>
#include "labirinto.h"
//Na pilha encadeada, cada elemento representa um movimento realizado no labirinto

/*Função de inserção da pilha de jogadas. Recebe o ponteiro do topo,
a jogada inicial, o vetor de posição, e o ponteiro da variável
que armazena o tamanho da pilha. Retorna o novo ponteiro do topo*/
mov *inserir_pilha(mov *topo, int nao_testar_jog, int *pos, int *tam_pilha){
    mov *elm = malloc(sizeof(mov));
    //insere a posição de referência do novo movimento 
    elm->pos[0] = pos[0];
    elm->pos[1] = pos[1];
    //insere qual jogada não irá ser testada para realizar o próximo movimento
    elm->nao_testar_jog = nao_testar_jog;
    //inicializa a jogada atual
    elm->jog_atu = nao_testar_jog;

    elm->ant = topo; 
    (*tam_pilha)++; //atualiza o tamanho da pilha
    
    topo = elm;
    return topo;
}
mov *remover_pilha(mov *topo, int *tam_pilha){
    mov *temp = topo;
    topo = topo->ant;
    free(temp); //limera o nó removido
    (*tam_pilha)--; //atualiza o tamanho da pilha
    return topo;
}
void encontrar_caminho(int lin, int col, char **labr, int *pos_ent){
    mov *topo = NULL, *aux;
    int i, tam_pilha=0, temp[2];

    //a posição (0,0) é a casa superior direita
    int jogadas[4][2]={{0,1},  //jogada 0: mover para direita
                       {1,0},  //jogada 1: mover para cima
                       {0,-1}, //jogada 2: mover para esquerda
                       {-1,0}};//jogada 3: mover para baixo

    topo = inserir_pilha(topo, 0, pos_ent, &tam_pilha);

    temp[0] = pos_ent[0];
    temp[1] = pos_ent[1];

    /*loop que processa todas os movimentos até encontrar a saída ou
    acabar os movimentos possíveis*/
    while(labr[temp[0]][temp[1]]!='S' && topo!=NULL){

        //testa de forma circular as jogadas entre "jog-atu" e "jog_nao_testar"
        for(i=(topo->jog_atu+1)%4; i!=topo->nao_testar_jog; i=(i+1)%4){
            temp[0] = topo->pos[0] + jogadas[i][0];
            temp[1] = topo->pos[1] + jogadas[i][1];

            /*caso a jogada for caso os movimentosum movimento possível, ou seja, 
            caso a jogada resulta em uma casa dentro do labirinto que não seja
            uma parede, o teste é interrompido antes de testar todas elas*/
            if (temp[0]>=0 && temp[0]<lin && temp[1]>=0 && temp[1]<col &&
               labr[temp[0]][temp[1]]!='X')
                break;        
        }
        /*caso todas as jogadas foram testadas e não foi encontrada uma válida,
        é voltado um movimento, significando retirar um elemento da pilha*/
        if (i==topo->nao_testar_jog)
            topo = remover_pilha(topo, &tam_pilha);

        //caso contrário, um novo movimento é realizado utilizando a jogada válida   
        else{
            /*salva qual foi a última jogada testada 
            para caso voltar movimentos até chegar nesse, é testado o resto das jogadas*/
            topo->jog_atu = i; 

            /*se uma jogada válida é realizada, no próximo
            movimento não pode ser testado a posição do movimento anterior,
            por isso "nao_testa_jog" inicia com a inversa da jogada válida*/
            topo = inserir_pilha(topo, (i+2)%4, temp, &tam_pilha);  
        }          
    }
    //caso voltar todos os movimentos sem encontrar uma saída
    if (topo==NULL){
        puts("Labirinto sem saida!");
        return;
    }
    int *caminho = malloc(2*tam_pilha*sizeof(int));
    for(int j=2*tam_pilha-1; topo!=NULL; j-=2){
        aux=topo;
        caminho[j-1] = lin-1-topo->pos[0]; 
        caminho[j] = topo->pos[1];
        topo=topo->ant;
        free(aux);
    }
    for (int j=0; j<2*tam_pilha; j+=2)
        printf("%d,%d\n", caminho[j+1], caminho[j]);
    free(caminho);
}