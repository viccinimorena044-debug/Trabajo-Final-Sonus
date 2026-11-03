#include <stdio.h>
#include <string.h>
#include "Registro.h"

#include "Artista.h"

void registrarse()
{
    char entrada[20];
    int op= -1;

    do
    {
        printf("\n\n---Menu Registro Sonus---");
        printf("\n1. Registrarse como Artista");
        printf("\n2. Registrarse como USuario");
        printf("\n0. Volver");
        printf("\nIngrese una opcion: ");

        fgets(entrada, sizeof(int), stdin);

        if(strcmp(entrada, "1\n")==0)
        {
            op= 1;
        }
        else if(strcmp(entrada, "2\n")==0)
        {
            op= 2;
        }
        else if(strcmp(entrada, "0\n")==0)
        {
            op= 0;
        }
        else
        {
            printf("\nOpcion invalida. Vuelva a intenatarlo");
        }

    }while(op == -1);

    switch (op)
    {
        case 1:
        {
           printf("\n---Registro de Artista---");
           registrarArtista();
           break;
        }

        case 2:
        {
           printf("\n---Registro de Usuario---");

           break;
        }

        case 0:
        {
           printf("\nVolviendo al menu principal...");
           break;
        }

        default:
            printf("\nOpcion ingresada no valida");
            break;
    }
}

void registrarArtista()
{
    Artista a;

    do
    {
        printf("\nIngrese nombre del artista: ");
        //comprobamos que se halla leido
        if(fgets(a.nombre, sizeof(Artista), stdin)==NULL)
        {
            return;
        }

        a.nombre[strcspn(a.nombre, "\n")]= '\0';

        if(strlen(a.nombre)==0) //verif q el mombre no este vacio
        {
            printf("\nNombre vacio, ingrese un nombre");
        }
    }while(strlen(a.nombre)==0);


    do
    {
        printf("\nIngrese genero musical: ");
        //comprobamos que se halla leido
        if(fgets(a.generoPrincipal, sizeof(a.generoPrincipal), stdin)==NULL)
        {
            return;
        }
        a.nombre[strcspn(a.generoPrincipal, "\n")]='\0';

        if(strlen(a.generoPrincipal)==0)   //verif q el mombre no este vacio
        {
            printf("\nGenero vacio, ingrese un genero");
        }

    }while(strlen(a.generoPrincipal)==0);


    do
    {
       printf("\nIngrese una contrasenia: ");
       if(fgets(a.contrasenia, sizeof(a.contrasenia), stdin)==NULL)
       {
           return;
       }

       a.contrasenia[strcspn(a.contrasenia, "\n")]= '\0';

       if(strlen(a.contrasenia)==0)
       {
           printf("\nContrasenia vacia, ingrese una contrasenia");
       }
    }while(strlen(a.contrasenia)==0);



    // Mostrar datos para comprobar la carga
    printf("\n---Datos del artista---");
    printf("\nNombre: %s", a.nombre);
    printf("\nGenero principal: %s", a.generoPrincipal);
    printf("\nContrasenia cargada correctamente.\n");

    if(generarId(a.idArtista, 'A')==0)
    {
        printf("\nNo se pudo generar el ID");
        return;
    }

    if(guardarArtista("artistas.dat", a)==1)
    {
        printf("\nArtista registrado");
        printf("\nID: %s", a.idArtista);
    }
    else
    {
        printf("\nNo se pudo guadar el artista");
    }
}

