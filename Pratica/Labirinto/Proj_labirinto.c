#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "labirinto.h"

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