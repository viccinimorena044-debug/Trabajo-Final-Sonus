#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "artista.h"
#include "usuario.h"
#include "album.h"
#include "cancion.h"
#include "calificacion.h"
#include "auxiliares.h"




void verCatalogoPorArtista()
{
    char nomBuscar[50];
    printf("Ingrese artista: ");
    fgets(nomBuscar, sizeof(nomBuscar), stdin);
    nomBuscar[strcspn(nomBuscar, "\n")] = '\0';

    FILE *fAlb = fopen("albumes.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb");
    Album alb;
    Cancion can;
    int encontrado = 0;

    if (!fAlb)
    {
        printf("No hay albumes cargados.\n");
        if (fCan) fclose(fCan);

        return;
    }

    while (fread(&alb, sizeof(Album), 1, fAlb) == 1)
    {
        if (strcmpi(alb.artista.nombre, nomBuscar) == 0)
    {
            encontrado = 1;
            printf("Album: %s %d\n", alb.titulo, alb.anioLanzamiento);

            if (fCan)
           {
                rewind(fCan);
                while (fread(&can, sizeof(Cancion), 1, fCan) == 1)
                {
                    if (strcmp(can.idAlbum, alb.idAlbum) == 0)
                        printf("%s Promedio: %.2f\n", can.titulo, can.calificacionPromedio);
                }
            }
        }
    }


    fclose(fAlb);
    if (fCan) fclose(fCan);

    if (!encontrado) printf("No se encontro el artista.\n");

}

void verMisCalificaciones(Usuario usu)
{
    FILE *fCal = fopen("calificaciones.dat", "rb");
    Calificacion cal;
    int cant = 0;
    int capacidad = 5;

    if (!fCal)
    {
        printf("Aun no hay calificaciones registradas.\n");
        return;
    }

    Calificacion *misCals = malloc(capacidad * sizeof(Calificacion));
    if (!misCals)
    {
        fclose(fCal);
        return;
    }

    while (fread(&cal, sizeof(Calificacion), 1, fCal) == 1)
    {
        if (strcmp(cal.nicknameUsuario, usu.nickname) == 0)
        {
            if (cant >= capacidad) {
                capacidad += 5;
                Calificacion *aux = realloc(misCals, capacidad * sizeof(Calificacion));
                if (aux) misCals = aux;
                else break;
            }
            misCals[cant++] = cal;
        }
    }
    fclose(fCal);

    if (cant == 0) {
        printf("No calificaste ninguna cancion todavia\n");
    } else {
        printf("--- Tus Calificaciones ---\n");
        for (int i = 0; i < cant; i++) {
            printf("Cancion ID: %s | Puntaje: %d/5\n", misCals[i].idCancion, misCals[i].puntuacion);
        }
    }

    free(misCals);

}
void limpiarPantalla()
{
 system("cls");
}

