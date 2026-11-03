#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>


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

    if (!fCal) {
        printf("Aun no hay calificaciones registradas.\n");
        return;
    }

    Calificacion *misCals = malloc(capacidad * sizeof(Calificacion));
    if (!misCals) {
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
