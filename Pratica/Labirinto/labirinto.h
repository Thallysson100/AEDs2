#ifndef LABIRINTO_H
#define LABIRINTO_H

//estrutura que representa um movimento
typedef struct mov_{ 
    int pos[2];    //recebe a posição de referência do movimento      
    int nao_testar_jog; //recebe qual jogada não deve ser testada 
    int jog_atu;  //recebe qual vai ser a primeira jogada a ser testada   
    struct mov_ *ant;   //ponteiro do elemento anterior na pilha
    struct mov_ *prox;  //ponteiro do elemento posterior na pilha
}mov;
mov *inserir_pilha(mov *topo, int nao_testar_jog, int *pos);
mov *remover_pilha(mov *topo);
void encontrar_caminho(int lin, int col, char **labr, int *pos_ent);

#endif