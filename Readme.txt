1ª SECCION:
	En el presente trabajo se presenta el tda ARBOL BINARIO DE BUSQUEDA junto con un
	iterador interno. en el mismo se encuentran las operaciones basicas de un arbol
	binario. en "crear_arbol" se crea el arbol , este debe tener de manera 
	obligatoria un comparador y el usuario decide si quiere tener un destructor.
	en "arbol_insertar" de inserta el elemento que se quiera al arbol, utilizando
	el comparador para saber donde se debe insertar, encaso de ser menor al elemento
	actual, se debe ingresar a la izquierda, caso contraio, se debe insertar en el 
	lado derecho. con la funcion "arbol_borrar" se elimina el elemento del arbol que
	se quiera, utilizando el destructor en el elemento, en el caso de 
	que hubiera un destructor, se tomo la decision de que en el caso que el elemento
	borrado tenga dos hijos, se utilizara el elemento predecesor para mantener el 
	equilibrio del arbol. con "arbol_buscar" se busca un elemento dentro del arbol
	que califique como igual por el comparador al elemento que se envio. se utiliza 
	"arbol_raiz" para ver que elemento es la raiz del arbol y con "arbol_vacio" para
	ver si el arbol esta vacio. tanto con "arbol_recorrido_preorden", 
	"arbol_recorrido_inorden" como con "arbol_recorrido_postorden" se recorre el
	arbol de una manera distinta, dependiendo de cual funcion se llame. con 
	"arbol_destruir" se libera toda la memoria que fue utiliza por el arbol. Y por
	ultimo, "abb_con_cada_elemento" es el iterador interno, el cual se itera hasta 
	que la funcion enviada retorne true, tambien se puede elegir de que manera se 
	quiere recorrer el arbol y retorna la cantidad de elementos recorridos hasta 
	que la funcion retorne true o se hayan recorrido todos los elementos del arbol.


	LINEA DE COMPILACION:
	se compila con la siguiente linea:
		"gcc *.c -o abb -g -std=c99  -Wall -Wconversion -Wtype-limits -pedantic 
		-Werror -O0"
	en el cual: 
		gcc: es un compilador de programas en c.
		*.c: significa que se deberan compilar todos los archivos con extencion .c en 
			la carpeta donde nos encontremos.
		-g -std=c99  -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0: flags
			 nesesarios para que el programa nos informe de cualquier error que 
			 tengamos.
		-o abb: como llamaremos al programa ya compilado y listo para ejecutar

	LINEA DE EJECUCION:
	se ejecuta de la siguiente manera:
	"./ abb"
	en el cual:
		./: lo que escribas despues de el sera un archivo dentro del directorio donde 
		te encontras y no un comando.
		abb: nombre del archivo. 


2ª SECCION:
	"Explicar qué es un ABB y cómo se diferencia de un Árbol Binario".

	un ABB es un arbol binario de busqueda, que al ser un arbol binario, utiliza 
	todas las caracteristicas fundamentales de un arbol binario (la utilizacion
	de nodos y tener solo un hijo para la derecha y para la izquierda), sin embargo,
	la principal diferencia con estos radica que los arboles binarios no tiene un
	orden en especifico y no tiene especificado ningun tipo de regla para poder
	insertar los elementos. los ABB, en cambio, si lo tienen el cual es que si el
	elemento es menor al comparado, se debe ingresar al sub-arbol izquierdo, caso 
	contrario, al sub-arbol derecho (en caso de ser igual, se deja la decision 
	al programador a que lado deb ser ingreaso el elemento repetido).

	"Explicar cuál es el objetivo de tener una función de destrucción en el TDA y 
	qué implicaría para el usuario no tenerla."

	el objetivo principal de tener un destructor en el arbol, es para automatizar
	la liberacion de memoria utiliza por el elemento que se quiere insertar en el
	arbol, ya que sin ella, el usuario deberia liberar la memoria de los elementos
	por si mismo, en el caso de que este usando memoria del heap. sin embargo, si
	no se utilizando memoria del heap para los elementos, no es necesario tener
	un destructor.

	"¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique."

	"arbol_crear": O(1), ya que es todo seguido, sin tener que iterar nada.

	"arbol_insertar": O(n), porque en el peor de los casos, el arbol se
	degenera en una lista, la cual tiene tiempo de ejecucion O(n) ya que deberia
	recorrer toda la lista si quiero insertar al final.

	"arbol_borrar": O(n), porque en el peor de los casos, el arbol se
	degenera en una lista, la cual tiene tiempo de ejecucion O(n) ya que deberia
	recorrer toda la lista si quiero borrar el nodo del final.

	"arbol_buscar": O(n), porque en el peor de los casos, el arbol se
	degenera en una lista, la cual tiene tiempo de ejecucion O(n) ya que deberia
	recorrer toda la lista si quiero buscar el elemento del final.

	"arbol_raiz": O(n), ya que es todo seguido, sin tener que iterar nada.

	"arbol_vacio": O(n), ya que es todo seguido, sin tener que iterar nada.

	"arbol_recorrido_inorden": O(n), porque en el peor de los casos, el arbol se
	degenera en una lista, la cual tiene tiempo de ejecucion O(n) si quiero recorrer
	toda la lista.

	"arbol_recorrido_preorden": O(n), porque en el peor de los casos, el arbol se
	degenera en una lista, la cual tiene tiempo de ejecucion O(n) si quiero recorrer
	toda la lista.

	"arbol_recorrido_postorden": O(n), porque en el peor de los casos, el arbol se
	degenera en una lista, la cual tiene tiempo de ejecucion O(n) si quiero recorrer
	toda la lista.

	"arbol_destruir": O(n), ya que es todo seguido, sin tener que iterar nada.

	"abb_con_cada_elemento": O(n), porque en el peor de los casos, el arbol se
	degenera en una lista, la cual tiene tiempo de ejecucion O(n) si quiero recorrer
	toda la lista.
