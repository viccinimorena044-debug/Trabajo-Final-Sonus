#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "time.h"

#include "reportes.h"
#include "estructuras.h"
#include "Artista.h"
#include "auxiliares.h"

void reporteTop10()
{
    typedef struct
    {
        char titulo[100];
        char artista[50];
        float promedio;
    } TopCancion;

    TopCancion lista[500], temp;
    int n = 0, i, j;
    Cancion can;
    Artista art;

    limpiarPantalla();
    printf("========== TOP 10 CANCIONES ==========\n");
    printf("========================================\n");

    FILE *fCan = fopen("canciones.dat", "rb");
    if (!fCan)
    {
        printf("No hay canciones cargadas.\n");
        pausa();
        return;
    }

    while (n < 500 && fread(&can, sizeof(Cancion), 1, fCan))
    {
        strcpy(lista[n].titulo, can.titulo);
        if (buscarArtistaPorId("artistas.dat",can.idArtista, &art))
        {
            strcpy(lista[n].artista, art.nombre);
        }else
        {
            strcpy(lista[n].artista, "Desconocido");
        }
        lista[n].promedio = can.calificacionPromedio;
        n++;
    }
    fclose(fCan);

    // Ordenar de mayor a menor promedio
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(lista[j].promedio < lista[j+1].promedio)
            {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    // Mostrar solo las primeras 10
    if(n == 0)
    {
        printf("No hay canciones para mostrar.\n");
    }else
    {
        int mostrar = (n < 10) ? n : 10;
        for(i = 0; i < mostrar; i++)
        {
            printf("%2d. %-30s — %-20s %.2f\n",
                   i+1, lista[i].titulo, lista[i].artista, lista[i].promedio);
        }
    }
    printf("========================================\n");
    pausa();
}

/// ==================================================
/// 17. REPORTE: ÁLBUMES RECIENTES
/// ==================================================
void reporteAlbumesRecientes()
{
    typedef struct
    {
        char titulo[100];
        char artista[50];
        int anio;
    } AlbumReciente;

    AlbumReciente lista[500], temp;
    int n = 0, i, j;
    Album alb;

    limpiarPantalla();
    printf("======= ALBUMES MAS RECIENTES =======\n");
    printf("========================================\n");

    FILE *fAlb = fopen("albumes.dat", "rb");
    if (!fAlb) {
        printf("No hay albumes cargados.\n");
        pausa();
        return;
    }

time_t ahora = time(NULL);
struct tm *fecha = localtime(&ahora);
int anioActual = fecha->tm_year + 1900;

    while (n < 500 && fread(&alb, sizeof(Album), 1, fAlb))
    {
        if (alb.anioLanzamiento >= anioActual - 1 &&
            alb.anioLanzamiento <= anioActual)
        {
          strcpy(lista[n].titulo, alb.titulo);
          strcpy(lista[n].artista, alb.artista.nombre);
          lista[n].anio = alb.anioLanzamiento;
          n++;
        }
    }
    fclose(fAlb);

    // Ordenar del más nuevo al más viejo
    for(i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if(lista[j].anio < lista[j+1].anio)
            {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    if (n == 0)
    {
        printf("No hay albumes para mostrar.\n");
    }else
    {
        printf("Del mas reciente al mas antiguo:\n\n");
        for (i = 0; i < n; i++)
        {
            printf("%4d | %-30s — %s\n",
                   lista[i].anio, lista[i].titulo, lista[i].artista);
        }
    }
    printf("========================================\n");
    pausa();
}

// ==================================================
// 18. REPORTE: ARTISTAS MÁS CALIFICADOS
// ==================================================
void reporteArtistaMasCalificado()
{
    typedef struct
    {
        char idArtista[10];
        char nombre[50];
        int cantidad;
    } ArtistaCalificado;

    ArtistaCalificado lista[500] = {0};
    ArtistaCalificado temp;

    int nArtistas = 0;
    int i, j, encontrado;
    int encontradaCancion;

    Calificacion cal;
    Cancion can;
    Artista art;

    FILE *fCal = fopen("calificaciones.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb");

    limpiarPantalla();

    printf("==== ARTISTAS MAS CALIFICADOS ====\n");
    printf("========================================\n");

    if (!fCal || !fCan)
    {
        printf("No se pudieron abrir los archivos.\n");

        if (fCal) fclose(fCal);
        if (fCan) fclose(fCan);

        pausa();
        return;
    }

    // Recorrer todas las calificaciones
    while (fread(&cal, sizeof(Calificacion), 1, fCal))
    {
        encontradaCancion = 0;

        // Buscar la canción correspondiente
        rewind(fCan);

        while (fread(&can, sizeof(Cancion), 1, fCan))
        {
            if (strcmp(can.idCancion, cal.idCancion) == 0)
            {
                encontradaCancion = 1;
                break;
            }
        }

        if (!encontradaCancion)
            continue;

        // Buscar al artista de esa canción
        if (!buscarArtistaPorId("artistas.dat", can.idArtista, &art))
            continue;

        encontrado = 0;

        // Verificar si el artista ya está en el arreglo
        for (i = 0; i < nArtistas; i++)
        {
            if (strcmp(lista[i].idArtista, art.idArtista) == 0)
            {
                lista[i].cantidad++;
                encontrado = 1;
                break;
            }
        }

        // Si no existe, agregarlo
        if (!encontrado && nArtistas < 500)
        {
            strcpy(lista[nArtistas].idArtista, art.idArtista);
            strcpy(lista[nArtistas].nombre, art.nombre);
            lista[nArtistas].cantidad = 1;

            nArtistas++;
        }
    }

    fclose(fCal);
    fclose(fCan);

    // Ordenar de mayor a menor cantidad de calificaciones
    for (i = 0; i < nArtistas - 1; i++)
    {
        for (j = 0; j < nArtistas - i - 1; j++)
        {
            if (lista[j].cantidad < lista[j + 1].cantidad)
            {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }

    // Mostrar resultados
    if (nArtistas == 0)
    {
        printf("No hay datos para mostrar.\n");
    }
    else
    {
        for (i = 0; i < nArtistas; i++)
        {
            printf("%2d. %-25s | Calificaciones: %d\n",
                   i + 1,
                   lista[i].nombre,
                   lista[i].cantidad);
        }
    }

    printf("========================================\n");
    pausa();
}

/// ==================================================
/// 19. REPORTE: USUARIO MÁS ACTIVO
/// ==================================================
void reporteUsuarioMasActivo()
{
    typedef struct
    {
        char nickname[30];
        int cantidad;
    }UsuarioActivo;

    UsuarioActivo lista[500] = {0};
    int nUsuarios = 0, i, j, encontrado;
    Calificacion cal;

    limpiarPantalla();
    printf("==== USUARIOS MAS ACTIVOS ====\n");
    printf("(Cantidad de calificaciones realizadas)\n");
    printf("========================================\n");

    FILE *fCal = fopen("calificaciones.dat", "rb");
    if (!fCal) {
        printf("No hay calificaciones registradas.\n");
        pausa();
        return;
    }

    while (nUsuarios < 500 && fread(&cal, sizeof(Calificacion), 1, fCal)) {
        encontrado = 0;
        for (i = 0; i < nUsuarios; i++) {
            if (strcmp(lista[i].nickname, cal.nicknameUsuario) == 0) {
                lista[i].cantidad++;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(lista[nUsuarios].nickname, cal.nicknameUsuario);
            lista[nUsuarios].cantidad = 1;
            nUsuarios++;
        }
    }
    fclose(fCal);

    // Ordenar de mayor a menor cantidad
    UsuarioActivo temp;
    for (i = 0; i < nUsuarios - 1; i++) {
        for (j = 0; j < nUsuarios - i - 1; j++) {
            if (lista[j].cantidad < lista[j+1].cantidad) {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    if (nUsuarios == 0) {
        printf("No hay datos para mostrar.\n");
    } else {
        for (i = 0; i < nUsuarios; i++) {
            printf("%2d. %-20s | Calificaciones: %d\n",
                   i+1, lista[i].nickname, lista[i].cantidad);
        }
    }
    printf("========================================\n");
    pausa();
}
