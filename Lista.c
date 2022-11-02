#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "lista.h"


void crearListaVacia(tLista *L)
{
        *L = (tLista)malloc(sizeof(struct tCelda));
        (*L)->siguiente = NULL;
        (*L)->elemento  = NULL;
}

void insertarElemento(tElem * E, tPosicion P, tLista * L)
{
        tPosicion aux;
        aux = (tPosicion)malloc(sizeof(struct tCelda));
        aux->elemento = E;
        aux->siguiente = P->siguiente;
        P->siguiente = aux;
}

void eliminarElemento(tPosicion P, tLista L)
{
        tPosicion aux;
        aux = P->siguiente;
        P->siguiente = aux->siguiente;
        free(aux->elemento);
        free(aux);
}
int esListaVacia(tLista L){
         if (L == NULL ) exit(LST_NO_INI);
        else
         return (L->siguiente==NULL);
}

tPosicion primera(tLista L){
        return L;
}

tPosicion fin(tLista L){
       tPosicion aux;
        if (L == NULL || L->siguiente == NULL) exit(LST_NO_INI);
        else {
            aux=L->siguiente;
            while (!(aux->siguiente==NULL)){
                aux=aux->siguiente;
            }
        }
       return aux;
}

tPosicion ultima(tLista L){
   tPosicion aux;
   if (!(L->siguiente==NULL)){
       aux=L->siguiente;
       while (!(aux->siguiente == NULL)){
        aux=aux->siguiente;
       }

    }else aux= NULL;
    return aux;

}

tPosicion anterior(tPosicion P, tLista L){
   tPosicion aux;
   int encontre = FALSE;
   if (!(L->siguiente==NULL)&& !(L==P)) {
       aux=L;
       while (aux->siguiente != NULL && !encontre){
            if (aux->siguiente == P) encontre = TRUE;
            else aux=aux->siguiente;
       }

    }else aux= NULL;
    return aux;

}
tPosicion siguiente(tPosicion P, tLista L){
    return P->siguiente;
}

tElem* recuperar(tPosicion P, tLista L){
    return P->siguiente->elemento;
}

void vaciarLista(tLista L){
    tPosicion aux=L,celda;
    tElem *elem;
    if (!(aux->siguiente == NULL)){
        celda= aux->siguiente;
        aux->siguiente=NULL;
        aux=celda;
        while(aux->siguiente != NULL ){
            celda= aux;
            aux=aux->siguiente;
            elem  = celda->elemento;
            free(elem);
            free(celda);
    }
    }
    free(L);
    L = NULL;
  }
