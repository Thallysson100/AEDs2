#ifndef LABIRINTO_H
#define LABIRINTO_H

//estrutura que representa um movimento
typedef struct mov_{ 
    int pos[2];    //recebe a posição de referência do movimento      
    int nao_testar_jog; //recebe qual jogada não deve ser testada 
    int jog_atu;  //recebe qual foi a última jogada testada antes de realizar próximo movimento   
    struct mov_ *ant;   //ponteiro do elemento anterior na pilha
}mov;
mov *inserir_pilha(mov *topo, int nao_testar_jog, int *pos, int *tam_pilha);
mov *remover_pilha(mov *topo, int *tam_pilha);
void encontrar_caminho(int lin, int col, char **labr, int *pos_ent);

#endif