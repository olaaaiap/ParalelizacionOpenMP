Para la correcta visualización de este readme, visitar  https://github.com/olaaaiap/ParalelizacionOpenMP?tab=readme-ov-file
  
# Ejercicios de paralelización en OpenMP

  

Este proyecto consiste en una serie de ejercicios de paralelización en OpenMP. Se han presentado diferentes ejercicios y se han utilizado técnicas de paralelización para mejorar los tiempos de ejecución. Por último, en este documento se ha hecho una interpretación de los datos para obtener la mejora que se ha dado entre las versiones paralelizadas y las secuenciales.

  
  

## Grupo 1

  
### Ejercicio 1: Dado un algoritmo, calcular su versión paralela.

La versión paralela de este ejercicio se llevó a cabo en clase. Como ya vimos, el tiempo de paralelización no mejoró respecto a la secuencial. Para un vector de 30 elementos, el tiempo secuencial era de 5,0012e-07 segundos, mientras que la versión paralela duraba 0,239287 segundos. En otras palabras, 0,0239282 segundos más que la secuencial. Lo mismo pasa para diferentes tamaños de vectores, en todos los casos la versión con hilos dura más que la secuencial.

Esto se debe a que no todo el bucle es paralelizable. Al haber dependencias entre valores del vector solo la parte sin dependencias se pueda paralelizar. Esto hace que la sincronización de hilos o el *overhead* tenga más carga que el algoritmo en sí. Por tanto, no merece paralelizar este código, ya que no se obtiene mejoría.

  
  
  
### Ejercicio 2: Calcular la media de los valores alojados en una matriz.

  
  Para analizar los tiempos en diferentes condiciones, se han considerado por un lado los tamaños de las matrices (20x20, 200x200, 1000x1000 y 10000x10000) y por otro lado el número de hilos utilizados en la paralelización. Para cada tamaño de matriz, se han probado tanto la versión secuencial como implementaciones con 2, 4, 8 y 16 hilos. Una vez obtenidos los valores, se ha calculado la proporción de mejora o el *speedup*, ya que la interpretación directa de los tiempos era compleja y difícil de plasmar en gráficos. 
#### Resultados:


