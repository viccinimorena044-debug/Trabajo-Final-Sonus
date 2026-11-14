#include <stdio.h>
#include <string.h>
#include "Usuario.h"
#include "Auxiliares.h"

Usuario cargar1Usuario()
{
    Usuario u = {0};
    printf("\nIngrese nickname: ");
    scanf(" %29[^\n]", u.nickname);
    printf("\nIngrese email: ");
    scanf(" %49[^\n]", u.email);
    printf("\nIngrese contrasenia: ");
    scanf(" %19[^\n]", u.contrasenia);
    return u;
}

int guardarUsuario(const char nombreArchivo[], Usuario u)
{
    FILE *archivo = fopen(nombreArchivo, "ab");
    if(archivo == NULL) return 0;
    if(fwrite(&u, sizeof(Usuario), 1, archivo) == 1)
    {
        fclose(archivo);
        return 1;
    }
    fclose(archivo);
    return 0;
}

void registrarUsuario()
{
    Usuario u = cargar1Usuario();
    limpiarBuffer();

    if(u.nickname[0] == '\0' || u.contrasenia[0] == '\0')
    {
        printf("\nDatos de usuario incompletos.\n");
        return;
    }

    generarIdUsuario(u.idUsuario);
    if(u.idUsuario[0] == '\0')
    {
        printf("\nNo se pudo generar el ID o se alcanzo el limite de usuarios.\n");
        return;
    }

    if(guardarUsuario("usuarios.dat", u) == 1)
    {
        printf("\nUsuario registrado. ID: %s\n", u.idUsuario);
    }
    else
    {
        printf("\nNo se pudo guardar el usuario.\n");
    }
}

int loginUsuario(char *nicknameSalida)
{
    FILE *archivo = fopen("usuarios.dat", "rb");
    Usuario u;
    char nicknameIngresado[30];
    char contraseniaIngresada[20];

    if(archivo == NULL)
    {
        printf("\nNo hay usuarios registrados.\n");
        return 0;
    }

    printf("\nNickname: ");
    int resultadoN = scanf(" %29[^\n]", nicknameIngresado);
    printf("\nContrasenia: ");
    int resultadoC = scanf(" %19[^\n]", contraseniaIngresada);
    limpiarBuffer();

    if(resultadoN != 1 || resultadoC != 1)
    {
        fclose(archivo);
        return 0;
    }

    while(fread(&u, sizeof(Usuario), 1, archivo) == 1)
    {
        if(strcmp(u.nickname, nicknameIngresado) == 0 &&
           strcmp(u.contrasenia, contraseniaIngresada) == 0)
        {
            strcpy(nicknameSalida, u.nickname);
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    printf("\nNickname o contrasenia incorrectos.\n");
    return 0;
}

void verCatalogoPorArtista()
{
    FILE *fArt = fopen("artistas.dat", "rb");
    FILE *fAlb = fopen("albums.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb");
    char nombreBuscar[50];
    Artista art;
    Album alb;
    Cancion can;
    int encontrado = 0;

    if (!fArt || !fAlb || !fCan) {
        printf("Error al abrir archivos.\n");
        if (fArt) fclose(fArt);
        if (fAlb) fclose(fAlb);
        if (fCan) fclose(fCan);
        return;
    }

    printf("\nCatálogo por Artista\n");
    printf("Nombre del artista: ");
    fgets(nombreBuscar, 50, stdin);
    nombreBuscar[strcspn(nombreBuscar, "\n")] = 0;

    while (fread(&art, sizeof(Artista), 1, fArt)) {
        if (strcmp(art.nombre, nombreBuscar) == 0) {
            encontrado = 1;
            printf("\nArtista: %s %s\n", art.nombre, art.generoPrincipal);

            while (fread(&alb, sizeof(Album), 1, fAlb)) {
                if (strcmp(alb.artista.idArtista, art.idArtista) == 0) {
                    printf("  Álbum:%s %d\n", alb.titulo, alb.anioLanzamiento);

                    while (fread(&can, sizeof(Cancion), 1, fCan)) {
                        if (strcmp(can.idAlbum, alb.idAlbum) == 0) {
                            printf("%s %d seg Nota: %.1f\n", can.titulo, can.duracionSegundos, can.calificacionPromedio);
                        }
                    }
                    fseek(fCan, 0, SEEK_SET);
                }
            }
            fseek(fAlb, 0, SEEK_SET);
        }
    }

    if (!encontrado) printf("Artista no encontrado.\n");

    fclose(fArt);
    fclose(fAlb);
    fclose(fCan);
}

void verCancionesPorAlbum()
{
    FILE *fAlb = fopen("albums.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb");
    char tituloBuscar[100];
    Album alb;
    Cancion can;
    int encontrado = 0;

    if (!fAlb || !fCan) {
        printf("Error al abrir archivos.\n");
        if (fAlb) fclose(fAlb);
        if (fCan) fclose(fCan);
        return;
    }

    printf("\nCanciones por Álbum\n");
    printf("Título del álbum: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    while (fread(&alb, sizeof(Album), 1, fAlb)) {
        if (strcmp(alb.titulo, tituloBuscar) == 0) {
            encontrado = 1;
            printf("\nÁlbum: %s %d\n", alb.titulo, alb.anioLanzamiento);

            while (fread(&can, sizeof(Cancion), 1, fCan)) {
                if (strcmp(can.idAlbum, alb.idAlbum) == 0) {
                    printf("- %s (%d seg) — Nota: %.1f\n", can.titulo, can.duracionSegundos, can.calificacionPromedio);
                }
            }
            break;
        }
    }

    if (!encontrado) printf("Álbum no encontrado.\n");

    fclose(fAlb);
    fclose(fCan);
}
void verInfoDetalladaCancion() {
    FILE *fCan = fopen("canciones.dat", "rb");
    char tituloBuscar[100];
    Cancion can;
    int encontrado = 0;

    if (!fCan) {
        printf("Error al abrir canciones\n");
        return;
    }

    printf("\nInfo Detallada de Canción \n");
    printf("Título de la canción: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    while (fread(&can, sizeof(Cancion), 1, fCan)) {
        if (strcmp(can.titulo, tituloBuscar) == 0) {
            encontrado = 1;
            printf("\n%s\n", can.titulo);
            printf("Duración: %d seg\n", can.duracionSegundos);
            printf("Calificación Promedio: %.1f / 5\n", can.calificacionPromedio);
            break;
        }
    }

    if (!encontrado)
    printf("Canción no encontrada.\n");

    fclose(fCan);
}
