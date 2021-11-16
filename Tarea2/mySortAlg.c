/**
 * Modulo creado por Diego Astaburuaga, contiene las funciones correspondientes al nombre del archivo
 */

#include "mySortAlg.h"
#include <stdio.h>


/******** EMPIEZA - Codificacion basada en el libro Introduction to algorithms********/

/**
 * Genera un max-heap a partir de los datos del arreglo
 */
void buildMaxHeap(Nodo** array, int inf, int sup){
    for (int i=inf+(sup-inf)/2; i>=inf; i--){
        maxHeapify(array, inf, sup, i);
    }
}

/**
 * Verifica que el nodo del argumento cumpla con max-heap
 */
void maxHeapify(Nodo** array, int inf, int sup, int pos){
    int largest;
    ActualizarNodo(array[pos], pos, inf, sup);
    // tiene hijo izquierdo y left mayor su padre 
    if ((array[pos]->left!=-1) && (array[array[pos]->left]->data)>(array[pos]->data)){
        largest = array[pos]->left; // el mayor es el hijo izquierdo
    }
    else{
        largest = pos; // el mayor es el mismo nodo
    }
    // tiene hijo derecho y right mayor al mayor entre left y su padre
    if ((array[pos]->right!=-1) && (array[array[pos]->right]->data)>(array[largest]->data)){
        largest = array[pos]->right; // el mayor es el hijo derecho
    }
    // si el mayor es un hijo, entonces se cambia y se sigue el algoritmo
    if (largest != pos){
        Nodo* aux;
        // swap de pos
        aux = array[pos];
        array[pos] = array[largest];
        array[largest] = aux;
        // recursividad
        maxHeapify(array, inf, sup, largest);
    }
}

/**
 * Genera un min-heap a partir de los datos del arreglo
 */
void buildMinHeap(Nodo** array, int inf, int sup){
    for (int i=inf+(sup-inf)/2; i>=inf; i--){
        minHeapify(array, inf, sup, i);
    }
}

/**
 * Verifica que el nodo del argumento cumpla con min-heap
 */
void minHeapify(Nodo** array, int inf, int sup, int pos){
    int shortest;
    ActualizarNodo(array[pos], pos, inf, sup);
    // tiene hijo izquierdo y left menor su padre 
    if ((array[pos]->left!=-1) && (array[array[pos]->left]->data)<(array[pos]->data)){
        shortest = array[pos]->left; // el menor es el hijo izquierdo
    }
    else{
        shortest = pos; // el menor es el mismo nodo
    }
    // tiene hijo derecho y right menor al menor entre el padre y left
    if ((array[pos]->right!=-1) && (array[array[pos]->right]->data)<(array[shortest]->data)){
        shortest = array[pos]->right; // el menor es el hijo derecho
    }
    // si el menor es un hijo, entonces se cambia y se sigue el algoritmo
    if (shortest != pos){
        Nodo* aux;
        // swap de pos
        aux = array[pos];
        array[pos] = array[shortest];
        array[shortest] = aux;
        // recursividad
        minHeapify(array, inf, sup, shortest);
    }
}

/**
 * Ejecuta heapSort sobre el arreglo segun se tenga max-heap o min-heap
 */
void heapSort(Nodo** array, int inf, int sup, int choice){
    Nodo* aux;
    // se quiere un maxheap
    if (choice==0){
        // algoritmo del libro
        buildMaxHeap(array, inf, sup);
        for (int pos = sup; pos>=inf+1; pos--){
            // swap
            aux=array[pos];
            array[pos]=array[inf];
            array[inf]=aux;
            sup-=1; // el elemento en sup ya esta ordenado
            maxHeapify(array, inf, sup, inf);
        }
    }
    // se quiere un minheap
    else if (choice==1){
        buildMinHeap(array, inf, sup);
        for (int pos = sup; pos>=inf+1; pos--){
            // swap
            aux=array[pos];
            array[pos]=array[inf];
            array[inf]=aux;
            sup-=1; // el elemento en sup ya esta ordenado
            minHeapify(array, inf, sup, inf);
        }
    }
    else{
        printf("\n||ERROR: argumento invalido sobre la funcion||\n");
    }
}

// el maxheap queda en orden creciente mientras que el minheap queda en orden decreciente

/******** TERMINA - Codificacion basada en el libro Introduction to algorithms********/

/**
 * Hace la fusión de 2 sub-arreglos ordenados (uno decreciente y el otro creciente) en uno ordenado
 */
void mergeArrays(Nodo** Newarray, Nodo** Oldarray, int inf1, int sup1, int inf2, int sup2){
    int j=sup1; // posicion del menor elemento
    int k=inf2; // posicion del menor elemento
    for (int i=0; i<sup1-inf1+1+sup2-inf2+1; i++){ // por cada indice el Newarray
        if (k>sup2 || j<inf1){ // terminamos uno de los arreglos
            if(k>sup2){ // no quedan elementos en el arreglo2
                Newarray[i]=Oldarray[j];
                j--;
            }
            else{ // no quedan elementos en el arreglo1
               Newarray[i]=Oldarray[k];
                k++; 
            }
        }
        else{ // si ambos arreglos aun tienen elementos, se comparan
            if(Oldarray[k]->data<Oldarray[j]->data && k<=sup2){ // data arreglo2 menor a data arreglo1
                Newarray[i]=Oldarray[k];
                k++;
            }
            else{ // data arreglo1 menor o igual a data arreglo2
                Newarray[i]=Oldarray[j];
                j--;
            }
        }
    }
}
/*la logica anterior es inspirida en el algoritmo Merge del libro citado anteriormente, pero alterada dado el caso especifico*/

/**
 * Actualiza los datos de left y right de la estructura, con -1 cuando no tiene hijo
 */
void ActualizarNodo(Nodo* nodo, int pos, int inf, int sup){
    if (2*pos-inf+1<=sup){
        nodo->left = 2*pos-inf+1;
    }
    else{
        nodo->left = -1;
    }
    if (2*pos-inf+2<=sup){
        nodo->right = 2*pos-inf+2;
    }
    else{
        nodo->right = -1;
    }
}
