#include "abb.h"
const static int ERROR = -1;
const static int OK = 0;
const static int IGUAL = 0;
const static size_t VACIO = 0;

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	if(!comparador){
		return NULL;
	}
	abb_t * arbol = calloc(1, sizeof(abb_t));
	if(!arbol){
		return NULL;
	}
	arbol->comparador = comparador;
	arbol->destructor = destructor;
	return arbol;
}
/*
POST: crea un nodo en el heap y le asigna el elemento enviado por referencia.
*/
nodo_abb_t * crear_nodo(void * elemento){
	nodo_abb_t * nodo_nuevo = calloc(1, sizeof(nodo_abb_t));
	if(!nodo_nuevo){
		return NULL;
	}
	nodo_nuevo->elemento = elemento;
	return nodo_nuevo;
}
/*
PRE: debe haber un nodo en la raiz.
POST: inserta nodo al arbol y le asigna el elemento enviado por referencia.
*/
nodo_abb_t *  insertar_nodo(abb_t* arbol, nodo_abb_t * nodo_actual, void * elemento, bool * error){
	if(!nodo_actual){
		nodo_abb_t * nodo_nuevo = crear_nodo(elemento);
		if(!nodo_nuevo){
			(*error) = true;
			return NULL;
		}else return nodo_nuevo;
	}
	if(arbol->comparador(nodo_actual->elemento, elemento) >= IGUAL){
		nodo_actual->izquierda = insertar_nodo(arbol, nodo_actual->izquierda, elemento, error);
	}else nodo_actual->derecha = insertar_nodo(arbol, nodo_actual->derecha, elemento, error);
	return nodo_actual;
}

int arbol_insertar(abb_t* arbol, void* elemento){
	if(!arbol || !arbol->comparador){
		return ERROR;
	}
	bool error = false;
	if(!arbol->nodo_raiz){
		arbol->nodo_raiz = crear_nodo(elemento);
		if(!arbol->nodo_raiz){
			return ERROR;
		}
	}else arbol->nodo_raiz = insertar_nodo(arbol, arbol->nodo_raiz, elemento, &error);
	if(error){
		return ERROR;
	}else return OK;
}
/*
POST: libera la memoria utilizada por el nodo y por el elemento, si es que es 
	usada. 
*/
void borrar_nodo( nodo_abb_t * nodo_a_borrar, abb_liberar_elemento destructor){
	if(destructor){
		destructor(nodo_a_borrar->elemento);
	}
	free(nodo_a_borrar);
}
/*
PRE: el nodo debe tener un solo hijo.
POST: libera la memoria utilizada por el nodo y por el elemento, si es que es 
	usada y asigna el nodo hijo a su abuelo.
*/
nodo_abb_t * borrar_elemento_un_hijo(nodo_abb_t * nodo_a_borrar, abb_liberar_elemento destructor){
	nodo_abb_t * nodo_hijo = NULL;
	if(nodo_a_borrar->derecha){
		nodo_hijo = nodo_a_borrar->derecha;
		borrar_nodo(nodo_a_borrar, destructor);
	}else{
		nodo_hijo = nodo_a_borrar->izquierda;
		borrar_nodo(nodo_a_borrar, destructor);
	}
	return nodo_hijo;
}
/*
POST: retorna el nodo predecesor al elemento a borrar.
*/
nodo_abb_t * buscar_predecesor(nodo_abb_t * nodo_actual, int * movimiento){
	if(!nodo_actual->derecha){
		return nodo_actual;
	}
	(*movimiento)++;
	return buscar_predecesor(nodo_actual->derecha, movimiento);
}
/*
POST: retorna el padre del predecesor.
*/
nodo_abb_t * buscar_padre_predecesor(nodo_abb_t * nodo_actual, nodo_abb_t * nodo_predecesor){
	if(nodo_actual->derecha == nodo_predecesor){
		return nodo_actual;
	}else if(!nodo_actual->derecha){
		return NULL;
	}else return buscar_padre_predecesor(nodo_actual->derecha, nodo_predecesor);
}
/*
PRE: el nodo debe tener dos hijos.
POST: libera la memoria utilizada por el nodo y por el elemento, si es que es 
	usada y prevé los casos en que el nodo a barrar tiene dos hijos.
*/
nodo_abb_t * borrar_elemento_dos_hijos(nodo_abb_t * nodo_a_borrar, abb_liberar_elemento destructor){
	int movimiento = 0;
	nodo_abb_t * nodo_predecesor = buscar_predecesor(nodo_a_borrar->izquierda, &movimiento);
	if(movimiento >= 1){
		nodo_abb_t * padre_predecesor = buscar_padre_predecesor(nodo_a_borrar->izquierda, nodo_predecesor);
		if(nodo_predecesor->izquierda){
			padre_predecesor->derecha = nodo_predecesor->izquierda;
			nodo_predecesor->izquierda = nodo_a_borrar->izquierda;
			nodo_predecesor->derecha = nodo_a_borrar->derecha;
		}else{
			padre_predecesor->derecha = NULL;
			nodo_predecesor->izquierda = nodo_a_borrar->izquierda;
			nodo_predecesor->derecha = nodo_a_borrar->derecha;
		}
	}else{
		nodo_predecesor->derecha = nodo_a_borrar->derecha;
	}
	borrar_nodo(nodo_a_borrar, destructor);
	return nodo_predecesor;
}
/*
POST: libera la memoria utilizada por el nodo y por el elemento, si es que es 
	usada y reacomoda los nodos para que sigan todos unidos y cumplan los requisitos de ser un ABB.
*/
 nodo_abb_t * borrar_elemento(nodo_abb_t * nodo_actual, void * elemento, abb_t * arbol, bool * error){
	if(!nodo_actual){
		(*error) = true;
		return nodo_actual;
	}
	int comparacion = arbol->comparador(nodo_actual->elemento, elemento);
	if(comparacion > IGUAL){
		nodo_actual->izquierda = borrar_elemento(nodo_actual->izquierda, elemento, arbol, error);
	}else if(comparacion < IGUAL){
		nodo_actual->derecha = borrar_elemento(nodo_actual->derecha, elemento, arbol, error);
	}else{
		if((!nodo_actual->izquierda) && (!nodo_actual->derecha)){
			borrar_nodo(nodo_actual, arbol->destructor);
			return NULL;
		}else if(((nodo_actual->izquierda) && (!nodo_actual->derecha)) || ((!nodo_actual->izquierda) && (nodo_actual->derecha))){
			nodo_actual = borrar_elemento_un_hijo(nodo_actual, arbol->destructor);
		}else{
			nodo_actual = borrar_elemento_dos_hijos(nodo_actual, arbol->destructor);
		}
	}
	return nodo_actual;
}

