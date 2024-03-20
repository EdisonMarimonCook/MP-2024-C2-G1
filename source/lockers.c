
#include "lockers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void modificarInformacion(tLockers *lock, int numLockers) {
    char idBuscar[IDLK];
    printf("Ingrese el ID del locker que desea modificar: ");
    scanf("%s", idBuscar);

    for (int i = 0; i < numLockers; i++) {
        if (strcmp(lock[i].ID_Locker, idBuscar) == 0) {
            printf("Ingrese la nueva información del locker:\n");
            printf("Ubicacion: ");
            scanf("%s", lock[i].Ubicacion);
            printf("Provincia: ");
            scanf("%s", lock[i].Provincia);
            printf("Poblacion: ");
            scanf("%s", lock[i].Poblacion);
            printf("Compartimentos totales: ");
            scanf("%s", lock[i].Compartimentos_totales);
            printf("Compartimentos ocupados: ");
            scanf("%s", lock[i].Compartimentos_ocupados);
            break;
        }
    }
}

void guardarModificaciones(tLockers *lock, int numLockers) {
    FILE *f = fopen("Lockers.txt", "w");
    if (f == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        exit(1);
    }

    for (int i = 0; i < numLockers; i++) {
        fprintf(f, "%s-%s-%s-%s-%s-%s\n", lock[i].ID_Locker, lock[i].Ubicacion, lock[i].Provincia,
                lock[i].Poblacion, lock[i].Compartimentos_totales, lock[i].Compartimentos_ocupados);
    }

    fclose(f);
}
