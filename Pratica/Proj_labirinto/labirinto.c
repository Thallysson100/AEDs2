#include<stdio.h>
#include<stdlib.h>
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
        printf("%d,%d\n", caminho[j], caminho[j+1]);
    free(caminho);
}
int main(){
    char labr[10][10], op;
    char diretorio[] = "./Labirintos/labirinto-.txt";
    int i, j, pos[2];
    FILE *arq;
    while(1){
        puts("Digite o numero do labirinto, de 1 a 5; ou 0 para sair");
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
    return 0;
}