/**
 * Modulo creado por Diego Astaburuaga, contiene las funciones necesarias para el manejo del stack
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myStack.h"

/**
 * Determina si no se puede alojar nueva memoria
 */
int isfull(Info_Alumno* p){
    //Revisa si se creo un nuevo puntero
    return (p==NULL);
}

/**
 * Determina si el stack esta vacio
 */
int isempty(Info_Alumno* p){
    //Revisa si el puntero apunta al nulo o a algun elemento
    return (p==NULL);
    }

/**
 * Asegura que el puntero este libre para un nuevo stack
 */
Info_Alumno* getNewStack(Info_Alumno* p){
    //Si el stack esta vacio mantiene el puntero al vacio
    if (p==NULL){
        return p;
    }
    //Si el puntero tiene asociado un stack, lo borra y reinicia el puntero
    else{
        stackDelete(p);
        printf("\n    ||Se ha eliminado un stack antiguo.||\n");
        return p;
    }
}

/**
 * Borra el stack completo
 */
Info_Alumno* stackDelete(Info_Alumno* p){
    //Si no hay stack
    if(isempty(p)){
        printf("\n    ||No hay Stack que eliminar.||\n");
        return p;
        }
    //si no esta vacio
    else{
        Info_Alumno* Aux;
        //Elimina nodo por nodo hasta que solo quede 1
        while (p->LeftNode!=NULL){
            Aux=p;
            p=p->LeftNode;
            p->RightNode=NULL;
            free(Aux);
        }
        //Elimina el ultimo elemento
        free(p);
        p=NULL;
        printf("\n    ||Stack eliminado exitosamente.||\n\n");
        return p;
    }
}

/**
 * Agrega un elemento a la parte posterior del stack, nombre clave: PUSH
 */
Info_Alumno* Agregar_Stack(Info_Alumno* p, char* Dato_Nombre, char* Dato_Apellido, int Dato_Nota){
    Info_Alumno* Aux=(Info_Alumno *)malloc(sizeof(Info_Alumno));
    if (isfull(Aux)){
        printf("\n    ||Unable to allocate required memory.||\n");
        return p;
    }
    //Rellena los datos.
    strcpy(Aux->Nombre,Dato_Nombre);
    strcpy(Aux->Apellido,Dato_Apellido);
    Aux->Nota=Dato_Nota;
    //Si esta vacio el stack
    if (isempty(p)){

        Aux->LeftNode=NULL;
        Aux->RightNode=NULL;
    }
    //Si ya existian elementos
    else{
        p->RightNode=Aux;
        Aux->LeftNode=p;
        Aux->RightNode=NULL;
    }
    p=Aux;
    return p;
}

/**
 * Elimina el ultimo elemento agregado del stack
 */
Info_Alumno* pop(Info_Alumno* p){
    //Si no hay stack
    if (p==NULL){
        printf("\n    ||Stack vacio||\n");
        return p;
    }
    //Si hay solo 1 elemento
    else if (p->LeftNode==NULL){
        free(p);
        p=NULL;
        return p;
    }
    //Si hay mas de un elemento
    else{
        Info_Alumno* Aux=p;
        p=Aux->LeftNode;
        p->RightNode=NULL;
        free(Aux);
        return p;
    }
}

/**
 * Muestra en pantalla los datos del nodo
 */
void peek(Info_Alumno* p){
    printf("    -%s, %s, %d.\n",p->Nombre,p->Apellido,p->Nota);
}

