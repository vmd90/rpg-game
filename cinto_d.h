#include "jog.h"

/** Numero maximo de elementos que podem ser guardados no cinto */
#define NRO_MAX_ELEMS  5

/** Cria e retorna uma nova lista c e inicializa todos os seus membros, se
    houver memoria insuficiente erro = 1 */
Cinto *CCriar(int *erro);

/** Retorna o numero de espacos que o cinto contem */
int CTamanho(Cinto *c);

/** Retorna 1 se a lista c estiver vazia, caso contrario retorna 0 */
int CVazio(Cinto *c);

/** Retorna 1 se a lista c estiver cheia, caso contrario retorna 0 */
int CCheio(Cinto *c);

/** Insere o elemento elem na lista c na posicao pos, se a lista c estiver cheia erro = 1,
    se algum erro de memoria ocorrer, erro = 2 */
void CInserir(Cinto *c, Elemento *elem, int pos, int *erro);

/** Retorna o elemento elem da lista c que eh passado pelo nome, caso ele nao
    esteja na lista nao eh removido nenhum elemento */
Elemento *CRemover(Cinto *c, char *nome_elem);

/** Destroi a lista c e caso ela esteja vazia nao faz nada */
void CDestruir(Cinto *c);

/** Imprime os elementos do cinto c */
void CMostrarElem(Cinto *c);
