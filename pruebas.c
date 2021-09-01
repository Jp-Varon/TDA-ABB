#include "abb.h"
#include <stdio.h>
#include "pa2mm.h"

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

bool mostrar_elemento(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(elemento)
        printf("%i ", ((cosa*)elemento)->clave);
    return false;
}

bool mostrar_hasta_5(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(elemento){
        printf("%i ", ((cosa*)elemento)->clave);
        if(((cosa*)elemento)->clave == 5)
            return true;
    }
    return false;
}

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c)
        c->clave = clave;
    return c;
}


int comparar_cosas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
        return 0;

    if(((cosa*)elemento1)->clave>((cosa*)elemento2)->clave)
        return 1;
    if(((cosa*)elemento1)->clave<((cosa*)elemento2)->clave)
        return -1;
    return 0;
}

void destruir_cosa(cosa* c){
    free(c);
}

void destructor_de_cosas(void* elemento){
    if(!elemento)
        return;
    destruir_cosa((cosa*)elemento);
}

void pruebas_crear(){
	pa2m_nuevo_grupo("PRUEBAS CREAR ARBOL:");
	pa2m_afirmar(arbol_crear(NULL, NULL) == NULL, "no se creo arbol, sin destructor y ni comparador");
	pa2m_afirmar(arbol_crear(NULL, destructor_de_cosas) == NULL, "no se pudo crear arbol, no hay comparador");
	abb_t * arbol = NULL;
	pa2m_afirmar((arbol = arbol_crear(comparar_cosas, NULL)) != NULL, "se pudo crear arbol sin destructor");
	arbol_destruir(arbol);
	pa2m_afirmar((arbol = arbol_crear(comparar_cosas, destructor_de_cosas)) != NULL, "se pudo crear arbol con todos los elementos");
	pa2m_afirmar(arbol_raiz(arbol) == NULL, "la raiz del arbol es NULL");
	pa2m_afirmar(arbol_vacio(arbol) == true, "el arbol esta vacio");
	arbol_destruir(arbol);

}

void pruebas_insertar(){
	pa2m_nuevo_grupo("PRUEBAS INSERTAR ARBOL:");
	abb_t * arbol = NULL;
	cosa* c1= crear_cosa(1);
    cosa* c2= crear_cosa(2);
    cosa* c3= crear_cosa(3);
	pa2m_afirmar(arbol_insertar(arbol, c1) == -1, "no se pudo insertar elemento, no existe arbol");
	pa2m_afirmar((arbol = arbol_crear(comparar_cosas, destructor_de_cosas)) != NULL, "se pudo crear arbol con todos los elementos");
	pa2m_afirmar(arbol_insertar(arbol, c1) == 0, "se pudo insertar elemento c1");
	pa2m_afirmar(arbol_raiz(arbol) == (cosa*)c1, "la raiz del arbol es c1");
	pa2m_afirmar(arbol_insertar(arbol, c2) == 0, "se pudo insertar elemento c2");
	pa2m_afirmar(arbol_buscar(arbol, c2) == (cosa*)c2, "se busco el elemento c2 y se encontro");
	pa2m_afirmar(arbol_buscar(arbol, c3) == NULL, "se busco el elemento c3 y no se encontro");
	pa2m_afirmar(arbol_insertar(arbol, c3) == 0, "se pudo insertar elemento c3");
	pa2m_afirmar(arbol_buscar(arbol, c3) == (cosa*)c3, "se busco el elemento c3 y se encontro");
    arbol_destruir(arbol);
}

