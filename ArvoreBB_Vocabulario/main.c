#include <stdio.h>

void divide_palavras(char frase[]);

int main() {
    char frase[1000]; 
    FILE *fptr;

    fptr = fopen("vocabulario.txt", "r");

    while(fgets(frase, 1000, fptr) != NULL) {
        if (frase[0] != '%' && frase[3] != '%') {
            divide_palavras(frase);
        }
    }

    return 0;
}

void divide_palavras(char frase[]) {
    int cont = 0, i;
    char p_ingles[30], p_portug[30];

    for (i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == ':')
            break;
        p_ingles[i] = frase[i]; 
    }

    p_ingles[i] = '\0';

    i = i + 2;

    for (i; frase[i] != '\0'; ++i) {
        if (frase[i] == ',' || frase[i] == '\n') {
            if (frase[i] != '\n')
                i = i + 1;

            p_portug[cont] = '\0';
            cont = 0;
            printf("%s\n", p_portug);
        } 

        else {
            p_portug[cont] = frase[i];    
            cont++;
        }
    }

}
