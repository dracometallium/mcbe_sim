# Ensamblador y simulador de `MCBE`

Este repositorio cuenta con dos herramientas. La primera es un ensamblador de
`MCBE` escrito en `AWK`, y la segunda es un simulador escrito en `C`.

## Ensamblador `mcbe_as`

El uso del ensamblador es sencillo, si se tiene un programa ensamblador
`p1.as` y se quiere crear el binario `p1.bin`, basta con ejecutar:
`./mcbe_as p1.as > p1.bin`.

**IMPORTANTE:** tener en cuenta que el ensamblador no realiza chequeos para
ver si los números están dentro del rango, ni que todas las etiquetas estén
correctamente definidas. Si hay algún error de sintaxis, no se notifica de
manera alguna. Capaz con el tiempo lo iremos mejorando, pero no cuente con
eso.

## Simulador `mcbe_sim`

Primero que nada, recordar que se debe compilar el simulador. Para esto es
suficiente con ejecutar el comando `make`.

Para ejecutar el programa `p1.bin` se debe ejecutar `mcbe_sim p1.sim`.

### Opciones:

-   `--fake-binary`: el archivo del programa no es un binario real, sino que
    es un archivo de texto. Cada linea representa el contenido binario de las
    celdas de memoria utilizando los caracteres `0` y `1` (ver ejemplo
    `programa1.fb`).

## Programas incluidos

En este repositorio se incluyen tres programas en ensamblador de `MCBE`.
Puede analizar el código o ensamblarlos y ejecutarlos.
