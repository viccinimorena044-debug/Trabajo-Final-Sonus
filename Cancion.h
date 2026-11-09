#ifndef CANCION_H_INCLUDED
#define CANCION_H_INCLUDED

#include "Cancion.h"

// ===== ESTRUCTURAS =====
typedef struct stCancion
{
    char idCancion[10];
    char titulo[100];
    char idAlbum[10];
    char idArtista[10];
    int duracionSegundos;
    float calificacionPromedio;
} Cancion;

// ===== PROTOTIPOS DE FUNCIONES =====

// Archivos - Canciones
int guardarCancion(Cancion c);
int buscarCancionPorId(char id[], Cancion *c);
int buscarCancionPorTitulo(char titulo[], Cancion *c);
int actualizarPromedioCancion(char idCancion[], float nuevoProm);

// Auxiliares
void pausa();
void limpiarPantalla();
int generarId(char destino[], char prefijo);
int verificarLoginArtista(char id[], char pass[], Artista *resultado);
int verificarLoginUsuario(char id[], char pass[], Usuario *resultado);

#endif // CANCION_H_INCLUDED
