
#include "auxiliares.h"
#include <stdio.h>
#include <string.h>

// Limpia lo que queda en el búfer del teclado
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Pausa antes de volver al menú
void pausa() {
    printf("\nPresione Enter para continuar...");
    limpiarBuffer();
}

// Genera ID automático para Artista
void generarIdArtista(char *destino) {
    FILE *archivo = fopen("artistas.dat", "rb");
    int contador = 0;
    Artista a;
    if (archivo) {
        while (fread(&a, sizeof(Artista), 1, archivo)) contador++;
        fclose(archivo);
    }
    sprintf(destino, "A%09d", contador + 1);
}

// Genera ID automático para Usuario
void generarIdUsuario(char *destino) {
    FILE *archivo = fopen("usuarios.dat", "rb");
    int contador = 0;
    Usuario u;
    if (archivo) {
        while (fread(&u, sizeof(Usuario), 1, archivo)) contador++;
        fclose(archivo);
    }
    sprintf(destino, "U%09d", contador + 1);
}

// Genera ID automático para Álbum
void generarIdAlbum(char *destino) {
    FILE *archivo = fopen("albumes.dat", "rb");
    int contador = 0;
    Album a;
    if (archivo) {
        while (fread(&a, sizeof(Album), 1, archivo)) contador++;
        fclose(archivo);
    }
    sprintf(destino, "L%09d", contador + 1);
}

// Genera ID automático para Canción
void generarIdCancion(char *destino) {
    FILE *archivo = fopen("canciones.dat", "rb");
    int contador = 0;
    Cancion c;
    if (archivo) {
        while (fread(&c, sizeof(Cancion), 1, archivo)) contador++;
        fclose(archivo);
    }
    sprintf(destino, "C%09d", contador + 1);
}

// Genera ID automático para Calificación
void generarIdCalificacion(char *destino) {
    FILE *archivo = fopen("calificaciones.dat", "rb");
    int contador = 0;
    Calificacion c;
    if (archivo) {
        while (fread(&c, sizeof(Calificacion), 1, archivo)) contador++;
        fclose(archivo);
    }
    sprintf(destino, "CAL%07d", contador + 1);
}

// Verifica si un álbum ya existe para ese artista
int existeAlbumPorTituloYArtista(const char *titulo, const char *idArtista, char *idEncontrado) {
    FILE *archivo = fopen("albumes.dat", "rb");
    Album a;
    int existe = 0;
    if (!archivo) return 0;
    while (fread(&a, sizeof(Album), 1, archivo)) {
        if (strcmp(a.titulo, titulo) == 0 && strcmp(a.artista.idArtista, idArtista) == 0) {
            existe = 1;
            if (idEncontrado) strcpy(idEncontrado, a.idAlbum);
            break;
        }
    }
    fclose(archivo);
    return existe;
}

// Recalcula el promedio de calificaciones de una canción
void recalcularPromedio(const char *idCancion) {
    FILE *fCal = fopen("calificaciones.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb+");
    Calificacion cal;
    Cancion can;
    float suma = 0;
    int cantidad = 0;

    if (!fCal || !fCan) { if(fCal)fclose(fCal); if(fCan)fclose(fCan); return; }

    while (fread(&cal, sizeof(Calificacion), 1, fCal)) {
        if (strcmp(cal.idCancion, idCancion) == 0) {
            suma += cal.puntuacion;
            cantidad++;
        }
    }
    fclose(fCal);

    while (fread(&can, sizeof(Cancion), 1, fCan)) {
        if (strcmp(can.idCancion, idCancion) == 0) {
            can.calificacionPromedio = (cantidad > 0) ? (suma / cantidad) : 0.0f;
            fseek(fCan, -sizeof(Cancion), SEEK_CUR);
            fwrite(&can, sizeof(Cancion), 1, fCan);
            break;
        }
    }
    fclose(fCan);
}
