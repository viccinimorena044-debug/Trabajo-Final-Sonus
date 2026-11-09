#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include "Artista.h"

// ===== ESTRUCTURAS =====
typedef struct stUsuario
{
    char idUsuario[10];
    char email[50];
    char contrasenia[20];
    char nickname[30];
} Usuario;

// ===== PROTOTIPOS DE FUNCIONES =====

// Archivos - Usuarios
void menuUsuario(Usuario usu);
int guardarUsuario(const char nombreArchivo[], Usuario u);
int buscarUsuarioPorId(char id[], Usuario *u);
int buscarUsuarioPorNickname(char nick[], Usuario *u);

// Auxiliares
void pausa();
void limpiarPantalla();
int generarId(char destino[], char prefijo);
//int verificarLoginArtista(char id[], char pass[], Artista *resultado);
int verificarLoginUsuario(char id[], char pass[], Usuario *resultado);

#endif // USUARIO_H_INCLUDED
