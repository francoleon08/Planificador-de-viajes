#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "colacp.h"

//METODOS AUXILIARES
TNodo getPadre(TColaCP cola, int pos);
void crearTNodo(TNodo nodo, TNodo padre, TEntrada entr);
void burbujeoInsertar(TColaCP cola, TNodo hijo, TNodo padre);
void burbujeoEliminar(TColaCP cola, TNodo raiz);
TNodo nodoMayorPrioridad(TColaCP cola, TNodo n1, TNodo n2);
void removerTNodo(TColaCP cola, TNodo padre);

//METODOS TDA COLA CON PRIORIDAD
/**
 * @brief Crea un Cola con prioridad.
 * @param f funcion de comparacion.
 * @return TColaCP generada.
 */
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)) {
    TColaCP cola;
    cola = (TColaCP) malloc(sizeof(struct cola_con_prioridad));
    cola->cantidad_elementos = 0;
    cola->raiz = NULL;
    cola->comparador = f;
    return cola;
}

/**
 * @brief Insertra una entrada en la cola.
 * @param cola cola con prioridad.
 * @param entr entrada a insertar en la cola.
 * @return int TRUE si se ejecuta la operacion, FALSE caso contrario.
 */
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

/**
 * @brief Elimina la raiz de la cola HEAP.
 * @param cola cola con prioridad.
 * @return TEntrada entrada removida de la cola.
 */
TEntrada cp_eliminar(TColaCP cola) {
    if(cola == NULL)
        exit(CCP_NO_INI);
    if(cola->cantidad_elementos == 0)
        exit(CCP_VACIA);
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

/**
 * @brief Consulta la cantidad de elementos insertados en la cola.
 * @param cola cola con prioridad.
 * @return int cantidad de elementos.
 */
int cp_cantidad(TColaCP cola) {
    if(cola == NULL)
        exit(CCP_NO_INI);
    return cola->cantidad_elementos;
}

/**
 * @brief Remueve todas las entradas insertadas en la cola.
 * @param cola cola con prioridad.
 * @param fEliminar funcion para eliminar las entradas.
 */
void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada)) {
    if(cola == NULL)
        exit(CCP_NO_INI);
    TNodo padre;
    TNodo hijoI;
    TNodo hijoD;
    if(cola->cantidad_elementos > 0){
        padre = getPadre(cola, (cola->cantidad_elementos)/2);
        while (padre != cola->raiz){
            if (padre->hijo_izquierdo != NULL){
                hijoI = padre->hijo_izquierdo;
                fEliminar(hijoI->entrada);
                hijoI = NULL;
                free(hijoI);
                padre->hijo_izquierdo = NULL;
                cola->cantidad_elementos--;
            }
            if (padre->hijo_derecho != NULL){
                hijoD= padre->hijo_derecho;
                fEliminar(hijoD->entrada);
                hijoD = NULL;
                free(hijoD);
                padre->hijo_derecho = NULL;
                cola->cantidad_elementos--;
            }
            padre = getPadre(cola, (cola->cantidad_elementos)/2);
        }
        if(padre != NULL) {
            fEliminar(cola->raiz->entrada);
            free(cola->raiz);
            cola->raiz = NULL;
        }
    }
    cola->comparador = NULL;
    free(cola);
    cola = NULL;
}

/**
 * @brief Busca el nodo padre respecto a la posicion pos.
 * @param cola cola con prioridad.
 * @param pos posicion del nodo hijo.
 * @return TNodo nodo padre.
 */
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

/**
 * @brief Crear un nodo.
 * @param nodo nodo a crear.
 * @param padre padre del nodo a crear.
 * @param entr entrada correspondiente al nodo creado.
 */
void crearTNodo(TNodo nodo, TNodo padre, TEntrada entr) {
    nodo->padre = padre;
    nodo->hijo_izquierdo = NULL;
    nodo->hijo_derecho = NULL;
    nodo->entrada = entr;
}

/**
 * @brief Recorre hacia arriba la estructura HEAP de la cola, reordenando las entradas.
 * @param cola cola con prioridad.
 * @param hijo nodo hijo.
 * @param padre nodo padre.
 */
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

/**
 * @brief Recorre hacia abajo la estructura HEAP de la cola, reordenando las entradas.
 * @param cola cola con prioridad.
 * @param raiz nodo hijo.
 */
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

/**
 * @brief Evalua y compara la prioridad de los nodos recibidos.
 * @param cola cola con prioridad.
 * @param n1 nodo a comparar.
 * @param n2 nodo a comparar.
 * @param TNodo nodo con mayor prioridad.
 */
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

/**
 * @brief Remueve el hijo correspondiente al nodo recibido.
 * @param cola cola con prioridad.
 * @param aux nodo padre.
 */
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