void pruebas_dos_hijos(){

	pa2m_nuevo_grupo("PRUEBAS BORRAR CON DOS HIJOS EN ARBOL:");
	cosa* c100= crear_cosa(100);
    cosa* c50= crear_cosa(50);
    cosa* c40= crear_cosa(40);
    cosa* c60= crear_cosa(60);
    cosa* c300= crear_cosa(300);
    cosa* c200= crear_cosa(200);
    cosa* c400= crear_cosa(400);
    cosa* c150= crear_cosa(150);
    cosa* c250= crear_cosa(250);
    cosa* c240= crear_cosa(240);
    cosa* c230= crear_cosa(230);
    abb_t * arbol = NULL;
    pa2m_afirmar((arbol = arbol_crear(comparar_cosas, destructor_de_cosas)) != NULL, "se pudo crear arbol con todos los elementos");

    pa2m_afirmar(arbol_insertar(arbol, c100) == 0, "se pudo insertar elemento c100");
    pa2m_afirmar(arbol_insertar(arbol, c50) == 0, "se pudo insertar elemento c50");
    pa2m_afirmar(arbol_insertar(arbol, c300) == 0, "se pudo insertar elemento c300");
    pa2m_afirmar(arbol_insertar(arbol, c40) == 0, "se pudo insertar elemento c40");
    pa2m_afirmar(arbol_insertar(arbol, c60) == 0, "se pudo insertar elemento c60");
    pa2m_afirmar(arbol_insertar(arbol, c200) == 0, "se pudo insertar elemento c200");
    pa2m_afirmar(arbol_insertar(arbol, c400) == 0, "se pudo insertar elemento c400");
    pa2m_afirmar(arbol_insertar(arbol, c150) == 0, "se pudo insertar elemento c150");
    pa2m_afirmar(arbol_insertar(arbol, c250) == 0, "se pudo insertar elemento c250");
    pa2m_afirmar(arbol_insertar(arbol, c240) == 0, "se pudo insertar elemento c240");
    pa2m_afirmar(arbol_insertar(arbol, c230) == 0, "se pudo insertar elemento c230");
  pa2m_afirmar(arbol_borrar(arbol, c50) == 0, "se pudo borrar elemento c50");
    pa2m_afirmar(arbol_buscar(arbol, c60) == (cosa*)c60, "se busco el elemento c60 y se encontro");
   pa2m_afirmar(arbol_borrar(arbol, c100) == 0, "se pudo borrar elemento c100");
    pa2m_afirmar(arbol_raiz(arbol) == (cosa*)c60, "la raiz del arbol es c60");
    c100= crear_cosa(100);
    pa2m_afirmar(arbol_buscar(arbol, c100) == NULL, "se busco el elemento c100 y no se encontro");
    pa2m_afirmar(arbol_borrar(arbol, c250) == 0, "se pudo borrar elemento c250");
    pa2m_afirmar(arbol_buscar(arbol, c240) == (cosa*)c240, "se busco el elemento c240 y se encontro");
    pa2m_afirmar(arbol_borrar(arbol, c200) == 0, "se pudo borrar elemento c200");
    pa2m_afirmar(arbol_buscar(arbol, c240) == (cosa*)c240, "se busco el elemento c240 y se encontro");
    pa2m_afirmar(arbol_borrar(arbol, c300) == 0, "se pudo borrar elemento c300");
    pa2m_afirmar(arbol_buscar(arbol, c400) == (cosa*)c400, "se busco el elemento c400 y se encontro");
    free(c100);
    arbol_destruir(arbol);
}

void pruebas_borrar(){
	pa2m_nuevo_grupo("PRUEBAS BORRAR EN ARBOL:");
	abb_t * arbol = NULL;
	cosa* c1= crear_cosa(1);
    cosa* c2= crear_cosa(2);
    cosa* c3= crear_cosa(3);
    pa2m_afirmar(arbol_borrar(arbol, c1) == -1, "no se pudo borrar, no existe arbol");
    pa2m_afirmar((arbol = arbol_crear(comparar_cosas, destructor_de_cosas)) != NULL, "se pudo crear arbol con todos los elementos");
    pa2m_afirmar(arbol_borrar(arbol, c1) == -1, "no se pudo borrar, arbol vacio");
    pa2m_afirmar(arbol_insertar(arbol, c1) == 0, "se pudo insertar elemento c1");
    pa2m_afirmar(arbol_borrar(arbol, c1) == 0, "se pudo borrar elemento c1");
    pa2m_afirmar(arbol_insertar(arbol, c2) == 0, "se pudo insertar elemento c2");
    pa2m_afirmar(arbol_insertar(arbol, c3) == 0, "se pudo insertar elemento c3");
    pa2m_afirmar(arbol_borrar(arbol, c3) == 0, "se pudo borrar elemento c3");
    pa2m_afirmar(arbol_borrar(arbol, c2) == 0, "se pudo borrar elemento c2");
    c1= crear_cosa(1);
    c2= crear_cosa(2);
    c3= crear_cosa(3);
    cosa* c4= crear_cosa(4);
    cosa* c5= crear_cosa(5);
    cosa* c6= crear_cosa(6);
    cosa* c7= crear_cosa(7);
    cosa* c9= crear_cosa(9);
    pa2m_afirmar(arbol_insertar(arbol, c4) == 0, "se pudo insertar elemento c4");
    pa2m_afirmar(arbol_insertar(arbol, c2) == 0, "se pudo insertar elemento c2");
    pa2m_afirmar(arbol_insertar(arbol, c6) == 0, "se pudo insertar elemento c6");
    pa2m_afirmar(arbol_insertar(arbol, c1) == 0, "se pudo insertar elemento c1");
    pa2m_afirmar(arbol_insertar(arbol, c3) == 0, "se pudo insertar elemento c3");
    pa2m_afirmar(arbol_insertar(arbol, c5) == 0, "se pudo insertar elemento c5");
    pa2m_afirmar(arbol_insertar(arbol, c7) == 0, "se pudo insertar elemento c7");
    pa2m_afirmar(arbol_insertar(arbol, c9) == 0, "se pudo insertar elemento c9");
    pa2m_afirmar(arbol_borrar(arbol, c7) == 0, "se pudo borrar elemento c7");
    c7= crear_cosa(7);
    pa2m_afirmar(arbol_buscar(arbol, c7) == NULL, "se busco el elemento c7 y no se encontro");
    pa2m_afirmar(arbol_buscar(arbol, c9) == (cosa*)c9, "se busco el elemento c9 y se encontro");
    pa2m_afirmar(arbol_insertar(arbol, c7) == 0, "se pudo insertar elemento c7");
    pa2m_afirmar(arbol_borrar(arbol, c9) == 0, "se pudo borrar elemento c9");
    pa2m_afirmar(arbol_borrar(arbol, c7) == 0, "se pudo borrar elemento c7");
    pa2m_afirmar(arbol_borrar(arbol, c5) == 0, "se pudo borrar elemento c5");
    pa2m_afirmar(arbol_borrar(arbol, c3) == 0, "se pudo borrar elemento c3");
    pa2m_afirmar(arbol_borrar(arbol, c1) == 0, "se pudo borrar elemento c1");
    pa2m_afirmar(arbol_borrar(arbol, c6) == 0, "se pudo borrar elemento c6");
    pa2m_afirmar(arbol_borrar(arbol, c2) == 0, "se pudo borrar elemento c2");
    pa2m_afirmar(arbol_borrar(arbol, c4) == 0, "se pudo borrar elemento c4");
    pa2m_afirmar(arbol_raiz(arbol) == NULL, "la raiz del arbol es NULL");
    arbol_destruir(arbol);
    pruebas_dos_hijos();

}

