#include <stdio.h>
#include <string.h>
#include "auxiliares.h"

void pausa()
{
    printf("\nPresione ENTER para continuar...");
    getchar();
    fflush(stdin);
}

void limpiarPantalla()
{
    system("cls");
}

int generarId(char destino[], char prefijo)
{
    char nombreArch[30];
    sprintf(nombreArch, "%c_contador.txt", prefijo);
    FILE *arch = fopen(nombreArch, "r");
    int num = 1;
    if (arch)
    {
        fscanf(arch, "%d", &num);
        fclose(arch);
    }
    sprintf(destino, "%c%09d", prefijo, num);
    arch = fopen(nombreArch, "w");
    fprintf(arch, "%d", num + 1);
    fclose(arch);
    return num;
}

int verificarLoginArtista(char id[], char pass[], Artista *resultado)
{
    FILE *arch = fopen("artistas.dat", "rb");
    if (!arch) return 0;
    while (fread(resultado, sizeof(Artista), 1, arch))
    {
        if (strcmp(resultado->idArtista, id) == 0 &&
            strcmp(resultado->contrasenia, pass) == 0)
        {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}

int verificarLoginUsuario(char id[], char pass[], Usuario *resultado)
{
    FILE *arch = fopen("usuarios.dat", "rb");
    if (!arch) return 0;
    while (fread(resultado, sizeof(Usuario), 1, arch))
    {
        if (strcmp(resultado->idUsuario, id) == 0 &&
            strcmp(resultado->contrasenia, pass) == 0)
        {
            fclose(arch);
            return 1;
        }
    }
    fclose(arch);
    return 0;
}
