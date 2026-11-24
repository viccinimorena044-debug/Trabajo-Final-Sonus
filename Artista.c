#include "Artista.h"
#include "Auxiliares.h"
#include <stdio.h>
#include <string.h>

// =====================================================
// INICIAR SESION COMO ARTISTA
// =====================================================
int loginArtista(char *idSalida, char *nombreSalida)
{
    FILE *archivo = fopen("artistas.dat", "rb");
    if (!archivo)
    {
        printf("No hay artistas registrados aun.\n");
        return 0;
    }

    Artista a;
    char nombreIngresado[50], passIngresada[20];

    printf("\nNombre artistico: ");
    fgets(nombreIngresado, 50, stdin);
    nombreIngresado[strcspn(nombreIngresado, "\n")] = 0;

    printf("\nContrasena: ");
    fgets(passIngresada, 20, stdin);
    passIngresada[strcspn(passIngresada, "\n")] = 0;

    while (fread(&a, sizeof(Artista), 1, archivo))
    {
        if (strcmp(a.nombre, nombreIngresado) == 0 && strcmp(a.contrasenia, passIngresada) == 0)
        {
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
void registrarArtista()
{
    FILE *archivo = fopen("artistas.dat", "ab");
    Artista nuevo;

    if (!archivo)
    {
        printf("\nError al abrir archivo");
        return;
    }

    generarIdArtista(nuevo.idArtista);

    printf("\nNombre artistico: ");
    fgets(nuevo.nombre, 50, stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;

    printf("\nGenero principal: ");
    fgets(nuevo.generoPrincipal, 30, stdin);
    nuevo.generoPrincipal[strcspn(nuevo.generoPrincipal, "\n")] = 0;

    printf("\nContrasenia: ");
    fgets(nuevo.contrasenia, 20, stdin);
    nuevo.contrasenia[strcspn(nuevo.contrasenia, "\n")] = 0;

    fwrite(&nuevo, sizeof(Artista), 1, archivo);
    fclose(archivo);

    printf("Artista registrado. ID: %s\n", nuevo.idArtista);
}

// =====================================================
// AGREGAR O MODIFICAR UN ALBUM
// =====================================================
void agregarModificarAlbum(char *idArtista, char *nombreArtista)
{
    FILE *archivo = fopen("albumes.dat", "rb+");
    Album alb, nuevoAlbum;
    char tituloBuscar[100];
    int encontrado = 0;

    if (!archivo)
    {
        archivo = fopen("albumes.dat", "wb+");

    if (!archivo) { printf("Error Albumes"); return; }
    }

    printf("\n--- Agregar / Modificar Album ---\n");
    printf("Titulo del album: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    rewind(archivo);
    while (fread(&alb, sizeof(Album), 1, archivo))
    {
        if (strcmp(alb.titulo, tituloBuscar) == 0 && strcmp(alb.artista.idArtista, idArtista) == 0)
        {
            encontrado = 1;
            printf("Modificando: %s\n", alb.titulo);
            nuevoAlbum = alb;
            printf("\nNuevo anio de lanzamiento: ");
            if(scanf("%d", &nuevoAlbum.anioLanzamiento)!= 1 ||nuevoAlbum.anioLanzamiento <=0)
            {
                limpiarBuffer();
                printf("\nEl anio debe ser un numero positivo");
                fclose(archivo);
                return;
            }

            limpiarBuffer();
            fseek(archivo, -(long)sizeof(Album), SEEK_CUR);
            fwrite(&nuevoAlbum, sizeof(Album), 1, archivo);
            printf("Album modificado.\n");
            break;
        }
    }

    if (!encontrado)
    {
        generarIdAlbum(nuevoAlbum.idAlbum);
        strcpy(nuevoAlbum.titulo, tituloBuscar);
        strcpy(nuevoAlbum.artista.idArtista, idArtista);
        strcpy(nuevoAlbum.artista.nombre, nombreArtista);
        printf("\nAnio de lanzamiento: ");
        if(scanf("%d", &nuevoAlbum.anioLanzamiento) !=1 || nuevoAlbum.anioLanzamiento <=0)
        {
            limpiarBuffer();
            printf("\nEl anio tiene que ser un numero positivo");
            fclose(archivo);
            return;
        }

        limpiarBuffer();
        nuevoAlbum.cantidadCanciones = 0;
        fwrite(&nuevoAlbum, sizeof(Album), 1, archivo);
        printf("\nAlbum creado ID: %s\n", nuevoAlbum.idAlbum);
    }
    fclose(archivo);
}

// =====================================================
// AGREGAR O MODIFICAR UNA CANCION
// =====================================================
void agregarModificarCancion(char *idArtista)
{
    FILE *fAlbumes = fopen("albumes.dat", "rb");
    FILE *fCanciones = fopen("canciones.dat", "rb+");
    char tituloAlbum[100], tituloCancion[100], idAlbumEncontrado[MAX_ID];
    Cancion can, nuevaCancion;
    int encontrado = 0;

    if (!fAlbumes) {
        printf("No hay albumes registrados.\n");

        if(fCanciones !=NULL)
        {
            fclose(fCanciones);
        }

        return;
    }
    if (!fCanciones)
    {
        fCanciones = fopen("canciones.dat", "wb+");

        if (!fCanciones) { printf("Error canciones"); fclose(fAlbumes); return; }
    }

    printf("\n--- Agregar / Modificar Cancion ---\n");

    //Mostrar los primeros 5 albumes
    Album a;
    char titulos[5][MAX_TITULO];
    int validos=0;

    while(validos <5 && fread(&a, sizeof(Album), 1, fAlbumes)==1)
    {
        if(strcmp(a.artista.idArtista, idArtista)==0)
        {
            strcpy(titulos[validos], a.titulo);
            validos++;
        }
    }

    printf("\nPrimeros cinco albumes: ");
    for(int i=0; i< validos; i++)
    {
        printf("\n %s", titulos[i]);
    }

    printf("Titulo del album: ");
    fgets(tituloAlbum, 100, stdin);
    tituloAlbum[strcspn(tituloAlbum, "\n")] = 0;

    if (!existeAlbumPorTituloYArtista(tituloAlbum, idArtista, idAlbumEncontrado))
    {
        printf("El album no existe o no te pertenece.\n");
        fclose(fAlbumes);
        fclose(fCanciones);
        return;
    }
    fclose(fAlbumes);

    printf("Titulo de la cancion: ");
    fgets(tituloCancion, 100, stdin);
    tituloCancion[strcspn(tituloCancion, "\n")] = 0;

    rewind(fCanciones);
    while (fread(&can, sizeof(Cancion), 1, fCanciones))
    {
        if (strcmp(can.titulo, tituloCancion) == 0 && strcmp(can.idArtista, idArtista) == 0 && strcmp(can.idAlbum, idAlbumEncontrado)==0)
        {
            encontrado = 1;
            printf("Modificando cancion\n");
            nuevaCancion = can;
            printf("\nNueva duracion (seg): ");
            if(scanf("%d", &nuevaCancion.duracionSegundos) !=1 || nuevaCancion.duracionSegundos <=0)
            {
                limpiarBuffer();
                printf("\nLa duracion tiene que ser un numero positiva");
                fclose(fCanciones);
                return;
            }

            limpiarBuffer();
            fseek(fCanciones, -(long)sizeof(Cancion), SEEK_CUR);
            fwrite(&nuevaCancion, sizeof(Cancion), 1, fCanciones);
            printf("Cancion modificada.\n");
            break;
        }
    }

    if (!encontrado)
    {
        generarIdCancion(nuevaCancion.idCancion);
        strcpy(nuevaCancion.titulo, tituloCancion);
        strcpy(nuevaCancion.idAlbum, idAlbumEncontrado);
        strcpy(nuevaCancion.idArtista, idArtista);
        printf("Duracion (segundos): ");
        if(scanf("%d", &nuevaCancion.duracionSegundos) != 1|| nuevaCancion.duracionSegundos <=0)
        {
            limpiarBuffer();
            printf("\nLa duracion debe ser un numero positivo");
            fclose(fCanciones);
            return;
        }

        limpiarBuffer();
        nuevaCancion.calificacionPromedio = 0.0f;
        fwrite(&nuevaCancion, sizeof(Cancion), 1, fCanciones);
        printf("Cancion creada. ID: %s\n", nuevaCancion.idCancion);
    }
    fclose(fCanciones);
}
