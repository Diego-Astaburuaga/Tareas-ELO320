# Comienzo del archivo makefile 
# define flags/opciones para el compilador (CFLAGS)
# define el compilador a utilizar (CC)
# define una variable para un parametro o entrada. 
# Al ejecutar make, puede usar: make run FILE="Algo.csv"

CFLAGS = -c -std=gnu99
CC = gcc
FILE_in= notas-EDA-C1.txt

#
# Se limpia cualquier tipo de definicion previa que exista para los archivos
# de estenxion .c .h .o debido a que su defincion sera implementda en este
# makefile.
# make tiene una lista de objetivos predetermindos para distintas extensiones
# (como .c.o) 

.SUFFIXES: .c .h .o

#
# This is a target entry that uses the suffix rule syntax:
#	DSTS:
#		rule
# DSTS (Dependency Suffix     Target Suffix)
# 'TS' is the suffix of the target file, 'DS' is the suffix of the dependency 
#  file, and 'rule'  is the rule for building a target	
# '$*' is a built-in macro that gets the basename of the current target 
# Remember that there must be a < tab > before the command line ('rule') 
# - Ejemplo - 
# Srs1.o: Srs1.c Srs1.h
#	gcc -c Srs1.c

%.o: %.c 
	@echo "Creating objects"
	@${CC} ${CFLAGS} $< -o $@

#
# MAIN es una variable con el nombre del archivo que contiene la funcion main.
# Cuidado, no deje ningun espacio en blanco despues del nombre de archivo. 

MAIN = Tarea1

#
# CLASSES es una macro que consiste de N palabras (uno por cada archivo fuente
# que se va a utilizar).
# Cuando una sola linea es muy larga, utilice \<return> para dividir las lineas 
# que serán consideradas.
# Ej.: 
 CLASSES = $(MAIN).c \
			  myABB.c \
			myStack.c \

#
# the default make target entry
# Next line is a target dependency line
# This target entry uses Suffix Replacement within a macro: 
# $(macroname:string1=string2)
# In the words in the macro named 'macroname' replace 'string1' with 'string2'

default: $(CLASSES:.c=.o)
	@$(CC) -o $(MAIN).out *.o

#
# Las siguientes lineas contienen el armado final del programa. Esto empieza con
# la etiqueta (TestCode) indicando las fuentes en la primera linea y luego el
# comando a utilizar para armar el programa.
# Recordar que la segunda linea debe tener tab para que funcione.
#
# - Ejemplo -
# TestCode: Srs1.o Srs2.o Srs_etc.o
#	gcc Code.c -o TestCode Srs1.o Srs2.o Srs_etc.o
./$(MAIN).out:  $(CLASSES:.c=.o)
	@$(CC) -o $(MAIN).out *.o

# ACLARACION: en revisiones, se ha actualizado para que usted solo necesite
# escribir make para compilar el programa ejecutable.

#
# Estas lineas solo ejecutan el programa creado:
run: ./$(MAIN).out
	@echo "Running..."
	@./$(MAIN).out $(FILE_in)

#
# Esta seccion elimina todos los archivos innecesarios que se crean en 
# el directorio despues de finalizada la ejecucion del programa y
# "limpia" el directorio para evitar posibles errores a futuro.
# RM es una macro predefinida en make (RM = rm -f)
clean:
	@echo "Cleaning:"
	@$(RM) -v *.o *.out