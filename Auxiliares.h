#ifndef AUXILIARES_H_INCLUDED
#define AUXILIARES_H_INCLUDED

#include "artista.h"
#include "usuario.h"

void pausa();
void limpiarPantalla();
int generarId(char destino[], char prefijo);
int verificarLoginArtista(char id[], char pass[], Artista *resultado);
int verificarLoginUsuario(char id[], char pass[], Usuario *resultado);

#endif
