/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"funcoes_hashing.h"
#include<stdio.h>
#include<string.h>

/**
 * Gera a posicao a ser gravada na hash usando o metodo da divisao.
 * @param chave
 * @param TABLE_SIZE
 * @return indice do vetor onde a informação será gravada.
 */
int chave_divisao(int chave, int TABLE_SIZE) {
	if (chave < 0)
		chave *= -1;
	return chave % TABLE_SIZE;
}

/**
 * Gera a posicao a ser gravada na hash usando o metodo da multiplicacao.
 * @param chave
 * @param TABLE_SIZE
 * @return indice do vetor onde a informação será gravada.
 */
int chave_multiplicacao(int chave, int TABLE_SIZE) {
	if (chave < 0)
		chave *= -1;
	double A = 0.7834729723;
	double val = chave * A;
	val = val - (int) val;
	return (int) (val * TABLE_SIZE);
}

/**
 * Gera a posicao a ser gravada na hash usando o metodo da dobra.
 * @param chave
 * @param TABLE_SIZE
 * @return indice do vetor onde a informação será gravada.
 */
int chave_dobra(int chave, int TABLE_SIZE){
	if (chave<0) chave = -chave;
	int aux, aux2;
	for (int i=sizeof(chave)<<2; chave>=TABLE_SIZE; i>>=1){
		aux = chave>>i; //metade mais significativa
		aux2 = chave & ((1<<i)-1); //metade menos signifcativa
		chave = aux^aux2; //soma considerando 1+1=0
	}
	return chave;
}

/**
 * Gera a partir da string um valor inteiro, de modo a poder
 * ser usada em alguma das outras funcoes de hashing.
 * @param str string que se deseja obter a chave.
 * @return valor inteiro obtido à partir da string passada.
 */
int valor_string(char * str){
	int i, valor = 7;
	int tam = strlen(str);
	for(i = 0; i < tam; i++){
		valor = 31 * valor + (int) str[i];
	}
	return valor;
}
