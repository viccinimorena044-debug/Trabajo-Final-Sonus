#include <stdio.h>

int main()
{
    int opcion;

    while (1)
    {
        menuPrincipal();
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

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
                printf("  ¡Gracias por usar Sonus 2.0! \n");
                printf("  Saliendo del sistema...\n");
                printf("=========================================\n");
                return 0;
            default:
                printf("\n Opción inválida. Intente nuevamente.\n");
                pausa();
        }
    }
}
