#include <stdio.h>
#include <string.h>
#include "Artista.h"
#include "Usuario.h"
#include "Album.h"

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

long cantidadRegistros(const char nombreArchivo[], int tamanioRegistro)
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    long bytes;

    if(archivo ==NULL)
    {
        return 0;
    }

    if(fseek(archivo, 0, SEEK_END) !=0)//indicador al final del archivo
    {
        fclose(archivo);
        return -1;
    }

    bytes=ftell(archivo);   //devuelve la pos del final, osea el tamanio total en bytes

    fclose(archivo);

    if(bytes< 0 || tamanioRegistro <=0)
    {
        return -1;
    }

    return bytes/tamanioRegistro;
}

int generarId(char destino[], char prefijo) //destino [] arr donde esta el ID- prefijo es la letra q identidica el tipo de registro
{
    long cantidad;

    if(prefijo == 'A')
    {
        cantidad = cantidadRegistros("artistas.dat", sizeof(Artista));
    }
    else if(prefijo == 'U')
    {
        cantidad= cantidadRegistros("usuarios.dat", sizeof(Usuario));
    }
    else
    {
        return 0;
    }

    if(cantidad <0 || cantidad >=999)
    {
        return 0;
    }

    int numero = (int) cantidad + 1;

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

void menuArtista(Artista art)
{
    char opcion[20];
    int op= -1;

    do
    {
        printf("\n  ---MENU ARTISTA: %s---", art.nombre);
        printf("\n1. Agregar/Modificar Album");
        printf("\n2. Agregar/Modicar Cancion");
        printf("\n\n  ---REPORTES--- ");
        printf("\n3. TOP 10 Canciones");
        printf("\n4. Albunes Recientes");
        printf("\n5. Artistas Mas calificado");
        printf("\n6. USuarios mas activos");
        printf("\n0. Cerrar sesion");
        printf("\nIngrese una opcion: ");

        if(fgets(opcion, sizeof(opcion), stdin)==NULL)
            return;

        if(strcmp(opcion, "1\n")==0)
            op=1;

        else if(strcmp(opcion, "2\n")==0)
            op=2;

        else if(strcmp(opcion, "3\n")==0)
            op=3;

        else if(strcmp(opcion, "4\n")==0)

            op=4;

        else if(strcmp(opcion, "5\n")==0)
            op= 5;

        else if(strcmp(opcion, "6\n")==0)
            op= 6;


        else if(strcmp(opcion, "0\n")==0)
            op= 0;

        else
            op= -1;

        switch(op)
        {
            case 1:
            {
                agregarModificarAlbum(art);

                break;
            }

            case 2:
            {

                break;
            }

            case 3:
            {

                break;
            }

            case 4:
            {

                break;
            }

            case 5:
            {

                break;
            }

            case 6:
            {

                break;
            }

            case 0:
            {
                printf("\nSesion cerrada");
                break;
            }

            default:
                printf("\nOpcion ingresada no valida");
                break;

        }
    }while(op != 0);
}

void agregarModificarAlbum(Artista art)
{
    Album alb;
    char idBuscar[10];
    char anioTexto[20];
    int encontrado;
    int anio=0;

    printf("\n\n  ---AGREGAR o MODIFICAR ALBUM");
    printf("\nIngrese ID del album: ");

    if(fgets(idBuscar, sizeof(idBuscar), stdin)==NULL)
    {
        return;
    }

    idBuscar[strcspn(idBuscar, "\n")]='\0';

    if(strlen(idBuscar)==0 || strlen(idBuscar)>= sizeof(alb.idAlbum))
    {
        printf("\nID ingresado no valido");
        return;
    }

    encontrado = buscarAlbumPorId(idBuscar, &alb);

    if(encontrado ==1)
    {

        if(strcmp(alb.artista.idArtista, art.idArtista)!=0)
        {
            printf("\nEl album es de otro artista");
            return;
        }
        printf("\nAlbum encontrado");

    }
    else
    {
        printf("\nAgregando el nuevo album");

        strcpy(alb.idAlbum, idBuscar);
        alb.artista =art;
        alb.cantidadCanciones=0;

    }
    printf("\nIngrese el titulo: ");

    if(fgets(alb.titulo, sizeof(alb.titulo), stdin)==NULL)
    {
        return;
    }

    alb.titulo[strcspn(alb.titulo, "\n")]='\0';

    if(strlen(alb.titulo)==0)
    {
        printf("\nTitulo vacio");
        return;
    }

    printf("\nIngrese anio: ");

    if(fgets(anioTexto, sizeof(anioTexto), stdin)==NULL)
    {
        return;
    }

    anioTexto[strcspn(anioTexto, "\n")]='\0';

    if(strlen(anioTexto) != 4)
    {
        printf("\nIngrese un anio en 4 cifras");
        return;
    }

    for(int i = 0; i < 4; i++)
    {
        if(anioTexto[i] < '0' || anioTexto[i] > '9')
        {
            printf("\nAnio invalido.");
            return;
        }

        anio = anio * 10 + (anioTexto[i] - '0'); //Cada caracter se pasa a valor numericoy lo agregamos al anio

    }

    if(anio== 0)
    {
        printf("\nAnio no valido");
        return;
    }

    alb.anioLanzamiento = anio;

    if(encontrado == 1)
    {
        if(actualizarAlbum(alb) == 1)
        {
            printf("\nAlbum modificado correctamente.");
        }
        else
        {
            printf("\nNo se modifico el album");
        }
    }
    else
    {
        if(guardarAlbum(alb) == 1)
        {
            printf("\nAlbum agregado");
        }
        else
        {
            printf("\nNo se guardo el album");
        }
    }
}
