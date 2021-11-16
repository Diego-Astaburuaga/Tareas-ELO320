/**
 * Modulo creado por Diego Astaburuaga, contiene las funciones correspondientes al nombre del archivo
 */

#ifndef _mySortAlgh_
#define _mySortAlgh_

/**
 * Def. de la estructura 
 */
typedef struct node{
 int data;
 int left;
 int right;
}Nodo;

void buildMaxHeap(Nodo** array, int inf, int sup); // genera un max-heap a partir de los datos del arreglo
void maxHeapify(Nodo** array, int inf, int sup, int pos); // verifica que el nodo del argumento cumpla con max-heap
void buildMinHeap(Nodo** array, int inf, int sup); // genera un min-heap a partir de los datos del arreglo
void minHeapify(Nodo** array, int inf, int sup, int pos); // verifica que el nodo del argumento cumpla con min-heap
void heapSort(Nodo** array, int inf, int sup, int choice); // ejecuta heapSort sobre el arreglo segun el modo
void mergeArrays(Nodo** Newarray, Nodo** Oldarray, int inf1, int sup1, int inf2, int sup2); // hace la fusión de 2 sub-arreglos ordenados en uno ordenado
void ActualizarNodo(Nodo* nodo, int pos, int inf, int sup); // actualiza left y right del nodo, usa -1 cuando no tiene hijo

#endif


