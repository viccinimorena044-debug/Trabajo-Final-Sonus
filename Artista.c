#include <stdio.h>
#include <string.h>
#include "Artista.h"
#include "Auxiliares.h"

int loginArtista(char *idSalida, char *nombreSalida)
{
    FILE *archivo = fopen("artistas.dat", "rb");
    Artista a;
    char nombreIngresado[50];
    char passIngresada[20];

    if(archivo == NULL)
    {
        printf("\nNo hay artistas registrados.\n");
        return 0;
    }

    printf("\nNombre artistico: ");
    if(fgets(nombreIngresado, 50, stdin) == NULL)
    {
        fclose(archivo);
        return 0;
    }
    nombreIngresado[strcspn(nombreIngresado, "\n")] = '\0';

    printf("Contrasenia: ");
    if(fgets(passIngresada, 20, stdin) == NULL)
    {
        fclose(archivo);
        return 0;
    }
    passIngresada[strcspn(passIngresada, "\n")] = '\0';

    while(fread(&a, sizeof(Artista), 1, archivo) == 1)
    {
        if(strcmp(a.nombre, nombreIngresado) == 0 &&
           strcmp(a.contrasenia, passIngresada) == 0)
        {
            strcpy(idSalida, a.idArtista);
            strcpy(nombreSalida, a.nombre);
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    printf("\nCredenciales incorrectas.\n");
    return 0;
}

Artista cargar1Artista()
{
    Artista a = {0};

    printf("\nIngrese nombre del artista: ");
    scanf(" %49[^\n]", a.nombre);

    printf("\nIngrese genero musical: ");
    scanf(" %29[^\n]", a.generoPrincipal);

    printf("\nIngrese contrasenia: ");
    scanf(" %19s", a.contrasenia);

    return a;
}

int guardarArtista(const char nombreArchivo[], Artista a)
{
    FILE *archivo = fopen(nombreArchivo, "ab");
    if(archivo == NULL) return 0;

    if(fwrite(&a, sizeof(Artista), 1, archivo) == 1)
    {
        fclose(archivo);
        return 1;
    }
    fclose(archivo);
    return 0;
}

void registrarArtista()
{
    Artista a = cargar1Artista();
    limpiarBuffer(); // Limpia el Enter que deja scanf antes de volver al menu.

    if(a.nombre[0] == '\0' || a.contrasenia[0] == '\0')
    {
        printf("\nDatos del artista incompletos.");
        return;
    }

    generarIdArtista(a.idArtista);
    if(a.idArtista[0] == '\0')
    {
        printf("\nNo se pudo generar el ID o se alcanzo el limite de artistas.");
        return;
    }

    if(guardarArtista("artistas.dat", a) == 1)
    {
        printf("\nArtista registrado. ID: %s\n", a.idArtista);
    }
    else
    {
        printf("\nNo se pudo guardar el artista.\n");
    }
}

int buscarArtistaPorId(const char nombreArchivo[],
                       const char idBuscado[],
                       Artista *artistaBuscado)
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    Artista a;
    if(archivo == NULL) return 0;

    while(fread(&a, sizeof(Artista), 1, archivo) == 1)
    {
        if(strcmp(a.idArtista, idBuscado) == 0)
        {
            *artistaBuscado = a;
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}

Album cargar1Album(Artista artista)
{
    Album a = {0};
    a.artista = artista;
    // No hace falta duplicar la contrasenia en el archivo de albumes.
    a.artista.contrasenia[0] = '\0';

    printf("\nIngrese titulo del album: ");
    scanf(" %99[^\n]", a.titulo);

    printf("\nIngrese anio de lanzamiento: ");
    if(scanf("%d", &a.anioLanzamiento) != 1)
    {
        a.anioLanzamiento = 0;
    }

    a.cantidadCanciones = 0;
    return a;
}

int guardarAlbum(const char nombreArchivo[], Album a)
{
    FILE *archivo = fopen(nombreArchivo, "ab");
    if(archivo == NULL) return 0;
    if(fwrite(&a, sizeof(Album), 1, archivo) == 1)
    {
        fclose(archivo);
        return 1;
    }
    fclose(archivo);
    return 0;
}

int buscarAlbumPorId(const char nombreArchivo[],
                     const char idBuscado[],
                     Album *albumBuscado)
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    Album a;
    if(archivo == NULL) return 0;

    while(fread(&a, sizeof(Album), 1, archivo) == 1)
    {
        if(strcmp(a.idAlbum, idBuscado) == 0)
        {
            *albumBuscado = a;
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}

int modificarAlbum(const char nombreArchivo[],
                   const char idBuscado[],
                   const char idArtista[])
{
    FILE *archivo = fopen(nombreArchivo, "r+b");
    Album a;

    if(archivo == NULL) return 0;

    while(fread(&a, sizeof(Album), 1, archivo) == 1)
    {
        if(strcmp(a.idAlbum, idBuscado) == 0)
        {
            if(strcmp(a.artista.idArtista, idArtista) != 0)
            {
                fclose(archivo);
                return 0;
            }

            printf("\nAlbum encontrado: %s", a.titulo);
            char nuevoTitulo[100];
            char idExistente[10];

            printf("\nNuevo titulo: ");
            int resultT = scanf(" %99[^\n]", nuevoTitulo);
            if(resultT != 1)
            {
                limpiarBuffer();
                fclose(archivo);
                return 0;
            }

            // Se permite mantener el mismo titulo, pero no copiar el de otro album propio.
            if(existeAlbumPorTituloYArtista(nuevoTitulo, idArtista, idExistente) == 1 &&
               strcmp(idExistente, idBuscado) != 0)
            {
                limpiarBuffer();
                printf("\nYa tenes otro album con ese titulo.\n");
                fclose(archivo);
                return 0;
            }

            int nuevoAnio;
            printf("\nNuevo anio de lanzamiento: ");
            int resultA = scanf("%d", &nuevoAnio);
            limpiarBuffer();

            if(resultA != 1 || nuevoAnio <= 0)
            {
                fclose(archivo);
                return 0;
            }

            strcpy(a.titulo, nuevoTitulo);
            a.anioLanzamiento = nuevoAnio;

            if(fseek(archivo, -(long)sizeof(Album), SEEK_CUR) != 0)
            {
                fclose(archivo);
                return 0;
            }

            if(fwrite(&a, sizeof(Album), 1, archivo) == 1)
            {
                fclose(archivo);
                return 1;
            }

            fclose(archivo);
            return 0;
        }
    }

    fclose(archivo);
    return 0;
}

void agregarModificarAlbum(char *idArtista, char *nombreArtista)
{
    int opcion;
    printf("\n\n--- AGREGAR / MODIFICAR ALBUM ---");
    printf("\nArtista: %s", nombreArtista);
    printf("\n1- Agregar album");
    printf("\n2- Modificar album");
    printf("\n0- Volver");
    printf("\nIngrese una opcion: ");

    int resultado = scanf("%d", &opcion);
    limpiarBuffer();
    if(resultado != 1)
    {
        printf("\nOpcion invalida.");
        return;
    }

    switch(opcion)
    {
        case 1:
        {
            Artista artistaEncontrado;
            if(buscarArtistaPorId("artistas.dat", idArtista, &artistaEncontrado) != 1)
            {
                printf("\nNo se encontro el artista.");
                return;
            }

            // Primero revisar el limite; despues pedir los datos del album.
            char nuevoId[10];
            generarIdAlbum(nuevoId);
            if(nuevoId[0] == '\0')
            {
                printf("\nNo se pueden registrar mas albumes.");
                return;
            }

            Album a = cargar1Album(artistaEncontrado);
            limpiarBuffer();

            if(a.titulo[0] == '\0' || a.anioLanzamiento <= 0)
            {
                printf("\nDatos del album invalidos.");
                return;
            }

            char idExistente[10];
            if(existeAlbumPorTituloYArtista(a.titulo, idArtista, idExistente) == 1)
            {
                printf("\nYa existe este album. ID: %s", idExistente);
                return;
            }

            strcpy(a.idAlbum, nuevoId);
            if(guardarAlbum("albumes.dat", a) == 1)
            {
                printf("\nAlbum guardado. ID: %s\n", a.idAlbum);
            }
            else
            {
                printf("\nNo se pudo guardar el album.\n");
            }
            break;
        }

        case 2:
        {
            char idBuscado[10];
            printf("\nIngrese ID del album: ");
            int resultadoId = scanf("%9s", idBuscado);
            limpiarBuffer();
            if(resultadoId != 1)
            {
                printf("\nID invalido.");
                return;
            }

            if(modificarAlbum("albumes.dat", idBuscado, idArtista) == 1)
            {
                printf("\nAlbum modificado correctamente.\n");
            }
            else
            {
                printf("\nNo se pudo modificar el album.\n");
            }
            break;
        }

        case 0:
            return;

        default:
            printf("\nOpcion invalida.\n");
            break;
    }
}

int actualizarCantidadCancionesAlbum(const char idAlbum[])
{
    FILE *fCanciones = fopen("canciones.dat", "rb");
    FILE *fAlbumes;
    Cancion c;
    Album a;
    int cantidad = 0;

    if(fCanciones == NULL) return 0;

    while(fread(&c, sizeof(Cancion), 1, fCanciones) == 1)
    {
        if(strcmp(c.idAlbum, idAlbum) == 0)
        {
            cantidad++;
        }
    }
    fclose(fCanciones);

    fAlbumes = fopen("albumes.dat", "r+b");
    if(fAlbumes == NULL) return 0;

    while(fread(&a, sizeof(Album), 1, fAlbumes) == 1)
    {
        if(strcmp(a.idAlbum, idAlbum) == 0)
        {
            a.cantidadCanciones = cantidad;
            if(fseek(fAlbumes, -(long)sizeof(Album), SEEK_CUR) != 0)
            {
                fclose(fAlbumes);
                return 0;
            }
            if(fwrite(&a, sizeof(Album), 1, fAlbumes) == 1)
            {
                fclose(fAlbumes);
                return 1;
            }
            fclose(fAlbumes);
            return 0;
        }
    }

    fclose(fAlbumes);
    return 0;
}

void agregarModificarCancion(char *idArtista)
{
    char tituloAlbum[100];
    char tituloCancion[100];
    char idAlbumEncontrado[10];
    FILE *archivo;
    Cancion can;

    printf("\n--- AGREGAR / MODIFICAR CANCION ---");
    printf("\nTitulo del album: ");
    int resultadoAlbum = scanf(" %99[^\n]", tituloAlbum);
    limpiarBuffer();

    if(resultadoAlbum != 1)
    {
        printf("\nTitulo de album invalido.\n");
        return;
    }

    // Ya no necesitamos abrir otro FILE * de albumes:
    // la funcion de Auxiliares.c hace esa busqueda.
    if(existeAlbumPorTituloYArtista(tituloAlbum, idArtista, idAlbumEncontrado) != 1)
    {
        printf("\nEl album no existe o no te pertenece.\n");
        return;
    }

    printf("\nTitulo de la cancion: ");
    int resultadoCancion = scanf(" %99[^\n]", tituloCancion);
    limpiarBuffer();
    if(resultadoCancion != 1)
    {
        printf("\nTitulo de cancion invalido.\n");
        return;
    }

    archivo = fopen("canciones.dat", "r+b");
    if(archivo != NULL)
    {
        while(fread(&can, sizeof(Cancion), 1, archivo) == 1)
        {
            if(strcmp(can.titulo, tituloCancion) == 0 &&
               strcmp(can.idAlbum, idAlbumEncontrado) == 0 &&
               strcmp(can.idArtista, idArtista) == 0)
            {
                int nuevaDuracion;
                printf("\nCancion encontrada. Nueva duracion (segundos): ");
                int resultado = scanf("%d", &nuevaDuracion);
                limpiarBuffer();

                if(resultado != 1 || nuevaDuracion <= 0)
                {
                    printf("\nDuracion invalida.\n");
                    fclose(archivo);
                    return;
                }

                can.duracionSegundos = nuevaDuracion;
                if(fseek(archivo, -(long)sizeof(Cancion), SEEK_CUR) != 0)
                {
                    printf("\nError al buscar la posicion de la cancion.\n");
                    fclose(archivo);
                    return;
                }

                if(fwrite(&can, sizeof(Cancion), 1, archivo) == 1)
                {
                    printf("\nCancion modificada.\n");
                }
                else
                {
                    printf("\nNo se pudo modificar la cancion.\n");
                }
                fclose(archivo);
                return;
            }
        }
        fclose(archivo);
    }

    Cancion nuevaCancion = {0};
    generarIdCancion(nuevaCancion.idCancion);
    if(nuevaCancion.idCancion[0] == '\0')
    {
        printf("\nNo se pudo generar el ID de la cancion.\n");
        return;
    }

    strcpy(nuevaCancion.titulo, tituloCancion);
    strcpy(nuevaCancion.idAlbum, idAlbumEncontrado);
    strcpy(nuevaCancion.idArtista, idArtista);
    nuevaCancion.calificacionPromedio = 0;

    printf("\nDuracion (segundos): ");
    int resultado = scanf("%d", &nuevaCancion.duracionSegundos);
    limpiarBuffer();
    if(resultado != 1 || nuevaCancion.duracionSegundos <= 0)
    {
        printf("\nDuracion invalida.\n");
        return;
    }

    archivo = fopen("canciones.dat", "ab");
    if(archivo == NULL)
    {
        printf("\nNo se pudo abrir el archivo de canciones.\n");
        return;
    }

    int guardado = fwrite(&nuevaCancion, sizeof(Cancion), 1, archivo);
    fclose(archivo);

    if(guardado == 1)
    {
        printf("\nCancion creada. ID: %s\n", nuevaCancion.idCancion);
        if(actualizarCantidadCancionesAlbum(idAlbumEncontrado) != 1)
        {
            printf("\nAviso: no se pudo actualizar cantidadCanciones en el album.\n");
        }
    }
    else
    {
        printf("\nNo se pudo guardar la cancion.\n");
    }
}
