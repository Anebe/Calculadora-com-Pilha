
#ifndef _TAD_H_INCLUDED
#define _TAD_H_INCLUDED


struct nodo
{
    void *elem;
    struct nodo* prox;
};
typedef struct nodo *PtrNodo;

#endif