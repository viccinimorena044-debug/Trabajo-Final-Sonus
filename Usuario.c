#include <stdio.h>
#include <string.h>
#include "usuario.h"

int guardarUsuario(Usuario u)
{
    FILE *arch = fopen("usuarios.dat", "ab");
    if (!arch) return 0;
    fwrite(&u, sizeof(Usuario), 1, arch);
    fclose(arch);
    return 1;
}

int buscarUsuarioPorId(char id[], Usuario *u)
{
    FILE *arch = fopen("usuarios.dat", "rb");
    if (!arch) return 0;
    while (fread(u, sizeof(Usuario), 1, arch))
    {
        if (strcmp(u->idUsuario, id) == 0)
        {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}

int buscarUsuarioPorNickname(char nick[], Usuario *u)
{
    FILE *arch = fopen("usuarios.dat", "rb");
    if (!arch) return 0;
    while (fread(u, sizeof(Usuario), 1, arch))
    {
        if (strcmp(u->nickname, nick) == 0)
        {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}
