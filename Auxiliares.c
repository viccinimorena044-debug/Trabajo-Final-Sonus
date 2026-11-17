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


void construirId  (char *destino, const char *prefijo, int numero, int anchoTotal)
{
    strcpy(destino, prefijo);

    char numStr[20];
    int i = 0;
    int temp = numero;

    // Extraer los digitos del numero al reves
    if (temp == 0)
    {
        numStr[i++] = '0';
    } else {
        while (temp > 0) {
            numStr[i++] = (temp % 10) + '0';
            temp /= 10;
        }
    }
    numStr[i] = '\0';

    int cantDigitos = i;
    int cerosFaltantes = anchoTotal - cantDigitos;

    // Agregar los ceros a la izquierda necesarios
    int pos = strlen(destino);
    for (int c = 0; c < cerosFaltantes; c++) {
        destino[pos++] = '0';
    }
    destino[pos] = '\0';

    // Agregar los digitos en el orden correcto invirtiendolos
    for (int j = cantDigitos - 1; j >= 0; j--) {
        destino[pos++] = numStr[j];
    }
    destino[pos] = '\0';
}


// Genera ID automatico para Artista
void generarIdArtista(char *destino)
{
    FILE *archivo= fopen("artistas.dat", "rb");
    int contador= 0;
    Artista a;

    if (archivo)
    {
        while (fread(&a, sizeof(Artista), 1, archivo)) contador++;
        fclose(archivo);
    }
    construirId(destino, "A", contador + 1, 9);
}


// Genera ID automatico para Usuario
void generarIdUsuario(char *destino)
{
    FILE *archivo = fopen("usuarios.dat", "rb");
    int contador = 0;
    Usuario u;
    if (archivo)
    {
        while (fread(&u, sizeof(Usuario), 1, archivo)) contador++;
        fclose(archivo);
    }

    construirId(destino, "U", contador + 1, 9);
}


// Genera ID automatico para album
void generarIdAlbum(char *destino)
{
    FILE *archivo = fopen("albumes.dat", "rb");
    int contador = 0;
    Album a;
    if (archivo)
    {
        while (fread(&a, sizeof(Album), 1, archivo)) contador++;
        fclose(archivo);
    }

    construirId(destino, "L", contador + 1, 9);
}


// Genera ID automatico para Cancion
void generarIdCancion(char *destino)
{
    FILE *archivo = fopen("canciones.dat", "rb");
    int contador = 0;
    Cancion c;
    if (archivo)
    {
        while (fread(&c, sizeof(Cancion), 1, archivo)) contador++;
        fclose(archivo);
    }
    construirId(destino, "C", contador + 1, 9);
}


// Genera ID automatico para Calificacion
void generarIdCalificacion(char *destino)
{
    FILE *archivo = fopen("calificaciones.dat", "rb");
    int contador = 0;
    Calificacion c;
    if (archivo)
    {
        while (fread(&c, sizeof(Calificacion), 1, archivo)) contador++;
        fclose(archivo);
    }
        construirId(destino, "CAL", contador + 1, 7);
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
