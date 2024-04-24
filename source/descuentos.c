#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descuentos.h"

static void agregarDescuento(Descuentos *descuentos, int *numDescuentos);
static void buscarDescuento(Descuentos *descuentos, int numDescuentos, char *id);
static void eliminarDescuento(Descuentos *descuentos, int *numDescuentos, char *id);
static void mostrarDescuentos(Descuentos *descuentos, int numDescuentos);

void menuDescuentos() {
    Descuentos *descuentos;
    int numDescuentos = 0;
    int opcion;
    char id[MAX_ID];
    char linea[MAX_LIN_FICH_DESC];

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

    while (fgets(linea, sizeof(linea), file)){
        sscanf(linea, "%[^-]-%[^-]-%[^-]-%[^-]-%f-%[^\n]\n", descuentos[numDescuentos].id_cod,
                descuentos[numDescuentos].Descrip, descuentos[numDescuentos].Tipo,
                descuentos[numDescuentos].Estado, &descuentos[numDescuentos].Importe,
                descuentos[numDescuentos].Aplicabilidad);

        numDescuentos++;

        descuentos = (Descuentos*)realloc(descuentos, (numDescuentos+1) * sizeof(Descuentos));
    }

    printf("\nMenú de Descuentos\n\n");
    mostrarDescuentos(descuentos, numDescuentos);

    do {
        
        printf("1. Agregar descuento\n");
        printf("2. Eliminar descuento\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");

        if(scanf("%i", &opcion) != 1 || opcion < 1 || opcion > 3){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "Entrada no valida.\n\n");

        }else{

            switch(opcion) {
                case 1:
                    agregarDescuento(descuentos, &numDescuentos);
                    break;
                case 2:
                    printf("Introduzca el ID del descuento a eliminar: ");
                    while(getchar() != '\n');
                    fgets(id, MAX_ID, stdin);
                    eliminarDescuento(descuentos, &numDescuentos, id);
                    break;
                case 3:
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

    fflush(stdin);

    printf("Ingrese el ID del descuento (máximo 10 caracteres): ");
    fgets(nuevoDescuento.id_cod, MAX_ID, stdin);
    nuevoDescuento.id_cod[strcspn(nuevoDescuento.id_cod, "\n")] = '\0';
    while(getchar() != '\n');

    printf("\n%s\n", nuevoDescuento.id_cod);

    fflush(stdin);

    printf("Ingrese la descripción del descuento (máximo 50 caracteres): ");
    fgets(nuevoDescuento.Descrip, MAX_DESCRIP, stdin);
    nuevoDescuento.Descrip[strcspn(nuevoDescuento.Descrip, "\n")] = '\0';

    fflush(stdin);

    printf("Ingrese el tipo de descuento (codpro o cheqreg): ");
    fgets(nuevoDescuento.Tipo, MAX_TIPO, stdin);
    nuevoDescuento.Tipo[strcspn(nuevoDescuento.Tipo, "\n")] = '\0';

    fflush(stdin);

    printf("Ingrese el estado del descuento (activo o inactivo): ");
    fgets(nuevoDescuento.Estado, MAX_ESTADO, stdin);
    nuevoDescuento.Estado[strcspn(nuevoDescuento.Estado, "\n")] = '\0';

    fflush(stdin);

    printf("Ingrese el importe del descuento en euros: ");
    while(scanf("%f", &nuevoDescuento.Importe) != 1 || nuevoDescuento.Importe < 0){
        fflush(stdin);
        perror("Entrada no valida, intentelo de nuevo.");
    }
    while(getchar() != '\n');
    fflush(stdin);

    printf("Ingrese la aplicabilidad del descuento (todos o esizon): ");
    fgets(nuevoDescuento.Aplicabilidad, MAX_APLICA, stdin);
    nuevoDescuento.Aplicabilidad[strcspn(nuevoDescuento.Aplicabilidad, "\n")] = '\0';

    fflush(stdin);

    descuentos = (Descuentos*)realloc(descuentos, (*numDescuentos)+1 * sizeof(Descuentos));

    descuentos[*numDescuentos] = nuevoDescuento;

    (*numDescuentos)++;

    printf("Descuento agregado correctamente.\n");
}

static void mostrarDescuentos(Descuentos *descuentos, int numDescuentos) {
    printf("Descuentos disponibles:\n\n");
    for(int i = 0; i < numDescuentos; i++) {
        printf("ID: %s, Descripción: %s, Tipo: %s, Estado: %s, Importe: %.2f, Aplicable: %s\n\n",
               descuentos[i].id_cod, descuentos[i].Descrip, descuentos[i].Tipo, descuentos[i].Estado,
               descuentos[i].Importe, descuentos[i].Aplicabilidad);
    }
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

static void eliminarDescuento(Descuentos *descuentos, int *numDescuentos, char *id) {
    id[strcspn(id, "\n")] = '\0';
    int indice = -1;

    for (int i = 0; i < *numDescuentos; i++) {
        if (strcmp(descuentos[i].id_cod, id) == 0) {
            indice = i; // Almacenamos el índice del descuento con el ID dado
            break; 
        }
    }

    if (indice == -1) {
        printf("No se encontró ningún descuento con el ID %s.\n", id);
        menuDescuentos();
    } else {
        // Movemos los descuentos siguientes una posición hacia atrás para "eliminar" el descuento con el ID dado
        for (int i = indice; i < (*numDescuentos - 1); i++) {
            descuentos[i] = descuentos[i + 1];
        }
        (*numDescuentos)--; // Decrementamos el contador de descuentos
        printf("Descuento con ID %s eliminado correctamente.\n", id);
    }
}


int main(){
    menuDescuentos();
    return 0;
}