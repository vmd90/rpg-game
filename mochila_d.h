#include "jog.h"

/** Cria e retorna uma pilha vazia com todos os membros de Mochila inicializados,
    caso a pilha nao seja criada, erro = 1
*/
Mochila *MCriar(int *erro);

/** Retorna o tamanho da pilha m */
int MTamanho(Mochila *m);

/** Insere na pilha m o elemento elem, e caso nao seja possivel inserir na
    pilha erro = 1
*/
void MInserir(Mochila *m, Elemento *elem, int *erro);

/** Remove e retorna o elemento do topo da pilha m */
Elemento *MRemover(Mochila *m);

/** Retorna o elemento do topo da pilha m, e caso a pilha esteja vazia
    retornara NULL */
Elemento *MTopo(Mochila *m);

/** Destroi a pilha m */
void MDestruir(Mochila *m);

/** Retorna 1 se vazia, caso contrario retorna 0 */
int MVazia(Mochila *m);

/** Imprime todos os itens da mochila */
void MMostrarElem(Mochila *m);


