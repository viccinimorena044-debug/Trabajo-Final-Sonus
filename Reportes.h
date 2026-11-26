#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED
#include "Estructuras.h"

void reporteTop10Canciones();
void reporteAlbumesRecientes(const char *idArtista);
void mostrarAlbumesRecursivo(Album lista[], int validos, int i);
void reporteArtistaMasCalificado();
void reporteUsuarioMasActivo();

#endif
