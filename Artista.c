#include <stdio.h>
#include <string.h>
#include "artista.h"

int guardarArtista(Artista a)
{
    FILE *arch = fopen("artistas.dat", "ab");
    if (!arch) return 0;
    fwrite(&a, sizeof(Artista), 1, arch);
    fclose(arch);
    return 1;
}

int buscarArtistaPorId(char id[], Artista *a)
{
    FILE *arch = fopen("artistas.dat", "rb");
    if (!arch) return 0;
    while (fread(a, sizeof(Artista), 1, arch))
    {
        if (strcmp(a->idArtista, id) == 0)
        {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}

int buscarArtistaPorNombre(char nombre[], Artista *a)
{
    FILE *arch = fopen("artistas.dat", "rb");
    char busq[50];
    strcpy(busq, nombre);
    strupr(busq);
    if (!arch) return 0;
    while (fread(a, sizeof(Artista), 1, arch))
    {
        char aux[50];
        strcpy(aux, a->nombre);
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


