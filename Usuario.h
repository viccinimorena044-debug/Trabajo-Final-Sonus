#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct stUsuario
{
    char idUsuario[10];
    char email[50];
    char contrasenia[20];
    char nickname[30];
} Usuario;

int guardarUsuario(Usuario u);
int buscarUsuarioPorId(char id[], Usuario *u);
int buscarUsuarioPorNickname(char nick[], Usuario *u);

#endif
