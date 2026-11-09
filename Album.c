#include <stdio.h>
#include <string.h>
#include "album.h"

int guardarAlbum(Album alb)
{
    FILE *arch = fopen("albumes.dat", "ab");
    if (!arch) return 0;
    fwrite(&alb, sizeof(Album), 1, arch);
    fclose(arch);
    return 1;
}

int buscarAlbumPorId(char id[], Album *alb)
{
    FILE *arch = fopen("albumes.dat", "rb");
    if (!arch) return 0;
    while (fread(alb, sizeof(Album), 1, arch))
    {
        if (strcmp(alb->idAlbum, id) == 0)
        {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}

int buscarAlbumPorTitulo(char titulo[], Album *alb)
{
    FILE *arch = fopen("albumes.dat", "rb");
    char busq[100];
    strcpy(busq, titulo);
    strupr(busq);
    if (!arch) return 0;
    while (fread(alb, sizeof(Album), 1, arch))
    {
        char aux[100];
        strcpy(aux, alb->titulo);
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

int actualizarAlbum(Album alb)
{
    FILE *arch = fopen("albumes.dat", "r+b");
    Album temp;
    int ok = 0;
    if (!arch) return 0;
    while (fread(&temp, sizeof(Album), 1, arch))
    {
        if (strcmp(temp.idAlbum, alb.idAlbum) == 0)
        {
            fseek(arch, -sizeof(Album), SEEK_CUR);
            fwrite(&alb, sizeof(Album), 1, arch);
            ok = 1;
            break;
        }
    }
    fclose(arch);
    return ok;
}
