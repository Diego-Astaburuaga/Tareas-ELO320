#ifndef _FunctionHeader_
#define _FunctionHeader_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myStack.h" //struct Nodo

#define NLED 30

FILE* AbrirArchivo (char* Nombre_Archivo);
void Leer_linea(FILE* Archivo_Notas, char Linea_leida[60]);
void CerrarArchivo(FILE* Nombre_Archivo);
void initEncryptionTable(char table[2][27]);
int comparar(char table[2][27]);
int Convertir_a_Entero(char Nota_Char[4]);
void encrypt(char* str, char table[2][27]);
void decrypt(char* str, char table[2][27]);
void Leer_Stack(Info_Alumno* p, char table[2][27]);
Info_Alumno* Llenar_ABB(Info_Alumno* Puntero_ABB,Info_Alumno* Puntero_Stack, char table[2][27]);
#endif 