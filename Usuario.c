#include "Usuario.h"
#include "Auxiliares.h"
#include <stdio.h>
#include <string.h>

// =====================================================
// INICIAR SESIÓN COMO USUARIO
// =====================================================
int loginUsuario(char *nicknameSalida)
{
    FILE *archivo = fopen("usuarios.dat", "rb");
    if (!archivo)
    {
        printf("No hay usuarios registrados aun.\n");
        return 0;
    }

    Usuario u;
    char nickIngresado[30], passIngresada[20];

    printf("Nickname: ");
    fgets(nickIngresado, 30, stdin);
    nickIngresado[strcspn(nickIngresado, "\n")] = 0;

    printf("Contrasena: ");
    fgets(passIngresada, 20, stdin);
    passIngresada[strcspn(passIngresada, "\n")] = 0;

    while (fread(&u, sizeof(Usuario), 1, archivo))
    {
        if (strcmp(u.nickname, nickIngresado) == 0 && strcmp(u.contrasenia, passIngresada) == 0)
        {
            fclose(archivo);
            strcpy(nicknameSalida, u.nickname);
            return 1;
        }
    }
    fclose(archivo);
    printf("Credenciales incorrectas.\n");
    return 0;
}

// =====================================================
// REGISTRAR NUEVO USUARIO
// =====================================================

