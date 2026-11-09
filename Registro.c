#include <stdio.h>
#include <string.h>
#include "Registro.h"
#include "Artista.h"
#include "Usuario.h"

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

        fgets(entrada, sizeof(entrada), stdin);

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
           registrarUsuario();
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
        if(fgets(a.nombre, sizeof(a.nombre), stdin)==NULL)
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
        a.generoPrincipal[strcspn(a.generoPrincipal, "\n")]='\0';

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

void registrarUsuario()
{
    Usuario u;

    do
    {
        printf("\nIngrese su email: ");
        if(fgets(u.email, sizeof(u.email), stdin)== NULL)
        {
            return;
        }
        u.email[strcspn(u.email, "\n")]='\0';

        if(strlen(u.email)==0)
        {
            printf("\nEl email no puede estar vacio");
        }
    }while(strlen(u.email)==0);


    do
    {
        printf("\nIngrese su nickname: ");
        if(fgets(u.nickname, sizeof(u.nickname), stdin)==NULL)
        {
            return;
        }
        u.nickname[strcspn(u.nickname, "\n")]='\0';

        if(strlen(u.nickname)==0)
        {
            printf("\nEl nickname no puede estar vacio");
        }
    }while(strlen(u.nickname)==0);


    do
    {
        printf("\nIngrese su contrasenia: ");

        if(fgets(u.contrasenia, sizeof(u.contrasenia), stdin)== NULL)
        {
            return;
        }
        u.contrasenia[strcspn(u.contrasenia, "\n")]='\0';

        if(strlen(u.contrasenia)==0)
        {
            printf("\nLa contrasenia no puede estar vacia");
        }
    }while(strlen(u.contrasenia)==0);


    if(generarId(u.idUsuario, 'U') == 0)
    {
        printf("\nNo se pudo generar el ID del usuario");
        return;
    }

    if(guardarUsuario("usuarios.dat", u) == 1)
    {
        printf("\nID del usuario registrado: %s", u.idUsuario);
    }
    else
    {
        printf("\nNo se pudo guardar el usuario");
    }

}

