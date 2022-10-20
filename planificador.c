#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "colacp.h"
#include "ciudad.h"

void ingresar_datos(FILE * archivo, TColaCP datos);
int ascendente(TEntrada x, TEntrada y);
int descendente(TEntrada x, TEntrada y);
void mostrarCiudades(datos);
void fEliminar(TEntrada ent);

void main() {
    FILE * viajes;
    TColaCP colaAscendente;
    TColaCP colaDescendente;
    int control;

    viajes = fopen("viajes.txt", "r");

    colaAscendente = crear_cola_cp(ascendente);
    colaDescendente = crear_cola_cp(descendente);

    printf("PLANIFICADOR\n");
    printf("1 - MOSTRAR ASCENDENTE\n");
    printf("2 - MOSTRAR DESCENDENTE\n");
    printf("3 - REDUCIR HORAS DE MANEJO\n");
    printf("4 - SALIR\n");
    while(control != 4) {
        printf("Opcion: ");
        scanf("%i", &control);
        switch (control) {
            case 1 : {
                rewind(viajes);
                ingresar_datos(viajes, colaAscendente);
                printf("Opcion 1 seleccionada: ciudades en orden ascendente\n");
                mostrarCiudades(colaAscendente);
                printf("//////////////////////////////////////////////\n");
                break;
            }
            case 2 : {
                rewind(viajes);
                ingresar_datos(viajes, colaDescendente);
                printf("Opcion 2 seleccionada: ciudades en orden descendente\n");
                mostrarCiudades(colaDescendente);
                printf("//////////////////////////////////////////////\n");
                break;
            }
            case 3 : {
                printf("Opcion 3 seleccionada: reducir horas de manejo\n");
                printf("//////////////////////////////////////////////\n");
                break;
            }
            case 4 : {
                printf("Opcion 4 seleccionada: salir\n");
                fclose(viajes);
                cp_destruir(colaAscendente, fEliminar);
                cp_destruir(colaDescendente, fEliminar);
                printf("GRACIAS POR UTILIZAR PLANIFICADOR.");
                break;
            }
            default : {
                printf("OPCION INCORRECTA!\n");
            }
        }
    }
    return 0;
}

void ingresar_datos(FILE * archivo, TColaCP datos) {
    char * valor;
    TCiudad ciudad;
    int x;
    int y;
    int clave;

    while(!feof(archivo)){
    TCiudad ciudad;
    int x;
    int y;
    int clave;
    char *valor;

    while(!feof(archivo)) {
        valor = (char *) malloc(sizeof(char)*30);
        ciudad = (TCiudad) malloc(sizeof(struct ciudad));
        fscanf(archivo, "%[^;];", valor);
        fscanf(archivo, "%d;", &x);
        fscanf(archivo, "%d\n", &y);
        ciudad->nombre = valor;
        ciudad->pos_x = x;
        ciudad->pos_y = y;
        clave = fabs(x-1);
        clave += fabs(y-1);
        cp_insertar(datos, crear_entrada(clave,ciudad));
    }
}
}

int ascendente(TEntrada x, TEntrada y) {
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

int descendente(TEntrada x, TEntrada y) {
    int toReturn;
    if(x->clave > y->clave)
        toReturn = -1;
    else if (x->clave == y->clave) {
        toReturn = 0;
    }
    else
        toReturn = 1;
    return toReturn;
}

void mostrarCiudades(datos) {
    TEntrada aux;
    TCiudad ciudad;
    int cant;
    int i;
    cant = cp_cantidad(datos) + 1;
    for(i = 1; i<cant; i++){
        aux = cp_eliminar(datos);
        ciudad = aux->valor;
        printf("%d. %s\n", i,ciudad->nombre);
    }
}

void fEliminar(TEntrada ent){
    ent->clave= NULL;
    ent->valor= NULL;
    ent= NULL;
    free(ent);
}