int buscarUsuario (char nickname[])
{
    FILE *archivo =fopen("usuarios.dat", "rb");
    if(archivo ==NULL)
    {
        printf("\nError al intentar abrir el archivo");
        return -1;
    }

    Usuario aux;

    while(fread(&aux, sizeof(Usuario), 1, archivo)==1)
    {
        if(strcmp(aux.nickname, nickname)==0)
        {
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}

void registrarUsuario()
{
    FILE *archivo = fopen("usuarios.dat", "ab");
    Usuario nuevo;

    if (!archivo)
    {
        perror("Error al abrir archivo");
        return;
    }

    generarIdUsuario(nuevo.idUsuario);

    printf("Nickname: ");
    fgets(nuevo.nickname, 30, stdin);
    nuevo.nickname[strcspn(nuevo.nickname, "\n")] = 0;

    int flag= buscarUsuario (nuevo.nickname);

    if(flag== -1)
    {
        fclose(archivo);
        return;
    }
    if(flag ==1)
    {
        printf("\nEse nickname ya se encunetra registrado");
        fclose(archivo);
        return;
    }

    printf("\nEmail: ");
    fgets(nuevo.email, 50, stdin);
    nuevo.email[strcspn(nuevo.email, "\n")] = 0;

    printf("Contrasena: ");
    fgets(nuevo.contrasenia, 20, stdin);
    nuevo.contrasenia[strcspn(nuevo.contrasenia, "\n")] = 0;

    fwrite(&nuevo, sizeof(Usuario), 1, archivo);
    fclose(archivo);
    printf("Usuario registrado correctamente.\n");
}

// =====================================================
// VER CATÁLOGO POR ARTISTA
// =====================================================
void verCatalogoPorArtista()
{
    FILE *fArt = fopen("artistas.dat", "rb");
    FILE *fAlb = fopen("albumes.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb");
    char nombreBuscar[50];
    Artista artEncontrado;
    Album alb;
    Cancion can;
    int artistaEncontrado = 0;

    if (!fArt || !fAlb || !fCan)
    {
        printf("No hay suficientes datos registrados.\n");
        if (fArt) fclose(fArt);
        if (fAlb) fclose(fAlb);
        if (fCan) fclose(fCan);
        return;
    }

    printf("\n--- Catalogo por Artista ---\n");
    printf("Nombre del artista: ");
    fgets(nombreBuscar, 50, stdin);
    nombreBuscar[strcspn(nombreBuscar, "\n")] = 0;

    while (fread(&artEncontrado, sizeof(Artista), 1, fArt))
    {
        if (strstr(artEncontrado.nombre, nombreBuscar) != NULL)
        {
            artistaEncontrado = 1;
            printf("\n Artista: %s | Genero: %s\n", artEncontrado.nombre, artEncontrado.generoPrincipal);
            printf(" ===============================================================================\n");

            int tieneAlbumes = 0;
            while (fread(&alb, sizeof(Album), 1, fAlb))
            {
                if (strcmp(alb.artista.idArtista, artEncontrado.idArtista) == 0)
                {
                    tieneAlbumes = 1;
                    printf("\n  Album: %s (%d) | %d canciones\n",
                           alb.titulo, alb.anioLanzamiento, contarCancionesPorAlbum(alb.idAlbum));
                    printf(" =================================================\n");

                    rewind(fCan);
                    while (fread(&can, sizeof(Cancion), 1, fCan))
                    {
                        if (strcmp(can.idAlbum, alb.idAlbum) == 0)
                        {
                            int min = can.duracionSegundos / 60;
                            int seg = can.duracionSegundos % 60;
                            printf("%s (%02d:%02d) | %.1f\n",
                                   can.titulo, min, seg, can.calificacionPromedio);
                        }
                    }
                }
            }
            if (!tieneAlbumes) printf("Este artista aun no tiene albumes publicados.\n");
            break;
        }
    }
    if (!artistaEncontrado) printf("No se encontro ningun artista con ese nombre.\n");

    fclose(fArt);
    fclose(fAlb);
    fclose(fCan);
}
// =====================================================
// VER CANCIONES POR ÁLBUM — COMPLETA
// =====================================================
void verCancionesPorAlbum()
{
    FILE *fAlb = fopen("albumes.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb");
    char tituloBuscar[100], idAlbumEncontrado[MAX_ID];
    char nombreArtistaBuscar[MAX_NOMBRE];
    Album alb;
    Cancion can;
    int albumEncontrado = 0;

    if (!fAlb || !fCan)
    {
        printf("No hay suficientes datos registrados.\n");
        if (fAlb) fclose(fAlb);
        if (fCan) fclose(fCan);
        return;
    }

    printf("\n--- Canciones por Album ---\n");
    printf("Titulo del album: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    printf("Nombre del artista: ");
    fgets(nombreArtistaBuscar, MAX_NOMBRE, stdin);
    nombreArtistaBuscar[strcspn(nombreArtistaBuscar, "\n")] = 0;

    while (fread(&alb, sizeof(Album), 1, fAlb))
    {
        if (strcmp(alb.titulo,tituloBuscar)==0 && strcmp(alb.artista.nombre,nombreArtistaBuscar)==0)
        {
            albumEncontrado = 1;
            strcpy(idAlbumEncontrado, alb.idAlbum);
            printf("\n Album: %s - %s (%d)\n",
                   alb.titulo, alb.artista.nombre, alb.anioLanzamiento);
            printf("====================================================\n");
            printf("  %-40s | Duracion | Calificacion\n", "Cancion");
            printf("====================================================\n");

            int contador = 0;
            rewind(fCan);
            while (fread(&can, sizeof(Cancion), 1, fCan))
            {
                if (strcmp(can.idAlbum, idAlbumEncontrado) == 0)
                {
                    int min = can.duracionSegundos / 60;
                    int seg = can.duracionSegundos % 60;
                    printf("  %-40s | %02d:%02d   | %.1f\n",
                           can.titulo, min, seg, can.calificacionPromedio);
                    contador++;
                }
            }
            if (contador == 0) printf("Este album aun no tiene canciones.\n");
            else printf("\n  Total: %d canciones\n", contador);
            break;
        }
    }
    if (!albumEncontrado) printf("No se encontro ningun album con ese titulo.\n");

    fclose(fAlb);
    fclose(fCan);
}

// =====================================================
// VER INFORMACIÓN DETALLADA DE UNA CANCIÓN
// =====================================================
void verInfoCancion()
{
    FILE *fCan = fopen("canciones.dat", "rb");
    FILE *fAlb = fopen("albumes.dat", "rb");
    FILE *fArt = fopen("artistas.dat", "rb");
    char tituloBuscar[100];
    Cancion can;
    Album alb;
    Artista art;
    int encontrada = 0;

    if (!fCan || !fAlb || !fArt)
    {
        printf("No hay suficientes datos registrados.\n");
        if (fCan) fclose(fCan);
        if (fAlb) fclose(fAlb);
        if (fArt) fclose(fArt);
        return;
    }

    printf("\n--- Informacion de Cancion ---\n");
    printf("Titulo de la cancion: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    while (fread(&can, sizeof(Cancion), 1, fCan))
    {
        if (strstr(can.titulo, tituloBuscar) != NULL)
        {
            encontrada = 1;

            //rewind(fAlb);
            char nombreAlbum[100] = "Desconocido";
            while (fread(&alb, sizeof(Album), 1, fAlb))
            {
                if (strcmp(alb.idAlbum, can.idAlbum) == 0)
                {
                    strcpy(nombreAlbum, alb.titulo);
                    break;
                }
            }

            rewind(fArt);
            char nombreArtista[50] = "Desconocido";
            while (fread(&art, sizeof(Artista), 1, fArt))
            {
                if (strcmp(art.idArtista, can.idArtista) == 0)
                {
                    strcpy(nombreArtista, art.nombre);
                    break;
                }
            }

            int min = can.duracionSegundos / 60;
            int seg = can.duracionSegundos % 60;

            printf(" ==================================================\n");
            printf("                INFORMACION DE CANCION             \n");
            printf(" ==================================================\n");
            printf(" Titulo:    %-45s \n", can.titulo);

            printf("\n ID de la cancion: %s\n", can.idCancion);
            printf(" Artista:   %-45s \n", nombreArtista);
            printf(" Album:     %-45s \n", nombreAlbum);
            printf(" Duracion:  %02d:%02d                               \n", min, seg);
            printf(" Calificacion Promedio:  %.1f / 5                   \n", can.calificacionPromedio);
            printf("====================================================\n");
            break;
        }
    }
    if (!encontrada) printf("No se encontro ninguna cancion con ese titulo.\n");

    fclose(fCan);
    fclose(fAlb);
    fclose(fArt);
}
