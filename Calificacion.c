#include "Calificacion.h"
#include "Auxiliares.h"
#include "pila.h"
#include <stdio.h>
#include <string.h>

void calificarCancion(char *usuarioLogueado)
{
    FILE *fCan = fopen("canciones.dat", "rb+");
    FILE *fCal = fopen("calificaciones.dat", "ab");
    char idBuscado[MAX_ID], idCancionEncontrada[MAX_ID];
    Cancion can;
    Calificacion nuevaCal;
    int puntuacion;
    int fCalCerrado = 0;
    int encontrada = 0;

    if (!fCan || !fCal)
    {
        printf("Error al acceder a los datos.\n");
        if (fCan) fclose(fCan);
        if (fCal) fclose(fCal);
        return;
    }

    printf("\n--- Calificar Cancion ---\n");
    printf("ID de la cancion: ");
    fgets(idBuscado, sizeof(idBuscado), stdin);
    idBuscado[strcspn(idBuscado, "\n")] = '\0';


    while (fread(&can, sizeof(Cancion), 1, fCan))
    {
        if (strcmp(can.idCancion, idBuscado) == 0)
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
            fCalCerrado = 1;
            recalcularPromedio(idCancionEncontrada);
            printf("¡Gracias por tu calificacion! \n");
            break;
        }
    }
    if (!encontrada)
        printf("No se encontro ninguna cancion con ese id.\n");

    if (!fCalCerrado)
    {
        fclose(fCal);
    }

    fclose(fCan);
}

void verMisCalificaciones(char *usuarioLogueado)
{
    FILE *fCal = fopen("calificaciones.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb");
    Calificacion cal;
    Cancion can;
    Pila notas;
    inicpila(&notas);
    int contador = 0;

    if (!fCal)
    {
        printf("Aun no has calificado ninguna cancion.\n");


    if (fCan!=NULL)
    {
            fclose(fCan);
        }

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
        }
    }

    if (contador == 0)
    {
      printf("Aun no has calificado ninguna cancion.\n");
      fclose(fCal);
      fclose(fCan);
      return;
    }
  printf("\n Mis Calificaciones — Usuario: %s\n", usuarioLogueado);
    printf("Total de calificaciones: %d\n", contador);
    printf("=========================================================================\n");
    printf("  %-40s | Tu nota\n", "Cancion");
    printf("==========================================================================\n");

    fseek(fCal, 0, SEEK_SET);

    while (fread(&cal, sizeof(Calificacion), 1, fCal) == 1)
    {
        if (strcmp(cal.nicknameUsuario, usuarioLogueado) == 0)
        {
            if (contador <= 3)
            {
                apilar(&notas, cal.puntuacion);
            }
            contador--;

            char nombreCancion[MAX_TITULO] = "Desconocida";
            fseek(fCan, 0, SEEK_SET);

            while (fread(&can, sizeof(Cancion), 1, fCan) == 1)
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

    printf("\nTus ultimas notas, de la mas reciente a la mas antigua:\n");

    while (!pilavacia(&notas))
    {
        printf("%d/5\n", desapilar(&notas));
    }

    fclose(fCal);
    fclose(fCan);
}



