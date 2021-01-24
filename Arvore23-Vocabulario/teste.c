#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listaIngles listaIngles;
typedef struct Vocabulario Vocabulario;

struct listaIngles {
    char palavraEn[30];
    listaIngles *prox;
};

struct Vocabulario {
    char Palavra1[30], Palavra2[30];
    listaIngles *Significados1, *Significados2;
    int nChaves;
    Vocabulario *esq, *centro, *dir;
};


Vocabulario *insere_palavra(Vocabulario **pai, Vocabulario **Raiz, char p_portug[], char p_ingles[], char infomeio[]);


void divide_palavras(Vocabulario **Raiz, char frase[]) {
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

            char infomeio[30];
            strcpy(infomeio, "EOF");
            insere_palavra(NULL, Raiz, p_portug, p_ingles, infomeio);
        } 

        else {
            p_portug[cont] = frase[i];    
            cont++;
        }
    }
}


listaIngles *insere_lista(listaIngles *Significados, char p_ingles[]) {
    listaIngles *No = (listaIngles*) malloc(sizeof(listaIngles));
    strcpy((*No).palavraEn, p_ingles);
    (*No).prox = NULL;    
    
    if (Significados == NULL) 
        return No;
    else {
        listaIngles *aux = Significados;

        while (aux->prox != NULL) 
            aux = aux->prox;

        aux->prox = No;
        return Significados;
    } 
}


Vocabulario *alocaNo(Vocabulario Palavra[], char Significado[], Vocabulario *noEsq, Vocabulario *noCentro) {
    Vocabulario *No = (Vocabulario*) malloc(sizeof(Vocabulario));

    strcpy((*No).Palavra1, Palavra);
    strcpy((*No).Palavra2, "EOF");
    (*No).Significados1 = insere_lista((*No).Significados1, Significado);
    (*No).Significados2 = NULL; 
    (*No).nChaves = 1;
    (*No).esq = noEsq;
    (*No).centro = noCentro;
    (*No).dir = NULL;

    return No;
}


Vocabulario *adicionaNo(Vocabulario *Raiz, char Palavra[], char p_ingles[], Vocabulario *Novo) {
    int n = strcmp(Palavra, (*Raiz).Palavra1);
    
    if (n > 0) {
        strcpy((*Raiz).Palavra2, Palavra);
        (*Raiz).Significados2 = insere_lista((*Raiz).Significados2, p_ingles);
        (*Raiz).dir = Novo;
    } 
    
    else if (n < 0) {
        strcpy((*Raiz).Palavra2, (*Raiz).Palavra1);
        strcpy((*Raiz).Palavra1, Palavra);
        (*Raiz).Significados2 = (*Raiz).Significados1;
        (*Raiz).Significados1 = insere_lista((*Raiz).Significados1, p_ingles);
        (*Raiz).dir = (*Raiz).centro;
        (*Raiz).centro = Novo;
    } 

    (*Raiz).nChaves = 2;
    return Raiz;
}


int folha(Vocabulario *Raiz) {
    int folha = 0;

    if ((*Raiz).esq == NULL && (*Raiz).centro == NULL && (*Raiz).dir == NULL)
        folha = 1;
    
    return folha;
}


// Vocabulario *quebraNo(Vocabulario **Raiz, Vocabulario *NovoNo, char Palavra1[], char infoMeio[]) {
//     Vocabulario *Novo;

//     int x = strcmp(Palavra1, (**Raiz).Palavra2);
//     int y = strcmp(Palavra1, (**Raiz).Palavra1);
    
//     if (x > 0) {
//         strcpy(infoMeio, (**Raiz).Palavra2);
//         Novo = alocaNo(Palavra1, (**Raiz).dir, NovoNo);
//     } 

//     else if (y < 0) {
//         strcpy(infoMeio, (**Raiz).Palavra1);
//         Novo = alocaNo((**Raiz).Palavra2, (**Raiz).centro, (**Raiz).dir);
        
//         strcpy((**Raiz).Palavra1, Palavra1);
//         (**Raiz).centro = NovoNo;
//     }

//     else {
//         strcpy(infoMeio, Palavra1);
//         Novo = alocaNo((**Raiz).Palavra2, NovoNo, (**Raiz).dir);  
//     }

//     strcpy((**Raiz).Palavra2, "EOF");
//     (**Raiz).nChaves = 1;
//     (**Raiz).dir = NULL; 

//     return Novo;
// }


Vocabulario *insere_palavra(Vocabulario **pai, Vocabulario **Raiz, char p_portug[], char p_ingles[], char infomeio[]) {
    Vocabulario *novo;

    if (*Raiz == NULL)
        *Raiz = alocaNo(p_portug, p_ingles, NULL, NULL);
    else {
        int x = strcmp(p_portug, (**Raiz).Palavra1);
        int y = strcmp(p_portug, (**Raiz).Palavra2);
        
        if (x == 0 || y == 0) 
            novo = NULL;
        else {
            if (folha(*Raiz)) {
                if ((**Raiz).nChaves == 1) {
                    *Raiz = adicionaNo(*Raiz, p_portug, p_ingles, NULL);
                    novo = NULL;
                } // else {
                //     novo = quebraNo(Raiz, NULL, p_portug, infomeio);
                    
                //     if (pai == NULL) {
                //         *Raiz = alocaNo(infomeio, *Raiz, novo);
                //         novo = NULL; 
                //     }
                // }
            } 
            
            // else {
            //     if (x < 0) 
            //         novo = insere_palavra(*Raiz, &(**Raiz).esq, p_portug, p_ingles, infomeio);
        
            //     else if ((**Raiz).nChaves == 1 || y < 0) 
            //         novo = insere_palavra(*Raiz, &(**Raiz).centro, p_portug, p_ingles, infomeio);

            //     else 
            //         novo = insere_palavra(*Raiz, &(**Raiz).dir, p_portug, p_ingles, infomeio);
                

            //     if (novo != NULL) {
            //         if ((**Raiz).nChaves == 1) {
            //             Raiz = adicionaNo(*Raiz, infomeio, novo);
            //             novo = NULL;
            //         } else {
            //             char auxMeio[30];
            //             strcpy(auxMeio, infomeio);

            //             novo = quebraNo(Raiz, novo, auxMeio, infomeio);
                    
            //             if (pai == NULL) {
            //                 *Raiz = alocaNo(infomeio, *Raiz, novo);
            //                 novo = NULL; 
            //             }
            //         }
            //     }
            // }
        }
    }

    return novo;
}


void imprime_vocabulario(Vocabulario *Raiz) {
    if (Raiz != NULL) {
        printf("%s %s %d\n", (*Raiz).Palavra1, (*Raiz).Palavra2, (*Raiz).nChaves);
        imprime_vocabulario(Raiz->esq);
        imprime_vocabulario(Raiz->centro);
        imprime_vocabulario(Raiz->dir);
    }
}
