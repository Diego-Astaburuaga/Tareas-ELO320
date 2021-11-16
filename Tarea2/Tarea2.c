/************************************************************************
*Headers
************************************************************************/
#include <stdio.h> 
#include <time.h> 
#include <stdlib.h>
#include <time.h>  /* clock_t, clock, CLOCKS_PER_SEC */
#include "mySortAlg.h"
#include "mySearchAlg.h"


#define NLED 1000

/************************************************************************
*Varibles globales
************************************************************************/

Nodo* myArray[NLED]; // arreglo de punteros inicial 
int aLim,bLim,cLim,dLim; // delimitadores para los arreglos de la parte B
int randindx[100]; // arreglo de indices aleatorios para realizar las busquedas


/************************************************************************
*Prototipos de funciones del main
************************************************************************/

void InsertData(Nodo** array, int value, int pos); //ingresa un valor dado a myArray
int Powerrand(); //crea un numero aleatorio de uno a un millon
void Fill(Nodo** array); // rellena myArray de forma automatica y con numeros aleatorios
void PowerFree(Nodo** array); // libera la memoria dinamica asociada al arreglo
void PrintVectorValue(Nodo** array, int inf, int sup); // segun valor, muestra los datos en la pantalla. Not neccesary but useful
void PrintVectorPosition(Nodo** array, int inf, int sup); // segun posicion, muestra los datos en la pantalla. Not neccesary but useful
void InputArray(int* a,int* b,int* c,int* d); // ingresa y verifica los  limites de los arrays
void VerifyInputArray(int* a,int* b,int* c,int* d); // verifica si los arrays se solapan y/o, entre los dos array hay menos de 100 elementos en suma
void CheckOrder(Nodo** array, int inf, int sup); // verifica que los datos esten ordenados de menor a mayor
void CheckOrder2(Nodo** array, int inf, int sup); // verifica que los datos esten ordenados de mayor a menor
void GenerateRandIndx(Nodo** array, int search[100], int sup); // rellena el arreglo de busqueda con valores existentes en el arreglo original
void CopyInfo(Nodo** new, Nodo** old, int sup); // copia la info de un array en otro
void inorder(Nodo** ABB, Nodo* root);// Not neccesary but useful

/*************************************************************************
 * main del programa
*************************************************************************/

int main(void){

    /* PARTE A DE LA TAREA */
    Fill(myArray);
    printf("\n || PARTE 'A' TERMINADA ||\n"); //flag

    /* PARTE B DE LA TAREA */
    // input para formas los sub-arreglos
    InputArray(&aLim,&bLim,&cLim,&dLim);
    VerifyInputArray(&aLim,&bLim,&cLim,&dLim);

    /* VISUALIZAR DATOS 
    printf("\n|||Primer Array inicial|||\n\n");
    PrintVectorPosition(myArray, aLim, bLim);
    printf("\n|||Segundo Array inicial|||\n\n");
    PrintVectorPosition(myArray, cLim ,dLim);
    */

    // se ordenan los arreglos
    heapSort(myArray, aLim, bLim, 1); // heapSort formando un minheap sobre el primero, decreciente
    heapSort(myArray, cLim, dLim, 0); // heapSort formando un maxheap sobre el segundo, creciente

    /* VISUALIZAR DATOS 
    printf("\n||Primer Array ordenado de mayor a menor||\n\n");
    PrintVectorPosition(myArray, aLim, bLim);
    CheckOrder2(myArray, aLim, bLim);
    printf("\n||Segundo Array ordenado de menor a mayor||\n\n");
    PrintVectorPosition(myArray, cLim ,dLim);
    CheckOrder(myArray, cLim, dLim);
    */

    // se crea el nuevo arreglo
    Nodo* mergedArray[bLim-aLim+1+dLim-cLim+1]; // arreglos unidos y ordenados
    mergeArrays(mergedArray, myArray, aLim, bLim, cLim, dLim);

    /* VISUALIZAR DATOS 
    printf("\n|||mergedArray ordenado de menor a mayor|||\n\n");
    PrintVectorPosition(mergedArray, 0 ,bLim-aLim+1+dLim-cLim);
    CheckOrder(mergedArray, 0, bLim-aLim+1+dLim-cLim);
    */

    printf("\n || PARTE 'B' TERMINADA ||\n"); //flag

    /* PARTE C DE LA TAREA */
    GenerateRandIndx(mergedArray, randindx, bLim-aLim+1+dLim-cLim); // el arreglo randindx ahora contiene elementos aleatorios para buscar que existen en mergedarray
    PoweredbinarySearch(mergedArray, bLim-aLim+1+dLim-cLim, randindx); // entrega el tiempo promedio en buscar 100 datos en el arreglo usando binarySearch
    printf("\n || PARTE 'C' TERMINADA ||\n");  //flag

    /* PARTE D DE LA TAREA */
    Nodo* ABBarray[bLim-aLim+1+dLim-cLim+1];
    CopyInfo(ABBarray, mergedArray, bLim-aLim+1+dLim-cLim);
    FillABBarray(ABBarray, 0, bLim-aLim+1+dLim-cLim); // modifica los nodos para generar un ABB balanceado
    PoweredABBSearch(ABBarray, randindx, (bLim-aLim+1+dLim-cLim)/2); // realiza la busqueda de 100 datos
    printf("\n || PARTE 'D' TERMINADA ||\n");  //flag

    /* VISUALIZAR DATOS
    inorder(ABBarray, ABBarray[(bLim-aLim+1+dLim-cLim)/2]);
    */

    PowerFree(myArray); // libera la memoria dinamica
    return 0;
}


