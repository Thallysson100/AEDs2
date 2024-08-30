#include<stdio.h>
#include<stdlib.h>
typedef struct no_{
    int pos[2];
    int jog_inc;
    int jog_atu;
    struct no_ *ant;
}no;
no *inserir_pilha(no *topo, int jog_inc, int *pos){
    no *elm = malloc(sizeof(no));
    elm->pos[0] = pos[0];
    elm->pos[1] = pos[1];
    elm->jog_inc = jog_inc;
    elm->jog_atu = jog_inc;
    elm->ant = topo;
    
    topo = elm;
    return topo;
}
no *remover_pilha(no *topo){
    no *temp = topo;
    topo = topo->ant;
    free(temp);
    return topo;
}
void encontrar_caminho(char **labr, int lin, int col, int *pos_ent){
    no *topo = NULL;
    int i, pos_atu[2];
    pos_atu[0] = pos_ent[0];
    pos_atu[1] = pos_ent[1];

    topo = inserir_pilha(topo, 0, pos_atu);
    int jogadas[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
    while(1){
        for(i=topo->jog_atu+1; i!=topo->jog_inc; i=(i+1)%4){
            pos_atu[0]+=jogadas[i][0];
            pos_atu[1]+=jogadas[i][1];
            
        }
    }
}
int main(){
    int jogadas[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
    for(int i=0; i<4; i++)
        printf("%d %d\n", jogadas[i][0], jogadas[i][1]);   
    return 0;
}