#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "TCP.c"

TNodo getPadre(TColaCP cola, int pos) {
    TNodo padre;
    if(cola == NULL)
        exit(CCP_NO_INI);
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
    if(cola->comparador(hijo, padre) == 1) {
        intercambiarTNodos(hijo, padre);
        burbujeoInsertar(cola, hijo, hijo->padre);
    }
}

/*
    INTERCAMBIA hijo CON padre
*/
void intercambiarTNodos(TNodo hijo, TNodo padre) {
    TNodo izq;
    TNodo der;
    izq = hijo->hijo_izquierdo;
    der = hijo->hijo_derecho;
    if(padre->hijo_izquierdo == hijo){
        hijo->hijo_izquierdo = padre;
        hijo->hijo_derecho = padre->hijo_derecho;
    }
    else {
        hijo->hijo_derecho = padre;
        hijo->hijo_izquierdo = padre->hijo_izquierdo;
    }
    hijo->padre = padre->padre;
    padre->padre = hijo;
    padre->hijo_izquierdo = izq;
    padre->hijo_derecho = der;
}
