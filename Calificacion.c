#include <stdio.h>
#include <string.h>
#include "calificacion.h"

int guardarCalificacion(Calificacion cal)
{
    FILE *arch = fopen("calificaciones.dat", "ab");
    if (!arch) return 0;
    fwrite(&cal, sizeof(Calificacion), 1, arch);
    fclose(arch);
    return 1;
}

float calcularPromedioCancion(char idCancion[])
{
    FILE *arch = fopen("calificaciones.dat", "rb");
    Calificacion cal;
    int suma = 0, cont = 0;
    if (!arch) return 0.0f;
    while (fread(&cal, sizeof(Calificacion), 1, arch))
    {
        if (strcmp(cal.idCancion, idCancion) == 0)
        {
            suma += cal.puntuacion;
            cont++;
        }
    }
    fclose(arch);
    return (cont == 0) ? 0.0f : (float)suma / cont;
}
