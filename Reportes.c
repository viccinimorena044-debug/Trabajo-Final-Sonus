#include "Reportes.h"
#include "Estructuras.h"
#include "Auxiliares.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estructura auxiliar para ordenar canciones
typedef struct
{
    char titulo[100];
    char artista[50];
    float promedio;
} CancionReporte;

int compararCanciones(const void *a, const void *b)
{
    float fa = ((CancionReporte*)a)->promedio;
    float fb = ((CancionReporte*)b)->promedio;
    if (fb > fa) return 1;
    if (fb < fa) return -1;
    return 0;
}

// =====================================================
// REPORTE: TOP 10 CANCIONES
// =====================================================
void reporteTop10Canciones()
{
    FILE *fCan = fopen("canciones.dat", "rb");
    FILE *fArt = fopen("artistas.dat", "rb");

    typedef struct {
        char titulo[100];
        char artista[50];
        float promedio;
    } CancionReporte;

    CancionReporte lista[500];
    int cantidad = 0;
    Cancion can;
    Artista art;

    printf("\n REPORTE: TOP 10 CANCIONES MEJOR CALIFICADAS\n");
    printf("=====================================================\n");

    if (!fCan || !fArt)
    {
        printf("No hay suficientes datos para generar el reporte.\n");
        if (fCan) fclose(fCan);
        if (fArt) fclose(fArt);
        return;
    }

    while (fread(&can, sizeof(Cancion), 1, fCan))
    {
        rewind(fArt);
        char nombreArt[50] = "Desconocido";
        while (fread(&art, sizeof(Artista), 1, fArt))
        {
            if (strcmp(art.idArtista, can.idArtista) == 0)
            {
                strcpy(nombreArt, art.nombre);
                break;
            }
        }
        if (can.calificacionPromedio > 0)
        {
            strcpy(lista[cantidad].titulo, can.titulo);
            strcpy(lista[cantidad].artista, nombreArt);
            lista[cantidad].promedio = can.calificacionPromedio;
            cantidad++;
        }
    }
    fclose(fCan);
    fclose(fArt);

    if (cantidad == 0)
    {
        printf("No hay canciones calificadas aun.\n");
        return;
    }


    for (int i = 0; i < cantidad - 1; i++)
    {
        for (int j = 0; j < cantidad - i - 1; j++)
        {
            if (lista[j].promedio < lista[j + 1].promedio)
            {
                CancionReporte temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }

    int mostrar = (cantidad < 10) ? cantidad : 10;
    printf("  #  | %-40s | %-20s |  Promedio\n", "Cancion", "Artista");
    printf("======================================================\n");
    for (int i = 0; i < mostrar; i++)
    {
        printf(" %3d | %-40s | %-20s |  %.2f\n",
               i + 1, lista[i].titulo, lista[i].artista, lista[i].promedio);
    }
    printf("\n  Total canciones en reporte: %d\n", cantidad);
}

// =====================================================
// REPORTE: ÁLBUMES MÁS RECIENTES
// =====================================================
void reporteAlbumesRecientes()
{
    FILE *fAlb = fopen("albumes.dat", "rb");
    Album alb;
    Album *lista= NULL;
    int cantidad= 0;
    int validos= 0;

    printf("\nREPORTE: ALBUMES MAS RECIENTES\n");

    if (fAlb == NULL)
    {
        printf("No se pudo abrir el archivo de albumes.\n");
        return;
    }

    while (fread(&alb, sizeof(Album), 1, fAlb) == 1)
    {
        cantidad++;
    }

    if (cantidad == 0)
    {
        printf("No hay albumes registrados.\n");
        fclose(fAlb);
        return;
    }

    fseek(fAlb, 0, SEEK_SET);
    lista = malloc(cantidad * sizeof(Album));

    if (lista == NULL)
    {
        printf("No se pudo reservar memoria.\n");
        fclose(fAlb);
        return;
    }

    // 3. Cargar los albumes en el arreglo dinamico.
    while (validos < cantidad &&
           fread(&lista[validos], sizeof(Album), 1, fAlb) == 1)
    {
        validos++;
    }

    fclose(fAlb);

    if (validos != cantidad)
    {
        printf("No se pudieron cargar todos los albumes.\n");
        free(lista);
        return;
    }

    // 4. Ordenar por insercion, del mas reciente al mas antiguo.
    for (int i = 1; i < validos; i++)
    {
        Album actual = lista[i];
        int j = i - 1;

        while (j >= 0 && lista[j].anioLanzamiento < actual.anioLanzamiento)
        {
            lista[j + 1] = lista[j];
            j--;
        }

        lista[j + 1] = actual;
    }

    printf("  %-40s | %-20s | Anio | Canciones\n", "Album", "Artista");
    mostrarAlbumesRecursivo(lista, validos, 0);
    printf("\nTotal albumes: %d\n", validos);

    free(lista);
    lista = NULL;
}

void mostrarAlbumesRecursivo(Album lista[], int validos, int i)
{
    if (i < validos)
    {
        printf("  %-40s | %-20s | %4d | %d\n",
               lista[i].titulo,
               lista[i].artista.nombre,
               lista[i].anioLanzamiento,
               contarCancionesPorAlbum(lista[i].idAlbum));

        mostrarAlbumesRecursivo(lista, validos, i + 1);
    }
}

// =====================================================
// REPORTE: ARTISTA MEJOR CALIFICADO
// =====================================================
void reporteArtistaMasCalificado()
{
    FILE *fCan = fopen("canciones.dat", "rb");
    FILE *fArt = fopen("artistas.dat", "rb");
    Artista art;
    Cancion can;

    struct DatosArtista
    {
        char id[MAX_ID];
        char nombre[50];
        float sumaPromedios;
        int cantidadCanciones;
    } listaArtistas[500];

    int cantArtistas = 0, i, j;
    int indiceMejor = -1;
    float mejorPromedio = 0;

    printf("\n REPORTE: ARTISTAS MEJOR CALIFICADOS\n");
    printf("======================================================\n");

    if (!fCan || !fArt)
    {
        printf("No hay suficientes datos para generar el reporte.\n");
        if (fCan) fclose(fCan);
        if (fArt) fclose(fArt);
        return;
    }

    // Inicializar lista de artistas
    while (fread(&art, sizeof(Artista), 1, fArt))
    {
        strcpy(listaArtistas[cantArtistas].id, art.idArtista);
        strcpy(listaArtistas[cantArtistas].nombre, art.nombre);
        listaArtistas[cantArtistas].sumaPromedios = 0;
        listaArtistas[cantArtistas].cantidadCanciones = 0;
        cantArtistas++;
    }

    // Sumar promedios por artista
    while (fread(&can, sizeof(Cancion), 1, fCan))
    {
        for (i = 0; i < cantArtistas; i++)
        {
            if (strcmp(listaArtistas[i].id, can.idArtista) == 0)
            {
                listaArtistas[i].sumaPromedios += can.calificacionPromedio;
                if (can.calificacionPromedio > 0)
                {
                    listaArtistas[i].cantidadCanciones++;
                }
                break;
            }
        }
    }

    fclose(fArt);
    fclose(fCan);

    if (cantArtistas == 0)
    {
        printf("No hay artistas registrados.\n");
        return;
    }

    printf("  %-30s | Canciones | Promedio Estelar\n", "Artista");
    printf("=================================================================================\n");

    for (i = 0; i < cantArtistas; i++)
    {
        float promedioArtista = 0;
        if (listaArtistas[i].cantidadCanciones > 0)
        {
            promedioArtista = listaArtistas[i].sumaPromedios / listaArtistas[i].cantidadCanciones;
        }
        printf("  %-30s | %10d | %.2f\n",
               listaArtistas[i].nombre,
               listaArtistas[i].cantidadCanciones,
               promedioArtista);

        if (promedioArtista > mejorPromedio && listaArtistas[i].cantidadCanciones > 0)
        {
            mejorPromedio = promedioArtista;
            indiceMejor = i;
        }
    }

    if (indiceMejor != -1)
    {
        printf("=============================================================\n");
        printf("ARTISTA MEJOR CALIFICADO: %s —  %.2f\n",
               listaArtistas[indiceMejor].nombre, mejorPromedio);
    } else
    {
        printf("=============================================================\n");
        printf("Aun no hay calificaciones suficientes.\n");
    }
}

// =====================================================
// REPORTE: USUARIO MÁS ACTIVO
// =====================================================
void reporteUsuarioMasActivo()
{
    FILE *fCal = fopen("calificaciones.dat", "rb");
    FILE *fUsu = fopen("usuarios.dat", "rb");
    Calificacion cal;
    Usuario usu;

    struct DatosUsuario
    {
        char nickname[30];
        int cantidadCalificaciones;
    } listaUsuarios[500];

    int cantUsuarios = 0, i;
    int indiceMasActivo = -1;
    int maxCalificaciones = 0;

    printf("\n REPORTE: USUARIOS MAS ACTIVOS\n");
    printf("=========================================================\n");

    if (!fCal || !fUsu)
    {
        printf("No hay suficientes datos para generar el reporte.\n");
        if (fCal) fclose(fCal);
        if (fUsu) fclose(fUsu);
        return;
    }

    // Inicializar lista de usuarios
    while (fread(&usu, sizeof(Usuario), 1, fUsu))
    {
        strcpy(listaUsuarios[cantUsuarios].nickname, usu.nickname);
        listaUsuarios[cantUsuarios].cantidadCalificaciones = 0;
        cantUsuarios++;
    }
    fclose(fUsu);

    // Contar calificaciones por usuario
    while (fread(&cal, sizeof(Calificacion), 1, fCal))
    {
        for (i = 0; i < cantUsuarios; i++)
        {
            if (strcmp(listaUsuarios[i].nickname, cal.nicknameUsuario) == 0)
            {
                listaUsuarios[i].cantidadCalificaciones++;
                break;
            }
        }
    }
    fclose(fCal);

    if (cantUsuarios == 0)
    {
        printf("No hay usuarios registrados.\n");
        return;
    }

    printf("  %-25s | Calificaciones Realizadas\n", "Usuario");
    printf("=============================================================\n");

    for (i = 0; i < cantUsuarios; i++)
    {
        printf("  %-25s | %d\n",
               listaUsuarios[i].nickname,
               listaUsuarios[i].cantidadCalificaciones);

        if (listaUsuarios[i].cantidadCalificaciones > maxCalificaciones)
        {
            maxCalificaciones = listaUsuarios[i].cantidadCalificaciones;
            indiceMasActivo = i;
        }
    }

    printf("===========================================================\n");
    if (indiceMasActivo != -1 && maxCalificaciones > 0)
    {
        printf("USUARIO MAS ACTIVO: %s — %d calificaciones\n",
               listaUsuarios[indiceMasActivo].nickname, maxCalificaciones);
    } else
    {
        printf("Aun no hay calificaciones registradas.\n");
    }
}
