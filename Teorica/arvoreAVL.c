#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct noArvoreAVL_{
    int valor;
    struct noArvoreAVL_ *esq;
    struct noArvoreAVL_ *dir;
    int nivel;
}noArvoreAVL;
int nivelNo(noArvoreAVL *no){
    return (no) ? no->nivel : 0;
}
int calculaNivel(noArvoreAVL *no){
    int nivelDir = nivelNo(no->dir);
    int nivelEsq = nivelNo(no->esq);
    return (nivelDir >= nivelEsq) ? nivelDir+1 : nivelEsq+1;
}
int calculaBalance(noArvoreAVL *no){
    int nivelDir = nivelNo(no->dir);
    int nivelEsq = nivelNo(no->esq);
    return nivelEsq-nivelDir;
}
noArvoreAVL *RSE(noArvoreAVL *raiz){
    noArvoreAVL *direita = raiz->dir;
    raiz->dir = direita->esq;
    direita->esq = raiz;
    raiz->nivel = calculaNivel(raiz);
    direita->nivel = calculaNivel(direita);
    return direita;
}

noArvoreAVL *RSD(noArvoreAVL *raiz){
    noArvoreAVL *esquerda = raiz->esq;
    raiz->esq = esquerda->dir;
    esquerda->dir = raiz;
    raiz->nivel = calculaNivel(raiz);
    esquerda->nivel = calculaNivel(esquerda);
    return esquerda;
}
//+ vai pra esquerda, rotaciona direita
//- vai para direita, rotaciona esquerda
noArvoreAVL *rotaciona_insere(noArvoreAVL *raiz, int fator_balance){
    if (fator_balance > 0){
        int fator_balance_esq = calculaBalance(raiz->esq);
        if (fator_balance_esq < 0)
            raiz->esq = RSE(raiz->esq);
        return RSD(raiz);
    }
    int fator_balance_dir = calculaBalance(raiz->dir);
        if (fator_balance_dir > 0)
            raiz->dir = RSD(raiz->dir);
        return RSE(raiz);
}
noArvoreAVL *insereNoAVL(noArvoreAVL *raiz, noArvoreAVL *no){
    if (!raiz){
        no->nivel = calculaNivel(no);
        return no;
    }
    if (raiz->valor > no->valor)
        raiz->esq = insereNoAVL(raiz->esq, no);
    else
        raiz->dir = insereNoAVL(raiz->dir, no);

    int fator_balance = calculaBalance(raiz);
    if (abs(fator_balance)>1)
        raiz = rotaciona_insere(raiz, fator_balance);
    raiz->nivel = calculaNivel(raiz);

    return raiz;
}

int pegaMaisDireira(noArvoreAVL *raiz){
    int valor;
    if (raiz->dir->dir)
        valor = pegaMaisDireira(raiz->dir);
    else{
        noArvoreAVL *temp = raiz->dir;
        raiz->dir = temp->esq;
        valor = temp->valor;
        free(temp);
    }
    raiz->nivel = calculaNivel(raiz);
    return valor;
}

