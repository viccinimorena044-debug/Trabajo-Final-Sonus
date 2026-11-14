
#ifndef ARTISTA_H
#define ARTISTA_H

#include "Estructuras.h"

int loginArtista(char *idSalida, char *nombreSalida);


Artista cargarArtista();
int guardarArtista(const char nombreArchivo[], Artista a);
void registrarArtista();
void menuArtista(char *idArtista, char *nombreArtista);
void agregarModificarAlbum(char *idArtista, char *nombreArtista);

int actualizarCantCancionesAlbum (const char idAlbum[]);
void agregarModificarCancion(char *idArtista);

#endif
