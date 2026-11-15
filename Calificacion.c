#include "Calificacion.h"
#include "Auxiliares.h"
#include <stdio.h>
#include <string.h>

void calificarCancion(char *usuarioLogueado)
{
    FILE *fCan = fopen("canciones.dat", "rb+");
    FILE *fCal = fopen("calificaciones.dat", "ab");
    char tituloBuscar[100], idCancionEncontrada[10];
    Cancion can;
    Calificacion nuevaCal;
    int puntuacion;
    int encontrada = 0;

    if (!fCan || !fCal)
    {
        printf("Error al acceder a los datos.\n");
        if (fCan) fclose(fCan);
        if (fCal) fclose(fCal);
        return;
    }

    printf("\n--- Calificar Cancion ---\n");
    printf("Titulo de la cancion: ");
    fgets(tituloBuscar, 100, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

    while (fread(&can, sizeof(Cancion), 1, fCan))
    {
        if (strstr(can.titulo, tituloBuscar) != NULL)
        {
            encontrada = 1;
            strcpy(idCancionEncontrada, can.idCancion);

            printf("Calificando: %s — %.1f (actual)\n", can.titulo, can.calificacionPromedio);
            printf("Ingrese puntuacion (1-5): ");
            scanf("%d", &puntuacion);
            limpiarBuffer();

            if (puntuacion < 1 || puntuacion > 5)
            {
                printf("La puntuacion debe estar entre 1 y 5.\n");
                break;
            }

            generarIdCalificacion(nuevaCal.idRegistroCal);
            strcpy(nuevaCal.nicknameUsuario, usuarioLogueado);
            strcpy(nuevaCal.idCancion, idCancionEncontrada);
            nuevaCal.puntuacion = puntuacion;
            fwrite(&nuevaCal, sizeof(Calificacion), 1, fCal);
            fclose(fCal);

            recalcularPromedio(idCancionEncontrada);
            printf("¡Gracias por tu calificacion! \n");
            break;
        }
    }
    if (!encontrada) printf("No se encontro ninguna cancion con ese titulo.\n");

    fclose(fCan);
}

void verMisCalificaciones(char *usuarioLogueado)
{
    FILE *fCal = fopen("calificaciones.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb");
    Calificacion cal;
    Cancion can;
    int contador = 0;

    if (!fCal)
    {
        printf("Aun no has calificado ninguna cancion.\n");
        return;
    }
    if (!fCan)
    {
        printf("Error al leer canciones.\n");
        fclose(fCal);
        return;
    }

    printf("\n Mis Calificaciones — Usuario: %s\n", usuarioLogueado);
    printf("=========================================================================\n");
    printf("  %-40s | Tu nota\n", "Cancion");
    printf("==========================================================================\n");

    while (fread(&cal, sizeof(Calificacion), 1, fCal))
    {
        if (strcmp(cal.nicknameUsuario, usuarioLogueado) == 0)
        {
            contador++;
            rewind(fCan);
            char nombreCancion[100] = "Desconocida";
            while (fread(&can, sizeof(Cancion), 1, fCan))
            {
                if (strcmp(can.idCancion, cal.idCancion) == 0)
                {
                    strcpy(nombreCancion, can.titulo);
                    break;
                }
            }
            printf("  %-40s | %d/5\n", nombreCancion, cal.puntuacion);
        }
    }

    if (contador == 0) printf("Aun no has calificado ninguna cancion.\n");
    else
    {
        printf("========================================================================\n");
        printf("  Total calificaciones: %d\n", contador);
    }

    fclose(fCal);
    fclose(fCan);
}



