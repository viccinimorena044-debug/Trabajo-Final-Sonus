#include <stdio.h>
#include <string.h>
#include "Auxiliares.h"

void limpiarBuffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void pausa()
{
    printf("\nPresione Enter para continuar...");
    limpiarBuffer();
}

long cantidadArtistas(const char nombreArchivo[])
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    long bytes;
    if(archivo == NULL) return 0;
    if(fseek(archivo, 0, SEEK_END) != 0)
    {
        fclose(archivo);
        return -1;
    }
    bytes = ftell(archivo);
    fclose(archivo);
    if(bytes < 0) return -1;
    return bytes / (long)sizeof(Artista);
}

long cantidadUsuarios(const char nombreArchivo[])
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    long bytes;
    if(archivo == NULL) return 0;
    if(fseek(archivo, 0, SEEK_END) != 0)
    {
        fclose(archivo);
        return -1;
    }
    bytes = ftell(archivo);
    fclose(archivo);
    if(bytes < 0) return -1;
    return bytes / (long)sizeof(Usuario);
}

long cantidadAlbumes(const char nombreArchivo[])
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    long bytes;
    if(archivo == NULL) return 0;
    if(fseek(archivo, 0, SEEK_END) != 0)
    {
        fclose(archivo);
        return -1;
    }
    bytes = ftell(archivo);
    fclose(archivo);
    if(bytes < 0) return -1;
    return bytes / (long)sizeof(Album);
}

long cantidadCancionesArchivo(const char nombreArchivo[])
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    long bytes;
    if(archivo == NULL) return 0;
    if(fseek(archivo, 0, SEEK_END) != 0)
    {
        fclose(archivo);
        return -1;
    }
    bytes = ftell(archivo);
    fclose(archivo);
    if(bytes < 0) return -1;
    return bytes / (long)sizeof(Cancion);
}

long cantidadCalificacionesArchivo(const char nombreArchivo[])
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    long bytes;
    if(archivo == NULL) return 0;
    if(fseek(archivo, 0, SEEK_END) != 0)
    {
        fclose(archivo);
        return -1;
    }
    bytes = ftell(archivo);
    fclose(archivo);
    if(bytes < 0) return -1;
    return bytes / (long)sizeof(Calificacion);
}

void generarIdArtista(char *destino)
{
    long cantidad = cantidadArtistas("artistas.dat");
    if(cantidad < 0 || cantidad >= 100)
    {
        destino[0] = '\0';
        return;
    }
    int numero = (int)cantidad + 1;
    destino[0] = 'A';
    destino[1] = '0' + numero / 100;
    destino[2] = '0' + (numero / 10) % 10;
    destino[3] = '0' + numero % 10;
    destino[4] = '\0';
}

void generarIdUsuario(char *destino)
{
    long cantidad = cantidadUsuarios("usuarios.dat");
    if(cantidad < 0 || cantidad >= 100)
    {
        destino[0] = '\0';
        return;
    }
    int numero = (int)cantidad + 1;
    destino[0] = 'U';
    destino[1] = '0' + numero / 100;
    destino[2] = '0' + (numero / 10) % 10;
    destino[3] = '0' + numero % 10;
    destino[4] = '\0';
}

void generarIdAlbum(char *destino)
{
    long cantidad = cantidadAlbumes("albumes.dat");
    if(cantidad < 0 || cantidad >= 100)
    {
        destino[0] = '\0';
        return;
    }
    int numero = (int)cantidad + 1;
    destino[0] = 'A';
    destino[1] = 'L';
    destino[2] = '0' + numero / 100;
    destino[3] = '0' + (numero / 10) % 10;
    destino[4] = '0' + numero % 10;
    destino[5] = '\0';
}

void generarIdCancion(char *destino)
{
    long cantidad = cantidadCancionesArchivo("canciones.dat");
    if(cantidad < 0 || cantidad >= 999)
    {
        destino[0] = '\0';
        return;
    }
    int numero = (int)cantidad + 1;
    destino[0] = 'C';
    destino[1] = '0' + numero / 100;
    destino[2] = '0' + (numero / 10) % 10;
    destino[3] = '0' + numero % 10;
    destino[4] = '\0';
}

void generarIdCalificacion(char *destino)
{
    long cantidad = cantidadCalificacionesArchivo("calificaciones.dat");
    if(cantidad < 0 || cantidad >= 999)
    {
        destino[0] = '\0';
        return;
    }
    int numero = (int)cantidad + 1;
    destino[0] = 'C';
    destino[1] = 'A';
    destino[2] = 'L';
    destino[3] = '0' + numero / 100;
    destino[4] = '0' + (numero / 10) % 10;
    destino[5] = '0' + numero % 10;
    destino[6] = '\0';
}

int existeAlbumPorTituloYArtista(const char titulo[],
                                 const char idArtista[],
                                 char idEncontrado[])
{
    FILE *archivo = fopen("albumes.dat", "rb");
    Album a;
    if(archivo == NULL) return 0;

    while(fread(&a, sizeof(Album), 1, archivo) == 1)
    {
        if(strcmp(a.titulo, titulo) == 0 &&
           strcmp(a.artista.idArtista, idArtista) == 0)
        {
            if(idEncontrado != NULL)
            {
                strcpy(idEncontrado, a.idAlbum);
            }
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}

void recalcularPromedio(const char *idCancion)
{
    FILE *fCal = fopen("calificaciones.dat", "rb");
    FILE *fCan = fopen("canciones.dat", "r+b");
    Calificacion cal;
    Cancion can;
    float suma = 0;
    int cantidad = 0;

    if(fCal == NULL || fCan == NULL)
    {
        if(fCal != NULL) fclose(fCal);
        if(fCan != NULL) fclose(fCan);
        return;
    }

    while(fread(&cal, sizeof(Calificacion), 1, fCal) == 1)
    {
        if(strcmp(cal.idCancion, idCancion) == 0)
        {
            suma += cal.puntuacion;
            cantidad++;
        }
    }
    fclose(fCal);

    while(fread(&can, sizeof(Cancion), 1, fCan) == 1)
    {
        if(strcmp(can.idCancion, idCancion) == 0)
        {
            if(cantidad > 0)
            {
                can.calificacionPromedio = suma / cantidad;
            }
            else
            {
                can.calificacionPromedio = 0;
            }
            if(fseek(fCan, -(long)sizeof(Cancion), SEEK_CUR) == 0)
            {
                if(fwrite(&can, sizeof(Cancion), 1, fCan) != 1)
                {
                    printf("\nNo se pudo actualizar el promedio.");
                }
            }
            break;
        }
    }
    fclose(fCan);
}