/************************************************************************
*Funciones del main
************************************************************************/

/**
 * Ingresa un valor dado a myArray
 */
void InsertData(Nodo** array, int value, int pos){
    // rellena los datos
    array[pos]->data=value;
    array[pos]->left=-1;
    array[pos]->right=-1;
}

/**
 * Crea un numero aleatorio de uno a un millon
 */
int Powerrand(){
    int a=25000;
    int b=rand()%a + a*(rand()%40); // utiliza dos veces rand para generar numeros de hasta un millon
    return b;
}

/* Dado que rand tiene un limite cercano a 32.000, se divide el millon en 40 partes, luego 
el numero obtenido de 0 a 25.000 escogido de forma equiprobable, esto es, se "mapea" en alguna posicion de los 40 espacios*/

/**
 * Rellena myArray de forma automatica y con numeros aleatorios
 */
void Fill(Nodo** array){
    srand (time(NULL)); // generar numeros aleatorios diferentes
    for (int i=0;i<NLED;i++){
        Nodo* Aux=(Nodo *)malloc(sizeof(Nodo)); // crea el nodo en memoria dinamica
        array[i]=Aux; // asocia un puntero del array al nuevo nodo creado
        InsertData(array,Powerrand(),i); // rellena los datos
    }
}

/**
 * Libera la memoria dinamica asociada al arreglo
 */
void PowerFree(Nodo** array){
    for (int i=0; i<NLED; i++){
        free(array[i]);
    }
}

LiberarMemoria(Nodo** array, int inf, int sup){
    for(int i=inf; i<=sup; i++){
        free(array[i]);
    }
}

/**
 * Segun valor, muestra los datos en la pantalla. Not neccesary but useful
 */
void PrintVectorValue(Nodo** array, int inf, int sup){
    for (int i=0; i<NLED; i++){
        if (array[i]->data>=inf && array[i]->data<=sup){
            printf("i=%d: ",i);
            printf("|%d|. ",array[i]->data);
        }
    }
}

/**
 * Segun posicion, inf=<pos=<sup, muestra los datos en la pantalla. Not neccesary but useful
 */
void PrintVectorPosition(Nodo** array, int inf, int sup){
    for (int i=inf; i<=sup; i++){
        printf("i=%d: ",i);
        printf("|%d|. ",array[i]->data);
        if ((i-inf+1)%8==0){
            printf("\n");
        }
    }
}

