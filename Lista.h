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
