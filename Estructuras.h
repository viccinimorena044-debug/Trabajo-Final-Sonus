#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define MAX_NOMBRE 50
#define MAX_TITULO 100
#define MAX_ID 10
#define MAX_EMAIL 50
#define MAX_PASS 20
#define MAX_NICK 30

typedef struct
{
    char idUsuario[MAX_ID];
    char nickname[MAX_NICK];
    char email[MAX_EMAIL];
    char contrasenia[MAX_PASS];
} Usuario;

typedef struct
{
    char idArtista[MAX_ID];
    char nombre[MAX_NOMBRE];
    char generoPrincipal[30];
    char contrasenia[MAX_PASS];
} Artista;

typedef struct
{
    char idAlbum[MAX_ID];
    char titulo[MAX_TITULO];
    Artista artista;
    int anioLanzamiento;
    int cantidadCanciones;
} Album;

typedef struct
{
    char idCancion[MAX_ID];
    char titulo[MAX_TITULO];
    char idAlbum[MAX_ID];
    char idArtista[MAX_ID];
    int duracionSegundos;
    float calificacionPromedio;
} Cancion;

typedef struct
{
    char idRegistroCal[15];
    char nicknameUsuario[MAX_NICK];
    char idCancion[MAX_ID];
    int puntuacion;
} Calificacion;

#endif