/**
 * Verifica que esten los datos ordenados de menor a mayor. Not neccesary but useful
 */
void CheckOrder(Nodo** array, int inf, int sup){
    int j=0;
    for (int i=inf; i<sup; i++){
        if (array[i]->data>array[i+1]->data){
            j++;
            printf("En i=%d, son %d errores\n",i,j);
        }
    }
    printf("\n\n");
}
void CheckOrder2(Nodo** array, int inf, int sup){
    int j=0;
    for (int i=inf; i<sup; i++){
        if (array[i]->data<array[i+1]->data){
            j++;
            printf("En i=%d, son %d errores\n",i,j);
        }
    }
    printf("\n\n");
}

/**
 * Ingresar y verificar los  limites de los arrays 
 */
void InputArray(int* a,int* b,int* c,int* d){
    //verifica si el primer array es valido
    do{
        //verifica el primer limite inferior
        do{
            printf("\nEl arreglo es de largo %d (indices validos desde 0 a %d)",NLED,NLED-1);
            printf("Seleccione los limites del primer arreglo:\n    Ingrese el limite inferior: ");
            scanf("%d", a);
            }while(*a >=NLED || *a<0);
        //verifica el primer limite superior
        do{
            printf("    Ingrese el limite superior: ");
            scanf("%d", b);
            }while(*b >=NLED || *b<0);
    }while(*a>*b);
    //verifica si el segundo array es valido
    do{
        //verifica el segundo limite inferior
        do{
            printf("\nSeleccione los limites del segundo arreglo:\n");
            printf("    Ingrese el limite inferior: ");
            scanf("%d", c);
            }while(*c >=NLED || *c<0);
        //verifica el segundo limite superior
        do{
            printf("    Ingrese el limite superior: ");
            scanf("%d", d);
            }while(*d >=NLED || *d<0);
    }while(*c>*d);
    
    
}

/**
 * Verifica si los arrays se solapan y/o, entre los dos array hay menos de 100 elementos en suma
 */
void VerifyInputArray(int* a,int* b,int* c,int* d){
    // si los arrays se solapan y/o, entre dos los array hay menos de 100 elementos
    while( ((*b)>=(*c) && (*c)>=(*a)) || ((*b)>=(*d) && (*d)>=(*a)) || ((*a)>=(*c) && (*d)>=(*a)) || ((*b)-(*a)+1 + (*d)-(*c)+1 <100)){
        // si se solapan
        if (((*b)>=(*c) && (*c)>=(*a)) || ((*b)>=(*d) && (*d)>=(*a)) || ((*a)>=(*c) && (*d)>=(*a))){
        printf("\n||ERROR: los arrays no se deben interesectan, intente denuevo||\n");
        }
        // si no hay suficientes elementos para despues
        if ((*b)-(*a)+1 + (*d)-(*c)+1 <100){
            printf("\n||ERROR: La suma de la cantidad de elementos de cada array debe ser mayor o igual a 100, intente denuevo||\n");
        }
        // volver a rellenar los datos del input
        InputArray(a,b,c,d);
    }
}

/**
 * Rellena el arreglo de busqueda con valores existentes en el arreglo original
 */
void GenerateRandIndx(Nodo** array, int search[100], int sup){
    srand(time(NULL));
    for (int i=0; i<100; i++){
        search[i]=array[rand()%(sup+1)]->data; // copia valores en el arreglo original
    }
}

/**
 * Copia la informacion de un array en otro
 */
void CopyInfo(Nodo** new, Nodo** old, int sup){
    for (int k = 0; k<=sup; k++){
        new[k]=old[k];
    }
}

/**
 * para visualizar el ABB
 */
void inorder(Nodo** array, Nodo* root){
    if (root->left != -1){
        inorder(array, array[root->left]);
    }
    printf("%d\n", root->data);
    if (root->right != -1){
        inorder(array, array[root->right]);
    }
}