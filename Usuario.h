#ifndef USUARIO_H
#define USUARIO_H

#include "Estructuras.h"

int loginUsuario(char *nicknameSalida);

Usuario cargar1Usuario();
int guardarUsuario(const char nombreArchivo[], Usuario u);
void registrarUsuario();

void menuUsuario(char *nicknameUsuario);
void verCatalogoPorArtista();
void verCancionesPorAlbum();
void verInfoCancion();

#endif
