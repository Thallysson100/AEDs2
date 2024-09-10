#include<stdio.h>
#include<stdlib.h>
#include "labirinto.h"

int main(){
    char **labr, op;
    char diretorio[] = "./Labirintos/labirinto-.txt";
    int i, j, pos[2];
    FILE *arq;

    labr = malloc(10*sizeof(char*));
    for (i=0; i<10; i++)
        labr[i] = malloc(10*sizeof(char));
    
    while(1){
        puts("Digite o numero do labirinto de 1 a 10 ou 0 para sair");
        scanf(" %c", &op);
        if (op=='0')
            break;

        diretorio[22]=op;
        arq = fopen(diretorio, "rt");
        if (arq==NULL){
            puts("Arquivo nao existe. Tente novamente");
            continue;
        }           
        for (i=0; i<10 && fgets(labr[i], 12, arq)!=NULL; i++);
        fclose(arq);

        if (i<10){
            puts("O labirinto não foi lido de forma correta. Tente novamente");
            continue;            
        }
        int tmp_l=0, tmp_c=0;
        for (i=0; i<10 && labr[tmp_l][tmp_c]!='E'; i++)
            for (j=0; j<10 && labr[tmp_l][tmp_c]!='E'; j++){
                    tmp_l=i;
                    tmp_c=j;
                }
        if (labr[tmp_l][tmp_c]!='E'){
            puts("Labirinto não possui entrada");
            continue;
        }
        pos[0]=tmp_l;
        pos[1]=tmp_c;   

        puts("Caminho da entrada ate a saida:");
        encontrar_caminho(10, 10, labr, pos);
        puts("-------------------------");
    }
    for (i=0; i<10; i++)
        free(labr[i]);
    free(labr);
    return 0;
}