void pruebas_recorrer(){
	pa2m_nuevo_grupo("PRUEBAS RECORRER ARBOL:");
	abb_t * arbol = NULL;
	cosa* c1= crear_cosa(1);
    cosa* c2= crear_cosa(2);
    cosa* c3= crear_cosa(3);
    cosa* c4= crear_cosa(4);
    cosa* c5= crear_cosa(5);
    cosa* c6= crear_cosa(6);
    cosa* c7= crear_cosa(7);
    cosa* elementos[10];
    size_t cantidad = 0;
    pa2m_afirmar((cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10)) == 0, "se recorrio el arbol en inorden y se obtuvieron 0 elementos, no existe arbol");
    pa2m_afirmar((cantidad = arbol_recorrido_preorden(arbol, (void**)elementos, 10)) == 0, "se recorrio el arbol en preorden y se obtuvieron 0 elementos, no existe arbol");
    pa2m_afirmar((cantidad = arbol_recorrido_postorden(arbol, (void**)elementos, 10)) == 0, "se recorrio el arbol en preorden y se obtuvieron 0 elementos, no existe arbol");
    pa2m_afirmar((arbol = arbol_crear(comparar_cosas, destructor_de_cosas)) != NULL, "se pudo crear arbol con todos los elementos");
    pa2m_afirmar((cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10)) == 0, "se recorrio el arbol en inorden y se obtuvieron 0 elementos, arbol vacio");
    pa2m_afirmar((cantidad = arbol_recorrido_preorden(arbol, (void**)elementos, 10)) == 0, "se recorrio el arbol en preorden y se obtuvieron 0 elementos, arbol vacio");
    pa2m_afirmar((cantidad = arbol_recorrido_postorden(arbol, (void**)elementos, 10)) == 0, "se recorrio el arbol en preorden y se obtuvieron 0 elementos, arbol vacio");

    pa2m_afirmar(arbol_insertar(arbol, c4) == 0, "se pudo insertar elemento c4");
    pa2m_afirmar(arbol_insertar(arbol, c2) == 0, "se pudo insertar elemento c2");
    pa2m_afirmar(arbol_insertar(arbol, c6) == 0, "se pudo insertar elemento c6");
    pa2m_afirmar(arbol_insertar(arbol, c1) == 0, "se pudo insertar elemento c1");
    pa2m_afirmar(arbol_insertar(arbol, c3) == 0, "se pudo insertar elemento c3");
    pa2m_afirmar(arbol_insertar(arbol, c5) == 0, "se pudo insertar elemento c5");
    pa2m_afirmar(arbol_insertar(arbol, c7) == 0, "se pudo insertar elemento c7");
    pa2m_afirmar((cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 3)) == 3, "se recorrio el arbol en inorden y se obtuvieron los maximos elementos posibles");
    pa2m_afirmar((cantidad = arbol_recorrido_preorden(arbol, (void**)elementos, 3)) == 3, "se recorrio el arbol en preorden y se obtuvieron los maximos elementos posibles");
    pa2m_afirmar((cantidad = arbol_recorrido_postorden(arbol, (void**)elementos, 3)) == 3, "se recorrio el arbol en preorden y se obtuvieron los maximos elementos posibles");
    pa2m_afirmar((cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10)) == 7, "se recorrio el arbol en inorden y se obtuvieron todos los elementos")
    printf("Recorrido inorden: ");
    for(size_t i=0;i<cantidad;i++)
        printf("%i ", elementos[i]->clave);
    printf("\n");
    pa2m_afirmar((cantidad = arbol_recorrido_preorden(arbol, (void**)elementos, 10)) == 7, "se recorrio el arbol en preorden y se obtuvieron todos los elementos")
    printf("Recorrido preorden: ");
    for(size_t i=0;i<cantidad;i++)
        printf("%i ", elementos[i]->clave);
    printf("\n");
    pa2m_afirmar((cantidad = arbol_recorrido_postorden(arbol, (void**)elementos, 10)) == 7, "se recorrio el arbol en preorden y se obtuvieron todos los elementos")
    printf("Recorrido postorden: ");
    for(size_t i=0;i<cantidad;i++)
        printf("%i ", elementos[i]->clave);
    printf("\n");
    arbol_destruir(arbol);
}

