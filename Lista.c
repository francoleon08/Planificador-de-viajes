#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "lista.h"

/**
 * @brief Inicializa la lista recibida por parametro.
 * @param L lista.
 */
void crearListaVacia(tLista *L)
{
    *L = (tLista)malloc(sizeof(struct tCelda));
    (*L)->siguiente = NULL;
    (*L)->elemento = NULL;
}

/**
 * @brief Inserta un elemento en la lista, en la posicion correspondiente.
 * @param E elemento de la a insertar.
 * @param P posicion del elemento.
 * @param L lista donde se inserta el elemento.
 */
void insertarElemento(tElem *E, tPosicion P, tLista *L)
{
    tPosicion aux;
    aux = (tPosicion)malloc(sizeof(struct tCelda));
    aux->elemento = E;
    aux->siguiente = P->siguiente;
    P->siguiente = aux;
}

/**
 * @brief Elimina el elemento que se encuentra en la posicion recibida.
 * @param P posicion del elemento.
 * @param L lista donde se inserta el elemento.
 */
void eliminarElemento(tPosicion P, tLista L)
{
    tPosicion aux;
    aux = P->siguiente;
    P->siguiente = aux->siguiente;
    free(aux->elemento);
    free(aux);
}

/**
 * @brief Consulta si la lista tiene elementos.
 * @param L lista donde se inserta el elemento.
 * @return int cantidad de elementos insertados.
 */
int esListaVacia(tLista L)
{
    if (L == NULL)
        exit(LST_NO_INI);
    else
        return (L->siguiente == NULL);
}

/**
 * @brief Solicita la primer posicion de la lista.
 * @param L lista.
 * @return tPosicion primera.
 */
tPosicion primera(tLista L)
{
    return L;
}

/**
 * @brief Solicita la ultima posicion de la lista.
 * @param L lista.
 * @return tPosicion ultima.
 */
tPosicion fin(tLista L)
{
    tPosicion aux;
    if (L == NULL || L->siguiente == NULL)
        exit(LST_NO_INI);
    else
    {
        aux = L->siguiente;
        while (!(aux->siguiente == NULL))
        {
            aux = aux->siguiente;
        }
    }
    return aux;
}

/**
 * @brief Solicita la ultima posicion de la lista.
 * @param L lista.
 * @return tPosicion ultima.
 */
tPosicion ultima(tLista L)
{
    tPosicion aux;
    if (!(L->siguiente == NULL))
    {
        aux = L->siguiente;
        while (!(aux->siguiente == NULL))
        {
            aux = aux->siguiente;
        }
    }
    else
        aux = NULL;
    return aux;
}

/**
 * @brief Solicita la posicion anterior a la recibida.
 * @param P posicion del elemento.
 * @param L lista.
 * @return tPosicion posicion anterior a P.
 */
tPosicion anterior(tPosicion P, tLista L)
{
    tPosicion aux;
    int encontre = FALSE;
    if (!(L->siguiente == NULL) && !(L == P))
    {
        aux = L;
        while (aux->siguiente != NULL && !encontre)
        {
            if (aux->siguiente == P)
                encontre = TRUE;
            else
                aux = aux->siguiente;
        }
    }
    else
        aux = NULL;
    return aux;
}

/**
 * @brief Solicita la posicion siguiente a la recibida.
 * @param P posicion del elemento.
 * @param L lista.
 * @return tPosicion posicion siguiente a P.
 */
tPosicion siguiente(tPosicion P, tLista L)
{
    return P->siguiente;
}

/**
 * @brief Recupera el elemento ubicado en la posicion recibida.
 * @param P posicion del elemento.
 * @param L lista.
 * @return tElem elemento.
 */
tElem *recuperar(tPosicion P, tLista L)
{
    return P->siguiente->elemento;
}

/**
 * @brief Remueve los elementos insertados en la lista recibida y libera la memoria utilizada.
 * @param L lista.
 */
void vaciarLista(tLista L)
{
    tPosicion aux = L, celda;
    tElem *elem;
    if (!(aux->siguiente == NULL))
    {
        celda = aux->siguiente;
        aux->siguiente = NULL;
        aux = celda;
        while (aux->siguiente != NULL)
        {
            celda = aux;
            aux = aux->siguiente;
            elem = celda->elemento;
            free(elem);
            free(celda);
        }
    }
    free(L);
    L = NULL;
}
