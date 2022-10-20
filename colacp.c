#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "colacp.h"

//METODOS TDA COLA CON PRIORIDAD
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)) {
    TColaCP cola;
    /*
    ASIGNO MEMORIA SUFICIENTE PARA CREAR LA COLA,
    LUEGO AL MOMEMNTO DE DESTRUIRLA DEBO HACER FREE
    */
    cola = (TColaCP) malloc(sizeof(struct cola_con_prioridad));
    cola->cantidad_elementos = 0;
    cola->raiz = NULL;
    cola->comparador = f;
    return cola;
}

int cp_insertar(TColaCP cola, TEntrada entr) {
    if(cola == NULL)
        exit(CCP_NO_INI);
    int posInsertar;
    TNodo padre;
    TNodo insertar;
    if(entr != NULL) {
        insertar = (TNodo) malloc(sizeof(struct nodo));
        posInsertar = cola->cantidad_elementos + 1;
        if(posInsertar == 1){
            crearTNodo(insertar, NULL, entr);
            cola->raiz = insertar;
        }
        else {
            padre = getPadre(cola, posInsertar/2);
            crearTNodo(insertar, padre, entr);
            if(posInsertar % 2 == 0)
                padre->hijo_izquierdo = insertar;
            else
                padre->hijo_derecho = insertar;
            burbujeoInsertar(cola, insertar, padre);
        }
        cola->cantidad_elementos++;
        return TRUE;
    }
    else
        return FALSE;
}

TEntrada cp_eliminar(TColaCP cola) {
    if(cola == NULL)
        exit(CCP_NO_INI);
    if(cola->cantidad_elementos == 0)
        exit(ELE_NULO);
    TEntrada toReturn;
    //aux es el padre del ultimo nodo
    TNodo aux;
    toReturn = cola->raiz->entrada;
    if(cola->cantidad_elementos > 1){
        aux = getPadre(cola, (cola->cantidad_elementos)/2);
        removerTNodo(cola, aux);
        burbujeoEliminar(cola, cola->raiz);
    }
    else
        cola->cantidad_elementos--;
    return toReturn;
}

int cp_cantidad(TColaCP cola) {
    if(cola == NULL)
        exit(CCP_NO_INI);
    return cola->cantidad_elementos;
}

void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada)) {
    if(cola == NULL)
        exit(CCP_NO_INI);
    TNodo padre;
    TNodo hijoI;
    TNodo hijoD;
    while (padre != cola->raiz){
        padre=getPadre(cola, (cola->cantidad_elementos)/2);// padre es el padre del ultimo elemento ingresado.
        if (padre->hijo_izquierdo != NULL){
            hijoI= padre->hijo_izquierdo;
            fEliminar(hijoI->entrada);
            hijoI= NULL;
            free(hijoI);
            padre->hijo_izquierdo = NULL;
            cola->cantidad_elementos--;
        }
        if (padre->hijo_derecho != NULL){
            hijoD= padre->hijo_derecho;
            fEliminar(hijoD->entrada);
            hijoD= NULL;
            free(hijoD);
            padre->hijo_derecho = NULL;
            cola->cantidad_elementos--;
        }
    }//al terminar nos quedaria la raiz con el hijo izquierdo y el derecho.
    fEliminar(cola->raiz->entrada);
    free(cola->raiz);
    cola->raiz= NULL;
    cola->cantidad_elementos = NULL;
    cola->comparador = NULL;
    free(cola);
    cola= NULL;
}


//METODOS AUXILIARES
TNodo getPadre(TColaCP cola, int pos) {
    if(cola == NULL)
        exit(CCP_NO_INI);
    TNodo padre;
    if(pos == 1)
        return cola->raiz;
    else {
        padre = getPadre(cola, pos/2);
        if(pos % 2 == 0)
            return padre->hijo_izquierdo;
        else
            return padre->hijo_derecho;
    }
}

void crearTNodo(TNodo nodo, TNodo padre, TEntrada entr) {
    nodo->padre = padre;
    nodo->hijo_izquierdo = NULL;
    nodo->hijo_derecho = NULL;
    nodo->entrada = entr;
}

void burbujeoInsertar(TColaCP cola, TNodo hijo, TNodo padre) {
    TEntrada aux;
    if(padre != NULL){
        if(cola->comparador(hijo->entrada, padre->entrada) == -1) {
            aux = padre->entrada;
            padre->entrada = hijo->entrada;
            hijo->entrada = aux;
            burbujeoInsertar(cola, padre, padre->padre);
        }
    }
}

void burbujeoEliminar(TColaCP cola, TNodo raiz) {
    TNodo auxTNodo;
    TEntrada auxEntrada;
    auxTNodo = nodoMayorPrioridad(cola, raiz->hijo_izquierdo, raiz->hijo_derecho);
    if(auxTNodo != NULL && cola->comparador(auxTNodo->entrada, raiz->entrada) == -1){
        auxEntrada = raiz->entrada;
        raiz->entrada = auxTNodo->entrada;
        auxTNodo->entrada = auxEntrada;
        burbujeoEliminar(cola, auxTNodo);
    }
}

TNodo nodoMayorPrioridad(TColaCP cola, TNodo n1, TNodo n2){
    if(n1 != NULL) {
        if( n2 != NULL){
            if(cola->comparador(n1->entrada, n2->entrada) == -1)
                return n1;
            else
                return n2;
        }
        else
            return n1;
    }
    else
        return NULL;
}

void removerTNodo(TColaCP cola, TNodo aux) {
    if(cola->cantidad_elementos % 2 == 0){
        cola->raiz->entrada = aux->hijo_izquierdo->entrada;
        free(aux->hijo_izquierdo);
        aux->hijo_izquierdo = NULL;
    }
    else {
        cola->raiz->entrada = aux->hijo_derecho->entrada;
        free(aux->hijo_derecho);
        aux->hijo_derecho = NULL;
    }
    cola->cantidad_elementos--;
}

TEntrada crear_entrada(TClave c, TValor v) {
    TEntrada toReturn;
    toReturn = (TEntrada) malloc(sizeof(struct entrada));
    toReturn->clave = c;
    toReturn->valor = v;
    return toReturn;
}