void pruebas_iterador(){
	pa2m_nuevo_grupo("PRUEBAS ITERADOR INTERNO:");
	abb_t * arbol = NULL;
	cosa* c1= crear_cosa(1);
    cosa* c2= crear_cosa(2);
    cosa* c3= crear_cosa(3);
    cosa* c4= crear_cosa(4);
    cosa* c5= crear_cosa(5);
    cosa* c6= crear_cosa(6);
    cosa* c7= crear_cosa(7);
    pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL) == 0, "se quiso recorrer el arbol, arbol no existe");
    pa2m_afirmar((arbol = arbol_crear(comparar_cosas, destructor_de_cosas)) != NULL, "se pudo crear arbol con todos los elementos");
    pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL) == 0, "se quiso recorrer el arbol, arbol vacio");

    pa2m_afirmar(arbol_insertar(arbol, c4) == 0, "se pudo insertar elemento c4");
    pa2m_afirmar(arbol_insertar(arbol, c2) == 0, "se pudo insertar elemento c2");
    pa2m_afirmar(arbol_insertar(arbol, c6) == 0, "se pudo insertar elemento c6");
    pa2m_afirmar(arbol_insertar(arbol, c1) == 0, "se pudo insertar elemento c1");
    pa2m_afirmar(arbol_insertar(arbol, c3) == 0, "se pudo insertar elemento c3");
    pa2m_afirmar(arbol_insertar(arbol, c5) == 0, "se pudo insertar elemento c5");
    pa2m_afirmar(arbol_insertar(arbol, c7) == 0, "se pudo insertar elemento c7");
    pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, NULL, NULL) == 0, "se quiso recorrer el arbol, no existe funcion");

    printf("Recorrido inorden iterador interno: ");
    pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL) == 7, "se recorrieron todos los nodos en inorden");
    printf("\n");

    printf("Recorrido preorden iterador interno: "); 
    pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL) == 7, "se recorrieron todos los nodos en preorden");
    printf("\n");
    
    printf("Recorrido postorden iterador interno: ");  
    pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL) == 7, "se recorrieron todos los nodos en preorden");
    printf("\n");

    size_t cant_elementos = 0;
    printf("\nRecorrido inorden hasta encontrar el 5: ");    
    cant_elementos = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
    printf("\n");
    printf("cantidad = %i\n", cant_elementos);

    printf("Recorrido preorden hasta encontrar el 5: ");    
    cant_elementos = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
    printf("\n");
    printf("cantidad = %i\n", cant_elementos);
    printf("Recorrido postorden hasta encontrar el 5: ");    
    cant_elementos = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
    printf("\n");
    printf("cantidad = %i\n", cant_elementos);
    arbol_destruir(arbol);


}

int main (){
	//pruebas_crear();
	pruebas_insertar();
	//pruebas_borrar();
	//pruebas_recorrer();
	//pruebas_iterador();
	pa2m_mostrar_reporte();
	return 0; 
}