noArvoreAVL *removeRaizAVL(noArvoreAVL *raiz){
    noArvoreAVL *temp=raiz;
    if (!raiz)
        return raiz;
    if (!raiz->dir)
        raiz=raiz->esq;
    else if (!raiz->esq)
        raiz=raiz->dir;
    else if (!raiz->esq->dir){
        raiz->esq->dir = raiz->dir;
        raiz = raiz->esq;
        raiz->nivel = calculaNivel(raiz);
    }else{
        raiz->valor = pegaMaisDireira(raiz->esq);
        raiz->nivel = calculaNivel(raiz);
        return raiz;
    }
    free(temp);
    return raiz; 
}
/*necessário porque a regra para esconher os nós 
da remoção é diferente da inserção*/
noArvoreAVL *rotaciona_remove(noArvoreAVL *raiz){
    noArvoreAVL *esquerda = raiz->esq;
    noArvoreAVL *direita = raiz->dir;
    int nivelEsq = nivelNo(esquerda);
    int nivelDir = nivelNo(direita);
    //caso o filho de esquerda tenha o maior nivel 
    if (nivelEsq > nivelDir){
        nivelEsq = nivelNo(esquerda->esq);
        nivelDir = nivelNo(esquerda->dir);
        //é realizada uma rotação dupla somente em caso obrigatório
        if (nivelDir > nivelEsq) 
            raiz->esq = RSE(raiz->esq);
        return RSD(raiz);

    }else if(nivelEsq < nivelDir){
        //faz o mesmo porém com filho da direita caso ele tenha a maior altura
        nivelEsq = nivelNo(direita->esq);
        nivelDir = nivelNo(direita->dir); 
        if (nivelDir < nivelEsq) 
            raiz->dir = RSD(raiz->dir);
        return RSE(raiz);
    }
    /*caso os filhos possuem niveis iguais, é priorizado uma rotação simples
    (rotação no caminho esquerda esquerda ou direita direita)*/
    nivelEsq = nivelNo(esquerda->esq);
    nivelDir = nivelNo(esquerda->dir);
    if(nivelDir <= nivelEsq)
        return RSD(raiz); //rotação direita direita

    nivelEsq = nivelNo(direita->esq);
    nivelDir = nivelNo(direita->dir);
    //é realizada uma rotação dupla somente em caso obrigatório
    if(nivelDir < nivelEsq)
        raiz->dir = RSD(raiz->dir); 
    return RSE(raiz);    
}
noArvoreAVL *removeNoAVL(noArvoreAVL *raiz, int valor){
    if (!raiz)
        return raiz;
    if (valor < raiz->valor)
        raiz->esq = removeNoAVL(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = removeNoAVL(raiz->dir, valor);
    else
        raiz = removeRaizAVL(raiz);
    
    if (raiz){
        if (abs(calculaBalance(raiz))>1)
            raiz = rotaciona_remove(raiz);
        raiz->nivel = calculaNivel(raiz);
    }

    return raiz;   
}


void printTree(noArvoreAVL *raiz, int nivel, FILE *arq) {
     if (!raiz) 
         return;
    printTree(raiz->dir, nivel + 1, arq);

    for (int i = 0; i < nivel; i++)
        fputs("      ", arq);  
    fprintf(arq, "%d\n", raiz->valor);

    printTree(raiz->esq, nivel + 1, arq);
}
void liberaArvore(noArvoreAVL *raiz){
    if (!raiz)
        return;
    if (raiz->esq)
        liberaArvore(raiz->esq);
    if (raiz->dir)
        liberaArvore(raiz->dir);
    free(raiz);
}

int main(int arqc, char *arqv[]){
    if (arqc<2){
        puts("digite quantos elementos vc quer que");
        puts("a arvore tenha hora de executar (./arvore x)");
        exit(0);
    }
    srand(time(NULL));
    int tam=atoi(arqv[1]); 
    int aux, random;
    int *valores=malloc(tam*sizeof(int));
    for (int i=0; i<tam; i++)
        valores[i]=i;
    for (int i=0; i<tam; i++){
        random = rand()%tam;
        aux=valores[i];
        valores[i]=valores[random];
        valores[random]=aux;
    }
    noArvoreAVL *raiz=NULL, *no;
    FILE *arq = fopen("saida_arvore.txt", "wt");
    
    for (int i=0; i<tam; i++){
        no = malloc(sizeof(noArvoreAVL));
        no->valor=valores[i];
        no->esq=NULL;
        no->dir=NULL;
        raiz = insereNoAVL(raiz, no); 
        fprintf(arq, "inseriu: %d\n", valores[i]);     
        printTree(raiz, 0, arq);
        fputs("---------------------------------------\n", arq);
    }
    puts("Olha no arquivo saida");
    for (int i=0; i<tam; i++){
        random = rand()%tam;
        aux=valores[i];
        valores[i]=valores[random];
        valores[random]=aux;
    }
    for (int i=0; i<tam; i++){
        raiz = removeNoAVL(raiz, valores[i]);       
        fprintf(arq, "removeu: %d\n", valores[i]);     
        printTree(raiz, 0, arq);
        fputs("---------------------------------------\n", arq);         
    }
    
    fclose(arq);
    liberaArvore(raiz);
    free(valores);
    return 0;
}