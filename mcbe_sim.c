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

int imprimirHeader()
{
    printf(" PC ~ IR ~ Co | Op ~ AC | Memoria  | >> ~ PC |\n");
    return 0;
}

void imprimirEstado_decode()
{
    printf(" %02X ~ %02X ~ %02X | %02X ~",
           get_PC(), get_IR(), (get_IR() & OP) >> 5, get_IR() & ARG);
}

void imprimirEstado_ejecute()
{
    if (get_flag(F_OUT)) {
        printf(" %02X |          | %02X ~ %02X |\n", get_AC(), out(), get_PC());
    } else if (get_flag(F_MEM)) {
        printf(" %02X | (%02X)<-%02X |    ~ %02X |\n",
               get_AC(), get_mdir(), get_mval(), get_PC());
    } else {
        printf(" %02X |          |    ~ %02X |\n", get_AC(), get_PC());
    }
}

int ejecutar(bool showTable)
{
    int num;
    num = 0;
    if (showTable) {
        imprimirHeader();
    }
    while (!(get_flag(F_HALT))) {
        if (get_flag(F_IN)) {
            if (showTable) {
                printf(" !! ");
            }
            printf("Ingrese un número: ");
            scanf("%d", &num);
            if (showTable) {
                imprimirEstado_decode();
            }
            in(num);
            if (showTable) {
                imprimirEstado_ejecute();
            }
        } else if (get_flag(F_OUT)) {
            if (showTable) {
                imprimirEstado_decode();
                imprimirEstado_ejecute();
            } else {
                num = out();
                printf("Salida: %d\n", num);
            }
        } else {
            step();
            if (showTable) {
                imprimirEstado_decode();
                if (!(get_flag(F_IN))) {
                    imprimirEstado_ejecute();
                }
            }
        }
    }
    printf("Ejecución terminada\n");
    return 0;
}

void showHelp(char * name)
{
    fprintf(stderr, "Cantidad incorrecta de parámetros\n"
            "USO: %s programa.bin\n"
            "USO: %s --fake-binary programa.txt\n"
            "USO: %s --table programa.bin\n" "USO: mcbe_sim --help\n",
            name, name , name);
    return;
}

int main(int carg, char **varg)
{
    FILE *entrada;
    bool fakeBinary;
    bool showTable;
    int i;
    char *file_name;
    fakeBinary = false;
    showTable = false;
    file_name = NULL;
    if (carg < 2) {
        showHelp(varg[0]);
        return 1;
    }
    for (i = 1; i < carg; i++) {
        if ((strcmp(varg[i], "-t") == 0 || strcmp(varg[i], "--table") == 0)) {
            showTable = true;
        } else if ((strcmp(varg[i], "-fb") == 0
                    || strcmp(varg[i], "--fake-binary") == 0)) {
            fakeBinary = true;
        } else if ((strcmp(varg[i], "-h") == 0
                    || strcmp(varg[i], "--help") == 0)) {
            showHelp(varg[0]);
            return 0;
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
        ejecutar(showTable);
        fclose(entrada);
        return 0;
    }
}
