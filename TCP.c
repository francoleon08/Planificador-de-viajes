#include <stdio.h>
#include <stdlib.h>
#include "types.c"

//Metodos
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));

int cp_insertar(TColaCP cola, TEntrada entr);

int cp_cantidad(TColaCP cola);

void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada));

int f(TEntrada x, TEntrada y);

//Implementación
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)) {
    TColaCP cola;
    cola->cantidad_elementos = 0;
    cola->raiz = NULL;
    cola->comparador = f;
    return cola;
}

int cp_cantidad(TColaCP cola) {
    return cola->cantidad_elementos;
}

int f(TEntrada x, TEntrada y) {
    int toReturn;
    if(x->clave < y->clave)
        toReturn = -1;
    else if (x->clave == y->clave) {
        toReturn = 0;
    }
    else
        toReturn = 1;
    return &toReturn;
}
