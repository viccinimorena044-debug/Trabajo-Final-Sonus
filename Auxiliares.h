#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "Estructuras.h"

void limpiarBuffer();
void pausa();
void construirId (char *destino, char prefijo, int numero, int anchoTotal);
int generarIdArtista(char *destino);
int generarIdUsuario(char *destino);
int generarIdAlbum(char *destino);
int generarIdCancion(char *destino);
int generarIdCalificacion(char *destino);
int existeAlbumPorTituloYArtista(const char *titulo, const char *idArtista, char *idEncontrado);
void recalcularPromedio(const char *idCancion);
int contarCancionesPorAlbum(const char *idAlbum);

#endif
