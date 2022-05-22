#include <stdlib.h>
#include "tad.h"


typedef struct
{
  PtrNodo topo;
  int tamanho;
} Pilha;

typedef Pilha* Tipo_pilha;

Pilha* new_stack()
{
  Pilha *p = (Pilha*) malloc(sizeof(Pilha));
  p->tamanho = 0;
  p->topo = NULL;

  return p;
}

int empity_stack(Pilha *p) { return (p->topo == NULL); }

int empilharElemento(Pilha *p, void *e)
{
  PtrNodo pnodo;
  pnodo = (PtrNodo)malloc(sizeof(struct nodo));
  if (pnodo == NULL)
  {
    return 0;
  }
  else
  {
    pnodo->elem = e;
    pnodo->prox = p->topo;
    p->topo = pnodo;
    p->tamanho++;
    return 1;
  }
}

void *desempilharElemento(Pilha *p)
{
  void *e;
  PtrNodo pnodo;
  if (empity_stack(p))
    return 0;
  else
  {
    pnodo = p->topo;
    p->topo = p->topo->prox;
    e = pnodo->elem;
    free(pnodo);
    p->tamanho--;
    return e;
  }
}

void *obterTopo(Pilha *p)
{
  void *e;
  if (!empity_stack(p))
  {
    e = p->topo->elem;
    return e;
  }
  else
    return 0;
}