#include "menu.h"
#include "auxiliares.h"
#include "artista.h"
#include "usuario.h"
#include "reportes.h"
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
    printf("   Sistema de Gestión Musical             \n");
    printf("==========================================\n");
    printf("  1. Iniciar Sesión                       \n");
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
    char idArtista[10], nombreArtista[50], nickname[30];

    printf("\n--- INICIO DE SESIÓN ---\n");
    printf("Que tipo de cuenta tienes?\n");
    printf("  1.  Soy Artista\n");
    printf("  2.  Soy Usuario\n");
    printf("Seleccione una opción: ");
    scanf("%d", &tipo);
    limpiarBuffer();

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
        printf("Opción inválida.\n");
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
    printf("Seleccione una opción: ");
    scanf("%d", &tipo);
    limpiarBuffer();

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
        printf("Opción inválida.\n");
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
        printf("========== MENÚ ARTISTA: %s ==========\n", nombreArtista);
        printf("  1. Agregar / Modificar Álbum\n");
        printf("  2. Agregar / Modificar Canción\n");
        printf("  3.  Top 10 Canciones\n");
        printf("  4.  Albumes Recientes\n");
        printf("  5.  Artista Más Calificado\n");
        printf("  6.  Usuario Más Activo\n");
        printf("  7. Cerrar Sesion\n");
        printf("========================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
            case 1: agregarModificarAlbum(idArtista, nombreArtista); break;
            case 2: agregarModificarCancion(idArtista); break;
            case 3: reporteTop10Canciones(); pausa(); break;
            case 4: reporteAlbumesRecientes(); pausa(); break;
            case 5: reporteArtistaMasCalificado(); pausa(); break;
            case 6: reporteUsuarioMasActivo(); pausa(); break;
            case 7: printf("Sesión cerrada.\n"); return;
            default: printf("Opción inválida.\n");
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
        printf("========== MENÚ USUARIO: %s ==========\n", nicknameUsuario);
        printf("  1.  Ver Catálogo por Artista\n");
        printf("  2.  Ver Canciones por Álbum\n");
        printf("  3.  Ver Info de Canción\n");
        printf("  4.  Calificar Canción\n");
        printf("  5.  Ver Mis Calificaciones\n");
        printf("  6.  Top 10 Canciones\n");
        printf("  7.  Álbumes Recientes\n");
        printf("  8.  Artista Más Calificado\n");
        printf("  9.  Usuario Más Activo\n");
        printf(" 10. Cerrar Sesión\n");
        printf("========================================\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
            case 1: verCatalogoPorArtista(); pausa(); break;
            case 2: verCancionesPorAlbum(); pausa(); break;
            case 3: verInfoCancion(); pausa(); break;
            case 4: calificarCancion(nicknameUsuario); pausa(); break;
            case 5: verMisCalificaciones(nicknameUsuario); pausa(); break;
            case 6: reporteTop10Canciones(); pausa(); break;
            case 7: reporteAlbumesRecientes(); pausa(); break;
            case 8: reporteArtistaMasCalificado(); pausa(); break;
            case 9: reporteUsuarioMasActivo(); pausa(); break;
            case 10: printf("Sesión cerrada.\n"); return;
            default: printf("Opción inválida.\n");
        }
    }
}
