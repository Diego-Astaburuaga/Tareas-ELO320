/**
 * Modulo creado por Diego Astaburuaga, contiene las funciones necesarias para el manejo del abb
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myABB.h"
#include "Tarea1.h"
/**
 * Inicializa un puntero creado y lo asocia a un nuevo nodo raiz
 */
Info_Alumno* New_ABB(Info_Alumno* Puntero_Stack){
    Info_Alumno* Nuevo_Nodo=(Info_Alumno *)malloc(sizeof(Info_Alumno));
    Copiar_Info(Nuevo_Nodo,Puntero_Stack);
    Nuevo_Nodo->LeftNode=NULL;
    Nuevo_Nodo->RightNode=NULL;
    return Nuevo_Nodo;
}

/**
 * Inserta un nuevo nodo al arbol (debe tener 1 elemento) siguiendo la regla "izquierda<derecha" tomando el ultimo elemento en el stack
 */
void InsertStudent(Info_Alumno* Puntero_ABB, Info_Alumno* Puntero_Stack, char table[2][27]){
    Info_Alumno* Aux=NULL;
    //Crea el nuevo nodo
    Info_Alumno* Nuevo_Nodo=(Info_Alumno *)malloc(sizeof(Info_Alumno));
    Copiar_Info(Nuevo_Nodo,Puntero_Stack);
    Nuevo_Nodo->RightNode=NULL; Nuevo_Nodo->LeftNode=NULL;
    Aux=Puntero_ABB;
    //Busca en donde alojar el nuevo nodo
    while (Camino(Aux, Nuevo_Nodo, table)!=NULL){
        Aux=Camino(Aux,Nuevo_Nodo, table);
    }
    //Desencripta para elegir donde va por ultima vez y luego vuelve a encriptar
    decrypt(Nuevo_Nodo->Apellido, table); decrypt(Aux->Apellido, table);
    if (Comparar_String(Nuevo_Nodo->Apellido,Aux->Apellido)){
        Aux->LeftNode=Nuevo_Nodo;
    }
    else{
        Aux->RightNode=Nuevo_Nodo; 
    }
    encrypt(Nuevo_Nodo->Apellido, table); encrypt(Aux->Apellido, table);
}

/**
 * Toma la informacion de un nodo y la copia en otro nuevo
 */
void Copiar_Info(Info_Alumno* Nodo_Nuevo, Info_Alumno* Nodo_Antiguo){
    strcpy(Nodo_Nuevo->Nombre,Nodo_Antiguo->Nombre);
    strcpy(Nodo_Nuevo->Apellido,Nodo_Antiguo->Apellido);
    Nodo_Nuevo->Nota=Nodo_Antiguo->Nota;
}

/**
 * Decide si el nuevo nodo va a la izquierda o a la derecha segun el apellido, retorna el puntero correspondiente
 */
Info_Alumno* Camino(Info_Alumno* Nodo_Padre, Info_Alumno* Nuevo_Nodo, char table[2][27]){
    //Desencripta para poder comparar la informacion y luego vuelve a encriptar
    decrypt(Nodo_Padre->Apellido, table);
    decrypt(Nuevo_Nodo->Apellido, table);
    if (Comparar_String(Nuevo_Nodo->Apellido,Nodo_Padre->Apellido)){
        encrypt(Nuevo_Nodo->Apellido, table);
        encrypt(Nodo_Padre->Apellido, table);
        return Nodo_Padre->LeftNode;
    }
    else{
        encrypt(Nuevo_Nodo->Apellido, table);
        encrypt(Nodo_Padre->Apellido, table);
        return Nodo_Padre->RightNode;
    }
}

/**
 *Retorna "TRUE" si string1 va antes alfabeticamente ("menor") del string2 y retorna "FALSE" si se repite o si va despues
 */
int Comparar_String(char* string1, char* string2){
    return (strcmp(string1,string2)<0);
}

/**
 * Retorna "TRUE" si string1 es identico a string2 y "FALSE" en caso contrario
 */
