#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "colacp.h"
#include "ciudad.h"

void ingresar_datos(FILE * archivo, TColaCP datos);
int ascendente(TEntrada x, TEntrada y);
int descendente(TEntrada x, TEntrada y);
void mostrar_Ciudades(datos);
void fEliminar(TEntrada ent);
void camino_mas_corto(TColaCP datos);

int main() {
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
                mostrar_Ciudades(colaAscendente);
                printf("//////////////////////////////////////////////\n");
                break;
            }
            case 2 : {
                rewind(viajes);
                ingresar_datos(viajes, colaDescendente);
                printf("Opcion 2 seleccionada: ciudades en orden descendente\n");
                mostrar_Ciudades(colaDescendente);
                printf("//////////////////////////////////////////////\n");
                break;
            }
            case 3 : {
                rewind(viajes);
                ingresar_datos(viajes, colaAscendente);
                printf("Opcion 3 seleccionada: reducir horas de manejo\n");
                camino_mas_corto(colaAscendente);
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

    return EXITO;
}

void ingresar_datos(FILE * archivo, TColaCP datos) {
    char * valor;
    TCiudad ciudad;
    int x;
    int y;
    int clave;

    while(!feof(archivo)) {
        valor = (char *) malloc(sizeof(char)*30);
        ciudad = (TCiudad) malloc(sizeof(struct ciudad));
        fscanf(archivo, "%[^;];", valor);
        fscanf(archivo, "%d;", &x);
        fscanf(archivo, "%d\n", &y);
        ciudad->nombre = valor;
        ciudad->pos_x = x;
        ciudad->pos_y = y;
        clave = fabs(x - 1);
        clave += fabs(y - 1);
        cp_insertar(datos, crear_entrada(clave,ciudad));
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

void mostrar_Ciudades(datos) {
    TEntrada aux;
    TCiudad ciudad;
    int cant;
    int i;
    cant = cp_cantidad(datos) + 1;
    for(i = 1; i<cant; i++){
        aux = cp_eliminar(datos);
        ciudad = aux->valor;
        printf("%d. %s, distancia: %d\n", i,ciudad->nombre, aux->clave);
    }
}

void camino_mas_corto(TColaCP datos) {
    TColaCP colaAux;
    TCiudad ciudadAux;
    TEntrada entradaAux;
    int cord_x;
    int cord_y;
    int clave;
    int control;
    int i;
    int totalDist;

    colaAux = crear_cola_cp(ascendente);
    entradaAux = cp_eliminar(datos);
    ciudadAux = entradaAux->valor;
    cord_x = ciudadAux->pos_x,
    cord_y = ciudadAux->pos_y;
    control = datos->cantidad_elementos+1;
    totalDist = entradaAux->clave;
    i = 1;

    printf("%i. %s\n", i,ciudadAux->nombre);

    while(i < control){
        while(datos->cantidad_elementos > 0){
            entradaAux = cp_eliminar(datos);
            ciudadAux = entradaAux->valor;
            clave = fabs(ciudadAux->pos_x - cord_x);
            clave += fabs(ciudadAux->pos_y - cord_y);
            cp_insertar(colaAux, crear_entrada(clave, ciudadAux));
        }
        entradaAux = cp_eliminar(colaAux);
        ciudadAux = entradaAux->valor;
        cord_x = ciudadAux->pos_x,
        cord_y = ciudadAux->pos_y;
        totalDist += entradaAux->clave;
        printf("%i. %s\n", i,ciudadAux->nombre);

        while(colaAux->cantidad_elementos > 0){
            cp_insertar(datos, cp_eliminar(colaAux));
        }
        i++;
    }
    printf("Total recorrido %i\n", totalDist);
    cp_destruir(colaAux, fEliminar);
}

void fEliminar(TEntrada ent){
    ent->clave= NULL;
    ent->valor= NULL;
    free(ent);
    ent= NULL;
}
