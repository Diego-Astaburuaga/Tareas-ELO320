/************************************************************************
*Headers
************************************************************************/
#include <string.h> //strtok, strcpy, etc
#include <stdio.h> 
#include <stdlib.h> // FILE
#include <time.h> //srand(time(NULL))

#include "myStack.h"
#include "myABB.h"
#include "Tarea1.h" //Prototipos de funciones

/************************************************************************
*Varibles globales
************************************************************************/

int i, Nota_int;
char Linea_Extraida[2*NLED], Nombre_Aux[NLED], Apellido_Aux[NLED], Nota_Aux[4],*Elemento;
const char Separador[2] = ",";
Info_Alumno *Top=NULL, *Raiz=NULL;
FILE* Archivo_Notas;
char Tabla_Encriptacion[2][27];

/************************************************************************
*main del programa
************************************************************************/

int main (int argc, char* argv[]) {
    //Sentencia para que el archivo ingresado sea el correcto
    if (!String_Iguales(argv[1],"notas-EDA-C1.txt")){printf("\n    ||Nombre de archivo no valido para este programa, fin del programa||\n\n"); return 1;}
    Archivo_Notas = AbrirArchivo(argv[1]); if(Archivo_Notas==NULL){return 1;}
    initEncryptionTable(Tabla_Encriptacion);
    printf("||Nombre_Encriptado, Apellido_Encriptado,Nota||\n\n");
    // Lectura del archivo y compilado en el stack
    while(feof(Archivo_Notas)==0){
        Leer_linea(Archivo_Notas,Linea_Extraida);
        //En cada linea, separa por comas para extraer la informacion y guardarla en auxiliares.
        //Parte de codigo referente a "strtok" obtenido de: www.tutorialspoint.com
        Elemento = strtok(Linea_Extraida, Separador);
        i=0;
        while(Elemento!=NULL){
            //Se guarda la informacion en variables auxiliares, luego se encriptan para agregarlas al stack.
            //Caso de que sea el nombre
            if (i==0){
                strcpy(Nombre_Aux, Elemento);
                encrypt(Nombre_Aux, Tabla_Encriptacion);
                }
            //Caso de que sea el apellido
            else if (i==1){
                strcpy(Apellido_Aux, Elemento);
                encrypt(Apellido_Aux, Tabla_Encriptacion);
                }
            //Caso de que sea la nota
            else if (i==2){
                strcpy(Nota_Aux, Elemento);
                Nota_int=Convertir_a_Entero(Nota_Aux);

            }
            Elemento = strtok(NULL, Separador); 
            i++;
        }
        Top=Agregar_Stack(Top,Nombre_Aux, Apellido_Aux, Nota_int);
        peek(Top);   
    }

    Leer_Stack(Top, Tabla_Encriptacion);
    Raiz=Llenar_ABB(Raiz, Top, Tabla_Encriptacion);
    Leer_ABB(Raiz, Tabla_Encriptacion);
    Top=stackDelete(Top);
    Raiz=abbDelete(Raiz);
    CerrarArchivo(Archivo_Notas);

    printf("\n    ||Fin de las operaciones.||\n\n");
    return(0);
}
/************************************************************************
*Funciones Propias
************************************************************************/

/**
 * Abre el archivo en modo lectura y retorna un puntero relacionado al archivo
 */
FILE* AbrirArchivo(char* Nombre_Archivo){
    FILE* punteroArchivo=fopen(Nombre_Archivo, "r");
    //Error al abrir el archivo
    if (punteroArchivo==NULL){
        printf("Error al abrir el archivo.\n");
        return NULL;
    }
    printf("\n    ||Inicio de las operaciones, documento abierto correctamente.||\n\n");
    return punteroArchivo;
}

/**
 * Guarda la linea leida en un string sin el salto de linea
 */
void Leer_linea(FILE* Nombre_Archivo, char Linea_leida[60]){
    char Aux='\0';
    int j=1;
    j=1;
    //Mientras quede codigo por leer
    while(Aux!='\n' && feof(Nombre_Archivo)==0){
        //Extrae la linea correspondiente (para cuando llega al salto de linea)
        Aux=fgetc(Nombre_Archivo);
        if (Aux!='\n'&& feof(Nombre_Archivo)==0){
            Linea_leida[j-1]=Aux;
            Linea_leida[j]='\0';
        }
        j++;
    }
}

/**
 * Cierra el archivo y comprueba que se cierra bien
 */
void CerrarArchivo(FILE* Nombre_Archivo){
    int Archivo_Cerrado=fclose(Nombre_Archivo);
    int i=0;
    //Si la funcion retorna error, se vuelve intentar hasta 3 veces.
    while (Archivo_Cerrado==EOF){
        fclose(Nombre_Archivo);
        i++;
        printf("    \n||Error en cerrar archivo numero: %d||\n\n",i);
        if (i==3){
            printf("    \n||Error al cerrar el archivo. Fin del programa.||\n\n");
            break;
        }
    }
    printf("\n    ||Documento cerrado correctamente.||\n\n");
}

/**
 *Compara las dos filas de strings columna a columna, si 2 columnas tienen el mismo elemento, retorna 1
 */
int comparar(char table[2][27]){
    for (int j=0; j<26; j++){
        if (table[0][j]==table[1][j]){
            return 1;
            }
    }
    return 0;
}

