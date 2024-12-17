#include"ordenacao.h"
#include<stdlib.h>

//Fução do InsertionSort que salva o número de comparações e trocas
void InsertionSort(jogador *vet[], int n, float *comparacoes, float *trocas) {
    jogador *chave;
    int j;
    for (int i = 1; i < n; i++) {
        chave = vet[i]; // O elemento a ser inserido
        j = i - 1;

        /*Move os elementos de vet[0..i-1], que são maiores que a chave,
        para uma posição à frente de sua posição atual*/
        (*comparacoes)++;
        while (j >= 0 && ComparaSemAcentoMinus(vet[j]->nome, chave->nome)>0) {
            vet[j + 1] = vet[j];
            j--;
            (*trocas)++;
            (*comparacoes)++;
        }
        (*trocas)++;
        vet[j + 1] = chave; // Insere a chave na posição correta
    }
}

//Seleciona a mediana entre vet[inf], vet[sup] e vet[(inf+sup)/2] e coloca em vet[sup]
void mediana(jogador *vet[], int inf, int sup, float *comparacoes, float *trocas){
    int mid = (inf+sup)/2;
    //determina vet[mid] = max(vet[inf], vet[mid])
    (*comparacoes)++;
    if (ComparaSemAcentoMinus(vet[inf]->nome, vet[mid]->nome)>0){
        (*trocas)++;
        troca(vet + inf, vet + mid);
    }
    //determina vet[sup] = min(vet[sup], vet[mid]))
    (*comparacoes)++;
    if (ComparaSemAcentoMinus(vet[sup]->nome, vet[mid]->nome)>0){
        (*trocas)++;
        troca(vet + sup, vet + mid);
    }else{
        /*caso vet[sup]<=vet[mid], vet[mid] é o maior valor dentre os três.
        Então é determinado que vet[sup] = max(vet[inf], vet[sup])*/
        (*comparacoes)++;
        if (ComparaSemAcentoMinus(vet[inf]->nome, vet[sup]->nome)>0){           
            (*trocas)++;
            troca(vet + inf, vet + sup);
        }
    }
}
/*Escolhe o pivô como vet[sup] e ordena o vetor resultando em 
todos os elementos menores que o pivô ficam a direita dele e 
os maiores a esquerda. Retorna o índice resultante do pivô. 
Também salva o número de trocas e comparações realizadas*/
int particao(jogador *vet[], int inf, int sup, float *comparacoes, float *trocas) {
    int j=inf-1;
    //Empilha no começo do vetor todos os elementos menores que o pivô
    for (int i=inf; i<sup; i++){
        (*comparacoes)++;
        if(ComparaSemAcentoMinus(vet[i]->nome, vet[sup]->nome)<0){
            j++;
            (*trocas)++;
            troca(vet + i, vet + j);
        }
    }
    //coloca o pivô na posição ordenada
    (*trocas)++;
    troca(vet + sup, vet + j + 1);
    return j+1;
}

//Fução do QuickSort que salva o número de comparações e trocas
void QuickSort(jogador *vet[], int inf, int sup,  float *comparacoes, float *trocas){
    if (inf>=sup)
        return;
    mediana(vet, inf, sup, comparacoes, trocas);
    int piv = particao(vet, inf, sup, comparacoes, trocas);
    QuickSort(vet, inf, piv-1, comparacoes, trocas);
    QuickSort(vet, piv+1, sup, comparacoes, trocas);
}

//Fução do CountingSort que salva o número de comparações e trocas
void CountingSort(jogador *vet[], int n, int max, int iChar, 
                  jogador **temp, int *count, float *trocas){   
    
    //inicializa o count com 0
    for (int i=0; i<=max; i++)
        count[i] = 0;

    /*Armazena o número de ocorrências do caracter de valor i de 
    índice iChar no nome de cada jogador em count[i]. Desconsidera acento, 
    maiúscula e transforma caracteres especiais*/
    wchar_t ch;
    for (int i = 0; i < n; i++){
        ch = normaliza_caracter(vet[i]->nome[iChar]);
        count[ch]++;
    }

    /*Cada elemento na posição i de cont agora armazena 
    quantos elementos iguais ou menores a vet[i]->nome[iChar] 
    existem até aquele ponto*/
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // Constrói a lista ordenada
    for (int i = n - 1; i >= 0; i--) {
        ch = normaliza_caracter(vet[i]->nome[iChar]);
        temp[count[ch] - 1] = vet[i];       
        count[ch]--;      
    }
    // Copia para o vetor original
    for (int i = 0; i < n; i++){
        vet[i] = temp[i];
        (*trocas)++;
    }
}

//Fução do CountingSort que salva o número de comparações, trocas e memória adicioal gasta
void RadixSort(jogador *vet[], int n, float *comparacoes, float *trocas, float *memor_adci){
    int max = L'z'; //define o valor máximo do caracter para o CountingSort
    int len, min=40; 
    //Vetores auxiliares para o algoritmo de CountingSort
    int *count = malloc((max+1)*sizeof(int)); 
    jogador **temp = malloc(n*sizeof(jogador*));

    (*memor_adci) += (max+1)*sizeof(int);
    (*memor_adci) += n*sizeof(jogador*);

    //acha o número de caracteres do menor nome do vetor  
    for (int i=0; i<n; i++){
        len = wcslen(vet[i]->nome);
        //min(a,b) = (a+b - |a-b|)/2
        min = (min+len - abs(min-len))>>1;
    }
    
    /*Faz interações de Counting Sort começando com o 
    índice do \0 da menor string até o índice do primeiro*/
    for (int i=min; i>=0; i--)
        CountingSort(vet, n, max, i, temp, count, trocas);
    
    /*Como após as interações do CountingSort a lista estará 
    praticamente ordenada, o InsertionSort terá complexidade 
    aproximadamente O(n) para ordenar o restante*/
    InsertionSort(vet, n, comparacoes, trocas);
    free(temp);
    free(count);
    
}