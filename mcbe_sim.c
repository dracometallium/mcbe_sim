#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcbe.h"

int leer_fb(FILE *entrada)
{
    int c;
    int i;
    int num;
    i = 0;
    num = 0;
    while ((EOF != (c = fgetc(entrada))) && (i <= 31)) {
        if (c == '\n') {
            set_mem(num, i);
            i++;
            num = 0;
        } else {
            num = num * 2;
            if (c == '1') {
                num = num + 1;
            }
        }
    }
    return 0;
}

int leer(FILE *entrada)
{
    int c;
    int i;
    i = 0;
    while ((EOF != (c = fgetc(entrada))) && (i <= 31)) {
        set_mem(c, i);
        i++;
    }
    return 0;

}

int imprimirEstado()
{
    printf("PC: %u\tIR: %u\tAC: %d\n", get_PC(), get_IR(), get_AC());
    return 0;
}

int ejecutar()
{
    int num;
    num = 0;
    /*imprimirEstado(); */
    while (!(get_flag(F_HALT))) {
        if (get_flag(F_IN)) {
            printf("Ingrese un número: ");
            scanf("%d", &num);
            in(num);
        } else if (get_flag(F_OUT)) {
            num = out();
            printf("Salida: %d\n", num);
        } else {
            step();
            /*imprimirEstado(); */
        }
    }
    printf("Ejecución terminada\n");
    return 0;
}

int main(int carg, char **varg)
{
    FILE *entrada;
    bool fakeBinary;
    int i;
    char *file_name = NULL;
    fakeBinary = false;
    if (carg < 2) {
        fprintf(stderr, "Cantidad incorrecta de parámetros\n"
                "USO: mcbe_sim programa.bin\n"
                "USO: mcbe_sim --fake-binary programa.txt\n");
        return 1;
    }
    for (i = 1; i < carg; i++) {
        if ((strcmp(varg[i], "-fb") == 0
             || strcmp(varg[i], "--fake-binary") == 0)) {
            fakeBinary = true;
        } else {
            file_name = varg[i];
        }
    }
    entrada = fopen(file_name, "r");
    if (entrada == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo de entrada T_T\n");
        return -1;
    } else {
        init();
        if (fakeBinary) {
            leer_fb(entrada);
        } else {
            leer(entrada);
        }
        ejecutar();
        fclose(entrada);
        return 0;
    }
}
