#ifndef _MYABB_
#define _MYABB_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myStack.h" //struct Nodo

#define NLED 30
/**
 * Estructura que contiene 2 nodos, los nombres, el apellido y la nota. 
 */

/*
typedef struct Nodo { 
    char Nombre[NLED];
    char Apellido[NLED];
    int Nota;
    struct Nodo* LeftNode;
    struct Nodo* RightNode;
} Info_Alumno;
*/

Info_Alumno* New_ABB(Info_Alumno* Puntero_Stack);
void InsertStudent(Info_Alumno* Puntero_ABB, Info_Alumno* Puntero_Stack, char table[2][27]);
void Copiar_Info(Info_Alumno* Nodo_Nuevo, Info_Alumno* Nodo_Antiguo);
Info_Alumno* Camino(Info_Alumno* Nodo_Padre, Info_Alumno* Nuevo_Nodo, char table[2][27]);
int Comparar_String(char* string1, char* string2);
void Leer_ABB(Info_Alumno* Nodo_Raiz, char Table[2][27]);
int Apellido_Condicion(Info_Alumno* Nodo_Raiz, char* Condicion, char Table[2][27]);
void Printear_Nodo(Info_Alumno* Nodo, char Table[2][27]);
Info_Alumno* abbDelete(Info_Alumno* Raiz);
void Llave(char llave[NLED], Info_Alumno *p, char Table[2][27]);
int String_Iguales(char* string1, char* string2);
#endif