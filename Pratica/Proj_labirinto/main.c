#include<stdio.h>
#include<stdlib.h>
#include "labirinto.h"
#include<string.h>
/*Ao executar, digite ./labirinto e os números dos labirintos que deseja ler
separados por espaço. Exemplo: ./labirinto 1 2 3*/
int main(int argc, char *argv[]){   
    if (argc<2){
        puts("Nenhuma instancia passada ao executar o programa");
        exit(0);
    }
    char **labr;
    //aloca memória para armazenar o labirinto
    labr = malloc(10*sizeof(char*));
    for (int i=0; i<10; i++)
        labr[i] = malloc(10*sizeof(char)); 

    //lê todas as instâncias passadas como argumento ao executar o programa
    for (int instancia=1; instancia<argc; instancia++){
        char diretorio[30]= "./Labirintos/labirinto";
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
        /*Lê o arquivo já salvando a posição da entrada
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