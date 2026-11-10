#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

typedef struct stArtista
{
    char idArtista[10];
    char nombre[50];
    char contrasenia[20];
    char generoPrincipal[30];
} Artista;

typedef struct stUsuario
{
    char idUsuario[10];
    char email[50];
    char contrasenia[20];
    char nickname[30];
} Usuario;

typedef struct stAlbum
{
    char idAlbum[10];
    Artista artista;
    char titulo[100];
    int anioLanzamiento;
    int cantidadCanciones;
} Album;

typedef struct stCancion
{
    char idCancion[10];
    char titulo[100];
    char idAlbum[10];
    char idArtista[10];
    int duracionSegundos;
    float calificacionPromedio;
} Cancion;

typedef struct stCalificacion
{
    char idRegistroCal[10];
    char nicknameUsuario[30];
    char idCancion[10];
    int puntuacion;
} Calificacion;

#endif // ESTRUCTURAS_H_INCLUDED
