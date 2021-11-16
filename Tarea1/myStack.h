#ifndef _MYSTACK_
#define _MYSTACK_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NLED 30
/**
 * Estructura que contiene 2 nodos, los nombres, el apellido y la nota. 
 */
typedef struct Nodo { 
    char Nombre[NLED];
    char Apellido[NLED];
    int Nota;
    struct Nodo* LeftNode;
    struct Nodo* RightNode;
} Info_Alumno;

int isfull(Info_Alumno* p);
int isempty(Info_Alumno* p);
Info_Alumno* getNewStack(Info_Alumno* p);
Info_Alumno* stackDelete(Info_Alumno* p);
Info_Alumno* Agregar_Stack(Info_Alumno* p, char* Dato_Nombre, char* Dato_Apellido, int Dato_Nota);
Info_Alumno* pop(Info_Alumno* p);
void peek(Info_Alumno* p);

#endif