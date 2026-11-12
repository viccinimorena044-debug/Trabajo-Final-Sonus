
#include "artista.h"
#include "auxiliares.h"
#include <stdio.h>
#include <string.h>

// =====================================================
// INICIAR SESIÓN COMO ARTISTA
// =====================================================
int loginArtista(char *idSalida, char *nombreSalida) {
    FILE *archivo = fopen("artistas.dat", "rb");
    if (!archivo) {
        printf("No hay artistas registrados aún.\n");
        return 0;
    }

    Artista a;
    char nombreIngresado[50], passIngresada[20];

    printf("Nombre artístico: ");
    fgets(nombreIngresado, 50, stdin);
    nombreIngresado[strcspn(nombreIngresado, "\n")] = 0;

    printf("Contraseña: ");
    fgets(passIngresada, 20, stdin);
    passIngresada[strcspn(passIngresada, "\n")] = 0;

    while (fread(&a, sizeof(Artista), 1, archivo)) {
        if (strcmp(a.nombre, nombreIngresado) == 0 && strcmp(a.contrasenia, passIngresada) == 0) {
            fclose(archivo);
            strcpy(idSalida, a.idArtista);
            strcpy(nombreSalida, a.nombre);
            return 1;
        }
    }
    fclose(archivo);
    printf("Credenciales incorrectas.\n");
    return 0;
}

// =====================================================
// REGISTRAR NUEVO ARTISTA
// =====================================================
void registrarArtista() {
    FILE *archivo = fopen("artistas.dat", "ab");
    Artista nuevo;

    if (!archivo) {
        perror("Error al abrir archivo");
        return;
    }

    generarIdArtista(nuevo.idArtista);

    printf("Nombre artístico: ");
    fgets(nuevo.nombre, 50, stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;

    printf("Género principal: ");
    fgets(nuevo.generoPrincipal, 30, stdin);
    nuevo.generoPrincipal[strcspn(nuevo.generoPrincipal, "\n")] = 0;

    printf("Contraseña: ");
    fgets(nuevo.contrasenia, 20, stdin);
    nuevo.contrasenia[strcspn(nuevo.contrasenia, "\n")] = 0;

    fwrite(&nuevo, sizeof(Artista), 1, archivo);
    fclose(archivo);
    printf("Artista registrado — ID: %s\n", nuevo.idArtista);
}

// =====================================================
// AGREGAR O MODIFICAR UN ÁLBUM
// =====================================================
void agregarModificarAlbum(char *idArtista, char *nombreArtista) {
    FILE *archivo = fopen("albumes.dat", "rb+");
    Album alb, nuevoAlbum;
    char tituloBuscar[100];
    int encontrado = 0;

    if (!archivo) {
        archivo = fopen("albumes.dat", "wb+");
        if (!archivo) { perror("Error álbumes"); return; }
    }

    printf("\n--- Agregar / Modificar Álbum ---\n");
    printf("Título del álbum: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    rewind(archivo);
    while (fread(&alb, sizeof(Album), 1, archivo)) {
        if (strcmp(alb.titulo, tituloBuscar) == 0 && strcmp(alb.artista.idArtista, idArtista) == 0) {
            encontrado = 1;
            printf("Modificando: %s\n", alb.titulo);
            nuevoAlbum = alb;
            printf("Nuevo año de lanzamiento: ");
            scanf("%d", &nuevoAlbum.anioLanzamiento);
            limpiarBuffer();
            fseek(archivo, -sizeof(Album), SEEK_CUR);
            fwrite(&nuevoAlbum, sizeof(Album), 1, archivo);
            printf("Álbum modificado.\n");
            break;
        }
    }

    if (!encontrado) {
        generarIdAlbum(nuevoAlbum.idAlbum);
        strcpy(nuevoAlbum.titulo, tituloBuscar);
        strcpy(nuevoAlbum.artista.idArtista, idArtista);
        strcpy(nuevoAlbum.artista.nombre, nombreArtista);
        printf("Año de lanzamiento: ");
        scanf("%d", &nuevoAlbum.anioLanzamiento);
        limpiarBuffer();
        nuevoAlbum.cantidadCanciones = 0;
        fwrite(&nuevoAlbum, sizeof(Album), 1, archivo);
        printf("Álbum creado — ID: %s\n", nuevoAlbum.idAlbum);
    }
    fclose(archivo);
}

// =====================================================
// AGREGAR O MODIFICAR UNA CANCIÓN
// =====================================================
void agregarModificarCancion(char *idArtista) {
    FILE *fAlbumes = fopen("albumes.dat", "rb");
    FILE *fCanciones = fopen("canciones.dat", "rb+");
    char tituloAlbum[100], tituloCancion[100], idAlbumEncontrado[10];
    Cancion can, nuevaCancion;
    int encontrado = 0;

    if (!fAlbumes) { printf("No hay álbumes registrados.\n"); return; }
    if (!fCanciones) {
        fCanciones = fopen("canciones.dat", "wb+");
        if (!fCanciones) { perror("Error canciones"); fclose(fAlbumes); return; }
    }

    printf("\n--- Agregar / Modificar Canción ---\n");
    printf("Título del álbum: ");
    fgets(tituloAlbum, 100, stdin);
    tituloAlbum[strcspn(tituloAlbum, "\n")] = 0;

    if (!existeAlbumPorTituloYArtista(tituloAlbum, idArtista, idAlbumEncontrado)) {
        printf("El álbum no existe o no te pertenece.\n");
        fclose(fAlbumes);
        fclose(fCanciones);
        return;
    }
    fclose(fAlbumes);

    printf("Título de la canción: ");
    fgets(tituloCancion, 100, stdin);
    tituloCancion[strcspn(tituloCancion, "\n")] = 0;

    rewind(fCanciones);
    while (fread(&can, sizeof(Cancion), 1, fCanciones)) {
        if (strcmp(can.titulo, tituloCancion) == 0 && strcmp(can.idArtista, idArtista) == 0) {
            encontrado = 1;
            printf("Modificando canción\n");
            nuevaCancion = can;
            printf("Nueva duración (seg): ");
            scanf("%d", &nuevaCancion.duracionSegundos);
            limpiarBuffer();
            fseek(fCanciones, -sizeof(Cancion), SEEK_CUR);
            fwrite(&nuevaCancion, sizeof(Cancion), 1, fCanciones);
            printf("Canción modificada.\n");
            break;
        }
    }

    if (!encontrado) {
        generarIdCancion(nuevaCancion.idCancion);
        strcpy(nuevaCancion.titulo, tituloCancion);
        strcpy(nuevaCancion.idAlbum, idAlbumEncontrado);
        strcpy(nuevaCancion.idArtista, idArtista);
        printf("Duración (segundos): ");
        scanf("%d", &nuevaCancion.duracionSegundos);
        limpiarBuffer();
        nuevaCancion.calificacionPromedio = 0.0f;
        fwrite(&nuevaCancion, sizeof(Cancion), 1, fCanciones);
        printf("Canción creada — ID: %s\n", nuevaCancion.idCancion);
    }
    fclose(fCanciones);
}
