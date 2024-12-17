#ifndef _H_ORDENACAO
#define _H_ORDENACAO
#include<wchar.h>
/*Struct que representa cada jogador, as strings são do tipo
wchat_t para suporte a caracteres especiais*/
typedef struct jogador_{
    wchar_t nome[41];
    wchar_t posicao[41];
    wchar_t naturalidade[41];
    wchar_t clube[41];
    int idade;
}jogador;

//Fuções auxiliares

void troca(jogador **a, jogador **b);
wchar_t normaliza_caracter(wchar_t ch);
int ComparaSemAcentoMinus(wchar_t *str1, wchar_t *str2);

//Funções de ordenação

void InsertionSort(jogador *vet[], int n, float *comparacoes, float *trocas);
void mediana(jogador *vet[], int inf, int sup, float *comparacoes, float *trocas);
int particao(jogador *vet[], int inf, int sup, float *comparacoes, float *trocas);
void QuickSort(jogador *vet[], int inf, int sup,  float *comparacoes, float *trocas);
void CountingSort(jogador *vet[], int n, int max, int iChar, jogador **temp, int *count, float *trocas);
void RadixSort(jogador *vet[], int n, float *comparacoes, float *trocas, float *memor_adci);
#endif