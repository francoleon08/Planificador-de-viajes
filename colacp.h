#include <stdio.h>
#include <stdlib.h>
#include "define.h"

typedef void * TClave;
typedef void * TValor;

typedef struct entrada {
    TClave clave;
    TValor valor;
} * TEntrada;

typedef struct nodo {
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
} * TNodo;

typedef struct cola_con_prioridad {
    int cantidad_elementos;
    TNodo raiz;
    int (*comparador)(TEntrada, TEntrada);
} * TColaCP;

//METODOS TDA COLA CON PRIORIDAD
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));

int cp_insertar(TColaCP cola, TEntrada entr);

TEntrada cp_eliminar(TColaCP cola);

int cp_cantidad(TColaCP cola);

void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada));

//METODOS AUXILIARES
TNodo getPadre(TColaCP cola, int pos);

void crearTNodo(TNodo nodo, TNodo padre, TEntrada entr);

void burbujeoInsertar(TColaCP cola, TNodo hijo, TNodo padre);

void burbujeoEliminar(TColaCP cola, TNodo raiz);

TNodo nodoMayorPrioridad(TColaCP cola, TNodo n1, TNodo n2);

void removerTNodo(TColaCP cola, TNodo padre);

TEntrada crear_entrada(TClave c, TValor v);