int String_Iguales(char* string1, char* string2){
    int Limite;
    //Establece como limite de iteraciones el string mas largo
    if(strlen(string1)>strlen(string2)){Limite=strlen(string1);}
    else {Limite=strlen(string2);}
    for (int i=0; i<Limite; i++){
        if (string1[i]!=string2[i]){
            //Retorna FALSE
            return (1==2);
        }
    }
    //Retorna TRUE
    return (1==1);
}
/**
 * Recorre el ABB de "izquierda a derecha" desencriptando la informacion (Inorder)
 */
void Leer_ABB(Info_Alumno* Nodo_Raiz, char Table[2][27]){
    Info_Alumno* Temp=Nodo_Raiz;
    char Condicion[NLED]="AAAAAAAAAA"; //String menor a cualquier nombre (simil a usar max=0)
    char Limite[NLED];
    printf("\n||Alumnos que aprueba ordenados alfabeticamente desde el ABB||\n\n");
    //Busca el ultimo nodo que debe printear
    while (Temp->RightNode!=NULL){
        Temp=Temp->RightNode;
    }
    //Guarda la informacion de Limite
    decrypt(Temp->Apellido,Table);
    strcpy(Limite,Temp->Apellido);
    encrypt(Temp->Apellido,Table);
    //Limite corresponde a la condicion del ultimo nodo, cuando estas sean iguales, habremos terminado
    while (Comparar_String(Condicion,Limite)){
        Apellido_Condicion(Nodo_Raiz, Condicion, Table);
    }
}
//La condicion consiste en un string que debe ser "lo menor posible" para comparar e ir en orden alfabetico (Que concuerda con Inorder).

/**
 * Busca el nodo a leer en funcion de la condicion, lo printea y actualiza la condicion.
 */ 
int Apellido_Condicion(Info_Alumno* Nodo_Raiz, char* Condicion, char Table[2][27]){
    Info_Alumno *Temp_1, *Temp_2;
    Temp_1=Nodo_Raiz; //Son
    Temp_2=Nodo_Raiz; //Parent
    char Aux_Llave[NLED]; //Apellido desencriptado de un nodo
    int flag_i=0, flag_j; //Metodos para salir de una situacion sin salida, flag_i=0 es pq esta todo bien, flag_j "Simila recursividad"
    char Nueva_Condicion[NLED]="Easter_Egg"; //Un string cualquiera diferente a cualquier nombre
    //Funciona como un "while (true)" no infinito.
    while (!String_Iguales(Condicion,Nueva_Condicion)){
        //Si la condicion es menor
        flag_j=0;
        Llave(Aux_Llave,Temp_1,Table);
        if (Comparar_String(Condicion,Aux_Llave)){
            //Si no tiene hijo izquierdo
            if (Temp_1->LeftNode==NULL){
                Llave(Aux_Llave,Temp_1,Table);
                strcpy(Condicion,Aux_Llave);
                Printear_Nodo(Temp_1, Table);
                return 0;
            }
            //Si tiene hijo izquierdo
            else if (Temp_1->LeftNode!=NULL){
                Temp_2=Temp_1;
                Temp_1=Temp_1->LeftNode;
            }
        }
        //Si la condicion es mayor o igual
        Llave(Aux_Llave,Temp_1,Table);
        if (!Comparar_String(Condicion,Aux_Llave)){
            //Si existe un caso especial
            if (flag_i==1){
                //Se entra en un bucle infinito
                Temp_1=Temp_2;
                Llave(Aux_Llave,Temp_1,Table);
                strcpy(Condicion,Aux_Llave);
                Printear_Nodo(Temp_1,Table);
                return 0;
            }
            //Si el nodo NO es la condicion
            Llave(Aux_Llave,Temp_1,Table); 
            if (!String_Iguales(Aux_Llave,Condicion)){
                Temp_2=Temp_1;
                Temp_1=Temp_1->RightNode;
            }
            //Si el nodo ES la condicion
            else if(String_Iguales(Aux_Llave,Condicion)){
                //Si tiene hijo derecho
                if(Temp_1->RightNode!=NULL){
                    Temp_1=Temp_1->RightNode;
                    //Si no tiene hijo izquierdo
                    if(Temp_1->LeftNode==NULL){
                        Llave(Aux_Llave,Temp_1,Table);
                        strcpy(Condicion,Aux_Llave);
                        Printear_Nodo(Temp_1, Table);
                        return 0;
                    }
                    //Si tiene hijo izquierdo
                    else if (Temp_1->LeftNode!=NULL){
                        flag_j=1;
                        //Bandera arriba dado que se debe reiniciar el bucle desde el nuevo nodo actual
                    }
                }
                //Si no tiene hijo derecho
                else if(Temp_1->RightNode==NULL && flag_j==0){
                    //Si es un hijo derecho: Caso especial
                    if(Temp_1==Temp_2->RightNode){
                        Temp_1=Nodo_Raiz;
                        Temp_2=Nodo_Raiz;
                        flag_i=1;
                        //Bandera arriba para reiniciar el bucle dado un caso especial
                    }
                    //Si es un hijo izquierdo
                    else if(Temp_1==Temp_2->LeftNode){
                        Temp_1=Temp_2;
                        Llave(Aux_Llave,Temp_1,Table);
                        strcpy(Condicion,Aux_Llave);
                        Printear_Nodo(Temp_1, Table);
                        return 0;
                    }
                }
            }
        }
    }
}

