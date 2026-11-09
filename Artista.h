#ifndef ARTISTA_H_INCLUDED
#define ARTISTA_H_INCLUDED

typedef struct stArtista
{
    char idArtista[10];
    char nombre[50];
    char contrasenia[20];
    char generoPrincipal[30];
} Artista;

int guardarArtista(Artista a);
int buscarArtistaPorId(char id[], Artista *a);
int buscarArtistaPorNombre(char nombre[], Artista *a);

#endif
