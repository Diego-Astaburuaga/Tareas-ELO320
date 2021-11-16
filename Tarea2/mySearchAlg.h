/**
 * Modulo creado por Diego Astaburuaga, contiene las funciones correspondientes al nombre del archivo
 */

#ifndef _mySearchAlg_
#define _mySearchAlg_

#include "mySortAlg.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(Nodo** array, int sup, int objetive); // devuelve la posicion en el array del elemento entregado, -1 si no lo encuentra
void PoweredbinarySearch(Nodo** array, int sup, int indx[100]); // entrega el tiempo promedio en buscar 100 datos aleatoreos en el arreglo usando binarySearch
int FillABBarray(Nodo** SortedArray, int inf, int sup); // actualiza left y right para generar un arbol balanceado, retorna el indice de la raiz
void PoweredABBSearch(Nodo** ABB, int* indx, int root); // realizar la busqueda de los 100 datos en el abb
int ABBSearch(Nodo** ABB, int sup, int objetive); // busca un elemento en un ABB


#endif