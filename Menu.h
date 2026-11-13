#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "estructuras.h"

// Menú Principal
void menuPrincipal();
void iniciarSesion();
void registrarse();

// Menú Artista
void menuArtista(char *idArtista, char *nombreArtista);

// Menú Usuario
void menuUsuario(char *nicknameUsuario);

#endif