![Tabla ejercicio 2](https://github.com/user-attachments/assets/993f8553-d7fa-467e-add7-8e083296d2d7)
![Gráfico ejercicio 2](https://github.com/user-attachments/assets/6c4a5081-35e1-4aae-8647-dd9f4a729e9b)

  Como se observa en el gráfico, para las matrices más pequeñas no se han obtenido mejoras significativas comparando con su versión secuencial. Sin embargo, con la matriz de 100.000.000 elementos se ha encontrado una notable mejora que ha ido incrementando hasta los 8 hilos. 
  Este comportamiento es habitual y está relacionado con el *overhead* relacionado a la creación y gestión de hilos en OpenMP. Cuando el coste de esta gestión supera la carga computacional del problema, el *speedup* tiende a estar por debajo o muy cerca a 1, indicando que no ha habido mejora relevante.
  En un escenario ideal, el *speedup* debería acercarse al número de hilos que se están utilizando. En este caso, se observa un desempeño cercano al óptimo para la matriz 10000x10000 con 8 hilos.
  
  
### Ejercicio 3: Obtener una aproximación numérica del valor de pi usando la regla del trapecio.

Para este problema (y para los siguientes) se ha mantenido la división de experimentos en secuencial y 2, 4, 8 y 16 hilos. La diferencia principal de este problema es que no se ha trabajado con matrices, si no con la cantidad de trapecios que se quieren utilizar.  Se han hecho pruebas con 10, 100, 1000 y 10000 trapecios.


![Tabla ejercicio 3](https://github.com/user-attachments/assets/fd0e2339-4886-4247-8dd0-d0f06e23c240)
![Gráfico ejercicio 3](https://github.com/user-attachments/assets/193385c6-c3fa-41de-8735-f59d9414972d)


A diferencia del ejercicio 2, el caso en el que se ha obtenido mejor rendimiento ha sido en 2 hilos y 10 trapecios. Esto se debe a que los cálculos que se llevan a cabo son poco costosos (sumas, restas, divisiones...), y al aumentar la cantidad de hilos, cada uno tiene menos carga computacional. En estos casos el coste de crear y gestionar los hilos se vuelve mayor que el de los cálculos de cada uno, por tanto, no hay mejora alguna en cuanto a los tiempos de ejecución.
En conclusión, para problemas pequeños como este, es contraproducente utilizar muchos hilos ya que puede aumentar el coste temporal.


### Ejercicio 6: Programar el Juego de la Vida.

En este ejercicio se han mantenido los experimentos del ejercicio 2. Aún así, para limitar el tiempo de ejecución del programa se han ejecutado 10 iteraciones del juego por cada prueba. 


![Tabla ejercicio 6](https://github.com/user-attachments/assets/a85b0250-c166-4095-95ed-8c9a240199ab)
![Gráfico ejercicio 6](https://github.com/user-attachments/assets/81c73007-c885-4727-9fcf-3bcf02b6ad07)

Como hemos podido ver en el ejercicio 2, en este también se observa una mejor mejora con la mayor matriz. Todas las demás pierden rendimiento al paralelizar con 8 hilos (en el caso de 1000x1000 y 200x200) o en 2 hilos (en el caso de 20x20). En este algoritmo también nos hemos acercado al caso ideal (*speedrun* = cantidad de hilos) en el caso de 8 hilos y la mayor matriz.
Como hemos analizado antes, esto ocurre porque el coste de crear y sincronizar los hilos es mayor que el beneficio que nos da la paralelización. En conclusión, en este caso solo merece paralelizar si trabajamos con matrices  grandes. 



### Ejercicio 8: Ejercicio personal: cálculos y búsquedas en matrices.

En el ejercicio de propuesta personal se ha intentado complicar el ejercicio 2. Aunque la idea principal era utilizar *sections*, mientras se fue desarrollando el problema se encontró que otras maneras de paralelización mejoraban aún más el rendimiento. 
En este último ejercicio, además de calcularse la media de los valores de la matriz, también se han buscado los valores máximos y mínimos, el valor que más veces se repite y la cantidad de valores mayores que 50. Por último se ha calculado la matriz traspuesta y se ha ordenado la matriz  en orden ascendente.


![Tabla ejercicio 8](https://github.com/user-attachments/assets/438f7a2e-ad21-49dc-a5fb-011c8e8b5fc9)
![Gráfico ejercicio 8](https://github.com/user-attachments/assets/f65c7a49-43fa-42cc-8450-d85019ff4b95)

El desempeño del algoritmo con las matrices más pequeñas ha disminuido notablemente.  Por otro lado, la matriz de 1000x1000 ha expuesto una pequeña mejora, aunque mínima. Por último, la mayor matriz, como hemos visto en otros ejercicios, ha obtenido una mejora en el rendimiento proporcional a la cantidad de hilos que se están utilizando.
Como hemos explicado antes, esto está directamente relacionado con la carga del algoritmo, y como esta supera la carga de la sincronización de hilos.

## Conclusión general
Aunque en algunos casos la paralelización de la oportunidad de mejorar el rendimiento notablemente, no siempre es eficaz. Cuando el coste de un problema secuencial no es elevado, la paralelización ha demostrado no tener buen desempeño. También, cuando el tamaño del problema es demasiado pequeño, la paralelización puede no mejorar (o incluso realentizar) su versión secuencial.
En conclusión, para saber si la paralelización vale la pena, hay que analizar detenidamente el problema y encontrar el equilibrio entre la carga de la gestión de los hilos y el beneficio que su uso nos puede traer.

## Autora

  Olaia Picabea