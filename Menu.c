#include "Menu.h"
#include "Auxiliares.h"
#include "Artista.h"
#include "Usuario.h"
#include "Reportes.h"
#include "Calificacion.h"
#include <stdio.h>
#include <string.h>

// =====================================================
// MENÚ PRINCIPAL DEL SISTEMA
// =====================================================
void menuPrincipal()
{
    printf("\n");
    printf("==========================================\n");
    printf("            SONUS 2.0                     \n");
    printf("   Sistema de Gestion Musical             \n");
    printf("==========================================\n");
    printf("  1. Iniciar Sesion                       \n");
    printf("  2. Registrarse                          \n");
    printf("  3. Salir del Sistema                    \n");
    printf("==========================================\n");
}

// =====================================================
// INICIO DE SESIÓN
// =====================================================
void iniciarSesion()
{
    int tipo;
    char idArtista[11], nombreArtista[50], nickname[30];

    printf("\n--- INICIO DE SESION ---\n");
    printf("Que tipo de cuenta tienes?\n");
    printf("  1.  Soy Artista\n");
    printf("  2.  Soy Usuario\n");
    printf("Seleccione una opcion: ");
    if(scanf("%d", &tipo)==1)
    {
        limpiarBuffer();
    }
    else
    {
        limpiarBuffer();
        tipo= -1;
    }

    if (tipo == 1)
    {
        if (loginArtista(idArtista, nombreArtista))
        {
            menuArtista(idArtista, nombreArtista);
        }
    }
    else if (tipo == 2)
    {
        if (loginUsuario(nickname))
        {
            menuUsuario(nickname);
        }
    }
    else
    {
        printf("Opcion invalida.\n");
    }
    pausa();
}

// =====================================================
// REGISTRO DE NUEVA CUENTA
// =====================================================
void registrarse()
{
    int tipo;

    printf("\n--- REGISTRO DE NUEVA CUENTA ---\n");
    printf("Que tipo de cuenta deseas crear?\n");
    printf("  1.  Cuenta de Artista\n");
    printf("  2.  Cuenta de Usuario\n");
    printf("Seleccione una opcion: ");
    if(scanf("%d", &tipo)==1)
    {
        limpiarBuffer();
    }
    else
    {
        limpiarBuffer();
        tipo= -1;
    }

    if (tipo == 1)
    {
        registrarArtista();
    }
    else if (tipo == 2)
    {
        registrarUsuario();
    }
    else
    {
        printf("Opcion invalida.\n");
    }
    pausa();
}

// =====================================================
// MENÚ ARTISTA
// =====================================================
void menuArtista(char *idArtista, char *nombreArtista)
{
    int opcion;
    while (1)
    {
        printf("\n");
        printf("========== MENU ARTISTA: %s ==========\n", nombreArtista);
        printf("  1. Agregar / Modificar Album\n");
        printf("  2. Agregar / Modificar Cancion\n");
        printf("  3.  Top 10 mis canciones\n");
        printf("  4.  Albumes Recientes\n");
        printf("  5.  Cerrar Sesion\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");
        if(scanf("%d", &opcion)==1)
        {
            limpiarBuffer();
        }
        else
        {
            limpiarBuffer();
            opcion= -1;
        }

        switch (opcion)
        {
            case 1: agregarModificarAlbum(idArtista, nombreArtista); break;
            case 2: agregarModificarCancion(idArtista); break;
            case 3: reporteTop10Canciones(idArtista); pausa(); break;
            case 4: reporteAlbumesRecientes(idArtista); pausa(); break;
            case 5: printf("Sesion cerrada.\n"); return;
            default: printf("Opcion invalida.\n");
        }
    }
}

// =====================================================
// MENÚ USUARIO
// =====================================================
void menuUsuario(char *nicknameUsuario)
{
    int opcion;
    while (1) {
        printf("\n");
        printf("========== MENU USUARIO: %s ==========\n", nicknameUsuario);
        printf("  1.  Ver Catalogo por Artista\n");
        printf("  2.  Ver Canciones por Album\n");
        printf("  3.  Ver Info de Cancion\n");
        printf("  4.  Calificar Cancion\n");
        printf("  5.  Ver Mis Calificaciones\n");
        printf("  6.  Top 10 Canciones\n");
        printf("  7.  Albumes Recientes\n");
        printf("  8.  Artista Mas Calificado\n");
        printf("  9.  Usuario Mas Activo\n");
        printf(" 10. Cerrar Sesion\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");

        if(scanf("%d", &opcion)==1)
        {
            limpiarBuffer();
        }
        else
        {
            limpiarBuffer();
            opcion= -1;
        }

        switch (opcion)
        {
            case 1: verCatalogoPorArtista(); pausa(); break;
            case 2: verCancionesPorAlbum(); pausa(); break;
            case 3: verInfoCancion(); pausa(); break;
            case 4: calificarCancion(nicknameUsuario); pausa(); break;
            case 5: verMisCalificaciones(nicknameUsuario); pausa(); break;
            case 6: reporteTop10Canciones(NULL); pausa(); break;
            case 7: reporteAlbumesRecientes(NULL); pausa(); break;
            case 8: reporteArtistaMasCalificado(); pausa(); break;
            case 9: reporteUsuarioMasActivo(); pausa(); break;
            case 10: printf("Sesion cerrada.\n"); return;
            default: printf("Opcion invalida.\n");
        }
    }
}
