#include <stdlib.h>
#include "tad.h"

#define INICIO 1
#define FIM tamanho

typedef struct
{
    PtrNodo lista;
    int tamanho;
} lista_encadeada;

typedef lista_encadeada* Tipo_lista;

/* Implementações */

int get_size(lista_encadeada *le)
{
    return le->tamanho;
}

const void *get_element(lista_encadeada *le, int i)
{
    int j;
    PtrNodo pnodo;
    if ((i <= le->tamanho) && (i > 0))
    {
        pnodo = le->lista;
        for (j = 2; j <= i; j++)
            pnodo = pnodo->prox;
        return pnodo->elem;
    }
    return 0;
}

lista_encadeada* new_list()
{
    Tipo_lista le = (lista_encadeada*) malloc(sizeof(lista_encadeada));
    le->tamanho = 0;
    le->lista = NULL;

    return le;
}

int add_element(lista_encadeada *le, int i, void *e)
{
    int j;
    PtrNodo pnodo_incluido, pnodo_anterior;
    if ((i <= le->tamanho + 1) && (i > 0))
    {
        pnodo_incluido = (PtrNodo)malloc(sizeof(struct nodo));
        if (pnodo_incluido == NULL)
            return 0; /* FALTA MEMÓRIA */
        else
        {
            pnodo_incluido->elem = e;
            if (i == 1)
            {
                pnodo_incluido->prox = le->lista;
                le->lista = pnodo_incluido;
            }
            else
            {
                pnodo_anterior = le->lista;
                for (j = 2; j < i; j++)
                    pnodo_anterior = pnodo_anterior->prox;
                pnodo_incluido->prox = pnodo_anterior->prox;
                pnodo_anterior->prox = pnodo_incluido;
            }
            le->tamanho = le->tamanho + 1;
            return 1;
        }
    }
    else
        return 0; /* POSIÇÃO INVÁLIDA */
}

int set_element(lista_encadeada *le, int i, void *e)
{
    int j;
    PtrNodo pnodo;
    if ((i <= le->tamanho) && (i > 0))
    {
        pnodo = le->lista;
        for (j = 2; j <= i; j++)
            pnodo = pnodo->prox;
        pnodo->elem = e;
        return 1;
    }
    else
        return 0; /* POSIÇÃO INVÁLIDA */
}

void *remove_element(lista_encadeada *le, int i)
{
    int j;
    PtrNodo pnodo_excluido, pnodo_anterior;
    if ((i <= le->tamanho) && (i > 0))
    {
        if (i == 1)
        {
            pnodo_excluido = le->lista;
            le->lista = pnodo_excluido->prox;
        }
        else
        {
            pnodo_anterior = le->lista;
            for (j = 2; j < i; j++)
                pnodo_anterior = pnodo_anterior->prox;
            pnodo_excluido = pnodo_anterior->prox;
            pnodo_anterior->prox = pnodo_excluido->prox;
        }
        le->tamanho = le->tamanho - 1;
        return pnodo_excluido;
    }
    else
        return 0; /* POSIÇÃO INVÁLIDA */
}

int reverse_list(lista_encadeada *le)
{
    PtrNodo anterior, proximo, atual;

    if (get_size(le) >= 2)
    {
        anterior = le->lista;
        atual = anterior->prox;
        proximo = atual->prox;

        /*PRIMEIRO CASO FORA DO LAÇO
          POR SER DIFERENTE E
          PARA NÃO TER IF NO LAÇO*/
        anterior->prox = NULL;
        atual->prox = anterior;

        while (proximo != NULL)
        {
            anterior = atual;
            atual = proximo;
            proximo = proximo->prox;

            atual->prox = anterior;
        }

        le->lista = atual;

        return 1;
    }

    return 0;
}

int tamanho_quantidade_nodos(lista_encadeada *le)
{
    int tamanho = 0;
    for (PtrNodo i = le->lista; i != NULL; i = i->prox, tamanho++)
    {
    }
    return tamanho;
}

void destroy_list(lista_encadeada *list){
    while (get_size(list) != 0)
    {
        remove_element(list, 1);
    }
    
    free(list);
}