#include <stdio.h>
#include <string.h>
#include "Usuario.h"
#include "Auxiliares.h"

Usuario cargar1Usuario()
{
    Usuario u = {0};

    printf("\nIngrese nickname: ");
    if(fgets(u.nickname, 30, stdin)==NULL)
    {
        return u;
    }
    u.nickname[strcspn(u.nickname, "\n")]='\0';


    printf("\nIngrese email: ");
    if(fgets(u.email, 50, stdin)==NULL)
    {
        return u;
    }
    u.email[strcspn(u.email, "\n")]='\0';

    printf("\nIngrese contrasenia: ");
    if(fgets(u.contrasenia, 20, stdin)==NULL)
    {
        return u;
    }
    u.contrasenia[strcspn(u.contrasenia, "\n")]='\0';

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

int existeNickname (const char nombreArchivo[], const char nickname[])
{
    FILE *archivo =fopen(nombreArchivo, "rb");

    if(archivo ==NULL)
    {
        return 0;
    }

    Usuario u;

    while(fread(&u, sizeof(Usuario), 1, archivo)==1)
    {
        if(strcmp(u.nickname, nickname)==0)
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
    Usuario u = cargar1Usuario();


    if(u.nickname[0] == '\0' || u.email[0]== '\0' || u.contrasenia[0]== '\0')
    {
        printf("\nDato/s del usuario no completos");
        return;
    }

    if(existeNickname("usuarios.dat", u.nickname)==1)
    {
        printf("\nEse nickname ya existe");
        return;
    }

    generarIdUsuario(u.idUsuario);

    if(u.idUsuario[0]=='\0')
    {
        printf("\nNo se pudo generar el ID del usuario");
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
    FILE *fAlb = fopen("albumes.dat", "rb");
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

    printf("\nCat�logo por Artista\n");
    printf("Nombre del artista: ");
    fgets(nombreBuscar, 50, stdin);
    nombreBuscar[strcspn(nombreBuscar, "\n")] = 0;

    while (fread(&art, sizeof(Artista), 1, fArt)) {
        if (strcmp(art.nombre, nombreBuscar) == 0) {
            encontrado = 1;
            printf("\nArtista: %s %s\n", art.nombre, art.generoPrincipal);

            while (fread(&alb, sizeof(Album), 1, fAlb)) {
                if (strcmp(alb.artista.idArtista, art.idArtista) == 0) {
                    printf("  �lbum:%s %d\n", alb.titulo, alb.anioLanzamiento);

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
    FILE * archivo=fopen("albumes.dat", "rb");

    if(archivo ==NULL)
    {
        printf("\nNo hay albumes registrados");
        return;
    }

    Album a;

    char tituloBuscado[100];
    char nombreArtistaBuscado[50];
    char idAlbumEncontrado[10]= "";
    int encontrado =0;

    printf("\nIngrese el titulo del album: ");
    fgets(tituloBuscado, 100, stdin);
    tituloBuscado[strcspn(tituloBuscado, "\n")]='\0';

    printf("\nIngresar el nombre del artista: ");
    fgets(nombreArtistaBuscado, 50, stdin);
    nombreArtistaBuscado[strcspn(nombreArtistaBuscado, "\n")]='\0';

    while(fread(&a, sizeof(Album), 1, archivo)==1)
    {
        if(strcmp(a.titulo, tituloBuscado)==0 && strcmp(a.artista.nombre, nombreArtistaBuscado)==0)
        {
            strcpy(idAlbumEncontrado, a.idAlbum);
            encontrado=1;
        }
    }

    fclose(archivo);
    if(encontrado ==0)
    {
        printf("\nNo se encontro el album del artista");
        return;
    }

    FILE *archivoCanciones = fopen("canciones.dat", "rb");

    if(archivoCanciones==NULL)
    {
        printf("\nNo hay canciones registradas");
        return;
    }

    Cancion c;
    int contador=0;

    while(fread(&c, sizeof(Cancion), 1, archivoCanciones)==1)
    {
        if(strcmp(c.idAlbum, idAlbumEncontrado)==0)
        {
            printf("\nCancion: %s", c.titulo);
            contador++;
        }
    }

    fclose(archivoCanciones);

    if(contador== 0)
    {
        printf("\nEl album no tiene registradas canciones");
    }
}

void mostrarCancion(Cancion c)
{
    printf("\n\nCanion: ");
    printf("\nID: %s", c.idCancion);
    printf("\nTitulo: %s", c.titulo);
    printf("\nId del artista: %s", c.idArtista);
    printf("\nId del album: %s", c.idAlbum);
    printf("\nCalificacion promedio: %.2f", c.calificacionPromedio);
    printf("\nDuracion (segundos): %d", c.duracionSegundos);
}

void verInfoCancion()
{
    FILE *archivo=fopen("canciones.dat", "rb");

    if(archivo ==NULL)
    {
        return;
    }

    char idCancion[15];
    int encontrado= 0;

    Cancion c;

    printf("\nIngresar ID de cancion: ");
    if(fgets(idCancion, sizeof(idCancion), stdin)==NULL)
    {
        fclose(archivo);
        return;
    }

    idCancion[strcspn(idCancion, "\n")]='\0';

    while(fread(&c, sizeof(Cancion), 1, archivo)==1)
    {
        if(strcmp(c.idCancion, idCancion)==0)
        {
            mostrarCancion(c);
            encontrado=1;
        }
    }
    fclose(archivo);

    if(encontrado ==0)
    {
        printf("\nNo se encontro la cancion");
    }
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

    printf("\nCanciones por �lbum\n");
    printf("T�tulo del �lbum: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    while (fread(&alb, sizeof(Album), 1, fAlb)) {
        if (strcmp(alb.titulo, tituloBuscar) == 0) {
            encontrado = 1;
            printf("\n�lbum: %s %d\n", alb.titulo, alb.anioLanzamiento);

            while (fread(&can, sizeof(Cancion), 1, fCan)) {
                if (strcmp(can.idAlbum, alb.idAlbum) == 0) {
                    printf("- %s (%d seg) � Nota: %.1f\n", can.titulo, can.duracionSegundos, can.calificacionPromedio);
                }
            }
            break;
        }
    }

    if (!encontrado) printf("�lbum no encontrado.\n");

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

    printf("\nInfo Detallada de Canci�n \n");
    printf("T�tulo de la canci�n: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    while (fread(&can, sizeof(Cancion), 1, fCan)) {
        if (strcmp(can.titulo, tituloBuscar) == 0) {
            encontrado = 1;
            printf("\n%s\n", can.titulo);
            printf("Duraci�n: %d seg\n", can.duracionSegundos);
            printf("Calificaci�n Promedio: %.1f / 5\n", can.calificacionPromedio);
            break;
        }
    }

    if (!encontrado)
    printf("Canci�n no encontrada.\n");

    fclose(fCan);
}

void verInfoDetalladaCancion()
{
    FILE *fCan = fopen("canciones.dat", "rb");

    if(fCan == NULL)
    {
        printf("\nError al abrir canciones");
        return;
    }

    char tituloBuscar[100];
    Cancion can;
    int encontrado = 0;

    printf("\nInfo detallada de cancion");
    printf("\nTitulo de la cancion: ");

    if(fgets(tituloBuscar, 100, stdin) == NULL)
    {
        fclose(fCan);
        return;
    }

    tituloBuscar[strcspn(tituloBuscar, "\n")] = '\0';

    while(fread(&can, sizeof(Cancion), 1, fCan) == 1)
    {
        if(strcmp(can.titulo, tituloBuscar) == 0)
        {
            encontrado = 1;

            printf("\nTitulo: %s", can.titulo);
            printf("\nID: %s", can.idCancion);
            printf("\nDuracion: %d segundos",
                   can.duracionSegundos);
            printf("\nCalificacion promedio: %.1f",
                   can.calificacionPromedio);

            break;
        }
    }

    if(encontrado == 0)
    {
        printf("\nCancion no encontrada");
    }

    fclose(fCan);
}
