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
float calcular_distancia(float x, float y, float cord_x, float cord_y);
int ascendente(TEntrada x, TEntrada y);
int descendente(TEntrada x, TEntrada y);
void mostrar_Ciudades(TColaCP datos);
void fEliminar(TEntrada ent);
void camino_mas_corto(TColaCP datos);
TEntrada crear_entrada(TCiudad ciudad, float cord_x, float cord_y);

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
    }
    */
    viajes = fopen("viajes.txt", "r");

    crearListaVacia(&listaDatos);
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

/**
    * @brief Ingresa datos de un archivo a una lista.
    * @param archivo archivo correspondiente a las ciudades.
    * @param list lista.
 */
void ingresar_datos_lista(FILE * archivo, tLista * list){
    char * valor;
    TCiudad ciudad;
    tElem * insert;
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
        insert = (tElem *) ciudad;
        insertarElemento(insert, aux, list);
    }
}

/**
    * @brief Cargar datos de una lista en una cola con prioridad.
    * @param list Lista.
    * @param datos Cola con prioridad.
 */
void cargar_datos_colaCP(tLista list, TColaCP datos) {
    TCiudad ciudad;
    TEntrada entrada;
    tPosicion aux;

    aux = list;
    while (siguiente(aux, list) != NULL) {
        ciudad = (TCiudad) recuperar(aux, list);
        entrada = crear_entrada(ciudad, 1, 1);
        cp_insertar(datos, entrada);
        aux = siguiente(aux, list);
    }
}

/**
    * @brief Calcula la distancia entre las coordenadas recibidas.
    * @param x coordenada destino.
    * @param y coordenada destino.
    * @param cord_x origen.
    * @param cord_y origen.
    * @return float resultado.
*/
float calcular_distancia(float x, float y, float cord_x, float cord_y) {
    float dist;
    dist = fabs(x - cord_x);
    dist += fabs(y - cord_y);
    return dist;
}

/**
    *@brief Funcion de comparacion de claves de entradas.
    *@param x entrada.
    *@param y entrada.
    *@return int -1 , 1 o 0.
*/
int ascendente(TEntrada x, TEntrada y) {
    int toReturn;
    float clave_1 = *(float*) x->clave;
    float clave_2 = *(float*) y->clave;
    if(clave_1 < clave_2)
        toReturn = -1;
    else if (clave_1 == clave_2) {
        toReturn = 0;
    }
    else
        toReturn = 1;
    return toReturn;
}

/**
    *@brief Funcion de comparacion de claves de entradas.
    *@param x entrada.
    *@param y entrada.
    *@return int -1 , 1 o 0.
*/
int descendente(TEntrada x, TEntrada y) {
    int toReturn;
    float clave_1 = *(float*) x->clave;
    float clave_2 = *(float*) y->clave;
    if(clave_1 > clave_2)
        toReturn = -1;
    else if (clave_1 == clave_2) {
        toReturn = 0;
    }
    else
        toReturn = 1;
    return toReturn;
}

/**
    *@brief muestra por pantalla los nombres de las ciudades ordenadas.
    *@param datos Cola con prioridad.
*/
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

/**
    *@brief  calcula y muestra por pantalla las ciudades de la cola que forman la distancia del camino mas corto.
    *@param datos Cola con prioridad.
*/
void camino_mas_corto(TColaCP datos) {
    TColaCP colaAux;
    TCiudad ciudadAux;
    TEntrada entradaAux;
    float cord_x;
    float cord_y;
    float clave;
    float totalDist;
    int control;
    int i;

    control = datos->cantidad_elementos;
    colaAux = crear_cola_cp(ascendente);
    entradaAux = cp_eliminar(datos);
    ciudadAux = entradaAux->valor;
    cord_x = ciudadAux->pos_x,
    cord_y = ciudadAux->pos_y;
    totalDist = *(float*) entradaAux->clave;
    i = 1;

    printf("%i. %s\n", i,ciudadAux->nombre);

    while(i < control){
        while(datos->cantidad_elementos > 0){
            entradaAux = cp_eliminar(datos);
            ciudadAux = entradaAux->valor;
            clave = fabs(ciudadAux->pos_x - cord_x);
            clave += fabs(ciudadAux->pos_y - cord_y);
            cp_insertar(colaAux, crear_entrada(ciudadAux, cord_x, cord_y));
        }
        entradaAux = cp_eliminar(colaAux);
        ciudadAux = entradaAux->valor;
        cord_x = ciudadAux->pos_x,
        cord_y = ciudadAux->pos_y;
        totalDist += *(float*) entradaAux->clave;
        printf("%i. %s\n", i,ciudadAux->nombre);

        while(colaAux->cantidad_elementos > 0){
            cp_insertar(datos, cp_eliminar(colaAux));
        }
        i++;
    }
    printf("Total recorrido %.0f\n", totalDist);
    cp_destruir(colaAux, fEliminar);
}

/**
    *@brief elimina una entrada en su totalidad.
    *@param ent Entrada.
*/
void fEliminar(TEntrada ent){
    ent->clave= NULL;
    ent->valor= NULL;
    free(ent);
    ent= NULL;
}

/**
    *@brief crea una entrada clave/valor, con respecto a las coordenadas origen.
    *@param ciudad Ciudad y Coordenadas.
    *@param cord_x coordenada origen.
    *@param cord_y coordenada origen.
    *@return TEntrada entrada generada.
*/
TEntrada crear_entrada(TCiudad ciudad, float cord_x, float cord_y) {
    TEntrada toReturn;
    float * dist;

    toReturn = (TEntrada) malloc(sizeof(struct entrada));
    dist = (float *) malloc(sizeof(float));
    *dist = calcular_distancia(ciudad->pos_x, ciudad->pos_y, cord_x, cord_y);
    toReturn->clave = dist;
    toReturn->valor = ciudad;
    return toReturn;
}
