#ifndef CALIFICACION_H_INCLUDED
#define CALIFICACION_H_INCLUDED

typedef struct stCalificacion
{
    char idRegistroCal[10];
    char nicknameUsuario[30];
    char idCancion[10];
    int puntuacion;
} Calificacion;

int guardarCalificacion(Calificacion cal);
float calcularPromedioCancion(char idCancion[]);

#endif
