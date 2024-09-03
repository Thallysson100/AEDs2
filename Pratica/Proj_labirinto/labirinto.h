#ifndef LABIRINTO_H
#define LABIRINTO_H

typedef struct no_{
    int pos[2];
    int jog_inc;
    int jog_atu;
    struct no_ *ant;
}no;
no *inserir_pilha(no *topo, int jog_inc, int *pos, int *tam_pilha);
no *remover_pilha(no *topo, int *tam_pilha);
void encontrar_caminho(int lin, int col, char **labr, int *pos_ent);

#endif