int arbol_borrar(abb_t* arbol, void* elemento){
	if(!arbol || !arbol->comparador || !arbol->nodo_raiz){
		return ERROR;
	}
	bool error = false;
	arbol->nodo_raiz = borrar_elemento(arbol->nodo_raiz, elemento, arbol, &error);
	if(error){
		return ERROR;
	}else return OK; 

}
/*
POST: retorna el elemento dentro del arbol cuyo comparador dio igual al elemento recibido por referencia.
*/
void * buscar_elemento(nodo_abb_t * nodo_actual, void * elemento, abb_comparador comparador){
	if(!nodo_actual){
		return NULL;
	}
	int comparacion = comparador(nodo_actual->elemento, elemento);
	if(comparacion > IGUAL){
		return buscar_elemento(nodo_actual->izquierda, elemento, comparador);
	}else if(comparacion < IGUAL){
		return buscar_elemento(nodo_actual->derecha, elemento, comparador);
	}else return nodo_actual->elemento;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
	if(!arbol || !arbol->comparador || !arbol->nodo_raiz){
		return NULL;
	}
	return buscar_elemento(arbol->nodo_raiz, elemento, arbol->comparador);
}

void* arbol_raiz(abb_t* arbol){
	if(!arbol || arbol_vacio(arbol)){
		return NULL;
	}else return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){
	return ((!arbol ) || (!arbol->nodo_raiz));
}
/*
POST: recorre el arbol de manera inorden y va llenando el array enviado con el elemento del nodo actual.
*/
void recorrer_inorden(abb_t* arbol, void** array, size_t tamanio_array, size_t *cantidad_actual, nodo_abb_t * nodo_actual){
	if(!nodo_actual){
		return;
	}
	if(nodo_actual->izquierda){
		recorrer_inorden(arbol, array, tamanio_array, cantidad_actual, nodo_actual->izquierda);
	}
	if(*cantidad_actual < tamanio_array){
		array[*cantidad_actual] = nodo_actual->elemento;
		(*cantidad_actual)++;
	}else return;
	if(nodo_actual->derecha){
		recorrer_inorden(arbol, array, tamanio_array, cantidad_actual, nodo_actual->derecha);
	}
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!arbol || !arbol->comparador || !arbol->nodo_raiz){
		return 0;
	}
	size_t cantidad = 0;
	recorrer_inorden(arbol, array, tamanio_array, &(cantidad), arbol->nodo_raiz);
	return cantidad;
}
/*
POST: recorre el arbol de manera preorden y va llenando el array enviado con el elemento del nodo actual.
*/
void recorrer_preorden(abb_t* arbol, void** array, size_t tamanio_array, size_t *cantidad_actual, nodo_abb_t * nodo_actual){
	if(!nodo_actual){
		return;
	}
	if(*cantidad_actual < tamanio_array){
		array[*cantidad_actual] = nodo_actual->elemento;
		(*cantidad_actual)++;
	}else return;
	if(nodo_actual->izquierda){
		recorrer_preorden(arbol, array, tamanio_array, cantidad_actual, nodo_actual->izquierda);
	}
	if(nodo_actual->derecha){
		recorrer_preorden(arbol, array, tamanio_array, cantidad_actual, nodo_actual->derecha);
	}
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!arbol || !arbol->comparador || !arbol->nodo_raiz){
		return 0;
	}
	size_t cantidad = 0;
	recorrer_preorden(arbol, array, tamanio_array, &(cantidad), arbol->nodo_raiz);
	return cantidad;
}
/*
POST: recorre el arbol de manera postorden y va llenando el array enviado con el elemento del nodo actual.
*/
void recorrer_postorden(abb_t* arbol, void** array, size_t tamanio_array, size_t *cantidad_actual, nodo_abb_t * nodo_actual){
	if(!nodo_actual){
		return;
	}
	if(nodo_actual->izquierda){
		recorrer_postorden(arbol, array, tamanio_array, cantidad_actual, nodo_actual->izquierda);
	}
	if(nodo_actual->derecha){
		recorrer_postorden(arbol, array, tamanio_array, cantidad_actual, nodo_actual->derecha);
	}
	if(*cantidad_actual < tamanio_array){
		array[*cantidad_actual] = nodo_actual->elemento;
		(*cantidad_actual)++;
	}else return;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!arbol || !arbol->comparador || !arbol->nodo_raiz){
		return 0;
	}
	size_t cantidad = 0;
	recorrer_postorden(arbol, array, tamanio_array, &(cantidad), arbol->nodo_raiz);
	return cantidad;
}
/*
POST: recorre el arbol y va libera la memoria utilizada por el nodo y por el
	elemento, si es que es usada.
*/
nodo_abb_t * destruir_nodos(abb_t* arbol, nodo_abb_t * nodo_actual){
	if(nodo_actual->izquierda){
		nodo_actual->izquierda = destruir_nodos(arbol, nodo_actual->izquierda);
	}
	if(nodo_actual->derecha){
		nodo_actual->derecha = destruir_nodos(arbol, nodo_actual->derecha);
	}
	if(arbol->destructor){
		arbol->destructor(nodo_actual->elemento);
	}
	free(nodo_actual);
	return NULL;
}

