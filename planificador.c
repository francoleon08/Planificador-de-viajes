#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "colacp.h"

TColaCP datos;

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

void iniciar_planificador() {
    FILE * viajes;
    viajes = fopen("viajes.txt", "r");

    ingresar_datos(viajes);

    fclose(viajes);
}

void ingresar_datos(FILE * archivo) {
    int clave;
    char valor[20];
    char c;
    int i;

    datos = crear_cola_cp(&f);

    if(archivo == NULL)
        exit(ELE_NULO);
    else {
        while(feof(archivo) == 0){
            int i=0;
            while(c != ';'){
                valor[i++] = c;
                c = fgetc(archivo);
            }
            c = fgetc(archivo);
            clave = fabs((c-'0')-1);
            c = fgetc(archivo);
            c = fgetc(archivo);
            clave += fabs((c-'0')-1);
            cp_insertar(datos, crear_entrada(clave, &valor)); //le estoy dando siempre el mismo arreglo

            clave = 0;
            c = fgetc(archivo);
            c = fgetc(archivo);
        }
    }
}
