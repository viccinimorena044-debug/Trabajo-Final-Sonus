#include<stdio.h>
#include "Artista.h"

int guardarArtista(const char nombreArchivo[], Artista a)
{
    FILE * archivo =fopen(nombreArchivo, "ab");

    if(archivo ==NULL)
    {
        return 0;
    }

    if(fwrite(&a, sizeof(Artista), 1, archivo)==1)
    {
        fclose(archivo);
        return 1;   //se cargo y devuelve 1 artista
    }

    fclose(archivo);
    return 0;
}

long cantidadArtistasArchivo(const char nombreArchivo[])
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    long bytes;

    if(archivo ==NULL)
    {
        return 0;
    }

    fseek(archivo, 0, SEEK_END);    //indicador al final del archivo
    bytes=ftell(archivo);   //devuelve la pos del final, osea el tamanio total en bytes

    fclose(archivo);

    if(bytes< 0)
    {
        return -1;
    }

    return bytes/sizeof(Artista);
}

int generarId(char destino[], char prefijo) //destino [] arr donde esta el ID- prefijo es la letra q identidica el tipo de registro
{
    int cantidad = cantidadArtistasArchivo("artistas.dat");

    if(prefijo != 'A' || cantidad < 0 || cantidad >= 999) //si no es el ID de A, o la cant no es suf. y evitar que sea un ID > 3
    {
        return 0;
    }

    int numero = cantidad + 1;

    destino[0] = prefijo;
    destino[1] = '0' + numero / 100;
    destino[2] = '0' + (numero / 10) % 10;
    destino[3] = '0' + numero % 10;
    destino[4] = '\0';  //no olvidar el caracner fin de cadena

    return 1;
}

void mostrarArtistas(const char nombreArchivo[])
{
    FILE *archivo= fopen(nombreArchivo, "rb");
    Artista a;

    if(archivo ==NULL)
    {
        printf("\nNo hay artistas cargados");
        return;
    }

    while(fread(&a, sizeof(Artista), 1, archivo)==1)
    {
        printf("\nID: %s", a.idArtista);
        printf("\nNombre: %s", a.nombre);
        printf("\nGenero: %s", a.generoPrincipal);
    }
    fclose(archivo);
}
