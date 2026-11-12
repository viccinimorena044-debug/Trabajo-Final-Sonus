#include <stdio.h>
#include <string.h>
#include "Usuario.h"
#include "Auxiliares.h"

Usuario cargar1Usuario()
{
    Usuario u = {0};
    printf("\nIngrese nickname: ");
    scanf(" %29[^\n]", u.nickname);
    printf("\nIngrese email: ");
    scanf(" %49[^\n]", u.email);
    printf("\nIngrese contrasenia: ");
    scanf(" %19[^\n]", u.contrasenia);
    return u;
}

int guardarUsuario(const char nombreArchivo[], Usuario u)
{
    FILE *archivo = fopen(nombreArchivo, "ab");
    if(archivo == NULL) return 0;
    if(fwrite(&u, sizeof(Usuario), 1, archivo) == 1)
    {
        fclose(archivo);
        return 1;
    }
    fclose(archivo);
    return 0;
}

void registrarUsuario()
{
    Usuario u = cargar1Usuario();
    limpiarBuffer();

    if(u.nickname[0] == '\0' || u.contrasenia[0] == '\0')
    {
        printf("\nDatos de usuario incompletos.\n");
        return;
    }

    generarIdUsuario(u.idUsuario);
    if(u.idUsuario[0] == '\0')
    {
        printf("\nNo se pudo generar el ID o se alcanzo el limite de usuarios.\n");
        return;
    }

    if(guardarUsuario("usuarios.dat", u) == 1)
    {
        printf("\nUsuario registrado. ID: %s\n", u.idUsuario);
    }
    else
    {
        printf("\nNo se pudo guardar el usuario.\n");
    }
}

int loginUsuario(char *nicknameSalida)
{
    FILE *archivo = fopen("usuarios.dat", "rb");
    Usuario u;
    char nicknameIngresado[30];
    char contraseniaIngresada[20];

    if(archivo == NULL)
    {
        printf("\nNo hay usuarios registrados.\n");
        return 0;
    }

    printf("\nNickname: ");
    int resultadoN = scanf(" %29[^\n]", nicknameIngresado);
    printf("\nContrasenia: ");
    int resultadoC = scanf(" %19[^\n]", contraseniaIngresada);
    limpiarBuffer();

    if(resultadoN != 1 || resultadoC != 1)
    {
        fclose(archivo);
        return 0;
    }

    while(fread(&u, sizeof(Usuario), 1, archivo) == 1)
    {
        if(strcmp(u.nickname, nicknameIngresado) == 0 &&
           strcmp(u.contrasenia, contraseniaIngresada) == 0)
        {
            strcpy(nicknameSalida, u.nickname);
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    printf("\nNickname o contrasenia incorrectos.\n");
    return 0;
}