/**
 * Si el estudiante aprueba (Nota>=55), lo escribe en pantalla "Apellido, Nombre"
 */
void Printear_Nodo(Info_Alumno* Nodo, char Table[2][27]){
    if (Nodo->Nota>=55){
        decrypt(Nodo->Nombre, Table); decrypt(Nodo->Apellido,Table);
        printf("    -.%s, %s\n",Nodo->Apellido, Nodo->Nombre);
        encrypt(Nodo->Nombre, Table); encrypt(Nodo->Apellido,Table);
    }
}
/**
 * Borra el arbol completo desde las hojas a la raiz
 */
Info_Alumno* abbDelete(Info_Alumno* Raiz){
    Info_Alumno *Temp_1, *Temp_2;
    Temp_1=Raiz; //Son
    Temp_2=Raiz; //Parent
    //Temp_1 solo sera NULL cuando no queden mas nodos que eliminar y se libere todo
    while (Temp_1!=NULL){
        //Si hay izquierda, voy a la izquierda
        if (Temp_1->LeftNode!=NULL){
            Temp_2=Temp_1;
            Temp_1=Temp_1->LeftNode;
        }
        //Si no hay izquierda, pero si derecha, voy a la derecha
        else if (Temp_1->LeftNode==NULL && Temp_1->RightNode!=NULL){
            Temp_2=Temp_1;
            Temp_1=Temp_1->RightNode;
        }
        //LLegamos a una hoja
        else if (Temp_1->LeftNode==NULL && Temp_1->RightNode==NULL){
            //Si el hijo esta a la izquierda
            if (Temp_2->LeftNode==Temp_1){
                Temp_2->LeftNode=NULL;
                Temp_2=Temp_1;
                Temp_1=Raiz;
                free(Temp_2);
                Temp_2=Raiz;
            }
            //Si el hijo esta a la derecha
            else if (Temp_2->RightNode==Temp_1){
                Temp_2->RightNode=NULL;
                Temp_2=Temp_1;
                Temp_1=Raiz;
                free(Temp_2);
                Temp_2=Raiz;
            }
            //Si el nodo corresponde a la raiz y no hay hijos:
            else if (Temp_1==Raiz){
                free(Raiz);
                Raiz=NULL;
                Temp_1=Raiz;
            }
        }
    }
    printf("\n    ||Arbol 'Quemado' exitosamente.||\n\n");
    return Raiz;
}
//El algoritmo anterior tiene un simil tremendo con recursividad pero a base de ciclos whiles

/**
 * Retorna el dato APELLIDO desencriptado del nodo incluido con fines de utilidad para recorrer el arbol
 */
void Llave(char llave[NLED], Info_Alumno *p, char Table[2][27]){
    decrypt(p->Apellido,Table);
    strcpy(llave,p->Apellido);
    encrypt(p->Apellido,Table);
}