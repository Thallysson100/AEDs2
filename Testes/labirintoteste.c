#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
typedef struct mov_{ 
    int pos[2];    //recebe a posição de referência do movimento      
    int nao_testar_jog; //recebe qual jogada não deve ser testada 
    int jog_atu;  //recebe qual foi a última jogada testada antes de realizar próximo movimento   
    struct mov_ *ant;   //ponteiro do elemento anterior na pilha
    struct mov_ *prox;
}mov;
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

void encontrar_caminho(int lin, int col, char **labr, int *pos_ent){
    mov *topo = NULL, *aux, *fundo;
    int i, temp[2];
    /*matrix que representa quais casas estão sendo consideradas no momento
    como caminho da entrada até a saída, é necessário para evitar que
    o algoritmo entre neste mesmo caminho, assim resultando em loop infinito*/
    bool **ja_passou = malloc(10*sizeof(bool*));
    for (int i=0; i<10; i++)
        ja_passou[i]=calloc(10, sizeof(bool));

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
            uma parede e que ainda não foi passada, o teste é interrompido*/
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
    ja_passou[topo->pos[0]][topo->pos[1]] = true;
    while(fundo != NULL){
        aux=fundo;
        printf("%d,%d\n", fundo->pos[1], lin-1-fundo->pos[0]);
        fundo=fundo->prox;
        free(aux); //vai liberando os elementos da pilha      
    }
    puts("");
    for (int i=0; i<10; i++){
    for (int j=0; j<10; j++)
        printf("%d", ja_passou[i][j] ? 1 : 0);
    puts("");
    }          
    for (int i=0; i<10; i++)
            free(ja_passou[i]);
        free(ja_passou);
}
int main(int argc, char *argv[]){   
    if (argc<2){
        puts("Nenhuma instancia passada ao executar o programa."); 
        puts("Ao executar, digite ./labirinto x, sendo x o numero do labirinto");
        exit(0);
    }

    //aloca memória para armazenar o labirinto
    char **labr;
    labr = malloc(10*sizeof(char*));
    for (int i=0; i<10; i++)
        labr[i] = malloc(10*sizeof(char)); 

    char diretorio[32]= "./Labirintos/labirinto";
    char str_txt[5] = ".txt";
    /*junta as strings para criar o caminho do diretório onde está o labirinto     
      expecificado*/
    strcat(diretorio, argv[1]);   
    strcat(diretorio, str_txt);
    FILE *arq; 
    arq = fopen(diretorio, "rt");
    if (arq==NULL){
        printf("%s\n", diretorio);
        perror("Arquivo nao existente");
        exit(0);
    }
    //Lê o arquivo já salvando a posição da entrada
    int tmp_l=0, tmp_c=0;
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            labr[i][j]=getc(arq);
            if (labr[i][j]=='E'){
                tmp_l=i;
                tmp_c=j;
            }
        }
        getc(arq); //lê a quebra de linha do arquivo para ser ignorada
    }
    fclose(arq);

    //caso não achar a entrada
    if (labr[tmp_l][tmp_c]!='E'){
        puts("Labirinto não possui entrada");
        exit(0);
    }

    int pos[2]= {tmp_l, tmp_c};
    encontrar_caminho(10, 10, labr, pos);
    
    //libera a memória alocada para o labirinto
    for (int i=0; i<10; i++)
        free(labr[i]);
    free(labr);
    return 0;
}