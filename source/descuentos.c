#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descuentos.h"

static void agregarDescuento(Descuentos *descuentos, int *numDescuentos);
static void mostrarDescuentos(Descuentos *descuentos, int numDescuentos);
static void buscarDescuento(Descuentos *descuentos, int numDescuentos, char *id);
static void guardarDescuentos(Descuentos *descuentos, int numDescuentos, char *filename);

void menuDescuentos() {
    Descuentos *descuentos;
    int numDescuentos = 0;
    int opcion;
    char id[MAX_ID];

    descuentos = (Descuentos*)malloc(1 * sizeof(Descuentos));

    if(descuentos == NULL){
        perror("Memory allocation failed.\n");
        exit(1);
    }

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

        descuentos = (Descuentos*)realloc(descuentos, (numDescuentos+1) * sizeof(Descuentos));
    }

    for(int i = 0; i < numDescuentos; i++) {
    printf("%s-%s-%s-%s-%.2f-%s\n",
            descuentos[i].id_cod, descuentos[i].Descrip, descuentos[i].Tipo, descuentos[i].Estado,
            descuentos[i].Importe, descuentos[i].Aplicabilidad);
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
                    fgets(id, MAX_ID, stdin);
                    buscarDescuento(descuentos, numDescuentos, id);
                    break;
                case 4:
                    printf("Saliendo del programa...\n");
                    break;
                default:
                    printf("Opción no válida. Intente de nuevo.\n");
                    menuDescuentos();
            } 
        }
    } while(opcion < 1 || opcion > 4);

    fclose(file);

    guardarDescuentos(descuentos, numDescuentos, "../datos/Descuentos.txt");

    free(descuentos);
}

static void agregarDescuento(Descuentos *descuentos, int *numDescuentos) {

    Descuentos nuevoDescuento;

    printf("Ingrese el ID del descuento (máximo 10 caracteres): ");
    fgets(nuevoDescuento.id_cod, MAX_ID, stdin);
    while (getchar() != '\n');
    fflush(stdin);
    nuevoDescuento.id_cod[MAX_ID] == '\0';

    printf("Ingrese la descripción del descuento (máximo 50 caracteres): ");
    fgets(nuevoDescuento.Descrip, MAX_DESCRIP, stdin);
    while (getchar() != '\n');
    fflush(stdin);
    nuevoDescuento.Descrip[MAX_DESCRIP] == '\0';


    printf("Ingrese el tipo de descuento (codpro o cheqreg): ");
    fgets(nuevoDescuento.Tipo, MAX_TIPO, stdin);
    while (getchar() != '\n');
    fflush(stdin);
    nuevoDescuento.Tipo[MAX_TIPO] == '\0';

    printf("Ingrese el estado del descuento (activo o inactivo): ");
    fgets(nuevoDescuento.Estado, MAX_ESTADO, stdin);
    while (getchar() != '\n');
    fflush(stdin);
    nuevoDescuento.Estado[MAX_ESTADO] == '\0';

    printf("Ingrese el importe del descuento en euros: ");
    while(scanf("%f", &nuevoDescuento.Importe) != 1 || nuevoDescuento.Importe < 0){
        fflush(stdin);
        perror("Entrada no valida, intentelo de nuevo.");
    }
    fflush(stdin);

    printf("Ingrese la aplicabilidad del descuento (todos o esizon): ");
    fgets(nuevoDescuento.Aplicabilidad, MAX_APLICA, stdin);
    while (getchar() != '\n');
    fflush(stdin);
    nuevoDescuento.Aplicabilidad[MAX_APLICA] == '\0';

    descuentos = (Descuentos*)realloc(descuentos, (*numDescuentos)+1 * sizeof(Descuentos));

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
            printf("%s-%s-%s-%s-%.2f-%s\n",
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
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        perror("Error al abrir el archivo para escribir.\n");
        fclose(file);
        exit(1);
    }

    FILE *temp = fopen("../datos/descuentoTemporal.txt", "w");
    if(temp == NULL){
        perror("Error al abrir el archivo temp para escribir.\n");
        fclose(temp);
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < numDescuentos; i++) {
        fprintf(temp, "%s-%s-%s-%s-%.2f-%s\n", descuentos[i].id_cod, descuentos[i].Descrip,
                descuentos[i].Tipo, descuentos[i].Estado, descuentos[i].Importe, descuentos[i].Aplicabilidad);
    }

    remove("../datos/Descuentos.txt");
    rename("../datos/descuentoTemporal.txt", "../datos/Descuentos.txt");
    printf("Descuentos modificados correctamente.\n");

    fclose(file);
    fclose(temp);
}

int main(){
    menuDescuentos();
    return 0;
}