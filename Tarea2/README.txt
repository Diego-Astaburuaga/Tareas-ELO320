*****************************************************
DATOS PERSONALES
*****************************************************
    Autor: Diego Astaburuaga
    Rol: 202010018-7

*****************************************************
RESULTADOS
*****************************************************

Las partes C y D se hacen respectivamente con la funcion PoweredbinarySearch() y PoweredABBSearch(), ambos algoritmos identicos
a excepcion del metodo de busqueda, donde se utiliza binarysearch() y ABBSearch() respectivamente, por tanto la diferencia en el
tiempo de ejecucion de cada algoritmo entregada corresponde a una representacion de la diferencia neta entre los algoritmos de 
busqueda.

Objetivo: Comparar ambos algoritmos de busqueda. 

El tiempo entregado en binarysearch corresponde al tiempo promedio de buscar 100 datos en un universo de 1000 elementos ya ordenado,
esto ejecutando el programa 10 veces en tiempos distintos. Luego se encuentran los mismos resultados pero para la busqueda en un ABB 
ya generado anteriormente. 

Siempre se utiliza el universo mas grande de datos (mergedArray y ABBarray de 1000 elementos) para uniformizar resultados y que solo
haya cambio en el tiempo de busqueda que dependa solo del computador, de esta forma se obtienen promedios representativos del tiempo de  ejecucion de
cada algoritmo en mi computadora personal y por ende una forma fiable de comparar tiempos de ejecucion de ambos algoritmos.

Tiempo de busqueda promedio de 100 elementos con binarysearch:
    - 0.004986 miliseconds
    - 0.005983 miliseconds
    - 0.004985 miliseconds
    - 0.003994 miliseconds
    - 0.004981 miliseconds
    - 0.003995 miliseconds
    - 0.003974 miliseconds
    - 0.004985 miliseconds
    - 0.004977 miliseconds
    - 0.004986 miliseconds
    Promedio de las 10 ejecuciones: 0.004785 milisegundos

Tiempo de busqueda promedio de 100 elementos en ABBarray:
    - 0.008007 miliseconds
    - 0.008985 miliseconds
    - 0.007007 miliseconds
    - 0.006021 miliseconds
    - 0.005983 miliseconds
    - 0.007979 miliseconds
    - 0.008016 miliseconds
    - 0.005981 miliseconds
    - 0.007977 miliseconds
    - 0.007751 miliseconds
    Promedio de las 10 ejecuciones: 0.007371 milisegundos

Notese que el tiempo promedio de binarysearch es claramente menor.

*****************************************************
CONCLUSIONES
*****************************************************

Si bien el promedio es un claro indicador de que binarysearch es mejor, esto no es suficiente ya que puede deberse a un caso especifico
, realizando un analisis rapido de complejidad computacional, poseen la misma cota asintotica (O(log n)) y por ende deben de pertenecer a 
la misma familia. Esto significa que la diferencia en tiempo (promedio) asociada al costo computacional esta relacionada con la 
diferencia en las constantes de las sentencias, que estan a razon de 1.5 aproximadamente, dicho de otra forma, son algoritmos distintos,
y por tanto los tiempos de ejecucion son distintos.

Dicho esto, en analisis asintotico ambos algoritmos son igual de eficientes, pero de forma mas especifica, binarysearch
(por como estan elaborados ambos algoritmos) es una mejor opcion porque tiene menos sentencias y (probablemente) estas tienen menor 
coste computacional (en promedio), propiciando un tiempo promedio menor al tiempo de busqueda en ABB, lo cual al probarse en Aragorn, 
el comportamiento es el mismo, donde binarysearch demora menos que la busqueda en ABB para los algoritmos presentados.

*****************************************************
RESUMEN DEL CODIGO
*****************************************************

El programa empieza generando en memoria dinamica los nodos y luego asignandolos al array en base a los punteros que este tiene.
Luego solicita al usuario ingresar los limites de los subarrays verificando que cumplan con las condiciones necesarias.
Entonces realiza el heapsort correspondiente a cada uno para luego unirlos.
Elije de forma al azar 100 datos existentes para ser los objetivos de busqueda en las partes C y D.
Realiza la busqueda de los 100 datos con binarysearch 1000 veces en total, por lo que el valor entregado es en milisegundos.
Se cambia la tipologia a ABB y se realiza la busqueda de los 100 datos en ABB 1000 veces en total, igual que en el punto anterior.
Se libera la memoria dinamica finalizando el programa.


*****************************************************
COMPILACION
*****************************************************

En mi computadora compilo con la sentencia gcc mySortAlg.c mySearchAlg.c Tarea2.c -o Tarea2, luego en Aragorn utilizo el makefile
facilitado por el ayudante para la tarea anterior, modificado para los archivos actuales. Se adjunta copia de esto ultimo.

*****************************************************
COMENTARIOS
*****************************************************
    -. La tipologia ABB de ABBarray esta dada por los valores asignados a left y right pero no por sus posiciones relativas.
    (lo anterior es por diseño, el algoritmo usado para generar un ABB balanceado, es incombatible con las definiciones de 
    left y right dadas por left = 2k+1 y right = 2k+2, por lo que solo actualizo left y right en cada nodo, mas no cambio sus posiciones)
    -. El programa cuenta con funciones y partes de codigo (comentadas) con la finalidad de ser utiles para visualizar los datos.
    -. Los arrays comparten los elementos, ya que la diferencia entre cada array creado es el orden en el cual se encuentran los punteros.
    -. Los 1000 datos que se crean (struct) viven en memoria dinamica y solo nos manejamos con los punteros.
    -. De esta manera, se generan "dinamicamente" aprovechando el uso de memoria dinamica. 
    -. La memoria dinamica se libera en una sola sentencia: PowerFree(myArray);.
    -. En mergedArray los valores de left y right pierden significado hasta volver a ser usados en la parte D.
