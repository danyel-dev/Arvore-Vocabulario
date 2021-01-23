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
    int nChaves;
    Vocabulario *esq, *centro, *dir;
};


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
            insere_palavra(NULL, Raiz, p_portug, infomeio);
        } 

        else {
            p_portug[cont] = frase[i];    
            cont++;
        }
    }
}


Vocabulario *alocaNo(Vocabulario Palavra1[], Vocabulario *noEsq, Vocabulario *noCentro) {
    Vocabulario *No = (Vocabulario*) malloc(sizeof(Vocabulario));

    strcpy((*No).Palavra1, Palavra1);
    strcpy((*No).Palavra2, "EOF");
    (*No).nChaves = 1;
    (*No).esq = noEsq;
    (*No).centro = noCentro;
    (*No).dir = NULL;

    return No;
}


Vocabulario *adicionaNo(Vocabulario *Raiz, char Palavra1[], Vocabulario *Novo) {
    int n = strcmp(Palavra1, (*Raiz).Palavra1);
    
    if (n > 0) {
        strcpy((*Raiz).Palavra2, Palavra1);
        (*Raiz).dir = Novo;
    } 
    
    else if (n < 0) {
        strcpy((*Raiz).Palavra2, (*Raiz).Palavra1);
        strcpy((*Raiz).Palavra1, Palavra1);
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


Vocabulario *quebraNo(Vocabulario **Raiz, Vocabulario *NovoNo, char Palavra1[], char infoMeio[]) {
    Vocabulario *Novo;

    int x = strcmp(Palavra1, (**Raiz).Palavra2);
    int y = strcmp(Palavra1, (**Raiz).Palavra1);
    
    if (x > 0) {
        strcpy(infoMeio, (**Raiz).Palavra2);
        Novo = alocaNo(Palavra1, (**Raiz).dir, NovoNo);
    } 

    else if (y < 0) {
        strcpy(infoMeio, (**Raiz).Palavra1);
        Novo = alocaNo((**Raiz).Palavra2, (**Raiz).centro, (**Raiz).dir);
        
        strcpy((**Raiz).Palavra1, Palavra1);
        (**Raiz).centro = NovoNo;
    }

    else {
        strcpy(infoMeio, Palavra1);
        Novo = alocaNo((**Raiz).Palavra2, NovoNo, (**Raiz).dir);  
    }

    strcpy((**Raiz).Palavra2, "EOF");
    (**Raiz).nChaves = 1;
    (**Raiz).dir = NULL; 

    return Novo;
}


void insere_palavra(Vocabulario **pai, Vocabulario **Raiz, char p_portug[], char infomeio[]) {
    Vocabulario *novo;

    if (*Raiz == NULL)
        *Raiz = alocaNo(p_portug, NULL, NULL);

    else {
        if (folha(*Raiz)) {
            if ((**Raiz).nChaves == 1) {
                *Raiz = adicionaNo(*Raiz, p_portug, NULL);
                novo = NULL;
            } else {
                novo = quebraNo(Raiz, NULL, p_portug, infomeio);
                
                if (pai == NULL) {
                    *Raiz = alocaNo(infomeio, *Raiz, novo);
                    novo = NULL; 
			    }
            }

        // } else {
        //     if (info < (**Raiz).chaveEsq)
        //         novo = insere23(*Raiz, &(**Raiz).esq, info, infoMeio);

        //     else if ((**Raiz).nChaves == 1) 
        //         novo = insere23(*Raiz, &(**Raiz).centro, info, infoMeio);

        //     else if (info < (**Raiz).chaveDir) 
        //         novo = insere23(*Raiz, &(**Raiz).centro, info, infoMeio);
            
        //     else 
        //         novo = insere23(*Raiz, &(**Raiz).dir, info, infoMeio);

        //     if (novo != NULL) {
        //         if ((**Raiz).nChaves == 1) {
        //             Raiz = adicionaNo(*Raiz, *infoMeio, novo);
        //             novo = NULL;
        //         } else {
        //             novo = quebraNo(Raiz, novo, *infoMeio, infoMeio);
                
        //             if (pai == NULL) {
        //                 *Raiz = criaNO(*infoMeio, *Raiz, novo);
        //                 novo = NULL; 
        //             }
        //         }
        //     }

        }
    }

    return novo;
}
