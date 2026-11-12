#ifndef ARTISTA_H
#define ARTISTA_H

#include "Estructuras.h"

int loginArtista(char *idSalida, char *nombreSalida);

//Registro
Artista cargar1Artista();
int guardarArtista(const char nombreArchivo[], Artista a);
void registrarArtista();


void menuArtista(char *idArtista, char *nombreArtista);

//Albumes
Album cargar1Album(Artista artista);
int guardarAlbum(const char nombreArchivo[], Album a);
int buscarArtistaPorId(const char nombreArchivo[], const char idBuscado[], Artista *artistaBuscado);
int buscarAlbumPorId(const char nombreArchivo[], const char idBuscado[],Album *albumBuscado);
int modificarAlbum(const char nombreArchivo[], const char idBuscado[], const char idArtista[]);
void agregarModificarAlbum(char *idArtista, char *nombreArtista);


void agregarModificarCancion(char *idArtista);

#endif