void arbol_destruir(abb_t* arbol){
	if(!arbol || !arbol->comparador){
		return;
	}
	while(arbol->nodo_raiz){
		arbol->nodo_raiz = destruir_nodos(arbol, arbol->nodo_raiz);
	}
	free(arbol);
}
/*
POST: recorre el arbol de manera inorden y le aplica la funcion al nodo_actual.
*/
void iterador_inorden(nodo_abb_t * nodo_actual,  bool (*funcion)(void*, void*), void* extra, size_t * cantidad, bool * encontro){
	if(!nodo_actual || (*encontro) == true){
		return;
	}
	if(nodo_actual->izquierda){
		iterador_inorden(nodo_actual->izquierda, funcion, extra, cantidad, encontro);
	}
	if(!(*encontro)){
		(*encontro) = funcion(nodo_actual->elemento, extra);
		(*cantidad)++;
		if((*encontro)){
			return;
		}
	}else return;
	if(nodo_actual->derecha){
		iterador_inorden(nodo_actual->derecha, funcion, extra, cantidad, encontro);
	}
}
/*
POST: recorre el arbol de manera preorden y le aplica la funcion al nodo_actual.
*/
void iterador_preorden(nodo_abb_t * nodo_actual,  bool (*funcion)(void*, void*), void* extra, size_t * cantidad, bool * encontro){
	if(!nodo_actual || (*encontro) == true){
		return;
	}
	if(!(*encontro)){
		(*encontro) = funcion(nodo_actual->elemento, extra);
		(*cantidad)++;
		if((*encontro)){
			return;
		}
	}else return;
	if(nodo_actual->izquierda){
		iterador_preorden(nodo_actual->izquierda, funcion, extra, cantidad, encontro);
	}
	if(nodo_actual->derecha){
		iterador_preorden(nodo_actual->derecha, funcion, extra, cantidad, encontro);
	}
}
/*
POST: recorre el arbol de manera postorden y le aplica la funcion al nodo_actual.
*/
void iterador_postorden(nodo_abb_t * nodo_actual,  bool (*funcion)(void*, void*), void* extra, size_t * cantidad, bool * encontro){
	if(!nodo_actual || (*encontro) == true){
		return;
	}
	if(nodo_actual->izquierda){
		iterador_postorden(nodo_actual->izquierda, funcion, extra, cantidad, encontro);
	}
	if(nodo_actual->derecha){
		iterador_postorden(nodo_actual->derecha, funcion, extra, cantidad, encontro);
	}
	if(!(*encontro)){
		(*encontro) = funcion(nodo_actual->elemento, extra);
		(*cantidad)++;
	}
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(!arbol || !arbol->comparador || !arbol->nodo_raiz || !funcion){
		return VACIO;
	}
	size_t cantidad = 0;
	bool encontro = false;
	if(recorrido == ABB_RECORRER_INORDEN){
		iterador_inorden(arbol->nodo_raiz, funcion, extra, &cantidad, &encontro);
	}else if(recorrido == ABB_RECORRER_PREORDEN){
		iterador_preorden(arbol->nodo_raiz, funcion, extra, &cantidad, &encontro);
	}else{
		iterador_postorden(arbol->nodo_raiz, funcion, extra, &cantidad, &encontro);
	}
	return cantidad;
}