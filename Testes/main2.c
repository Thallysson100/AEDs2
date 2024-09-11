#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct no_{
    int pos[2];
    int jog_inc;
    int jog_atu;
    struct no_ *ant;
}no;
no *inserir_pilha(no *topo, int jog_inc, int *pos, int *tam_pilha){
    no *elm = malloc(sizeof(no));
    elm->pos[0] = pos[0];
    elm->pos[1] = pos[1];
    elm->jog_inc = jog_inc;
    elm->jog_atu = jog_inc;
    elm->ant = topo;
    (*tam_pilha)++;
    
    topo = elm;
    return topo;
}
no *remover_pilha(no *topo, int *tam_pilha){
    no *temp = topo;
    topo = topo->ant;
    free(temp);
    (*tam_pilha)--;
    return topo;
}
void encontrar_caminho(int lin, int col, char **labr, int *pos_ent){
    no *topo = NULL, *aux;
    int i, tam_pilha=0;
    int jogadas[4][2]={{0,1},{1,0},{0,-1},{-1,0}}, temp[2];

    topo = inserir_pilha(topo, 0, pos_ent, &tam_pilha);

    temp[0] = pos_ent[0];
    temp[1] = pos_ent[1];
    while(labr[temp[0]][temp[1]]!='S' && topo!=NULL){
        for(i=(topo->jog_atu+1)%4; i!=topo->jog_inc; i=(i+1)%4){
            temp[0] = topo->pos[0] + jogadas[i][0];
            temp[1] = topo->pos[1] + jogadas[i][1];
            if (temp[0]>=0 && temp[0]<lin && temp[1]>=0 && temp[1]<col &&
               labr[temp[0]][temp[1]]!='X')
                break;        
        }
        if (i==topo->jog_inc)
            topo = remover_pilha(topo, &tam_pilha);
        else{
            topo->jog_atu = i;
            topo = inserir_pilha(topo, (i+2)%4, temp, &tam_pilha);  
        }          
    }
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
//ao executar, digite
int main(int argc, char *argv[]){
    char **labr;
    

    if (argc<2){
        puts("Nenhuma instancia passada ao executar o programa");
        exit(0);
    }

    //aloca memória para armazenar o labirinto
    labr = malloc(10*sizeof(char*));
    for (int i=0; i<10; i++)
        labr[i] = malloc(10*sizeof(char)); 

    //lê todas as instâncias passadas como argumento ao executar o programa
    for (int instancia=1; instancia<argc; instancia++){
        char diretorio[40]= "./Labirintos/labirinto";
        char str_txt[5] = ".txt";

        /*junta as strings para criar o caminho do diretório onde está o labirinto 
        expecificado*/
        strcat(diretorio, argv[instancia]);
        strcat(diretorio, str_txt);

        printf("Labirinto %s:\n", argv[instancia]);

        FILE *arq; 
        arq = fopen(diretorio, "rt");
        if (arq==NULL){
            printf("%s\n", diretorio);
            perror("Arquivo nao existente");
            continue;
        }
        /*Lê o arquivo já salvando a posição de entrada
        Por referência, (0,0) é a casa superior esquerda*/
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
            continue;
        }

        int pos[2]= {tmp_l, tmp_c};
        encontrar_caminho(10, 10, labr, pos);
        puts("---------------------");
    }
    //libera a memória alocada para o labirinto
    for (int i=0; i<10; i++)
        free(labr[i]);
    free(labr);
    return 0;
}