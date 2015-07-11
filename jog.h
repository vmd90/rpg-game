#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct cinto Cinto;
typedef struct mochila Mochila;
typedef struct heroi Heroi;
typedef struct inimigo Inimigo;

/** Armas que o heroi pode encontrar pelo caminho */
#define VARINHA       0
#define ARCO_FLECHA   1
#define FACA          2
#define REVOLVER      3
#define METRALHADORA  4

/** Pocoes que o heroi pode encontrar */
#define PVIDA   5
#define PSUPER  6

typedef enum etipoelem { ARMA = 0, POCAO } eTipoElem;
typedef struct elemento Elemento;

/** Cria e retorna um novo elemento de tipo elem (ARMA ou POCAO), e recebe como
    parametro nome definido pelas contantes simbolicas (FACA, VARINHA, ...),
    caso ocorra um erro de memoria insuficiente, erro = 1 */
Elemento *CriarElemento(eTipoElem elem, int nome, int *erro);

/** Destroi elemento elem */
void DestruirElemento(Elemento *elem);

/** Retorna o nome do elemento elem */
char *NomeElemento(Elemento *elem);

/** Retorna o peso do elemento elem */
int PesoElemento(Elemento *elem);

/** Retorna o ataque do elemento elem */
int InfoAtaque(Elemento *elem);

/** Retorna a cura do elemento elem */
int InfoCura(Elemento *elem);

/** Retorna o tipo do elemento */
eTipoElem TipoElem(Elemento *elem);


/** Cria e retorna um ponteiro do tipo heroi com todos os seus campos
    inicializados; passando por parametro o seu nome e caso algum erro de memoria
    insuficiente ocorra erro = 1 */
Heroi *Inicializar(char *nome, int *erro);

/** Retorna um ponteiro para o cinto do heroi h */
Cinto *CintoHeroi(Heroi *h);

/** Retorna um ponteiro para a mochila do heroi h */
Mochila *MochilaHeroi(Heroi *h);

/** Retorna o numero de vidas do heroi */
int VidasHeroi(Heroi *h);

/* Aumenta ou diminue o numero de vidas do heroi h com valor v */
void ModificarVidasHeroi(Heroi *h, int v);

/** Retorna o nome do heroi */
char *NomeHeroi(Heroi *h);

/** Destroi todos os campos de h se h nao for NULL, caso contrario, nao
    faz nada */
void DestruirHeroi(Heroi *h);

/** Cria e retorna um novo ponteiro do tipo inimigo com todos os seus campos
    inicializados, caso ocorra um erro de memoria insuficiente, erro = 1 */
Inimigo *CriarInimigo(char *nome, int ataque, int vidas, int nivel, int *erro);

/** Cria o nome do inimigo */
char *CriarNomeInimigo();

/** Retorna vidas do inimigo */
int VidasInimigo(Inimigo *inim);

/** Retorna o nome do inimigo inim */
char *NomeInimigo(Inimigo *inim);

/* Aumenta ou diminue o numero de vidas do inimigo com valor v */
void ModificarVidasInimigo(Inimigo *inim, int v);

/** Retorna o numero de ataque do inimigo */
int AtaqueInimigo(Inimigo *inim);

/** Destroi todos os campos de inim se nao for NULL, caso contrario nao faz nada */
void DestruirInimigo(Inimigo *inim);
