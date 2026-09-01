Máximo Subarreglo — Comparación de Algoritmos

Descripción

Este proyecto implementa y compara tres algoritmos para encontrar la suma máxima de un subarreglo contiguo:

Algoritmo cúbico: O(n³)

Algoritmo cuadrático: O(n²)

Algoritmo de Kadane: O(n)

El objetivo es comprobar experimentalmente cómo crece el tiempo de ejecución de cada algoritmo al aumentar el tamaño del arreglo y relacionar los resultados observados con su complejidad teórica.

Requisitos

Windows

Compilador C++ compatible con C++17

g++ (por ejemplo, el incluido en MSYS2)

VS Code es opcional

El programa utiliza solamente estas librerías estándar:

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

Compilación en Windows

Desde PowerShell, ubicándose en la carpeta donde está max_subarray.cpp:

g++ -std=c++17 -O2 -Wall -Wextra max_subarray.cpp -o max_subarray.exe

Si g++ no está agregado al PATH y está instalado en MSYS2 UCRT64:

C:\msys64\ucrt64\bin\g++.exe -std=c++17 -O2 -Wall -Wextra max_subarray.cpp -o max_subarray.exe

Ejecución

.\max_subarray.exe

El programa realiza las siguientes etapas:

Ejecuta 100 pruebas de corrección con arreglos aleatorios.

Genera arreglos de tamaño 1000, 2000, 4000 y 8000.

Mide primero Kadane para todos los tamaños y muestra su tabla.

Mide después el algoritmo cuadrático para todos los tamaños y muestra su tabla.

Mide finalmente el algoritmo cúbico. Para n = 8000 no se ejecuta para evitar un tiempo de espera excesivo.

Ejecuta Kadane con n = 10^8.

Algoritmos

1. Algoritmo cúbico — O(n³)

Considera todos los subarreglos posibles y calcula desde cero la suma de cada uno.

La estructura tiene tres ciclos anidados, por lo que su costo crece aproximadamente de manera cúbica.

2. Algoritmo cuadrático — O(n²)

Fija el inicio del subarreglo y va acumulando la suma mientras avanza el segundo índice.

Se elimina el tercer ciclo del algoritmo anterior, reduciendo la complejidad a O(n²).

3. Algoritmo de Kadane — O(n)

Recorre el arreglo una sola vez y mantiene:

sumaActual: mejor suma de un subarreglo que termina en la posición actual.

mejor: mayor suma encontrada hasta ese momento.

Por esta razón, el algoritmo necesita tiempo lineal O(n).

Prueba de corrección

Antes de las mediciones, el programa genera 100 arreglos aleatorios y compara los resultados de los tres algoritmos.

Resultado obtenido:

CORRECCION: OK (100/100 pruebas)

Esto indica que las tres implementaciones produjeron el mismo valor en las 100 pruebas.

Mediciones obtenidas

Kadane — O(n)

n           Tiempo(ms)     Razon
----------------------------------------
1000        0.017          -
2000        0.030          1.713
4000        0.056          1.876
8000        0.091          1.635
----------------------------------------

Las razones son menores que 2 en estas mediciones, pero se mantienen aproximadamente en el entorno esperado para un crecimiento lineal al duplicar n. Las pequeñas variaciones se deben al costo de medición y al funcionamiento del sistema.

Cuadrática — O(n²)

n           Tiempo(ms)     Razon
----------------------------------------
1000        1.339          -
2000        5.311          3.967
4000        21.323         4.015
8000        85.916         4.029
----------------------------------------

Al duplicar el tamaño del arreglo, el tiempo aumenta aproximadamente 4 veces. Esto coincide claramente con un crecimiento cuadrático:

O(n²)  →  (2n)² / n² = 4

Cúbica — O(n³)

n           Tiempo(ms)     Razon
----------------------------------------
1000        410.105        -
2000        3313.884       8.081
4000        26553.400      8.013
8000        N/E            -
----------------------------------------

La medición para n = 8000 fue omitida debido al costo excesivo de ejecutar la versión cúbica.

Las razones observadas son aproximadamente 8, lo cual coincide con el crecimiento cúbico:

O(n³)  →  (2n)³ / n³ = 8

Ejecución con n = 10^8

Para un arreglo de 100 millones de elementos se ejecutó únicamente Kadane, ya que es el algoritmo con crecimiento lineal.

Resultado obtenido:

Generando arreglo...
Ejecutando Kadane...
Tiempo: 1.104 segundos

La versión cúbica y la cuadrática no se ejecutan directamente para n = 10^8 debido a su costo computacional.

Conclusiones experimentales

Los resultados permiten observar de forma práctica las diferencias entre las tres complejidades:

Kadane presenta el mejor comportamiento y escala linealmente.

El algoritmo cuadrático muestra un aumento cercano a 4 veces cada vez que se duplica n.

El algoritmo cúbico muestra un aumento cercano a 8 veces cada vez que se duplica n.

Para tamaños grandes, las diferencias entre O(n), O(n²) y O(n³) se vuelven muy importantes.

En este experimento, Kadane fue el único algoritmo utilizado para n = 10^8, obteniendo un tiempo de 1.104 segundos en el entorno de prueba.

Estructura del proyecto

max_subarray_project/
├── max_subarray.cpp
├── README.md
└── informe_maximo_subarreglo.docx

Nota sobre las mediciones

Los tiempos dependen del hardware, sistema operativo, compilador, opciones de optimización y carga del equipo en el momento de ejecutar el programa. Por ello, los valores pueden variar entre computadoras. Lo importante para el análisis es el comportamiento de las razones de crecimiento y su correspondencia con la complejidad teórica.
