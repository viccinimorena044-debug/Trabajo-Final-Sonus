#include "Auxiliares.h"
#include <stdio.h>
#include <string.h>


// Limpia lo que queda en el buffer del teclado
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Pausa antes de volver al menu
void pausa()
{
    printf("\nPresione Enter para continuar...");
    limpiarBuffer();
}


int construirId (char *destino, char prefijo, int numero, int anchoTotal)
{
    destino[0]= prefijo;
    destino[1]= '0';
    destino[2]= '0';
    destino[1 + anchoTotal] = '\0';

    for (int i =0; i <numero; i++)
    {
        if (destino[2] == '9')
        {
            destino[2] = '0';
            destino[1]++;
        }
        else
        {
            destino[2]++;
        }
    }
}



// Genera ID automatico para Artista
int generarIdArtista(char *destino)
{
    FILE *archivo= fopen("artistas.dat", "rb");
    int contador= 0;
    Artista a;

    if (!archivo)
    {
        printf("\nNo se pudo abrir el archivo");
        return 0;
    }

    while (fread(&a, sizeof(Artista), 1, archivo)) contador++;
    fclose(archivo);

    if(contador >=99)
    {
        printf("\nLimite de ID artistas");
        return 0;
    }

    construirId(destino, 'A', contador + 1, 2);
    return 1;
}


// Genera ID automatico para Usuario
int generarIdUsuario(char *destino)
{
    FILE *archivo = fopen("usuarios.dat", "rb");
    int contador = 0;
    Usuario u;
    if (!archivo)
    {
        printf("\nNo se pudo abrir el archivo");
        return 0;
    }

    while (fread(&u, sizeof(Usuario), 1, archivo)) contador++;
        fclose(archivo);

    if(contador>=99)
    {
        printf("\nLimite de ID usuarios");
        return 0;
    }

    construirId(destino, 'U', contador + 1, 2);
    return 1;
}

// Genera ID automatico para album
int generarIdAlbum(char *destino)
{
    FILE *archivo = fopen("albumes.dat", "rb");
    int contador = 0;
    Album a;
    if (!archivo)
    {
        printf("\nNo se pudo abrir el archivo");
        return 0;
    }
        while (fread(&a, sizeof(Album), 1, archivo)) contador++;
        fclose(archivo);

    if(contador>=99)
    {
        printf("\nLimite de ID albumes");
        return 0;
    }

    construirId(destino, 'L', contador + 1, 2);
    return 1;
}


// Genera ID automatico para Cancion
int generarIdCancion(char *destino)
{
    FILE *archivo = fopen("canciones.dat", "rb");
    int contador = 0;
    Cancion c;
    if (!archivo)
    {
        printf("\nNo se pudo abrir el archivo");
        return 0;
    }
        while (fread(&c, sizeof(Cancion), 1, archivo)) contador++;
        fclose(archivo);

        if(contador >=99)
        {
            printf("\nLimite de ID canciones");
            return 0;
        }

    construirId(destino, 'C', contador + 1, 2);
    return 1;
}


// Genera ID automatico para Calificacion
int generarIdCalificacion(char *destino)
{
    FILE *archivo = fopen("calificaciones.dat", "rb");
    int contador = 0;
    Calificacion c;
    if (!archivo)
    {
        printf("\nNo se pudo abrir el archivo");
        return 0;
    }

        while (fread(&c, sizeof(Calificacion), 1, archivo)) contador++;
        fclose(archivo);

    if(contador>=99)
    {
        printf("\nLimite de ID calificaciones");
        return 0;
    }

    construirId(destino, 'I', contador + 1, 2);
    return 1;
}


// Verifica si un album ya existe para ese artista
int existeAlbumPorTituloYArtista(const char *titulo, const char *idArtista, char *idEncontrado)
{
    FILE *archivo = fopen("albumes.dat", "rb");
    Album a;
    int existe = 0;
    if (!archivo) return 0;
    while (fread(&a, sizeof(Album), 1, archivo))
    {
        if (strcmp(a.titulo, titulo) == 0 && strcmp(a.artista.idArtista, idArtista) == 0)
        {
            existe = 1;
            if (idEncontrado) strcpy(idEncontrado, a.idAlbum);
            break;
        }
    }
    fclose(archivo);
    return existe;
}


// Recalcula el promedio de calificaciones de una cancion
void recalcularPromedio(const char *idCancion)
{
    FILE *fCal = fopen("calificaciones.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "rb+");
    Calificacion cal;
    Cancion can;
    float suma = 0;
    int cantidad = 0;

    if (!fCal || !fCan) { if(fCal)fclose(fCal); if(fCan)fclose(fCan); return; }

    while (fread(&cal, sizeof(Calificacion), 1, fCal))
    {
        if (strcmp(cal.idCancion, idCancion) == 0)
        {
            suma += cal.puntuacion;
            cantidad++;
        }
    }
    fclose(fCal);

    while (fread(&can, sizeof(Cancion), 1, fCan))
    {
        if (strcmp(can.idCancion, idCancion) == 0)
        {
            can.calificacionPromedio = (cantidad > 0) ? (suma / cantidad) : 0.0f;

            fseek(fCan, -(long)sizeof(Cancion), SEEK_CUR);
            fwrite(&can, sizeof(Cancion), 1, fCan);
            break;
        }
    }
    fclose(fCan);
}

int contarCancionesPorAlbum(const char *idAlbum)
{
    FILE *archivo = fopen("canciones.dat", "rb");
    Cancion cancion;
    int cantidad = 0;

    if (archivo == NULL)
    {
        return 0;
    }

    while (fread(&cancion, sizeof(Cancion), 1, archivo) == 1)
    {
        if (strcmp(cancion.idAlbum, idAlbum) == 0)
        {
            cantidad++;
        }
    }

    fclose(archivo);
    return cantidad;
}
