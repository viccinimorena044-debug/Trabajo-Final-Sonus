#include <stdio.h>
#include <string.h>
#include "cancion.h"

int guardarCancion(Cancion c)
{
    FILE *arch = fopen("canciones.dat", "ab");
    if (!arch) return 0;
    fwrite(&c, sizeof(Cancion), 1, arch);
    fclose(arch);
    return 1;
}

int buscarCancionPorId(char id[], Cancion *c)
{
    FILE *arch = fopen("canciones.dat", "rb");
    if (!arch) return 0;
    while (fread(c, sizeof(Cancion), 1, arch))
    {
        if (strcmp(c->idCancion, id) == 0)
        {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}

int buscarCancionPorTitulo(char titulo[], Cancion *c)
{
    FILE *arch = fopen("canciones.dat", "rb");
    char busq[100];
    strcpy(busq, titulo);
    strupr(busq);
    if (!arch) return 0;
    while (fread(c, sizeof(Cancion), 1, arch))
    {
        char aux[100];
        strcpy(aux, c->titulo);
        strupr(aux);
        if (strstr(aux, busq) != NULL)
        {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}

int actualizarPromedioCancion(char idCancion[], float nuevoProm)
{
    FILE *arch = fopen("canciones.dat", "r+b");
    Cancion c;
    int ok = 0;
    if (!arch) return 0;
    while (fread(&c, sizeof(Cancion), 1, arch))
    {
        if (strcmp(c.idCancion, idCancion) == 0)
        {
            c.calificacionPromedio = nuevoProm;
            fseek(arch, -sizeof(Cancion), SEEK_CUR);
            fwrite(&c, sizeof(Cancion), 1, arch);
            ok = 1;
            break;
        }
    }
    fclose(arch);
    return ok;
}
