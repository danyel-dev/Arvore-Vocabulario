#include <stdio.h>
#include <stdlib.h>

typedef struct listaIngles listaIngles;

typedef struct Vocabulario Vocabulario;


struct listaIngles {
    char palavraEn[30];
    listaIngles *prox;
};

struct Vocabulario {
    char Palavra1[30], Palavra2[30];
    int nChaves;
    listaIngles *Signi_palavra1, *Signi_palavra2;
    Vocabulario *esq, *Centro, *dir;
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
            insere_palavra(Raiz, p_portug, p_ingles);
        } 

        else {
            p_portug[cont] = frase[i];    
            cont++;
        }
    }
}


void insere_palavra(Vocabulario **Raiz, char p_portug[], char p_ingles[]) {
    printf("%s: %s\n", p_ingles, p_portug);

    // Arv23 *novo;

    // if (*Raiz == NULL)
    //     *Raiz = criaNO(info, NULL, NULL);
    // else {
    //     if (folha(*Raiz)) {
    //         if ((**Raiz).nChaves == 1) {
    //             *Raiz = adicionaNo(*Raiz, info, NULL);
    //             novo = NULL;
    //         } else {
    //             novo = quebraNo(Raiz, NULL, info, infoMeio);
                
    //             if (pai == NULL) {
    //                 *Raiz = criaNO(*infoMeio, *Raiz, novo);
    //                 novo = NULL; 
	// 		    }
    //         }
    //     } else {
    //         if (info < (**Raiz).chaveEsq)
    //             novo = insere23(*Raiz, &(**Raiz).esq, info, infoMeio);

    //         else if ((**Raiz).nChaves == 1) 
    //             novo = insere23(*Raiz, &(**Raiz).centro, info, infoMeio);

    //         else if (info < (**Raiz).chaveDir) 
    //             novo = insere23(*Raiz, &(**Raiz).centro, info, infoMeio);
            
    //         else 
    //             novo = insere23(*Raiz, &(**Raiz).dir, info, infoMeio);

    //         if (novo != NULL) {
    //             if ((**Raiz).nChaves == 1) {
    //                 Raiz = adicionaNo(*Raiz, *infoMeio, novo);
    //                 novo = NULL;
    //             } else {
    //                 novo = quebraNo(Raiz, novo, *infoMeio, infoMeio);
                
    //                 if (pai == NULL) {
    //                     *Raiz = criaNO(*infoMeio, *Raiz, novo);
    //                     novo = NULL; 
    //                 }
    //             }
    //         }

    //     }
    // }

    // return novo;
}

// Arv23 *criaNO(int info1, Arv23 *noEsq, Arv23 *noCentro) {
//     Arv23 *no = (Arv23*) malloc(sizeof(Arv23));

//     (*no).chaveEsq = info1;
//     (*no).chaveDir = 0;
//     (*no).nChaves = 1;
//     (*no).esq = noEsq;
//     (*no).centro = noCentro;
//     (*no).dir = NULL;

//     return no;
// }

// Arv23 *adicionaNo(Arv23 *Raiz, int info, Arv23 *Novo) {
//     if (info > (*Raiz).chaveEsq) {
//         (*Raiz).chaveDir = info;
//         (*Raiz).dir = Novo;
//     } else {
//         (*Raiz).chaveDir = (*Raiz).chaveEsq;
//         (*Raiz).chaveEsq = info;
//         (*Raiz).dir = (*Raiz).centro;
//         (*Raiz).centro = Novo;
//     }

//     (*Raiz).nChaves = 2;
//     return Raiz;
// }

// int folha(Arv23 *Raiz) {
//     int folha = 0;

//     if ((*Raiz).esq == NULL && (*Raiz).centro == NULL && (*Raiz).dir == NULL)
//         folha = 1;
    
//     return folha;
// }

// Arv23 *quebraNo(Arv23 **Raiz, Arv23 *NovoNo, int info, int *infoMeio) {
//     Arv23 *Novo;

//     if (info > (**Raiz).chaveDir) {
//         *infoMeio = (**Raiz).chaveDir;
//         Novo = criaNO(info, (**Raiz).dir, NovoNo);
//     } 
    
//     else if (info < (**Raiz).chaveEsq) {
//         *infoMeio = (**Raiz).chaveEsq;
//         Novo = criaNO((**Raiz).chaveDir, (**Raiz).centro, (**Raiz).dir);
        
//         (**Raiz).chaveEsq = info;
//         (**Raiz).centro = NovoNo;
//     }

//     else {
//         *infoMeio = info;
//         Novo = criaNO((**Raiz).chaveDir, NovoNo, (**Raiz).dir);  
//     }

//     (**Raiz).chaveDir = 0;
//     (**Raiz).nChaves = 1;
//     (**Raiz).dir = NULL; 

//     return Novo;
// }
