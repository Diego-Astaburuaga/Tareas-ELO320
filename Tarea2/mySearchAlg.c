/**
 * Modulo creado por Diego Astaburuaga, contiene las funciones correspondientes al nombre del archivo
 */

#include "mySortAlg.h"
#include <stdio.h>
#include <sys/time.h>  // desconozco "sys" pero sirve para obtener struc timeval
#include <time.h> 
#include <stdlib.h>



/**
 * Devuelve la posicion en el array del elemento entregado, -1 si no lo encuentra
 */
int binarySearch(Nodo** array, int sup,int objetive){
    int inf = 0;
    int mid;
    while (inf <= sup){ // mientras quede arreglo por buscar
        mid = inf + (sup - inf)/2; // obtenemos el medio
        if (array[mid]->data == objetive){return mid;} // si el valor esta en medio, estamos listos
        if (array[mid]->data < objetive){inf = mid +1;} // si el valor buscado es mayor, debe estar a la derecha
        else{sup = mid - 1;} // si el valor buscado es menor, debe estar a la izquierda
    }
    return -1;
}

/*binarySearch obtenido de BettaTech: https://www.youtube.com/watch?v=OfqrO2hUEZY*/

/**
 * Entrega el tiempo promedio en buscar 100 datos en el arreglo usando binarySearch
 */
void PoweredbinarySearch(Nodo** array, int sup, int indx[100]){
    struct timeval begin, end; // estructuras de tiempo para obtener medicion
    gettimeofday(&begin, 0); // tiempo inicial
    for (int i=0; i<1000; i++){ // iteracion i-esima
        for (int j=0; j<100; j++){ // valor j-esimo, busca 100 datos aleatorios que existen
            binarySearch(array, sup, indx[j]);
        }
    }
    printf("\n");
    gettimeofday(&end, 0); // tiempo final
    long seconds = end.tv_sec - begin.tv_sec; // diferencia de segundos
    long microseconds = end.tv_usec - begin.tv_usec; // diferencia de microsegundos
    double elapsed = seconds + microseconds*1e-6; // diferencia de tiempo
    printf("This time take: %.6f miliseconds to find 100 randoms values in mergedArray.\n", elapsed);
    // es en milisegundos ya que al buscar 1000 veces cada valor, hay que dividir el tiempo en segundos por 1000.
}

/* codificacion utilizada para medicion de tiempo obtenida de https://ichi.pro/es/8-formas-de-medir-el-tiempo-de-ejecucion-en-c-c-79591185633529*/

/**
 * Cambia left y right de los nodos para que estos representen un ABB balanceado
 */
int FillABBarray(Nodo** SortedArray, int inf, int sup){  
    if( inf>sup ){
        return -1; // cuando es hoja
    }
    int i = (sup-inf)/2 + inf; // posicion de la mediana
    SortedArray[i]->left=FillABBarray(SortedArray, inf, i-1); // la mediana izquierda es el hijo izquierdo, entra en recursividad
    SortedArray[i]->right=FillABBarray(SortedArray, i+1, sup); // la mediana derecha es el hijo derecho, entra en recursividad
    return i; 
} 

/**
 * retorna la posicion del valor buscando en el ABB, retorna -1 si no lo encuentra
 */
int ABBSearch(Nodo** ABB, int root, int objetive){
    while (ABB[root]->left != -1 || ABB[root]-> right != -1){ // mientras no sea una hoja
        if (ABB[root]->left != -1 && objetive < ABB[root]->data){ // es menor, se busca por la izquierda
            root = ABB[root]->left;
        }
        if (ABB[root]->right != -1 && objetive > ABB[root]->data){ // es mayor, se busca por la derecha
            root = ABB[root]->right;
        }
        if ((ABB[root]->right == -1 && objetive > ABB[root]->data) || (ABB[root]->left == -1 && objetive < ABB[root]->data)){ // no existe el valor
            return -1;
        }
        if (ABB[root]->data == objetive){ // se encuentra
            return root;
        }
    }
    return -1; // no se encuentra
}

/**
 * Realiza la busqueda de los mismos 100 datos pero en el arbol binario
 */
void PoweredABBSearch(Nodo** ABB, int* indx, int root){
    struct timeval begin, end; // estructuras de tiempo para obtener medicion
    gettimeofday(&begin, 0); // tiempo inicial
    for (int i=0; i<1000; i++){ // iteracion i-esima
        for (int j=0; j<100; j++){ // valor j-esimo, busca 100 datos aleatorios que existen
            ABBSearch(ABB, root, indx[j]);
        }
    }
    printf("\n");
    gettimeofday(&end, 0); // tiempo final
    long seconds = end.tv_sec - begin.tv_sec; // diferencia de segundos
    long microseconds = end.tv_usec - begin.tv_usec; // diferencia de microsegundos
    double elapsed = seconds + microseconds*1e-6; // diferencia de tiempo
    printf("This time take: %.6f miliseconds to find 100 randoms values in ABBarray.\n", elapsed);
    // es en milisegundos ya que al buscar 1000 veces cada valor, hay que dividir el tiempo en segundos por 1000.
}

// misma cita utilizada para Poweredbinarysearch



