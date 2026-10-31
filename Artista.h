#ifndef ARTISTA_H_INCLUDED
#define ARTISTA_H_INCLUDED

// ===== ESTRUCTURAS =====
typedef struct stArtista
{
    char idArtista[10];
    char nombre[50];
    char contrasenia[20];
    char generoPrincipal[30];
} Artista;

// ===== PROTOTIPOS DE FUNCIONES =====

// Archivos - Artistas
int guardarArtista(Artista a);
int buscarArtistaPorId(char id[], Artista *a);
int buscarArtistaPorNombre(char nombre[], Artista *a);

// Auxiliares
void pausa();
void limpiarPantalla();
int generarId(char destino[], char prefijo);
int verificarLoginArtista(char id[], char pass[], Artista *resultado);
int verificarLoginUsuario(char id[], char pass[], Usuario *resultado);

#endif // ARTISTA_H_INCLUDED
