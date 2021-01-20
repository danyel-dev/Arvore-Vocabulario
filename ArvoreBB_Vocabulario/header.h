typedef struct listaIngles listaIngles;
typedef struct Vocabulario Vocabulario;


void divide_palavras(Vocabulario **Raiz, char frase[]);

void insere_palavra(Vocabulario **Raiz, char p_portug[], char p_ingles[]);

Vocabulario *aloca(char p_portug[], char p_ingles[]);

listaIngles *insere_lista(listaIngles *significado, char p_ingles[]);

void imprimeArv(Vocabulario *Raiz);

void imprime_lista(listaIngles *significados);

int busca(Vocabulario *Raiz, char frase[]);

void excluir_palavra(Vocabulario **Raiz, char palavra[]);

int qtd_filhos(Vocabulario *Raiz);

Vocabulario *menorfilho(Vocabulario **Raiz);
