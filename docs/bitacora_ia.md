# Bitácora IA

## Prompt utilizado
ENTRADA 1:
Analizar la estructura del proyecto y determinar qué archivos faltan implementar.


...

## Respuesta IA
ENTRADA 1:
Se revisó la estructura del proyecto y los archivos de prueba (tests). Se identificó que era necesario crear los archivos:

scheduler.h
queue.h
queue.c
circular_queue.h
circular_queue.c

Además, se explicó la relación entre FIFO, Round Robin y las estructuras de datos necesarias para implementarlos.
...

## Errores encontrados
ENTRADA 1: 
Inicialmente se pensó que no era necesario crear queue.h ni circular_queue.h porque no aparecían en la estructura principal del proyecto, pero al revisar el pdf, se vió que era necesario implementarlos
...

## Correcciones realizadas
ENTRADA 1:
Se analizaron los archivos test_queue.c y test_circular_queue.c, comprobando que dichas estructuras sí eran requeridas por las pruebas.

...

## Validaciones realizadas
ENTRADA 1:
Se verificó que las funciones utilizadas en los tests coincidieran con las declaradas en los nuevos archivos de encabezado.

...
