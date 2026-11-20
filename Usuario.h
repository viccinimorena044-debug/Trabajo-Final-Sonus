#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include "Estructuras.h"

int loginUsuario(char *nicknameSalida);
int buscarUsuario (char nickname[]);
void registrarUsuario();
void verCatalogoPorArtista();
void verCancionesPorAlbum();
void verInfoCancion();

#endif
