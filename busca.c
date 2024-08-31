#include <stdio.h>
struct{
    int chave;
    int valor;
} l[10];

int busca(int x){
    int inf=0, sup=9, meio;
    while (inf<=sup){
        meio = (inf+sup)/2;
        if (l[meio].chave==x)
            return meio;
        else if (l[meio].chave<x)
            inf = meio+1;
        else 
            sup = meio-1;
    }
    return -1;
}

int main(){
int x;
for (int i=0; i<10; i++)
    l[i].chave=i;   
printf("Digite:");
scanf("%d", &x);
printf("%d", busca(x));
}