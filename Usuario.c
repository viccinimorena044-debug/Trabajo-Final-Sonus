#include <stdio.h>
#include "Usuario.h"
#include <string.h>

int guardarUsuario(const char nombreArchivo[], Usuario u)
{
    FILE *archivo= fopen(nombreArchivo, "ab");

    if(archivo ==NULL)
    {
        return 0;
    }

    if(fwrite(&u, sizeof(Usuario), 1, archivo)==1)
    {
        fclose(archivo);
        return 1;
    }

    fclose(archivo);

    return 0;
}

void menuUsuario(Usuario usu)
{
    char opcion[20];
    int op= -1;

    do
    {
        printf("\n\n  ---MENU USUARIOS---");
        printf("\nIngreso como: %s", usu.nickname);
        printf("\n\n1.Ver catalogo por atista");
        printf("\n2. Ver canciones por album");
        printf("\n3. Ver informacion de cancion");
        printf("\n4. Calificar cancion");
        printf("\n5. Ver calificaciones");

        printf("\n\n   ---REPORTES--- ");
        printf("\n6. TOP 10 canciones");
        printf("\n7. Albumes recientes");
        printf("\n8. Artista mas calificado");
        printf("\n9. Usuario mas activo");
        printf("\n0. Cerrar sesion");
        printf("\nIngrese una opcion: ");



        ///

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

        else if(strcmp(opcion, "7\n")==0)
            op= 7;

        else if(strcmp(opcion, "8\n")==0)
            op= 8;

        else if(strcmp(opcion, "9\n")==0)
            op= 9;

        else if(strcmp(opcion, "0\n")==0)
            op= 0;

        else
            op= -1;

        switch(op)
        {
            case 1:
            {

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

            case 7:
            {

                break;
            }

            case 8:
            {

                break;
            }

            case 9:
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
    }while(op!=0);

}
