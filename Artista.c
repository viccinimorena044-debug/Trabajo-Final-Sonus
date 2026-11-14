
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

    printf("\nNombre artístico: ");
    fgets(nombreIngresado, 50, stdin);
    nombreIngresado[strcspn(nombreIngresado, "\n")] = 0;

    printf("\nContraseña: ");
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

int guardarArtista(const char nombreArchivo[], Artista a)
{
    FILE *archivo=fopen(nombreArchivo, "ab");

    if(archivo ==NULL)
    {
        return 0;
    }

    if(fwrite(&a, sizeof(Artista), 1, archivo)==1)
    {
        fclose(archivo);
        return 1;
    }
    fclose(archivo);
    return 0;
}

void registrarArtista()
{

    FILE *archivo = fopen("artistas.dat", "ab");
    Artista nuevo;

    if(archivo == NULL)
    {
        perror("Error al abrir archivo");
        return;
    }

    generarIdArtista(nuevo.idArtista);

    printf("\nNombre artistico: ");
    fgets(nuevo.nombre, 50, stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';

    printf("\nGenero principal: ");
    fgets(nuevo.generoPrincipal, 30, stdin);
    nuevo.generoPrincipal[strcspn(nuevo.generoPrincipal, "\n")] = '\0';

    printf("\nContrasenia: ");
    fgets(nuevo.contrasenia, 20, stdin);
    nuevo.contrasenia[strcspn(nuevo.contrasenia, "\n")] = '\0';

    if(nuevo.nombre[0]=='\0' || nuevo.generoPrincipal[0]=='\0' || nuevo.contrasenia[0]=='\0')
    {
        printf("\nIntento registrar un artista con datos vacios");

        fclose(archivo);
        return;
    }

    fwrite(&nuevo, sizeof(Artista), 1, archivo);
    fclose(archivo);

    printf("\nArtista registrado. ID: %s", nuevo.idArtista);
}


// =====================================================
// AGREGAR O MODIFICAR UN ÁLBUM
// =====================================================
void agregarModificarAlbum(char *idArtista, char *nombreArtista) {
    FILE *archivo = fopen("albumes.dat", "r+b");
    Album alb;
    Album nuevoAlbum={0};
    char tituloBuscar[100];
    int encontrado = 0;

    if (!archivo) {
        archivo = fopen("albumes.dat", "wb+");
        if (!archivo) { printf("\nError álbumes"); return; }
    }

    printf("\n--- Agregar / Modificar Álbum ---\n");
    printf("Título del álbum: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    if(tituloBuscar[0]=='\0')
    {
        printf("\nError al intentar registrar un album sin titulo");
        fclose(archivo);
        return;
    }

    rewind(archivo);
    while (fread(&alb, sizeof(Album), 1, archivo)) {
        if (strcmp(alb.titulo, tituloBuscar) == 0 && strcmp(alb.artista.idArtista, idArtista) == 0) {
            encontrado = 1;
            printf("Modificando: %s\n", alb.titulo);
            nuevoAlbum = alb;
            printf("Nuevo año de lanzamiento: ");

            int resultado= scanf("%d", &nuevoAlbum.anioLanzamiento);
            limpiarBuffer();

            if(resultado !=1 || nuevoAlbum.anioLanzamiento<=0)
            {
                printf("\nEl anio debe ser postivo");
                fclose(archivo);
                return;
            }

            fseek(archivo, -(long)sizeof(Album), SEEK_CUR);
            if(fwrite(&nuevoAlbum, sizeof(Album), 1, archivo)==1)
            {
                printf("Álbum modificado.\n");
            }
            else
            {
                printf("\nNo se pudo modificar el album");
            }

            break;
        }
    }

    if (!encontrado) {
        generarIdAlbum(nuevoAlbum.idAlbum);
        strcpy(nuevoAlbum.titulo, tituloBuscar);
        strcpy(nuevoAlbum.artista.idArtista, idArtista);
        strcpy(nuevoAlbum.artista.nombre, nombreArtista);
        printf("Año de lanzamiento: ");

        int resultado= scanf("%d", &nuevoAlbum.anioLanzamiento);
        limpiarBuffer();

        if(resultado !=1 || nuevoAlbum.anioLanzamiento<=0)
        {
            printf("\nEl anio debe ser postivo");
            fclose(archivo);
            return;
        }

        nuevoAlbum.cantidadCanciones = 0;
        fseek(archivo, 0, SEEK_END);
        if(fwrite(&nuevoAlbum, sizeof(Album), 1, archivo)==1)
        {
            printf("Álbum creado — ID: %s\n", nuevoAlbum.idAlbum);
        }
        else
        {
            printf("\nNo se pudo guardar el album");
        }
    }
    fclose(archivo);
}

// =====================================================
// AGREGAR O MODIFICAR UNA CANCIÓN
// =====================================================

int actualizarCantCancionesAlbum (const char idAlbum[])
{
    FILE* archivoCanciones= fopen("canciones.dat", "rb");

    if(archivoCanciones==NULL)
    {
        return 0;
    }

    Cancion c;

    int contador=0;

    while(fread(&c, sizeof(Cancion), 1, archivoCanciones)==1)
    {
        if(strcmp(c.idAlbum, idAlbum)==0)
        {
            contador++;
        }
    }

    fclose(archivoCanciones);

    FILE *archivoAlbumes= fopen("albumes.dat", "r+b");
    if(archivoAlbumes ==NULL)
    {
        return 0;

    }

    Album a;

    while(fread(&a, sizeof(Album), 1, archivoAlbumes)==1)
    {
        if(strcmp(a.idAlbum, idAlbum)==0)
        {
            a.cantidadCanciones = contador;
            if(fseek(archivoAlbumes, -(long)sizeof(Album), SEEK_CUR)!=0)
            {
                fclose(archivoAlbumes);
                return 0;
            }

            if(fwrite(&a, sizeof(Album), 1, archivoAlbumes)==1)
            {
                fclose(archivoAlbumes);
                return 1;
            }
        }
    }
    fclose(archivoAlbumes);
    return 0;
}


void agregarModificarCancion(char *idArtista) {
    FILE *fAlbumes = fopen("albumes.dat", "rb");
    char tituloAlbum[100], tituloCancion[100], idAlbumEncontrado[10];
    Cancion can;
    Cancion nuevaCancion={0};
    int encontrado = 0;

    if (!fAlbumes) { printf("No hay álbumes registrados.\n"); return; }

    printf("\n--- Agregar / Modificar Canción ---\n");
    printf("Título del álbum: ");
    fgets(tituloAlbum, 100, stdin);
    tituloAlbum[strcspn(tituloAlbum, "\n")] = 0;


    if (!existeAlbumPorTituloYArtista(tituloAlbum, idArtista, idAlbumEncontrado)) {
        printf("El álbum no existe o no te pertenece.\n");
        fclose(fAlbumes);
        return;
    }
    fclose(fAlbumes);

    FILE *fCanciones = fopen("canciones.dat", "rb+");
    if(fCanciones ==NULL)
    {
        fCanciones= fopen("canciones.dat", "wb+");
        if(fCanciones ==NULL)
        {
            printf("\nError al abrir canciones");
            return;
        }
    }

    printf("\nTítulo de la canción: ");
    fgets(tituloCancion, 100, stdin);
    tituloCancion[strcspn(tituloCancion, "\n")] = '\0';

    if(tituloCancion[0]=='\0')
    {
        printf("\nError al intentar registrar una cancion sin titulo");
        fclose(fCanciones);
        return;
    }


    rewind(fCanciones);
    while (fread(&can, sizeof(Cancion), 1, fCanciones)) {
        if (strcmp(can.titulo, tituloCancion) == 0 && strcmp(can.idArtista, idArtista) == 0 &&strcmp(can.idAlbum, idAlbumEncontrado)==0) {
            encontrado = 1;
            printf("Modificando canción\n");
            nuevaCancion = can;
            printf("\nNueva duración (seg): ");

            int result =scanf("%d", &nuevaCancion.duracionSegundos);
            limpiarBuffer();

            if(result !=1 || nuevaCancion.duracionSegundos <=0)
            {
                printf("\nLa duracion de la cancion tiene que ser positiva");
                fclose(fCanciones);
                return;
            }

            fseek(fCanciones, -(long)sizeof(Cancion), SEEK_CUR);
            if(fwrite(&nuevaCancion, sizeof(Cancion), 1, fCanciones)==1)
            {
                printf("Canción modificada.\n");
            }

            break;
        }
    }

    if (!encontrado) {
        generarIdCancion(nuevaCancion.idCancion);
        strcpy(nuevaCancion.titulo, tituloCancion);
        strcpy(nuevaCancion.idAlbum, idAlbumEncontrado);
        strcpy(nuevaCancion.idArtista, idArtista);

        printf("\nDuracion (segundos): ");

        int result= scanf("%d", &nuevaCancion.duracionSegundos);
        limpiarBuffer();

        if(result != 1 ||nuevaCancion.duracionSegundos<= 0)
        {
            printf("\nLa duracion de la cancion tiene que ser positiva");
            fclose(fCanciones);
            return;
        }
        nuevaCancion.calificacionPromedio = 0.0f;
        fseek(fCanciones, 0, SEEK_END); //ir al final

        int guardado= fwrite(&nuevaCancion, sizeof(Cancion), 1, fCanciones);

        fclose(fCanciones);

        if(guardado ==1)
        {
            printf("\nCancion creada. ID: %s", nuevaCancion.idCancion);

            if(actualizarCantCancionesAlbum(idAlbumEncontrado)==1)
            {
                printf("\nCantidad de canciones del album actualizada");
            }
            else
            {
                printf("\nNo se pudo actualizar la cantidad de canciones del album");
            }
        }
        else
        {
            printf("\nNo se pudo guardar la cancion en el album");
        }
        return;
    }
    fclose(fCanciones);

}
