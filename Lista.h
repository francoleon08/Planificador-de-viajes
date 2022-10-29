//#ifndef LISTA_H_INCLUDED
//#define LISTA_H_INCLUDED



//#endif // LISTA_H_INCLUDED
/*
Archivo       : Lista.h
Descripción   : .h de la implementaciín del TDA Lista con celda de encabezamiento y concepto de posición
                indirecta.
Actualizaci�n : 15-09-2022 M. Escudero
Autor		  :  L. De Matteis - M. Escudero
Materia       : Organización de Computadoras
 */

//#include "define.h"
typedef int tElem;
typedef struct tCelda
{
        tElem *elemento;
        struct tCelda *siguiente;
} *tLista;

typedef tLista tPosicion;

void crearListaVacia(tLista *L);
void insertarElemento(tElem *E, tPosicion P, tLista L);
void eliminarElemento(tPosicion P, tLista L);
int esListaVacia(tLista L);
tPosicion primera(tLista L);
tPosicion ultima(tLista L);
tPosicion anterior(tPosicion P, tLista L);
tPosicion siguiente(tPosicion P, tLista L);
tElem* recuperar(tPosicion P, tLista L);
void vaciarLista(tLista L);
