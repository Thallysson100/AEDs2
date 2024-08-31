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
void encontrar_caminho(int lin, int col, char labr[lin][col], int *pos_ent){
    no *topo = NULL, *aux;
    int i, tam_pilha=0;
    int jogadas[4][2]={{0,1},{1,0},{0,-1},{-1,0}}, temp[2];

    topo = inserir_pilha(topo, 0, pos_ent, &tam_pilha);
    while(1){
        for(i=(topo->jog_atu+1)%4; i!=topo->jog_inc; i=(i+1)%4){
            temp[0] = topo->pos[0] + jogadas[i][0];
            temp[1] = topo->pos[1] + jogadas[i][1];
            if (temp[0]>=0 && temp[0]<lin && temp[1]>=0 && temp[1]<col &&
               (labr[temp[0]][temp[1]]=='0' || labr[temp[0]][temp[1]]=='S'))
                break;        
        }
        if (i==topo->jog_inc)
            topo = remover_pilha(topo, &tam_pilha);
        else if (labr[temp[0]][temp[1]]=='0'){
            topo->jog_atu = i;
            topo = inserir_pilha(topo, (i+2)%4, temp, &tam_pilha);            
        }else{
            topo = inserir_pilha(topo, 0, temp, &tam_pilha);
            break;
        }
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
        printf("(%d,%d)\n", caminho[j], caminho[j+1]);
    free(caminho);
}
int main(){
    char labr[10][10]={
        "EXXXXXXXXX",
        "000XXXXXXX",
        "0X0000X000",
        "0X0XX0X0X0",
        "0X0XX000XS",
        "0X0XXXXXXX",
        "0X00000XXX",
        "0XXXXX0XXX",
        "000XX000XX",
        "0XXXX0X0XX"
    };
    int pos[2]={0,0};
    encontrar_caminho(10, 10, labr, pos);
    return 0;
}