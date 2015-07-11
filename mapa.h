#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "jog.h"

typedef struct mapa Mapa;
typedef struct caixa Caixa;

/** Variavel global que armazena o nivel do jogo */
int nivel_jogo;

/** tipos que serao usados na estrutura caixa */
typedef enum etipocaixa { VAZIO = 0, ELEM, INIMIGO } eTipoCaixa;

/** Cria e retorna um mapa com seus campos inicializados */
Mapa *MapaCriar(int *erro);

/** Destroi o mapa e caso ele esteja vazio, nao faz nada */
void MapaDestruir(Mapa *map);

/** Cria e retorna um novo bloco caixa com o tipo especificado; caso ocorra erro de
    memoria, erro = 1 */
Caixa *CriarCaixa(eTipoCaixa tipo, int *erro);

/** Retorna o tipo */
eTipoCaixa TipoCaixa(Caixa *c);

/** Retorna um ponteiro para elemento do campo info que existe na caixa c */
Elemento *InfoElem(Caixa *c);

/** Retorna um ponteiro para tipo inimigo do campo info que existe na caixa c */
Inimigo *InfoInim(Caixa *c);

/** Cria e insere um novo bloco do tipo caixa no mapa map com o tipo VAZIO ou ELEM
    ou INIMIGO; caso ocorra erro de memoria, erro = 1 */
void MapaInserir(Mapa *map, eTipoCaixa tipo, int *erro);

/** Remove o elemento da caixa da posicao pos */
void MapaRemover(Mapa *map, int pos);

/** Imprime o mapa map */
void MapaMostrar(Mapa *map);

/** Retorna o numero de caixas do mapa map */
int MapaTamanho(Mapa *map);

/** Retorna um ponteiro para objeto do tipo caixa de posicao pos */
Caixa *MapaPercorrer(Mapa *map, int pos);


/** Cria um mapa de nivel 1 */
void MapaCriarNivel1(Mapa **map, int *erro);

/** Cria um mapa de nivel 2 */
void MapaCriarNivel2(Mapa **map, int *erro);