/**
 * Se inicializa la tabla de encriptacion
 */
void initEncryptionTable(char table[2][27]){
    strcpy(table[0],"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    strcpy(table[1],table[0]);
    srand(time(NULL));
    int random;
    char aux;
    do{
        for (int i=0; i<26; i++){
            random=rand()%(25);
            aux=table[1][i];
            table[1][i]=table[1][random];
            table[1][random]=aux;
        }
    //Recombina las letras hasta que se cumpla la condicion de que en una columna no se repiten las letras
    } while (comparar(table)!=0);
}

/**
 *Encripta el string ingresado (Deja los caracteres que no son letras igual)
 */
void encrypt(char* str, char table[2][27]){
    int i=0;
    while (str[i]!='\0'){
        //Caso de que sea mayuscula
        if (str[i]>=65 && str[i]<=90){
            //str[i]-65 es la posicion que corresponde al caracter ingresado
            str[i]=table[1][str[i]-65];
            i++;
        }
        //Caso de que sea minuscula
        else if (str[i]>=97 && str[i]<=122){
            str[i]-=32;
            str[i]=table[1][str[i]-65];
            str[i]+=32;
            i++;
        }
        else{
            i++;
        }
    }
}

/**
 *Desencripta el string ingresado (Deja los caracteres que no son letras igual)
 */
void decrypt(char* str, char table[2][27]){
    int i=0;
    int j;
    while (str[i]!='\0'){
        //Caso de que sea mayuscula
        j=0;
        if (str[i]>=65 && str[i]<=90){
            //Busca la posicion del caracter a desencriptar en la segunda tabla
            while (table[1][j]!=str[i]){
                j++;
            }
            str[i]=table[0][j];
            i++;
        }
        //Caso de que sea minuscula
        else if (str[i]>=97 && str[i]<=122){
            str[i]-=32;
            while (table[1][j]!=str[i]){
                j++;
            }
            str[i]=table[0][j];
            str[i]+=32;
            i++;
        }
        else{
            i++;
        }
    }
}

/**
 *Toma un numero escrito como string de 1 a 3 cifras y devuelve su entero respectivo.
 */
int Convertir_a_Entero(char Nota_Char[4]){
    int entero;
    int i=0;
    //Funcion similar a "strlen" e inclusive diria que igual
    while (Nota_Char[i]!='\0'){
        i++;
    }
    //Caso cuando es 1 cifra, al restarlo del '0' obtengo en el valor del numero expresado en ascii
    if (i==1){
        entero=Nota_Char[0]-'0';
    }
    //Dos cifras 10 veces la decena + la unidad
    else if (i==2){
        entero=(Nota_Char[0]-'0')*10+Nota_Char[1]-'0';
    }
    //Solo puede ser 100
    else if (i==3){
        entero=100;
    }
    return entero;
}

/**
 * Toma la informacion del stack y muestra en pantalla a aquellos que aprobaron y destacando la mejor nota
 */
void Leer_Stack(Info_Alumno* p, char table[2][27]){
    Info_Alumno* Auxiliar_Leer=p;
    int max=54;
    char Nombre_max[30], Apellido_max[30];
    printf("\n||Alumnos que aprueban la asignatura||\n\n");
    //Lee hasta que se acaba el stack inicial
    while (Auxiliar_Leer!=NULL){
        if (Auxiliar_Leer->Nota>=55){
            //Guarda los datos de la mejor nota
            if (Auxiliar_Leer->Nota>max){
                strcpy(Nombre_max,Auxiliar_Leer->Nombre);strcpy(Apellido_max,Auxiliar_Leer->Apellido);
                max=Auxiliar_Leer->Nota;
                }
            //Desencripta para mostrar en pantalla y encripta denuevo para volver a guardar la informacion
            decrypt(Auxiliar_Leer->Nombre, table); decrypt(Auxiliar_Leer->Apellido, table);
            printf("    -%s %s.\n",Auxiliar_Leer->Nombre,Auxiliar_Leer->Apellido);
            encrypt(Auxiliar_Leer->Nombre, table); encrypt(Auxiliar_Leer->Apellido, table);
        }
        //Guarda la informacion en otro stack y la libera del actual
        Auxiliar_Leer=Auxiliar_Leer->LeftNode;
    }
    //Mostrar al mejor
    decrypt(Nombre_max, table); decrypt(Apellido_max, table);
    printf("\n    Mencion honorrfica para %s %s que aprobo con la mejor nota: %d\n\n", Nombre_max, Apellido_max, max);
}

/**
 * Toma la informacion del Stack y la copia en el ABB
 */
Info_Alumno* Llenar_ABB(Info_Alumno* Puntero_ABB,Info_Alumno* Puntero_Stack, char table[2][27]){
    //Inicializa el ABB
    Puntero_ABB=New_ABB(Puntero_Stack);
    Puntero_Stack=Puntero_Stack->LeftNode;  
    //Hasta que nuestro puntero auxiliar "Puntero_Stack" termine de recorrer el stack
    while (Puntero_Stack!=NULL){
        InsertStudent(Puntero_ABB,Puntero_Stack, table);
        Puntero_Stack=Puntero_Stack->LeftNode; 
    }
    printf("\n    ||Arbol creado exitosamente.||\n\n");
    return Puntero_ABB;
}


