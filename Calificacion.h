#ifndef CALIFICACION_H_INCLUDED
#define CALIFICACION_H_INCLUDED

#include "Calificacion.h"

// ===== ESTRUCTURAS =====
typedef struct stCalificacion
{
    char idRegistroCal[10];
    char nicknameUsuario[30];
    char idCancion[10];
    int puntuacion;
} Calificacion;

// ===== PROTOTIPOS DE FUNCIONES =====

// Archivos - Calificaciones
int guardarCalificacion(Calificacion cal);
float calcularPromedioCancion(char idCancion[]);

// Auxiliares
void pausa();
void limpiarPantalla();
int generarId(char destino[], char prefijo);
int verificarLoginArtista(char id[], char pass[], Artista *resultado);
int verificarLoginUsuario(char id[], char pass[], Usuario *resultado);

#endif // CALIFICACION_H_INCLUDED
