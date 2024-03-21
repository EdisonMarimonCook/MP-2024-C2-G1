#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descuentos.h"

static void agregarDescuento(Descuentos *descuentos, int *numDescuentos);
static void mostrarDescuentos(Descuentos *descuentos, int numDescuentos);
static void buscarDescuento(Descuentos *descuentos, int numDescuentos, char *id);
static void guardarDescuentos(Descuentos *descuentos, int numDescuentos, char *filename);

void menuDescuentos() {
    Descuentos descuentos[100]; // Cambiar con malloc
    int numDescuentos = 0;
    int opcion;
    char id[11];

    FILE *file = fopen("../datos/Descuentos.txt", "r");
    if (file == NULL){
        perror("Archivo no encontrado o no se pudo abrir para lectura.\n");
        return;
    }

    while (fscanf(file, "%10s-%50s-%7s-%7s-%f-%7s\n", descuentos[numDescuentos].id_cod,
                  descuentos[numDescuentos].Descrip, descuentos[numDescuentos].Tipo,
                  descuentos[numDescuentos].Estado, &descuentos[numDescuentos].Importe,
                  descuentos[numDescuentos].Aplicabilidad) == 6) {
        (numDescuentos)++;
    }

    do {
        
        printf("\nMenú de Descuentos\n");
        printf("1. Agregar descuento\n");
        printf("2. Mostrar descuentos\n");
        printf("3. Buscar descuento\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");

        if(scanf("%i", &opcion) != 1 || opcion < 1 || opcion > 4){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");

        }else{

            switch(opcion) {
                case 1:
                    agregarDescuento(descuentos, &numDescuentos);
                    break;
                case 2:
                    mostrarDescuentos(descuentos, numDescuentos);
                    break;
                case 3:
                    printf("Introduzca el ID del descuento a buscar: ");
                    scanf("%s", id);
                    buscarDescuento(descuentos, numDescuentos, id);
                    break;
                case 4:
                    printf("Saliendo del programa...\n");
                    break;
                default:
                    printf("Opción no válida. Intente de nuevo.\n");
            } 
        }
    } while(opcion < 1 || opcion > 4);

    fclose(file);

    guardarDescuentos(descuentos, numDescuentos, "../datos/Descuentos.txt");
}

static void agregarDescuento(Descuentos *descuentos, int *numDescuentos) {
    if(*numDescuentos >= 100) {
        printf("Ya se ha alcanzado el máximo de descuentos.\n");
        return;
    }

    Descuentos nuevoDescuento;

    printf("Ingrese el ID del descuento (máximo 10 caracteres): ");
    scanf("%s", nuevoDescuento.id_cod);
    while (getchar() != '\n');

    printf("Ingrese la descripción del descuento (máximo 50 caracteres): ");    // aqui hay error, no deja terminar y borra lo siguiente
    scanf("%s", nuevoDescuento.Descrip);
    while (getchar() != '\n');

    printf("Ingrese el tipo de descuento (codpro o cheqreg): ");
    scanf("%s", nuevoDescuento.Tipo);
    while (getchar() != '\n');

    printf("Ingrese el estado del descuento (activo o inactivo): ");
    scanf("%s", nuevoDescuento.Estado);
    while (getchar() != '\n');

    printf("Ingrese el importe del descuento en euros: ");
    scanf("%f", &nuevoDescuento.Importe);
    while (getchar() != '\n');

    printf("Ingrese la aplicabilidad del descuento (todos o esizon): ");
    scanf("%s", nuevoDescuento.Aplicabilidad);
    while (getchar() != '\n');

    descuentos[*numDescuentos] = nuevoDescuento;
    (*numDescuentos)++;

    printf("Descuento agregado correctamente.\n");
}

static void mostrarDescuentos(Descuentos *descuentos, int numDescuentos) {
    printf("Descuentos disponibles:\n");
    for(int i = 0; i < numDescuentos; i++) {
        printf("ID: %s, Descripción: %s, Tipo: %s, Estado: %s, Importe: %.2f, Aplicable: %s\n",
               descuentos[i].id_cod, descuentos[i].Descrip, descuentos[i].Tipo, descuentos[i].Estado,
               descuentos[i].Importe, descuentos[i].Aplicabilidad);
    }
}

static void buscarDescuento(Descuentos *descuentos, int numDescuentos, char *id) {
    int encontrado = 0;
    for(int i = 0; i < numDescuentos; i++) {
        if(strcmp(descuentos[i].id_cod, id) == 0) {
            printf("Descuento encontrado:\n");
            printf("ID: %s, Descripción: %s, Tipo: %s, Estado: %s, Importe: %.2f, Aplicable: %s\n",
                   descuentos[i].id_cod, descuentos[i].Descrip, descuentos[i].Tipo, descuentos[i].Estado,
                   descuentos[i].Importe, descuentos[i].Aplicabilidad);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado)
        printf("No se encontró ningún descuento con ese ID.\n");
}

static void guardarDescuentos(Descuentos *descuentos, int numDescuentos, char *filename) { //aqui no guarda bien los archivos (borra los antiguos)
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error al abrir el archivo para escribir.\n");
        return;
    }

    for (int i = 0; i < numDescuentos; i++) {
        fprintf(file, "%s-%s-%s-%s-%.2f-%s\n", descuentos[i].id_cod, descuentos[i].Descrip,
                descuentos[i].Tipo, descuentos[i].Estado, descuentos[i].Importe, descuentos[i].Aplicabilidad);
    }

    fclose(file);
}

int main(){
    menuDescuentos();
    return 0;
}