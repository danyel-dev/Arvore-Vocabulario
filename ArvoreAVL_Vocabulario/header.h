typedef struct listaIngles listaIngles;
typedef struct Vocabulario Vocabulario;

void divide_palavras(Vocabulario **Raiz, char frase[]);

Vocabulario *alocaNo(char p_portug[], char p_ingles[]);

int altura(Vocabulario *Raiz);

listaIngles *insere_lista(listaIngles *significados, char p_ingles[]);

int insere_palavra(Vocabulario **Raiz, char p_portug[], char p_ingles[]);

void rotate_right(Vocabulario **Raiz);

void rotate_left(Vocabulario **Raiz);

void rotate_LeftRight(Vocabulario **Raiz);

void rotate_RightLeft(Vocabulario **Raiz);

void imprimeArv(Vocabulario *Raiz);

void imprime_lista(listaIngles *significados);

int busca(Vocabulario *Raiz, char palavra[]);

int qtd_filhos(Vocabulario *raiz);

Vocabulario *menorfilho(Vocabulario **raiz);

int excluir_palavra(Vocabulario **Raiz, char palavra[]);
