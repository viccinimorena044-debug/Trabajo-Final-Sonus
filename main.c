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

void menuPrincipal();
void login();
void registrarse();
void menuArtista(Artista);
void agregarModificarAlbum(Artista);
void agregarModificarCancion(Artista);
void menuUsuario(Usuario);
void verCatalogoPorArtista();
void verCancionesPorAlbum();
void verInfoCancion();
void calificarCancion(Usuario);
void verMisCalificaciones(Usuario);
void reporteTop10();
void reporteAlbumesRecientes();
void reporteArtistaMasCalificado();
void reporteUsuarioMasActivo();

int main()
{
    system("chcp 65001 > nul");
    limpiarPantalla();

    printf("============================================\n");
    printf("      SISTEMA DE GESTION MUSICAL SONUS     \n");
    printf("    Trabajo Practico - Programacion I     \n");
    printf("============================================\n\n");

    menuPrincipal();
    return 0;
}

void menuPrincipal()
{
    int op;
    do
    {
        limpiarPantalla();
        printf("=========== MENU PRINCIPAL ===========\n");
        printf("  1. Iniciar Sesion\n");
        printf("  2. Registrarse\n");
        printf("  0. Salir\n");
        printf("=======================================\n");
        printf("Ingrese opcion: ");
        scanf("%d", &op);
        fflush(stdin);

        switch (op)
        {
            case 1: login(); break;
            case 2: registrarse(); break;
            case 0:
                printf("Gracias por usar Sonus. Hasta pronto!\n");
                break;
            default:
                printf("Opcion invalida!\n");
                pausa();
        }
    } while (op != 0);
}

void login()
{
    char id[10], pass[20];
    Artista art;
    Usuario usu;

    limpiarPantalla();
    printf("=========== INICIO DE SESION ===========\n");
    printf("Ingrese su ID: ");
    gets(id);

    printf("Ingrese su contrasena: ");
    for (int i = 0; i < 19; i++)
    {
        pass[i] = getch();
        if (pass[i] == 13)
        {
            pass[i] = '\0';
            break;
        }
        printf("*");
    }
    pass[19] = '\0';
    printf("\n");

    if (verificarLoginArtista(id, pass, &art))
    {
        printf("\n Bienvenido, %s!\n", art.nombre);
        pausa();
        menuArtista(art);
    }
    else if (verificarLoginUsuario(id, pass, &usu))
    {
        printf("\n Bienvenido, %s!\n", usu.nickname);
        pausa();
        menuUsuario(usu);
    }
    else
    {
        printf("\n ID o contrasena incorrectos.\n");
        pausa();
    }
}

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
            if (cant >= capacidad)
            {
                capacidad += 5;
                Calificacion *aux = realloc(misCals, capacidad * sizeof(Calificacion));
                if (aux) misCals = aux;
                else break;
            }
            misCals[cant++] = cal;
        }
    }
    fclose(fCal);

    if (cant == 0)
    {
        printf("No calificaste ninguna cancion todavia\n");
    } else
    {
        printf("--- Tus Calificaciones ---\n");
        for (int i = 0; i < cant; i++)
        {
            printf("Cancion ID: %s | Puntaje: %d/5\n", misCals[i].idCancion, misCals[i].puntuacion);
        }
    }

    free(misCals);

}
void limpiarPantalla()
{
 system("cls");
}
