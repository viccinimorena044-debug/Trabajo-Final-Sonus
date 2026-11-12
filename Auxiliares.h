#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "Estructuras.h"

void limpiarBuffer();
void pausa();

long cantidadArtistas(const char nombreArchivo[]);
long cantidadUsuarios(const char nombreArchivo[]);
long cantidadAlbumes(const char nombreArchivo[]);
long cantidadCancionesArchivo(const char nombreArchivo[]);
long cantidadCalificacionesArchivo(const char nombreArchivo[]);

void generarIdArtista(char *destino);
void generarIdUsuario(char *destino);
void generarIdAlbum(char *destino);
void generarIdCancion(char *destino);
void generarIdCalificacion(char *destino);

int existeAlbumPorTituloYArtista(const char titulo[],
                                 const char idArtista[],
                                 char idEncontrado[]);
void recalcularPromedio(const char *idCancion);

#endif
