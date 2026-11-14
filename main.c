#include <stdio.h>
#include "Menu.h"
#include "Auxiliares.h"

int main()
{
    int opcion;

    while (1)
    {
        menuPrincipal();
        printf("Ingrese una opcion: ");
        if(scanf("%d", &opcion)==1)
        {
            limpiarBuffer();
        }
        else
        {
            limpiarBuffer();
            opcion= -1;
        }

        switch (opcion)
        {
            case 1:
                iniciarSesion();
                break;
            case 2:
                registrarse();
                break;
            case 3:
                printf("\n=========================================\n");
                printf("  Gracias por usar Sonus 2.0! \n");
                printf("  Saliendo del sistema...\n");
                printf("=========================================\n");
                return 0;
            default:
                printf("\n Opcion invalida. Intente nuevamente.\n");
                pausa();
                break;
        }
    }
}
