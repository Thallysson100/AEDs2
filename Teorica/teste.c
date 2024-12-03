#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdio.h>
void printBin(int n){
    for (int i=(sizeof(n)<<3)-1; i>=0; i--){
        printf("%u", (n>>i)&1);
    }
    putchar('\n');
}
int chave_dobra(int chave, int TABLE_SIZE){
	int aux, aux2, j;
	if (chave<0) chave = -chave;
    printBin(chave);
	for (int i=sizeof(chave)<<2; chave>=TABLE_SIZE; i>>=1){
        for (j=0; j<32-i; j++){
            putchar(' ');
        }
        for (j=0; j<i>>1; j++){
            putchar('-');
        }
        putchar(':');
        for (;j<i-1; j++){
            putchar(':');
        }

        putchar('\n');
		aux = chave>>i; //metade mais significativa
		aux2 = chave & (1<<i)-1; //metade menos signifcativa
		chave = aux^aux2; //soma considerando 1+1=0
        printBin(chave);
	}
	return chave;
}

int main(int argc, char *argv[]){
    printf("\n%u", chave_dobra(65698984, 100));
}