#ifndef ALBUM_H_INCLUDED
#define ALBUM_H_INCLUDED
#include "artista.h"

typedef struct stAlbum
{
    char idAlbum[10];
    Artista artista;
    char titulo[100];
    int anioLanzamiento;
    int cantidadCanciones;
} Album;

int guardarAlbum(Album alb);
int buscarAlbumPorId(char id[], Album *alb);
int buscarAlbumPorTitulo(char titulo[], Album *alb);
int actualizarAlbum(Album alb);

#endif
