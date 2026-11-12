
#ifndef ARTISTA_H
#define ARTISTA_H

#include "Estructuras.h"

int loginArtista(char *idSalida, char *nombreSalida);

void registrarArtista();
void menuArtista(char *idArtista, char *nombreArtista);
void agregarModificarAlbum(char *idArtista, char *nombreArtista);

void agregarModificarCancion(char *idArtista);

#endif
