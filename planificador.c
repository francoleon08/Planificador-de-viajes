#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "define.h"
#include "colacp.h"
#include "ciudad.h"
#include "Lista.h"

void ingresar_datos_lista(FILE * archivo, tLista * list);
void cargar_datos_colaCP(tLista list, TColaCP datos);
float calcular_distancia(float x, float y);
int ascendente(TEntrada x, TEntrada y);
int descendente(TEntrada x, TEntrada y);
void mostrar_Ciudades(TColaCP datos);
void fEliminar(TEntrada ent);
void camino_mas_corto(TColaCP datos);

int main(int argc, char * argv[]) {
    FILE * viajes;
    TColaCP colaAscendente;
    TColaCP colaDescendente;
    tLista listaDatos;
    int control;

    /*
    viajes = fopen(argv[1], "r");
    if(viajes == NULL) {
        printf("Error en la carga de datos");
        exit(FALSE);
    } */

    crearListaVacia(&listaDatos);
    viajes = fopen("viajes.txt", "r");
    ingresar_datos_lista(viajes, &listaDatos);
    fclose(viajes);

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
                cargar_datos_colaCP(listaDatos, colaAscendente);
                printf("Opcion 1 seleccionada: ciudades en orden ascendente\n");
                mostrar_Ciudades(colaAscendente);
                printf("//////////////////////////////////////////////\n");
                break;
            }
            case 2 : {
                cargar_datos_colaCP(listaDatos, colaDescendente);
                printf("Opcion 2 seleccionada: ciudades en orden descendente\n");
                mostrar_Ciudades(colaDescendente);
                printf("//////////////////////////////////////////////\n");
                break;
            }
            case 3 : {
                cargar_datos_colaCP(listaDatos, colaAscendente);
                printf("Opcion 3 seleccionada: reducir horas de manejo\n");
                camino_mas_corto(colaAscendente);
                printf("//////////////////////////////////////////////\n");
                break;
            }
            case 4 : {
                printf("Opcion 4 seleccionada: salir\n");
                cp_destruir(colaAscendente, fEliminar);
                cp_destruir(colaDescendente, fEliminar);
                vaciarLista(listaDatos);
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

void ingresar_datos_lista(FILE * archivo, tLista * list){
    char * valor;
    TCiudad ciudad;
    tPosicion aux;
    float x;
    float y;

    aux = *list;
    while(!feof(archivo)) {
        valor = (char *) malloc(sizeof(char)*30);
        ciudad = (TCiudad) malloc(sizeof(struct ciudad));
        fscanf(archivo, "%[^;];", valor);
        fscanf(archivo, "%f;", &x);
        fscanf(archivo, "%f\n", &y);
        ciudad->nombre = valor;
        ciudad->pos_x = x;
        ciudad->pos_y = y;
        insertarElemento(ciudad, aux, list);
    }
}

void cargar_datos_colaCP(tLista list, TColaCP datos) {
    TCiudad ciudad;
    TEntrada entrada;
    tPosicion aux;
    float clave;

    aux = list;
    while (siguiente(aux, list) != NULL) {
        ciudad = (TCiudad) recuperar(aux, list);
        clave = calcular_distancia(ciudad->pos_x, ciudad->pos_y);
        entrada = crear_entrada((int) clave, ciudad); //no puedo pasar un float :(
        cp_insertar(datos, entrada);
        aux = siguiente(aux, list);
    }
}

float calcular_distancia(float x, float y) {
    float dist;
    dist = fabs(x - 1);
    dist += fabs(y - 1);
    return dist;
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

void mostrar_Ciudades(TColaCP datos) {
    TEntrada aux;
    TCiudad ciudad;
    int cant;
    int i;
    cant = cp_cantidad(datos) + 1;
    for(i = 1; i<cant; i++){
        aux = cp_eliminar(datos);
        ciudad = aux->valor;
        printf("%i. %s\n", i,ciudad->nombre);
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
    i = 1;
    totalDist = 0;
    totalDist += (unsigned long long) entradaAux->clave;

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
        totalDist += (unsigned long long) entradaAux->clave;
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
