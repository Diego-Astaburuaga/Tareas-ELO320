************************************* README *************************************

*********Datos Personales*********

*Autor: Diego Astaburuaga
*Rol: 202010018-7

*********Resumen del codigo*********

El codigo empieza abriendo un archivo indicado desde consola y extrae la informacion guardandola encriptada en un stack a la vez
que la muestra en pantalla, luego muestra en pantalla los nombres de quienes aprueban destacando la mejor nota, una vez terminada 
esta tarea, copia la informacion del stack y la ordena en un arbol binario de busqueda siguiendo el orden alfabetico de los apellidos 
, luego vuelve a mostrar en pantalla a quienes aprueban pero esta vez recorriendo el arbol binario de busqueda inorder, termina
eliminando el stack y el ABB creados durante el codigo y cierra el archivo.

*********Compilacion*********

Para compilar yo hago uso el archivo Makefile encontrado en el aula para la correcta compilacion en Aragorn, de todas maneras viene adjunto 
como documento  pdf al final de este documento. Al momento de crear los .c y .h que se ven en el pdf, procure mantener los nombres 
como vienen en la parte posterior de la hoja del pdf,  ej: "Tarea1.c" y luego el nombre del archivo a ingresar debe ser 
"notas-EDA-C1.txt" el cual viene incluido en el Makefile de todas maneras, cualquier otro nombre el programa lo considerara como no 
valido regresando un warning. Luego lo demas es solo mantener todos los archivos .c y .h respectivos en una sola carpeta junto al 
Makefile y ejecutar <make> seguido de <make run> para la compilacion.

(Recuerde incluir en la carpeta el archivo txt de nombre "notas-EDA-C1.txt" tambien)
*********Comentarios importantes*********

*La funcion "Leer_Stack" esta en el main porque en su inicio necesitaba de las funciones definidas alli, lo cual
sucedio antes de tener el header "Tarea1.h".

*Aproposito de "Tarea1.h" este fue agregado por obligatoreidad, ya que las funciones en "myABB.C" requerian de 
funciones presentes en el main, asi de esta manera podia invocarlas (desencrypt, encrypt, etc).

*Existe mas de una nota maxima, pero velando por la simplicidad (y con debida autorizacion y comentario de ayudante y profesor)
se opta por solo poner un alumno.

*El modo de ordenar en el ABB corresponde a izquierda<derecha, usando como parametro de comparacion el apellido asociado al nodo, esto
es: "Astaburuaga"<"Martinez" dado que la A va antes de la M.

*En my ABB.h se ve comentada la estructura, ya que esta viene definida desde el header myStack.h.

*********Otros comentarios*********

*Todo el codigo es de autoria propia usando tecnicas de programacion aprendidas en el curso ELO320 y experiencia en el curso IWI131
con python. De esta manera, reconozco que hay algoritmos similares empleados en clases pero que no fueron copiados en ningun momento
texual, ni el pseudocodigo.

*Existen MUCHAS funciones que desarrolle que desconozco si ya existian de antes dado a que recien estoy aprendiendo C con este curso.

*En pantalla tambien se muestra el orden en que van ocurriendo los procesos para que sea intuitivo de seguir.