void reporteTop10()
{
    typedef struct
    {
        char nombre[100];
        float promedio;
    }TopCancion;

    TopCancion lista[500], aux;
    int n = 0, i, j;
    Cancion can;

    limpiarPantalla();
    printf("========== TOP 10 CANCIONES ==========\n\n");

    FILE *fCan = fopen("canciones.dat", "rb");
    if (!fCan)
    {
        printf("No hay canciones registradas en el sistema.\n");
        pausa();
        return;
    }

    while(n < 500 && fread(&can, sizeof(Cancion), 1, fCan))
    {
        strcpy(lista[n].nombre, can.titulo);
        lista[n].promedio = can.calificacionPromedio;
        n++;
    }
    fclose(fCan);

    if (n == 0)
    {
        printf("No hay canciones registradas en el sistema.\n");
        pausa();
        return;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (lista[j].promedio < lista[j + 1].promedio)
            {
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }

    int limite = (n < 10) ? n : 10;
    for (i = 0; i < limite; i++)
    {
        printf("%2d. %-35s %.2f/5\n", i + 1, lista[i].nombre, lista[i].promedio);
    }
    printf("\n=======================================\n");
    pausa();
}

void reporteAlbumesRecientes()
{
    Album lista[500], aux;
    int n = 0, i, j;
    time_t ahora = time(NULL);
    struct tm *fechaActual = localtime(&ahora);
    int anioActual = fechaActual->tm_year + 1900;

    limpiarPantalla();
    printf("==== ALBUMES LANZADOS EN EL ULTIMO ANIO (%d-%d) ====\n\n",
           anioActual - 1, anioActual);

    FILE *fAlb = fopen("albumes.dat", "rb");
    if (!fAlb)
    {
        printf("No hay albumes registrados.\n");
        pausa();
        return;
    }

    while (n < 500 && fread(&lista[n], sizeof(Album), 1, fAlb))
    {
        if (lista[n].anioLanzamiento >= anioActual - 1 && lista[n].anioLanzamiento <= anioActual)
        {
            n++;
        }
    }
    fclose(fAlb);

    if (n == 0)
    {
        printf("No hay albumes lanzados en el ultimo anio.\n");
        pausa();
        return;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (lista[j].anioLanzamiento < lista[j + 1].anioLanzamiento)
            {
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        printf("%d | %-30s | %s\n",
               lista[i].anioLanzamiento,
               lista[i].titulo,
               lista[i].artista.nombre);
    }
    printf("\n=======================================================\n");
    pausa();
}

void reporteArtistaMasCalificado()
{
    typedef struct
    {
        char idArtista[10];
        char nombre[50];
        int totalPuntos;
    }ContadorArtista;

    ContadorArtista lista[200] = {{0}};
    int cantidadArtistas = 0;
    Calificacion cal;
    Cancion can;
    Artista art;

    limpiarPantalla();
    printf("==== ARTISTA CON MAS CALIFICACIONES ====\n\n");

    FILE *fCal = fopen("calificaciones.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb");

    if (!fCal || !fCan)
    {
        printf("No hay calificaciones registradas aun.\n");
        if (fCal) fclose(fCal);
        if (fCan) fclose(fCan);
        pausa();
        return;
    }

    while (fread(&cal, sizeof(Calificacion), 1, fCal))
    {
        rewind(fCan);
        while (fread(&can, sizeof(Cancion), 1, fCan))
        {
            if (strcmp(can.idCancion, cal.idCancion) == 0)
            {
                int encontrado = 0;
                for (int i = 0; i < cantidadArtistas; i++)
                {
                    if (strcmp(lista[i].idArtista, can.idArtista) == 0)
                    {
                        lista[i].totalPuntos++;
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado && cantidadArtistas < 200)
                {
                    strcpy(lista[cantidadArtistas].idArtista, can.idArtista);
                    if (buscarArtistaPorId(can.idArtista, &art))
                    {
                        strcpy(lista[cantidadArtistas].nombre, art.nombre);
                    }
                    lista[cantidadArtistas].totalPuntos = 1;
                    cantidadArtistas++;
                }
                break;
            }
        }
    }

    fclose(fCal);
    fclose(fCan);

    if (cantidadArtistas == 0)
    {
        printf("No hay calificaciones registradas aun.\n");
        pausa();
        return;
    }

    int indiceMaximo = 0;
    for (int i = 1; i < cantidadArtistas; i++)
    {
        if (lista[i].totalPuntos > lista[indiceMaximo].totalPuntos)
        {
            indiceMaximo = i;
        }
    }

    printf("Artista: %s\n", lista[indiceMaximo].nombre);
    printf("Cantidad de calificaciones: %d\n", lista[indiceMaximo].totalPuntos);
    printf("\n==========================================\n");
    pausa();
}

void reporteUsuarioMasActivo()
{
    typedef struct
    {
        char nickname[30];
        int cantidad;
    }ContadorUsuario;

    ContadorUsuario lista[500] = {{0}};
    int cantidadUsuarios = 0;
    Calificacion cal;

    limpiarPantalla();
    printf("==== USUARIO MAS ACTIVO (mas calificaciones) ====\n\n");

    FILE *fCal = fopen("calificaciones.dat", "rb");
    if (!fCal)
    {
        printf("No hay calificaciones registradas aun.\n");
        pausa();
        return;
    }

    while (fread(&cal, sizeof(Calificacion), 1, fCal))
    {
        int encontrado = 0;
        for (int i = 0; i < cantidadUsuarios; i++)
        {
            if (strcmp(lista[i].nickname, cal.nicknameUsuario) == 0)
            {
                lista[i].cantidad++;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado && cantidadUsuarios < 500)
        {
            strcpy(lista[cantidadUsuarios].nickname, cal.nicknameUsuario);
            lista[cantidadUsuarios].cantidad = 1;
            cantidadUsuarios++;
        }
    }
    fclose(fCal);

    if (cantidadUsuarios == 0)
    {
        printf("No hay calificaciones registradas aun.\n");
        pausa();
        return;
    }

    int indiceMaximo = 0;
    for (int i = 1; i < cantidadUsuarios; i++)
    {
        if (lista[i].cantidad > lista[indiceMaximo].cantidad)
        {
            indiceMaximo = i;
        }
    }

    printf("Usuario: %s\n", lista[indiceMaximo].nickname);
    printf("Canciones calificadas: %d\n", lista[indiceMaximo].cantidad);
    printf("\n===================================================\n");
    pausa();
}
