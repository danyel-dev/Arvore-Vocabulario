#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

struct listaIngles {
    char palavraEn[30];
    listaIngles *prox;
};

struct Vocabulario {
    char palavraPt[30];
    listaIngles *significados;
    Vocabulario *esq, *dir;
};


void divide_palavras(Vocabulario **Raiz, char frase[]) {
    /* 
        Recebe a raiz da árvore e uma frase vindo do arquivo txt.
        essa função divide as palavras da frase e manda para uma função 
        que é responsável por adicionar essa palavra na árvore. 
    */
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
            insere_palavra(Raiz, p_portug, p_ingles);
        } 

        else {
            p_portug[cont] = frase[i];    
            cont++;
        }
    }
}


void insere_palavra(Vocabulario **Raiz, char p_portug[], char p_ingles[]) {
    /* 
        Recebe a raiz da árvore, uma palavra em português e seu significado 
        em inglês. essa função adiciona a palavra em português na árvore e 
        o seu significado na lista de significados, se a palavra já estiver 
        na árvore só vai adicionar o significado no nó onde se encontra 
        a palavra repetida. 
    */
    if (*Raiz == NULL) {
        *Raiz = aloca(p_portug, p_ingles);
    } else {
        int n = strcmp(p_portug, (**Raiz).palavraPt);

        if (n < 0) 
            insere_palavra(&(**Raiz).esq, p_portug, p_ingles); 

        else if (n > 0)
            insere_palavra(&(**Raiz).dir, p_portug, p_ingles);

        else 
            (**Raiz).significados = insere_lista((**Raiz).significados, p_ingles);
    }
}


Vocabulario *aloca(char p_portug[], char p_ingles[]) {
    /* 
        Recebe uma palavra em português e outra em inglês
        essa função aloca um nó da árvore e o retorna.
    */
    Vocabulario *No = (Vocabulario*) malloc(sizeof(Vocabulario));
    
    strcpy((*No).palavraPt, p_portug);
    (*No).esq = NULL;
    (*No).dir = NULL;
    (*No).significados = NULL;
    (*No).significados = insere_lista((*No).significados, p_ingles);
    
    return No;
}


listaIngles *insere_lista(listaIngles *significados, char p_ingles[]) {
    /* 
        recebe uma lista de siginicados e uma palavra em inglês.
        essa função adiciona uma palavra em uma lista de significados
        e então retorna.
    */
    listaIngles *No = (listaIngles*) malloc(sizeof(listaIngles));
    strcpy((*No).palavraEn, p_ingles);
    (*No).prox = NULL;    
    
    if (significados == NULL) 
        return No;
    else {
        listaIngles *aux = significados;

        while (aux->prox != NULL) 
            aux = aux->prox;

        aux->prox = No;
        return significados;
    } 
}


void imprimeArv(Vocabulario *Raiz) {
    /* 
        Recebe a raiz da árvore e então imprime todas as palavras
        em português e seus significados.
    */
    if (Raiz != NULL) {
        printf("%s: ", Raiz->palavraPt);
        imprime_lista((*Raiz).significados);
        imprimeArv(Raiz->esq);
        imprimeArv(Raiz->dir);
    }
}


void imprime_lista(listaIngles *significados) {
    /* 
        Recebe uma lista de significados e então imprime
        cada palavra dessa lista. 
    */
    for (listaIngles *aux = significados; aux != NULL; aux = aux->prox)
        printf("%s ", aux->palavraEn);
    printf("\n");
}


int busca(Vocabulario *Raiz, char frase[]) {
    /* 
        Recebe a raiz da árvore e uma palavra, busca essa palavra
        na árvore, se encontrar então retorna 1, se não, retorna 0.
    */
    int i = 0;

    if (Raiz != NULL) {
        int n = strcmp(frase, Raiz->palavraPt);
        
        if (n < 0)
            busca((*Raiz).esq, frase);
        else if (n > 0)
            busca((*Raiz).dir, frase);
        else {
            printf("%s: ", (*Raiz).palavraPt);
            imprime_lista((*Raiz).significados);
            i = 1;
        }
    } else 
        return i; 
}


void excluir_palavra(Vocabulario **Raiz, char palavra[]) {
    /* 
        Recebe a raiz da árvore e uma palavra. essa função 
        exclui uma palavra da árvore caso a palavra esteja na
        árvore.
    */  
    if (*Raiz != NULL) {
        int n = strcmp(palavra, (**Raiz).palavraPt);

        if (n < 0) 
            excluir_palavra(&(**Raiz).esq, palavra);

        else if (n > 0) 
            excluir_palavra(&(**Raiz).dir, palavra);
        
        else {
            Vocabulario *aux;
            aux = *Raiz;

            if (qtd_filhos(*Raiz) == 0)
                *Raiz = NULL;

            else if (qtd_filhos(*Raiz) == 2) 
                *Raiz = (**Raiz).esq;

            else if (qtd_filhos(*Raiz) == 3) 
                *Raiz = (**Raiz).dir;

            else if (qtd_filhos(*Raiz) == 1) {
                Vocabulario *menor;
                menor = menorfilho(&(**Raiz).dir);
                menor->esq = (**Raiz).esq;
                *Raiz = (**Raiz).dir;
            }

            free(aux);
        }
    } 
}


int qtd_filhos(Vocabulario *Raiz) {
    /* 
        Essa palavra recebe a raiz de uma árvore e retorna:
        0 se o nó for folha.
        1 se o nó tiver os dois filhos.
        2 se o nó tiver apenas o filho da esquerda.
        3 se o nó tiver apenas o filho da direita.
    */
    if (Raiz->esq == NULL && Raiz->dir == NULL) 
        return 0;
    if (Raiz->esq != NULL && Raiz->dir != NULL) 
        return 1;
    if (Raiz->esq != NULL)
        return 2;
    else 
        return 3;
}


Vocabulario *menorfilho(Vocabulario **Raiz) {
    /* 
        Essa função recebe uma raiz e retorna o menor 
        filho dessa raiz.
    */
    Vocabulario *menor;

    if((**Raiz).esq != NULL)
        menor = menorfilho(&(**Raiz).esq);
    else 
        menor = *Raiz;
    
    return menor;
}
