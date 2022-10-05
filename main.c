#include <stdio.h>
#include <stdlib.h>
#include "types.c"
#include "define.h"


/*FUNCION COMPARADOR*/
int f(TEntrada x, TEntrada y) {
    int toReturn;
    if(x->clave < y->clave)
        toReturn = -1;
    else if (x->clave == y->clave) {
        toReturn = 0;
    }
    else
        toReturn = 1;
    return toReturn;
}

int main()
{

    TEntrada a;
    TEntrada b;
    TEntrada c;
    TEntrada d;

    TClave k = 10;
    TValor v = 100;
    TClave k1 = 20;
    TValor v1 = 200;
    TClave k2 = 30;
    TValor v2 = 300;
    TClave k3 = 40;
    TValor v3 = 500;

    a->clave= k;
    a->valor= v;

    b->clave= k1;
    b->valor= v1;

    c->clave= k2;
    c->valor= v2;

    d->clave= k3;
    d->valor= v3;

    TColaCP cola;
    cola = crear_cola_cp(&f);
    cp_insertar(cola, a);
    cp_insertar(cola, b);
    cp_insertar(cola, c);
    cp_insertar(cola, d);

    printf("cant %i", cp_cantidad(cola));
    return 0;
}
