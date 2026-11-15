#ifndef ARTISTA_H
#define ARTISTA_H

#include "Estructuras.h"

// Prototipos simples sin estructuras
int loginArtista(char *idSalida, char *nombreSalida);
void registrarArtista();
void agregarModificarAlbum(char *idArtista, char *nombreArtista);
void agregarModificarCancion(char *idArtista);

#endif
