#ifndef CANCION_H_INCLUDED
#define CANCION_H_INCLUDED
#include "album.h"
#include "artista.h"

typedef struct stCancion
{
    char idCancion[10];
    char titulo[100];
    char idAlbum[10];
    char idArtista[10];
    int duracionSegundos;
    float calificacionPromedio;
} Cancion;

int guardarCancion(Cancion c);
int buscarCancionPorId(char id[], Cancion *c);
int buscarCancionPorTitulo(char titulo[], Cancion *c);
int actualizarPromedioCancion(char idCancion[], float nuevoProm);

#endif

