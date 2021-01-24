#include <stdio.h>
#include <time.h>
#include "functions.c"

int main() {    
    char frase[1000]; 
    Vocabulario *Raiz = NULL;

    FILE *fptr;
    fptr = fopen("vocabulario.txt", "r");

    clock_t inicio, fim;
    inicio = clock();

    // inserção na árvore
    int cont = 0;
    while (fgets(frase, 1000, fptr) != NULL) {
        if (frase[0] != '%' && frase[3] != '%') {  
            divide_palavras(&Raiz, frase);   
            cont++;
        }

        if (cont == 1) 
            break;
    }

    imprime_palavras(Raiz);

    return 0;
}

void imprime_palavras(Vocabulario *Raiz) {
    if (Raiz != NULL) {
        printf("%s %s %d: ", Raiz->chaveEsq->Palavra, Raiz->chaveDir->Palavra, Raiz->nChaves);
        imprime_lista(Raiz);
        imprime_palavras(Raiz->esq);
        imprime_palavras(Raiz->centro);
        imprime_palavras(Raiz->dir);
    }
}

void imprime_lista(Vocabulario *Raiz) {
    listaIngles *aux = Raiz->chaveEsq->Significados;

    if (aux != NULL) {
        printf("%s ", aux->palavra_Engles);
        aux = aux->prox;
    }

    aux = Raiz->chaveDir->Significados;

    if (aux != NULL) {
        printf("%s ", aux->palavra_Engles);
        aux = aux->prox;
    }

    printf("\n");
}
