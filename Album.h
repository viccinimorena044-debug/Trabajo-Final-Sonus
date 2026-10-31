#ifndef ALBUM_H_INCLUDED
#define ALBUM_H_INCLUDED

// ===== ESTRUCTURAS =====
typedef struct stAlbum
{
    char idAlbum[10];
    Artista artista;
    char titulo[100];
    int anioLanzamiento;
    int cantidadCanciones;
} Album;

// ===== PROTOTIPOS DE FUNCIONES =====

// Archivos - Albumes
int guardarAlbum(Album alb);
int buscarAlbumPorId(char id[], Album *alb);
int buscarAlbumPorTitulo(char titulo[], Album *alb);
int actualizarAlbum(Album alb);

// Auxiliares
void pausa();
void limpiarPantalla();
int generarId(char destino[], char prefijo);
int verificarLoginArtista(char id[], char pass[], Artista *resultado);
int verificarLoginUsuario(char id[], char pass[], Usuario *resultado);

#endif // ALBUM_H_INCLUDED
