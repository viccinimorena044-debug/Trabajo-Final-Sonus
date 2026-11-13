
#ifndef USUARIO_H
#define USUARIO_H

#include "Estructuras.h"

// ===== INICIO DE SESION =====
int loginUsuario(char *nicknameSalida);

// ===== REGISTRO =====
Usuario cargar1Usuario();
int guardarUsuario(const char nombreArchivo[], Usuario u);
void registrarUsuario();

// ===== MENU USUARIO =====
void menuUsuario(char *nicknameUsuario);

// ===== CONSULTAS =====
void verCatalogoPorArtista();
void verCancionesPorAlbum();
void verInfoCancion();

// ===== AUXILIARES =====
void pausa();
void limpiarPantalla();
int generarId(char destino[], char prefijo);

#endif
