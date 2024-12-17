#include "ordenacao.h"
#include <wctype.h>
//Função que troca dois ponteiros de lugar
void troca(jogador **a, jogador **b){
    jogador *tmp = *a;
    *a = *b;
    *b = tmp;
}
/*Retira acento, transforma maiúsula em minúscula e 
transforma alguns caracteres especiais para comparação de ordem alfabética*/
wchar_t normaliza_caracter(wchar_t ch) {
    switch (ch) {
        case L'á': 
        case L'à': 
        case L'ã': 
        case L'â': 
        case L'Á': 
        case L'À': 
        case L'Ã': 
        case L'Â':        
            return L'a';

        case L'é': 
        case L'ê': 
        case L'ë': 
        case L'É': 
        case L'Ê': 
            return L'e';

        case L'í': 
        case L'Í': 
        case L'İ': 
        case L'ï':
        case L'ı':
            return L'i';

        case L'ó': 
        case L'ò': 
        case L'õ': 
        case L'ô': 
        case L'Ó':
        case L'Ø': 
        case L'Ò': 
        case L'Õ': 
        case L'Ô': 
            return L'o';

        case L'ú':
        case L'ü':
        case L'Ú':
        case L'Ü':
            return L'u';

        case L'ñ':
            return L'n';
        case L'ç':
            return L'c';

        case L'š': 
        case L'ş':
            return L's';

        default:
            return towlower(ch);  // Converte outros caracteres para minúscula
    }
}

/*Retorna um número positivo caso a primeira string sejá "menor" 
(venha primeiro em ordem alfabética) que a segunda, um número negativo caso contrário e 0 caso sejam iguais*/
int ComparaSemAcentoMinus(wchar_t *str1, wchar_t *str2) {
    wchar_t ch1, ch2;
    while (*str1 && *str2) {
        /*Transforma e compara caracteres um a um. 
        Necessário pois caracteres especiais são 
        considerados maiores que qualquer caracter normal.
        Exemplo: 'á' é considerado maior que 'z'*/
        ch1 = normaliza_caracter(*str1);
        ch2 = normaliza_caracter(*str2);
        if (ch1 != ch2)
            return ch1 - ch2;
        str1++;
        str2++;
    }
    // Verifica se ambas strings terminaram ao mesmo tempo
    return *str1 - *str2;
}

